#include "Engine.h"

void Class_Engine::Start()
{
	Window_Main = std::make_shared<sf::RenderWindow>();
	Window_Main->create({ 637, 477 }, "WSE2 Launcher", sf::Style::None);
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
		HRGN hRegion = CreateRectRgn(0, 0, image.getSize().x, image.getSize().y);

		for (unsigned int y = 0; y < image.getSize().y; y++)
		{
			for (unsigned int x = 0; x < image.getSize().x; x++)
			{
				if (pixelData[y * image.getSize().x * 4 + x * 4 + 3] == 0)
				{
					HRGN hRegionPixel = CreateRectRgn(x, y, x + 1, y + 1);
					CombineRgn(hRegion, hRegion, hRegionPixel, RGN_XOR);
					DeleteObject(hRegionPixel);
				}
			}
		}

		SetWindowRgn(hWnd, hRegion, true);
		DeleteObject(hRegion);
	}
	catch (const std::exception&)
	{
		// �� �� ���������� � �� ����������, ���� � ���
	}
}