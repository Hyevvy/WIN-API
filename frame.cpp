#include "frame.h"
#include "Misc.h"
#include "figure.h"
#include "graphics.h"
#include "button.h"
#include "Toolbar.h"
#include "RadioGroup.h"
#include "Rbutton.h"
// 일단은 전역 변수 1개는 사용한다.
extern Frame* mainWindow;
// 전역함수로는 윈도 메시지 처리 함수가 있다.
LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam)
{ // wparam 키보드, lparam 마우스

	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_SIZE:
		if(mainWindow != nullptr)
			mainWindow->eventHandler(MyEvent(Msg, wParam, lParam));
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Hw, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		if (ps.fErase) {
			OutputDebugString(L"배경을 그려야함\n");  // 이 줄은 테스트용이니 나중에 없앤다.
		}
		// MainWindow  객체의 repaint 를 호출한다.
		
		//Rectangle(hdc, 100, 100, 200, 300);   // 이것도 테스트용이니 없앤다.
		if (mainWindow != nullptr)
			mainWindow->repaint();
		EndPaint(Hw, &ps);

	}
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
}

Frame::Frame() {

}

Frame::Frame(std::wstring title, int width, int height) {
	hInst_ = GetModuleHandle(NULL);
	FreeConsole(); // No console
	// Register win class
	WNDCLASSEX Wc;

	Wc.cbSize = sizeof(WNDCLASSEX);
	Wc.style = CS_HREDRAW | CS_VREDRAW;
	Wc.lpfnWndProc = WndProc;
	Wc.cbClsExtra = 0;
	Wc.cbWndExtra = 0;
	Wc.hInstance = hInst_;
	Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wc.lpszMenuName = NULL;
	Wc.lpszClassName = L"MyWin";
	Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wc);

	hWnd_ = CreateWindowExW(WS_EX_TOPMOST, L"MyWIn", (WCHAR*)title.c_str(),
		WS_OVERLAPPED |
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // 종료 최소화 최대화 아이콘
		WS_THICKFRAME,  // resize가 가능하게
		0, 0, width, height, // x, y, width, height
		NULL, NULL, hInst_, NULL);  // Parent, Menu, instance handle, lpParam
	if (!hWnd_) throw 0;

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_); 
	SetFocus(hWnd_);
	hDC_ = GetDC(hWnd_);
	ready_ = true;

	graphics = new Graphics(hDC_);
	checkedRgb = nullptr;
}
Frame::~Frame() {
	delete graphics;
}
void Frame::initialize() {
}


void Frame::run() {
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));
	initialize();
	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

bool Frame::eventHandler(MyEvent e)
{
	// TODO: 여기에 구현 코드 추가.
	//OutputDebugString(L"Event\n");
	// 이벤트의 종류를 파악해서 사각형 그리기를 여기서 해준다.
	//버튼이 눌렸는지 먼저 확인하고 좌표를 얻는다.
	
	if (e.isLButtonDown()) {
		start.x = e.getX();
		start.y = e.getY();
	}
	else if (e.isLButtonUp()) {
		end.x = e.getX();
		end.y = e.getY();
		Toolbar* tempTb = nullptr;//어떤 툴바가 눌렸는지 확인
		RadioGroup* tempRgb = nullptr;//어떤 라디오 그룹이 눌렸는지
		if ((tempTb = findIncludedToolbar(start.x, start.y)) == findIncludedToolbar(end.x, end.y) && tempTb) {
			//체크된 툴바가 있다면 툴바에게 좌표를 넘겨준다.
			tempTb->menuhandler(end.x, end.y);
			return true; // 버튼 눌림
		}
		if ((tempRgb = findIncludedRadioGroup(start.x, start.y)) == findIncludedRadioGroup(end.x, end.y) && tempRgb)
		{ 
			//체크된 라디오그룹이 있다면 라디오그룹에게 좌표를 넘겨준다.
			tempRgb->Rgbhandler(end.x, end.y);
			return true; //라디오 그룹이 눌렸다. 
		}
		

	}
	return false;
}
void Frame::setPushedGrouping(bool flag) {
	ispushedGrouping = flag;
}

void Frame::repaint() {
	// 모든 사각형을 그린다.
	//툴바의 리페인트, 라디오 그룹의 draw호출
	for (list<Toolbar*>::iterator i = myToolbarList.begin(); i != myToolbarList.end(); i++) {
		(*i)->draw();
	}
	for (list<RadioGroup*>::iterator i = myRadioGroupList.begin(); i != myRadioGroupList.end(); i++) {
		(*i)->draw();
	}
	OutputDebugString(L"REPAINT called\n");
	//Rectangle(hDC_, 100, 100, 200, 300);
	//Rectangle(hDC_, 200, 200, 300, 400);
}

Graphics* Frame::getGraphics() {
	return graphics;
}
void Frame::invalidate() {
	InvalidateRect(hWnd_, nullptr, true);
}
void Frame::addToolbar(Toolbar* added) {
	myToolbarList.push_back(added);
	added->setHDC(hDC_);
	added->setParent(this);
}
void Frame::addRgroup(RadioGroup* added) {
	myRadioGroupList.push_back(added);
	added->setHDC(hDC_);
	added->setParent(this);
}
void Frame::setThick(int thick) {
	thick_ = thick;
}
void Frame::setFigure(int figtype) {
	figtype_ = figtype;
}

Toolbar* Frame::findIncludedToolbar(int x, int y) {
	for (auto i = myToolbarList.rbegin(); i != myToolbarList.rend(); i++) {
		if ((*i)->isIncluded(x, y)) {
			return *i;
		}
	}
	return nullptr;
}

RadioGroup* Frame::findIncludedRadioGroup(int x, int y) {
	//OutputDebugStringW(L"어떤 라디오그룹이 눌려졌는지 확인했음\n");
	for (auto i = myRadioGroupList.rbegin(); i != myRadioGroupList.rend(); i++) {
		if ((*i)->isIncluded(x, y)) {
			return *i;
		}
	}
	return nullptr;
}