#include "button.h"
#include "graphics.h"
#include "frame.h"
Button::Button(){
//비어있습니다.
}
Button::Button(string a){
	typestr = a; //생성자에서 받은 스트링이 버튼의 타입
}

void Button::draw() {
	//OutputDebugStringW(L"버튼의 드로우 실행");
//버튼들이 화면에 보이게 해주는 함수
	Graphics* g = (this->parent_)->getGraphics();
	g->setColor(Graphics::PEN_BLACK);
	g->setFill(Graphics::BRUSH_WHITE);
	Rectangle(hDC_, x_, y_, x_ + width_, y_ + height_);
	Rectangle(hDC_, x_, y_, x_ + width_, y_ + height_);
	TextOutA(hDC_, x_+10, y_+5, typestr.c_str(), strlen(typestr.c_str()));
}

bool Button::isIncluded(int x, int y) {
	if ((x_ < x && x < width_+x_) && (y_ < y && y < height_+y_)) return true;
	else return false;
}
//void Button::setisRgbDown(bool flag) {
	//isRgbDown = flag;
//}
