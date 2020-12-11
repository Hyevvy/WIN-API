#include "Component.h"
#include "frame.h"
Component::Component() {
	
}
Component::Component(int x, int y, int width, int height) :x_(x), y_(y),width_(width),height_(height) {
}
void Component::setHDC(HDC& hDC) {
	hDC_ = hDC;
}
Frame* Component::getParent() {
	return parent_;
}
bool Component::getIsRgbdown() {
	return isRgbDown;
}
void Component::IsRgbdown(bool flag) {
	OutputDebugStringW(L"�˹�ư�� ������ �˹�ư �ٿ�ȴ�\n");
	isRgbDown = flag;
	parent_->repaint();
	parent_->invalidate();
}

void Component::setParent(Frame* parent_) {
	this->parent_ = parent_;
}
void Component::setBounds(int x, int y, int width, int height) {
	OutputDebugStringW(L"���۳�Ʈ �¹ٿ�� �۵�\n");
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	//x,y��ġ, ��, ����
}

std::string Component::getTypestr() {
	return typestr;
}