#include "frame.h"
#include "Misc.h"
#include "figure.h"
#include "graphics.h"
#include "button.h"
#include "Toolbar.h"
#include "RadioGroup.h"
#include "Rbutton.h"
// �ϴ��� ���� ���� 1���� ����Ѵ�.
extern Frame* mainWindow;
// �����Լ��δ� ���� �޽��� ó�� �Լ��� �ִ�.
LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam)
{ // wparam Ű����, lparam ���콺

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
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		if (ps.fErase) {
			OutputDebugString(L"����� �׷�����\n");  // �� ���� �׽�Ʈ���̴� ���߿� ���ش�.
		}
		// MainWindow  ��ü�� repaint �� ȣ���Ѵ�.
		
		//Rectangle(hdc, 100, 100, 200, 300);   // �̰͵� �׽�Ʈ���̴� ���ش�.
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
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // ���� �ּ�ȭ �ִ�ȭ ������
		WS_THICKFRAME,  // resize�� �����ϰ�
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

	// �⺻ �޽��� �����Դϴ�:
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
	// TODO: ���⿡ ���� �ڵ� �߰�.
	//OutputDebugString(L"Event\n");
	// �̺�Ʈ�� ������ �ľ��ؼ� �簢�� �׸��⸦ ���⼭ ���ش�.
	//��ư�� ���ȴ��� ���� Ȯ���ϰ� ��ǥ�� ��´�.
	
	if (e.isLButtonDown()) {
		start.x = e.getX();
		start.y = e.getY();
	}
	else if (e.isLButtonUp()) {
		end.x = e.getX();
		end.y = e.getY();
		Toolbar* tempTb = nullptr;//� ���ٰ� ���ȴ��� Ȯ��
		RadioGroup* tempRgb = nullptr;//� ���� �׷��� ���ȴ���
		if ((tempTb = findIncludedToolbar(start.x, start.y)) == findIncludedToolbar(end.x, end.y) && tempTb) {
			//üũ�� ���ٰ� �ִٸ� ���ٿ��� ��ǥ�� �Ѱ��ش�.
			tempTb->menuhandler(end.x, end.y);
			return true; // ��ư ����
		}
		if ((tempRgb = findIncludedRadioGroup(start.x, start.y)) == findIncludedRadioGroup(end.x, end.y) && tempRgb)
		{ 
			//üũ�� �����׷��� �ִٸ� �����׷쿡�� ��ǥ�� �Ѱ��ش�.
			tempRgb->Rgbhandler(end.x, end.y);
			return true; //���� �׷��� ���ȴ�. 
		}
		

	}
	return false;
}
void Frame::setPushedGrouping(bool flag) {
	ispushedGrouping = flag;
}

void Frame::repaint() {
	// ��� �簢���� �׸���.
	//������ ������Ʈ, ���� �׷��� drawȣ��
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
	//OutputDebugStringW(L"� �����׷��� ���������� Ȯ������\n");
	for (auto i = myRadioGroupList.rbegin(); i != myRadioGroupList.rend(); i++) {
		if ((*i)->isIncluded(x, y)) {
			return *i;
		}
	}
	return nullptr;
}