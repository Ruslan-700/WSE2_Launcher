#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <cstdint>

// Reader for stored/deflated zip archives, with its own inflate implementation so
// that no compression library has to be linked into any build configuration.
namespace Zip
{
	struct Entry
	{
		std::wstring Path;              // as stored in the archive, '/' separated
		uint64_t CompressedSize = 0;
		uint64_t UncompressedSize = 0;
		uint64_t LocalHeaderOffset = 0;
		uint32_t Crc32 = 0;
		uint16_t Method = 0;
		bool IsDirectory = false;
	};

	class Archive
	{
	public:
		bool Open(const std::wstring& ArchivePath, std::string& OutError);
		const std::vector<Entry>& GetEntries() const { return Entries; }
		bool Extract(const Entry& ArchiveEntry, std::vector<uint8_t>& OutData, std::string& OutError);

	private:
		bool ReadCentralDirectory(std::string& OutError);
		std::ifstream File;
		uint64_t FileSize = 0;
		std::vector<Entry> Entries;
	};
}
