#include <windows.h>


//----------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID CALLBACK MyTimer(HWND, UINT, UINT, DWORD);
HWND CreateMainWindow(HINSTANCE hInstance);

PAINTSTRUCT ps;
tagPOINT Mouse;
HWND hWnd = 0;
MSG msg;
HDC hDC;

int Zufall;


//----------------------------------------------------------------------------------------------------------------------

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
  rand();

  SetTimer(NULL, NULL, 10, MyTimer);

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}


//----------------------------------------------------------------------------------------------------------------------

HWND CreateMainWindow (HINSTANCE hInstance) {
  WNDCLASSEX wndClass;

  wndClass.cbSize = sizeof(WNDCLASSEX);
  wndClass.style  = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

  wndClass.lpfnWndProc   = MessageHandler;
  wndClass.cbClsExtra    = 0;
  wndClass.cbWndExtra    = 0;
  wndClass.hInstance     = hInstance;
  wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wndClass.lpszMenuName  = NULL;
  wndClass.lpszClassName = "WindowClass";
  wndClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
  wndClass.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);

  RegisterClassEx(&wndClass);

  return CreateWindowEx(
    NULL,
    "WindowClass",
    "",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100,
    100,
    300,
    300,
    NULL,
    NULL,
    hInstance,
    NULL
  );
}


//----------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK MessageHandler (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_DESTROY:
      PostQuitMessage(0);
    break;
  }

  return (DefWindowProc(hWnd, msg, wParam, lParam));
}


//----------------------------------------------------------------------------------------------------------------------

void CALLBACK MyTimer (HWND hWnd, UINT msg, UINT idEvent, DWORD dwTime) {
  GetCursorPos(&Mouse);

  for (int i = 0; i < 8; i++) {
    Zufall = rand() % 8;
  }

  switch (Zufall) {
    case 1: //++
      Mouse.x -= 1;
      Mouse.y -= 1;
    break;
    case 2: //--
      Mouse.x += 1;
      Mouse.y += 1;
    break;
    case 3: //+-
      Mouse.x += 1;
      Mouse.y -= 1;
    break;
      case 4: //-+
      Mouse.x -= 1;
      Mouse.y += 1;
    break;
      case 5: //-x
      Mouse.x -= 1;
    break;
      case 6: //-y
      Mouse.y -= 1;
    break;
      case 7: //+x
      Mouse.x += 1;
    break;
      case 8: //+y
      Mouse.y += 1;
    break;
    default:
    break;
  }

  SetCursorPos(Mouse.x, Mouse.y);
}

