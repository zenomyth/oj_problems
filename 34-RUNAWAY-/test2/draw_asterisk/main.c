#include <windows.h>
#include <math.h>
#include <stdio.h>

struct point_f {
	float x;
	float y;
};

int cxClient, cyClient;

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

void convert_point_to_pixel(struct point_f *p_f, POINT *p)
{
	int midx = cxClient / 2;
	int midy = cyClient / 2;
	float unit = (float)(cxClient > cyClient ? cyClient : cxClient) / 30;
	p->x = midx + p_f->x * unit;
	p->y = midy - p_f->y * unit;
}

void draw_point(HDC hdc, struct point_f *p_f)
{
	HBRUSH hbrush;
	HBRUSH hbrushOld;
	POINT p;

	hbrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	hbrushOld = SelectObject(hdc, hbrush);
	convert_point_to_pixel(p_f, &p);
	Ellipse(hdc, p.x - 2, p.y - 2, p.x + 2, p.y + 2);
	SelectObject(hdc, hbrushOld);
}

void draw_line(HDC hdc, struct point_f *pf1, struct point_f *pf2)
{
	POINT p;
	convert_point_to_pixel(pf1, &p);
	MoveToEx(hdc, p.x, p.y, NULL);
	convert_point_to_pixel(pf2, &p);
	LineTo(hdc, p.x, p.y);
}

void draw_plots(HDC hdc)
{
	struct point_f p1 = {-2, 3};
	struct point_f p2 = {3, 1};
	float k;

	draw_point(hdc, &p1);
	draw_point(hdc, &p2);

	draw_line(hdc, &p1, &p2);
	// MoveToEx(hdc, midx + p1.x * unit, midy - p1.y * unit, NULL);
	// LineTo(hdc, midx + p2.x * unit, midy - p2.y * unit);

	k = -(p2.x - p1.x) / (p2.y - p1.y);
	printf("k=%f\n", k);

	/*for(i = 0; i < NUM; i++)
	{
	   apt[i].x = i * cxClient / NUM;
	   apt[i].y =(int)(cyClient / 2 *(1 - sin(TWOPI * i / NUM)));
	}

	Polyline(hdc, apt, NUM);*/
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	int         i;
	PAINTSTRUCT ps;
	//POINT       apt [NUM];

	switch (message) {
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		draw_plots(hdc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
