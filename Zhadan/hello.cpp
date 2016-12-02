#include <Windows.h>
	struct tagWNDCLASSEX{
      UINT cbSize; // �������� ��������� (� ������)
      UINT style; // ����� ������ ������
      WNDPROC WndProc; // ��������� �� ��� ���������������� �������
      int cbWndExtra; // ����� ������������� ������ � ����� ���������
      int cbClsExtra; // ����� ������������� ������ ��� �������� ���������� ����������
      HICON hIcon; // ���������� ������
      HICON hIconMini; // .... ���������� ������ (� ����)
      HCURSOR hCursor; // .... ������� ����
      HBRUSH hbrBack; // .... ����� ���� ������
      HINSTANCE hInst; // .... ���������� ����������
      LPCTSTR lpszClassName; // ��������� �� const-������, ���������� ��� ������
      LPCTSTR lpszMenuName; // ��������� �� const-������, ���������� ��� ����, ������������ ��� ������
	};

	HWND CreateWindow(
                  LP�TSTR lpClassName, // ��� ������ ������
                  LPCTSTR lpWindowName, // �������� ������ (������� ������)
                  DWORD dwStyle, // ����� ������
                  int x, // ������� ������ �� ��� �
                  int y,  // ������� ���� �� ��� � (������ ����)
                  int nWidth, // ������ ������
                  int nHeight, // ������ ������
                  HWND hWndParent, // ������������� ������������� ������
                  HMENU hMenu, // .....����
                  HINSTANCE hInst, // ���������� ���-�� ����-���
                  LPVOID lParam
                  ); // ��������� �� ������, ������������ �� ���������������� �������

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdline,int nCommandShow)
{
	MessageBox(NULL, L"Hello World", L"Window",MB_OK);
	HWND hMainWnd;
	

	WNDCLASSEX w;
	WNDPROC WndProc;
	w.cbSize = sizeof(w);
	w.lpfnWndProc = WndProc;
	

	RegisterClassEx;
	
	if(!RegisterClassEx(&w)){
     // � ������ ���������� ����������� ������:
     MessageBox(NULL,
                L"�� ���������� ���������������� �����!",
                L"������", MB_OK);
     return NULL; // ����������, �������������, ������� �� WinMain
	}


	hMainWnd = CreateWindow(w, // ��� ������
                 L"����������� ������� ���������", // ��� ���� (�� ��� ������)
                 WS_OVERLAPPEDWINDOW | WS_VSCROLL, // ������ ����������� ������
                 CW_USEDEFAULT, // ��������� ���� �� ��� � (�� ���������)
                 NULL, // ������� ���� �� ��� � (��� ������ � �, �� ������ �� �����)
                 CW_USEDEFAULT, // ������ ������ (�� ���������)
                 NULL, // ������ ���� (��� ������ � ������, �� ������ �� �����)
                 HWND(NULL), // ���������� ������������� ������ (� ��� ��� ���. ����)
                 NULL, // ���������� ���� (� ��� ��� ���)
				 HINSTANCE(hInst), // .... ���������� ����������
                 NULL); // ������ �� ������� �� WndProc

	
	if(!hMainWnd){
    // � ������ ������������� �������� ���� (�������� ��������� � ��):
    MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
    return NULL; // ������� �� ����������
	}

	ShowWindow(hMainWnd,nCommandShow);
	UpdateWindow(hMainWnd);
	return NULL;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdline,int nCmdShow)
{
	
	
	return NULL;
}