#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("* operation test");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(NULL, IDI_SHIELD);
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("Program requires Windows NT!"),
					szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Test * operation on bisectors"),
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT,
							NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  cxClient, cyClient;
	HDC         hdc;
	int         i;
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	HBRUSH hbrushOld;
	//POINT       apt [NUM];

	switch (message) {
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		MoveToEx(hdc, 0,        cyClient / 2, NULL);
		LineTo  (hdc, cxClient, cyClient / 2);

		// SetPixel(hdc, cxClient / 4, cyClient / 4, RGB(0, 0, 255));
		hbrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
		hbrushOld = SelectObject(hdc, hbrush);
		Ellipse(hdc, cxClient / 4 - 3, cyClient / 4 - 3, cxClient / 4 + 3, cyClient / 4 + 3);
		SelectObject(hdc, hbrushOld);

		/*for(i = 0; i < NUM; i++)
		{
		   apt[i].x = i * cxClient / NUM;
		   apt[i].y =(int)(cyClient / 2 *(1 - sin(TWOPI * i / NUM)));
		}

		Polyline(hdc, apt, NUM);*/
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
