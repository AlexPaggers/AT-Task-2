#include <windows.h>

LPCTSTR WndClassName = L"firstwindow";  
HWND hwnd = NULL; 

const int Width = 800; 
const int Height = 600;

bool InitializeWindow(HINSTANCE hInstance,  
	int ShowWnd,
	int width, int height,
	bool windowed);

int messageloop();  

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	messageloop();    

	return 0;
}

bool InitializeWindow(HINSTANCE hInstance, 
	int ShowWnd,
	int width, int height,
	bool windowed)
{

	WNDCLASSEX wc; 

	wc.cbSize = sizeof(WNDCLASSEX);    
	wc.style = CS_HREDRAW | CS_VREDRAW;    
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;    
	wc.cbWndExtra = NULL;    
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);    
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2); 
	wc.lpszMenuName = NULL;   
	wc.lpszClassName = WndClassName;    
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&wc))   
	{
		
		MessageBox(NULL, L"Error registering class",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	hwnd = CreateWindowEx(
		NULL,  
		WndClassName, 
		L"Hey guys, MASSIVE LEGEND here", 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT,    
		width,  
		height, 
		NULL,   
		NULL,   
		hInstance,   
		NULL  
		);

	if (!hwnd)  
	{
		MessageBox(NULL, L"Error creating window",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	ShowWindow(hwnd, ShowWnd);   
	UpdateWindow(hwnd);  

	return true;   
}

int messageloop() {   

	MSG msg;    
	ZeroMemory(&msg, sizeof(MSG));   

	while (true)   
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;  

			TranslateMessage(&msg);    
									   
			DispatchMessage(&msg);
		}

		else 
		{   

		}
	}

	return (int)msg.wParam;    

}

LRESULT CALLBACK WndProc(HWND hwnd,  
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{

	case WM_KEYDOWN: 
					
		if (wParam == VK_ESCAPE) {
			if (MessageBox(0, L"Are you sure you want to exit?",
				L"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)

				
				DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:  
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}