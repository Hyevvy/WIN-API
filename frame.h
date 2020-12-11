#pragma once
#include "Windows.h"
#include <string>
#include "Misc.h"
#include <list>

using namespace std;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
class Graphics;
class Figure;
class Button;
class Toolbar;
class Rbutton;
class RadioGroup;
class Frame {
private:
	// Window 프로그래밍을 위한 기본 변수들이다. 건드리지 않는다. 
	//-> 라이브러리로 가야함 (응용프로그램만드는 사람들이 몰라도 괜찮음)
	HINSTANCE hInst_;
	HWND hWnd_;
	HDC hDC_;
	bool ready_ = false;
	
public:
	Frame();
	Frame(std::wstring, int, int);
	~Frame();
	virtual void run();
	virtual bool eventHandler(MyEvent e);
	virtual void repaint();
	virtual void grouping() = 0;
	Graphics* getGraphics();
	virtual void initialize();
	void invalidate();
	Toolbar* findIncludedToolbar(int x, int y);
	RadioGroup* findIncludedRadioGroup(int x, int y);
	void addToolbar(Toolbar* added);
	void addRgroup(RadioGroup* added);
	void setThick(int thick);
	void setFigure(int figtype);
	void setPushedGrouping(bool);
	
protected:
	bool ispushedGrouping;
	int figtype_;
	int thick_;
	Rbutton* checkedRgb;
	MyPoint start;
	MyPoint end;
	Graphics* graphics;//라이브러리
	
	list<Toolbar*> myToolbarList;
	list<RadioGroup*> myRadioGroupList;
};