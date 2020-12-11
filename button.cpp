#include "button.h"
#include "graphics.h"
#include "frame.h"
Button::Button(){
//����ֽ��ϴ�.
}
Button::Button(string a){
	typestr = a; //�����ڿ��� ���� ��Ʈ���� ��ư�� Ÿ��
}

void Button::draw() {
	//OutputDebugStringW(L"��ư�� ��ο� ����");
//��ư���� ȭ�鿡 ���̰� ���ִ� �Լ�
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
