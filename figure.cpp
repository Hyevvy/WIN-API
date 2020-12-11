#include "figure.h"
#include "graphics.h"
#include "frame.h"
#include "Misc.h"
#include "PainterFrame.h"
Figure::Figure() {
//비어있습니다.
}
Figure::Figure(int x1, int y1, int x2, int y2,int thick) :x1(x1), y1(y1), x2(x2), y2(y2),thick(thick) {
}
/*Figure::Figure(Frame* parent_, int x1, int y1, int x2, int y2) :parent_(parent_), x1(x1), y1(y1), x2(x2), y2(y2) {

}*/
void Figure::draw() {
	//myrect 코드 실행됨.
}
void Figure::setParent(PainterFrame* setP) {
	parent_ = setP;
}


void Figure::changePosition(int prev_x, int prev_y, int next_x, int next_y) {
	int h1 = prev_x - x1;
	int w1 = prev_y - y1;
	int h2 = x2 - prev_x;
	int w2 = y2 - prev_y;
	x1 = next_x - h1;
	y1 = next_y - w1;
	x2 = next_x + h2;
	y2 = next_y + w2;
}

int Figure::getX1() {
	return x1;
}
int Figure::getY1() {
	return y1;
}
int Figure::getX2() {
	return x2;
}
int Figure::getY2() {
	return y2;
}

void Figure::setX1(int x1) {
	this->x1 = x1;
}
void Figure::setY1(int y1) {
	this->y1 = y1;
}
void Figure::setX2(int x2) {
	this->x2 = x2;
}
void Figure::setY2(int y2) {
	this->y2 = y2;
}

void Figure::setMyGroup(Figure* myGroup) {
	this->myGroup = myGroup;
}

MyPoint Figure::getBasePosition() {
	// 기준 좌표 구하기
	MyPoint p;
	if (myGroup) { // 그룹이 연달아 있으면 재귀적으로 들어가서 기준 좌표 구함
		MyPoint pp = myGroup->getBasePosition();
		p.x = myGroup->getX1() + pp.x;
		p.y = myGroup->getY1() + pp.y;
	}
	else { // 그룹이 없으면 0, 0
		p.x = p.y = 0;
	}
	return p;
}