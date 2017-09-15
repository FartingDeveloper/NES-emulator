#include <Windows.h>
#include <ctime>
#include <fstream>

#include "NES.h"

#define ID_FILE_OPEN 100

const int width = 256;
const int height = 240;

NES * console;
bool loaded = false;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void openFile(HWND hWnd, unsigned char *&bytes, int &size);
void drawGraphics(HDC hdc, COLORREF * pixels, int w, int h);

int WINAPI WinMain(HINSTANCE hInstance, // identifier of program
	HINSTANCE hPrevInstance, //identifier of last copie of the same program
	LPSTR lpCmdLine, //cmd argument
	int nCmdShow) //how window looks when it has been created
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX); //structure size
	wc.style = CS_HREDRAW | CS_VREDRAW; //window style
	wc.lpfnWndProc = WindowProc; //event handler
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //cursor style
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //background style
	wc.lpszClassName = L"WindowClass"; //name of the class

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, width, height };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

	hWnd = CreateWindowEx(NULL, //style stuff
		L"WindowClass", //name of the class
		L"CHIP-8", //tytle
		WS_OVERLAPPEDWINDOW, //options of window
		300, //coord x
		300, //coord y
		wr.right - wr.left, //width
		wr.bottom - wr.top, //height
		NULL, //window parent
		NULL, //menu bar handler
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;

	console = new NES();

	COLORREF * screen = console->getScreenBuffer();
	int screenWidth = console->getScreenWidth();
	int screenHeight = console->getScreenHeight();

	time_t currentTime = time(0);
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); //change format of msg
			DispatchMessage(&msg); //send to window proc
			if (msg.message == WM_QUIT) break;
		}
		else {
			if (loaded) {
				time_t now = time(0);

				if (now - currentTime > 0.016) 	console->run();

				if (console->getDrawFlag()) {
					drawGraphics(GetDC(hWnd), screen, screenWidth, screenHeight);
					currentTime = now;
				}
			}
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: {
		HMENU hMenu, hSubMenu;

		hMenu = CreateMenu();
		hSubMenu = CreatePopupMenu();

		AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, _T("Open"));
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, _T("File"));

		SetMenu(hWnd, hMenu);

		break;
	} //MenuBar
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN: {
			unsigned char *bytes = NULL;
			int size;

			openFile(hWnd, bytes, size);

			loaded = console->loadROM(bytes, size);

			delete[] bytes;
			break;
		}
		}
		break;
	} //MenuBar handler
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN: {
		switch (wParam)
		{
		case '1': {
			console->pressKey(false, 0);
			break;
		}
		case '2': {
			console->pressKey(false, 1);
			break;
		}
		case '3': {
			console->pressKey(false, 2);
			break;
		}
		case '4': {
			console->pressKey(false, 3);
			break;
		}
		case 'Q': {
			console->pressKey(false, 4);
			break;
		}
		case 'W': {
			console->pressKey(false, 5);
			break;
		}
		case 'E': {
			console->pressKey(false, 6);
			break;
		}
		case 'R': {
			console->pressKey(false, 7);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_KEYUP: {
		switch (wParam)
		{
		case '1': {
			console->releaseKey(false, 0);
			break;
		}
		case '2': {
			console->releaseKey(false, 1);
			break;
		}
		case '3': {
			console->releaseKey(false, 2);
			break;
		}
		case '4': {
			console->releaseKey(false, 3);
			break;
		}
		case 'Q': {
			console->releaseKey(false, 4);
			break;
		}
		case 'W': {
			console->releaseKey(false, 5);
			break;
		}
		case 'E': {
			console->releaseKey(false, 6);
			break;
		}
		case 'R': {
			console->releaseKey(false, 7);
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void openFile(HWND hWnd, unsigned char *&bytes, int &size) 
{
	OPENFILENAME ofn;

	wchar_t fileName[MAX_PATH];
	fileName[0] = '\0'; //used to be init

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT;

	if (GetOpenFileName(&ofn))
	{
		size_t i;
		char tmp[MAX_PATH];
		wcstombs_s(&i, tmp, MAX_PATH, fileName, MAX_PATH);
		const char *name = tmp;

		FILE * file;
		fopen_s(&file, name, "rb");
		if (file == NULL) return;
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fclose(file);

		fopen_s(&file, name, "rb");
		bytes = new unsigned char[size];
		int bytes_read = fread(bytes, sizeof(unsigned char), size, file);
		fclose(file);
	}
}

void drawGraphics(HDC hdc, COLORREF * pixels, int w, int h)
{
	// Creating temp bitmap
	HBITMAP map = CreateBitmap(width, // width. 
		height, // height
		1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
		8*4, // Size of memory for one pixel in bits(in win32 4 bytes = 4*8 bits)
		(void*)pixels); // pointer to array
					 // Temp HDC to copy picture
	HDC src = CreateCompatibleDC(hdc); // hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
	SelectObject(src, map); // Inserting picture into our temp HDC
							// Copy image from temp HDC to window
	BitBlt(hdc, // Destination
		0,  // x and
		0,  // y - upper-left corner of place, where we'd like to copy
		width, // width of the region
		height, // height
		src, // source
		0,   // x and
		0,   // y of upper left corner  of part of the source, from where we'd like to copy
		SRCCOPY); // way of copy;

	DeleteDC(src); // Deleting temp HDC
}
