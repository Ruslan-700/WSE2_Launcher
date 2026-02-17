#include "Engine.h"

void Class_Engine::DetectDPIScale()
{
	SetProcessDPIAware();
	HDC hdc = GetDC(NULL);
	int dpi = GetDeviceCaps(hdc, LOGPIXELSX);
	ReleaseDC(NULL, hdc);
	ScaleFactor = dpi / 96.0f;
	if (ScaleFactor < 1.0f) ScaleFactor = 1.0f;
}

void Class_Engine::Start()
{
	DetectDPIScale();
	Window_Main = std::make_shared<sf::RenderWindow>();
	Window_Main->create({ (unsigned int)(637 * ScaleFactor), (unsigned int)(477 * ScaleFactor) }, "WSE2 Launcher", sf::Style::None);
	Window_Main->setFramerateLimit(50);
	SetWindowTransparency();
	Initialize();
	Runtime();
}

void Class_Engine::SetWindowTransparency()
{
	try
	{
		sf::Image Icon;
		Icon.loadFromMemory(Image_Icon, Image_Icon_Length);
		Window_Main->setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
		sf::Image image;
		image.loadFromMemory(Image_MainBackground, Image_MainBackground_Length);
		HWND hWnd = Window_Main->getSystemHandle();

		const sf::Uint8* pixelData = image.getPixelsPtr();
		HRGN hRegion = CreateRectRgn(0, 0, (int)(image.getSize().x * ScaleFactor), (int)(image.getSize().y * ScaleFactor));

		for (unsigned int y = 0; y < image.getSize().y; y++)
		{
			for (unsigned int x = 0; x < image.getSize().x; x++)
			{
				if (pixelData[y * image.getSize().x * 4 + x * 4 + 3] == 0)
				{
					HRGN hRegionPixel = CreateRectRgn(
						(int)(x * ScaleFactor), (int)(y * ScaleFactor),
						(int)((x + 1) * ScaleFactor), (int)((y + 1) * ScaleFactor));
					CombineRgn(hRegion, hRegion, hRegionPixel, RGN_XOR);
					DeleteObject(hRegionPixel);
				}
			}
		}

		SetWindowRgn(hWnd, hRegion, true);
	}
	catch (const std::exception&)
	{
		// �� �� ���������� � �� ����������, ���� � ���
	}
}