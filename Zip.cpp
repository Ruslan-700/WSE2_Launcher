#include "Zip.h"
#include <windows.h>

namespace
{
	const int MaxCodeBits = 15;

	struct BitStream
	{
		const uint8_t* Data = nullptr;
		size_t Size = 0;
		size_t Position = 0;
		uint32_t BitBuffer = 0;
		int BitCount = 0;
		bool Error = false;
	};

	int ReadBits(BitStream& Stream, int Count)
	{
		uint32_t Value = Stream.BitBuffer;
		while (Stream.BitCount < Count) {
			if (Stream.Position >= Stream.Size) { Stream.Error = true; return 0; }
			Value |= (uint32_t)Stream.Data[Stream.Position++] << Stream.BitCount;
			Stream.BitCount += 8;
		}
		Stream.BitBuffer = Value >> Count;
		Stream.BitCount -= Count;
		return (int)(Value & ((1u << Count) - 1));
	}

	// Canonical Huffman decoding table: how many codes have each length, plus the
	// symbols sorted by code length.
	struct HuffmanTable
	{
		uint16_t Counts[MaxCodeBits + 1] = {};
		std::vector<uint16_t> Symbols;
	};

	bool BuildHuffmanTable(HuffmanTable& Table, const uint16_t* Lengths, int SymbolCount)
	{
		for (int Length = 0; Length <= MaxCodeBits; Length++) Table.Counts[Length] = 0;
		for (int Symbol = 0; Symbol < SymbolCount; Symbol++) {
			if (Lengths[Symbol] > MaxCodeBits) return false;
			Table.Counts[Lengths[Symbol]]++;
		}
		if (Table.Counts[0] == SymbolCount) return true;

		int Left = 1;
		for (int Length = 1; Length <= MaxCodeBits; Length++) {
			Left <<= 1;
			Left -= Table.Counts[Length];
			if (Left < 0) return false;
		}

		uint16_t Offsets[MaxCodeBits + 2] = {};
		for (int Length = 1; Length <= MaxCodeBits; Length++) Offsets[Length + 1] = Offsets[Length] + Table.Counts[Length];
		Table.Symbols.assign(SymbolCount, 0);
		for (int Symbol = 0; Symbol < SymbolCount; Symbol++)
			if (Lengths[Symbol] != 0) Table.Symbols[Offsets[Lengths[Symbol]]++] = (uint16_t)Symbol;
		return true;
	}

	int DecodeSymbol(BitStream& Stream, const HuffmanTable& Table)
	{
		int Code = 0, First = 0, Index = 0;
		for (int Length = 1; Length <= MaxCodeBits; Length++) {
			Code |= ReadBits(Stream, 1);
			if (Stream.Error) return -1;
			int Count = Table.Counts[Length];
			if (Code - Count < First) {
				size_t SymbolIndex = (size_t)Index + (size_t)(Code - First);
				if (SymbolIndex >= Table.Symbols.size()) return -1;
				return Table.Symbols[SymbolIndex];
			}
			Index += Count;
			First = (First + Count) << 1;
			Code <<= 1;
		}
		return -1;
	}

	const uint16_t LengthBase[29] = { 3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258 };
	const uint16_t LengthExtra[29] = { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0 };
	const uint16_t DistanceBase[30] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577 };
	const uint16_t DistanceExtra[30] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13 };

	bool InflateCodes(BitStream& Stream, const HuffmanTable& LengthTable, const HuffmanTable& DistanceTable, std::vector<uint8_t>& Output)
	{
		for (;;) {
			int Symbol = DecodeSymbol(Stream, LengthTable);
			if (Symbol < 0) return false;
			if (Symbol < 256) { Output.push_back((uint8_t)Symbol); continue; }
			if (Symbol == 256) return true;

			Symbol -= 257;
			if (Symbol >= 29) return false;
			int Length = LengthBase[Symbol] + ReadBits(Stream, LengthExtra[Symbol]);

			int DistanceSymbol = DecodeSymbol(Stream, DistanceTable);
			if (DistanceSymbol < 0 || DistanceSymbol >= 30) return false;
			size_t Distance = (size_t)DistanceBase[DistanceSymbol] + (size_t)ReadBits(Stream, DistanceExtra[DistanceSymbol]);
			if (Stream.Error || Distance == 0 || Distance > Output.size()) return false;

			for (int i = 0; i < Length; i++) {
				uint8_t Byte = Output[Output.size() - Distance];
				Output.push_back(Byte);
			}
		}
	}

	bool InflateStored(BitStream& Stream, std::vector<uint8_t>& Output)
	{
		Stream.BitBuffer = 0;
		Stream.BitCount = 0;
		if (Stream.Position + 4 > Stream.Size) return false;
		unsigned Length = Stream.Data[Stream.Position] | ((unsigned)Stream.Data[Stream.Position + 1] << 8);
		unsigned LengthComplement = Stream.Data[Stream.Position + 2] | ((unsigned)Stream.Data[Stream.Position + 3] << 8);
		Stream.Position += 4;
		if (((~Length) & 0xFFFF) != LengthComplement) return false;
		if (Stream.Position + Length > Stream.Size) return false;
		Output.insert(Output.end(), Stream.Data + Stream.Position, Stream.Data + Stream.Position + Length);
		Stream.Position += Length;
		return true;
	}

	bool InflateFixed(BitStream& Stream, std::vector<uint8_t>& Output)
	{
		uint16_t Lengths[288] = {};
		for (int Symbol = 0; Symbol < 144; Symbol++) Lengths[Symbol] = 8;
		for (int Symbol = 144; Symbol < 256; Symbol++) Lengths[Symbol] = 9;
		for (int Symbol = 256; Symbol < 280; Symbol++) Lengths[Symbol] = 7;
		for (int Symbol = 280; Symbol < 288; Symbol++) Lengths[Symbol] = 8;
		HuffmanTable LengthTable, DistanceTable;
		if (!BuildHuffmanTable(LengthTable, Lengths, 288)) return false;
		for (int Symbol = 0; Symbol < 30; Symbol++) Lengths[Symbol] = 5;
		if (!BuildHuffmanTable(DistanceTable, Lengths, 30)) return false;
		return InflateCodes(Stream, LengthTable, DistanceTable, Output);
	}

	bool InflateDynamic(BitStream& Stream, std::vector<uint8_t>& Output)
	{
		static const uint16_t CodeLengthOrder[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };

		int LiteralCount = ReadBits(Stream, 5) + 257;
		int DistanceCount = ReadBits(Stream, 5) + 1;
		int CodeLengthCount = ReadBits(Stream, 4) + 4;
		if (Stream.Error || LiteralCount > 286 || DistanceCount > 30) return false;

		uint16_t Lengths[320] = {};
		for (int i = 0; i < CodeLengthCount; i++) Lengths[CodeLengthOrder[i]] = (uint16_t)ReadBits(Stream, 3);
		if (Stream.Error) return false;

		HuffmanTable CodeLengthTable;
		if (!BuildHuffmanTable(CodeLengthTable, Lengths, 19)) return false;

		int Total = LiteralCount + DistanceCount;
		for (int i = 0; i < 320; i++) Lengths[i] = 0;
		int Index = 0;
		while (Index < Total) {
			int Symbol = DecodeSymbol(Stream, CodeLengthTable);
			if (Symbol < 0) return false;
			if (Symbol < 16) { Lengths[Index++] = (uint16_t)Symbol; continue; }

			uint16_t Repeated = 0;
			int RepeatCount = 0;
			if (Symbol == 16) {
				if (Index == 0) return false;
				Repeated = Lengths[Index - 1];
				RepeatCount = 3 + ReadBits(Stream, 2);
			}
			else if (Symbol == 17) RepeatCount = 3 + ReadBits(Stream, 3);
			else RepeatCount = 11 + ReadBits(Stream, 7);
			if (Stream.Error || Index + RepeatCount > Total) return false;
			while (RepeatCount-- > 0) Lengths[Index++] = Repeated;
		}
		if (Lengths[256] == 0) return false;

		HuffmanTable LengthTable, DistanceTable;
		if (!BuildHuffmanTable(LengthTable, Lengths, LiteralCount)) return false;
		if (!BuildHuffmanTable(DistanceTable, Lengths + LiteralCount, DistanceCount)) return false;
		return InflateCodes(Stream, LengthTable, DistanceTable, Output);
	}

	bool Inflate(const uint8_t* Data, size_t Size, uint64_t ExpectedSize, std::vector<uint8_t>& Output, std::string& OutError)
	{
		BitStream Stream;
		Stream.Data = Data;
		Stream.Size = Size;
		Output.clear();
		if (ExpectedSize > 0 && ExpectedSize < (uint64_t)1024 * 1024 * 1024) Output.reserve((size_t)ExpectedSize);

		int IsLastBlock = 0;
		do {
			IsLastBlock = ReadBits(Stream, 1);
			int BlockType = ReadBits(Stream, 2);
			if (Stream.Error) { OutError = "the compressed data ends too early"; return false; }

			bool Ok = false;
			if (BlockType == 0) Ok = InflateStored(Stream, Output);
			else if (BlockType == 1) Ok = InflateFixed(Stream, Output);
			else if (BlockType == 2) Ok = InflateDynamic(Stream, Output);
			else { OutError = "the compressed data uses a reserved block type"; return false; }
			if (!Ok) { OutError = "the compressed data is damaged"; return false; }
		} while (!IsLastBlock);

		return true;
	}

	uint32_t Crc32(const uint8_t* Data, size_t Size)
	{
		static uint32_t Table[256];
		static bool TableIsReady = false;
		if (!TableIsReady) {
			for (uint32_t i = 0; i < 256; i++) {
				uint32_t Value = i;
				for (int Bit = 0; Bit < 8; Bit++) Value = (Value & 1) ? (0xEDB88320u ^ (Value >> 1)) : (Value >> 1);
				Table[i] = Value;
			}
			TableIsReady = true;
		}
		uint32_t Crc = 0xFFFFFFFFu;
		for (size_t i = 0; i < Size; i++) Crc = Table[(Crc ^ Data[i]) & 0xFF] ^ (Crc >> 8);
		return Crc ^ 0xFFFFFFFFu;
	}

	uint16_t Read16(const uint8_t* Data) { return (uint16_t)(Data[0] | ((uint16_t)Data[1] << 8)); }
	uint32_t Read32(const uint8_t* Data) { return Data[0] | ((uint32_t)Data[1] << 8) | ((uint32_t)Data[2] << 16) | ((uint32_t)Data[3] << 24); }
	uint64_t Read64(const uint8_t* Data) { return (uint64_t)Read32(Data) | ((uint64_t)Read32(Data + 4) << 32); }

	std::wstring DecodeEntryName(const uint8_t* Data, size_t Size, bool IsUtf8)
	{
		if (Size == 0) return L"";
		UINT CodePage = IsUtf8 ? CP_UTF8 : 437;
		int Length = MultiByteToWideChar(CodePage, 0, (LPCCH)Data, (int)Size, NULL, 0);
		if (Length <= 0) return L"";
		std::wstring Result((size_t)Length, L' ');
		MultiByteToWideChar(CodePage, 0, (LPCCH)Data, (int)Size, &Result[0], Length);
		return Result;
	}
}

bool Zip::Archive::Open(const std::wstring& ArchivePath, std::string& OutError)
{
	Entries.clear();
	File.close();
	File.clear();
	File.open(ArchivePath, std::ios::binary);
	if (!File.good()) { OutError = "could not open the downloaded archive"; return false; }

	File.seekg(0, std::ios::end);
	FileSize = (uint64_t)File.tellg();
	if (FileSize < 22) { OutError = "the downloaded archive is truncated"; return false; }

	return ReadCentralDirectory(OutError);
}

bool Zip::Archive::ReadCentralDirectory(std::string& OutError)
{
	// The end of central directory record lives in the last 64 KB of the file.
	const uint64_t TailSize = (FileSize < 66560) ? FileSize : 66560;
	std::vector<uint8_t> Tail((size_t)TailSize);
	File.seekg((std::streamoff)(FileSize - TailSize), std::ios::beg);
	File.read((char*)Tail.data(), (std::streamsize)TailSize);
	if (!File.good()) { OutError = "could not read the archive index"; return false; }

	size_t EndRecord = (size_t)-1;
	for (size_t Offset = Tail.size() - 22 + 1; Offset-- > 0; ) {
		if (Read32(&Tail[Offset]) == 0x06054B50) { EndRecord = Offset; break; }
	}
	if (EndRecord == (size_t)-1) { OutError = "the downloaded file is not a zip archive"; return false; }

	uint64_t EntryCount = Read16(&Tail[EndRecord + 10]);
	uint64_t DirectorySize = Read32(&Tail[EndRecord + 12]);
	uint64_t DirectoryOffset = Read32(&Tail[EndRecord + 16]);

	// Zip64 layout: the real values sit in a separate record found through its locator.
	if (EntryCount == 0xFFFF || DirectorySize == 0xFFFFFFFF || DirectoryOffset == 0xFFFFFFFF) {
		if (EndRecord < 20 || Read32(&Tail[EndRecord - 20]) != 0x07064B50) { OutError = "the archive index is damaged"; return false; }
		uint64_t Zip64Offset = Read64(&Tail[EndRecord - 20 + 8]);
		uint8_t Zip64Record[56] = {};
		File.seekg((std::streamoff)Zip64Offset, std::ios::beg);
		File.read((char*)Zip64Record, sizeof(Zip64Record));
		if (!File.good() || Read32(Zip64Record) != 0x06064B50) { OutError = "the archive index is damaged"; return false; }
		EntryCount = Read64(Zip64Record + 32);
		DirectorySize = Read64(Zip64Record + 40);
		DirectoryOffset = Read64(Zip64Record + 48);
	}

	if (DirectoryOffset + DirectorySize > FileSize || DirectorySize > 64 * 1024 * 1024) { OutError = "the archive index is damaged"; return false; }

	std::vector<uint8_t> Directory((size_t)DirectorySize);
	File.seekg((std::streamoff)DirectoryOffset, std::ios::beg);
	File.read((char*)Directory.data(), (std::streamsize)DirectorySize);
	if (!File.good()) { OutError = "could not read the archive index"; return false; }

	size_t Position = 0;
	for (uint64_t i = 0; i < EntryCount; i++) {
		if (Position + 46 > Directory.size() || Read32(&Directory[Position]) != 0x02014B50) { OutError = "the archive index is damaged"; return false; }

		uint16_t Flags = Read16(&Directory[Position + 8]);
		uint16_t NameLength = Read16(&Directory[Position + 28]);
		uint16_t ExtraLength = Read16(&Directory[Position + 30]);
		uint16_t CommentLength = Read16(&Directory[Position + 32]);
		uint32_t ExternalAttributes = Read32(&Directory[Position + 38]);
		if (Position + 46 + (size_t)NameLength + ExtraLength + CommentLength > Directory.size()) { OutError = "the archive index is damaged"; return false; }

		Entry ArchiveEntry;
		ArchiveEntry.Method = Read16(&Directory[Position + 10]);
		ArchiveEntry.Crc32 = Read32(&Directory[Position + 16]);
		ArchiveEntry.CompressedSize = Read32(&Directory[Position + 20]);
		ArchiveEntry.UncompressedSize = Read32(&Directory[Position + 24]);
		ArchiveEntry.LocalHeaderOffset = Read32(&Directory[Position + 42]);
		ArchiveEntry.Path = DecodeEntryName(&Directory[Position + 46], NameLength, (Flags & 0x800) != 0);
		ArchiveEntry.IsDirectory = (!ArchiveEntry.Path.empty() && ArchiveEntry.Path.back() == L'/') || (ExternalAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		// Oversized values are stored in the zip64 extra field, in this fixed order.
		const uint8_t* Extra = &Directory[Position + 46 + NameLength];
		size_t ExtraLeft = ExtraLength;
		while (ExtraLeft >= 4) {
			uint16_t FieldId = Read16(Extra);
			uint16_t FieldSize = Read16(Extra + 2);
			if ((size_t)FieldSize + 4 > ExtraLeft) break;
			if (FieldId == 0x0001) {
				const uint8_t* Field = Extra + 4;
				size_t FieldLeft = FieldSize;
				if (ArchiveEntry.UncompressedSize == 0xFFFFFFFF && FieldLeft >= 8) { ArchiveEntry.UncompressedSize = Read64(Field); Field += 8; FieldLeft -= 8; }
				if (ArchiveEntry.CompressedSize == 0xFFFFFFFF && FieldLeft >= 8) { ArchiveEntry.CompressedSize = Read64(Field); Field += 8; FieldLeft -= 8; }
				if (ArchiveEntry.LocalHeaderOffset == 0xFFFFFFFF && FieldLeft >= 8) { ArchiveEntry.LocalHeaderOffset = Read64(Field); }
				break;
			}
			Extra += 4 + FieldSize;
			ExtraLeft -= 4 + FieldSize;
		}

		Position += 46 + (size_t)NameLength + ExtraLength + CommentLength;
		if (!ArchiveEntry.Path.empty()) Entries.push_back(ArchiveEntry);
	}

	return true;
}

bool Zip::Archive::Extract(const Entry& ArchiveEntry, std::vector<uint8_t>& OutData, std::string& OutError)
{
	OutData.clear();
	if (ArchiveEntry.Method != 0 && ArchiveEntry.Method != 8) { OutError = "unsupported compression method in the archive"; return false; }
	if (ArchiveEntry.LocalHeaderOffset + 30 > FileSize) { OutError = "the archive is damaged"; return false; }

	uint8_t LocalHeader[30] = {};
	File.seekg((std::streamoff)ArchiveEntry.LocalHeaderOffset, std::ios::beg);
	File.read((char*)LocalHeader, sizeof(LocalHeader));
	if (!File.good() || Read32(LocalHeader) != 0x04034B50) { OutError = "the archive is damaged"; return false; }

	uint64_t DataOffset = ArchiveEntry.LocalHeaderOffset + 30 + Read16(LocalHeader + 26) + Read16(LocalHeader + 28);
	if (DataOffset + ArchiveEntry.CompressedSize > FileSize) { OutError = "the archive is damaged"; return false; }

	std::vector<uint8_t> Compressed((size_t)ArchiveEntry.CompressedSize);
	if (ArchiveEntry.CompressedSize > 0) {
		File.seekg((std::streamoff)DataOffset, std::ios::beg);
		File.read((char*)Compressed.data(), (std::streamsize)ArchiveEntry.CompressedSize);
		if (!File.good()) { OutError = "could not read the archive"; return false; }
	}

	if (ArchiveEntry.Method == 0) OutData.swap(Compressed);
	else if (!Inflate(Compressed.data(), Compressed.size(), ArchiveEntry.UncompressedSize, OutData, OutError)) return false;

	if (OutData.size() != ArchiveEntry.UncompressedSize) { OutError = "unexpected size after unpacking"; return false; }
	if (Crc32(OutData.data(), OutData.size()) != ArchiveEntry.Crc32) { OutError = "checksum mismatch after unpacking"; return false; }
	return true;
}
