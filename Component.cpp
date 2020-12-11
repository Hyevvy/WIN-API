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
	OutputDebugStringW(L"알버튼의 셋이즈 알버튼 다운눌렸다\n");
	isRgbDown = flag;
	parent_->repaint();
	parent_->invalidate();
}

void Component::setParent(Frame* parent_) {
	this->parent_ = parent_;
}
void Component::setBounds(int x, int y, int width, int height) {
	OutputDebugStringW(L"컴퍼넌트 셋바운드 작동\n");
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	//x,y위치, 폭, 높이
}

std::string Component::getTypestr() {
	return typestr;
}