#define _CRT_SECURE_NO_WARNINGS
#include "FigGroup.h"
#include "graphics.h"
#include "PainterFrame.h"
FigGroup::FigGroup(){
//비어있습니다.
	// addFigure할 때 업데이트하기 위해 초기화
	x1 = 999; 
	y1 = 999;
	x2 = -1;
	y2 = -1;
}
void FigGroup::addFigure(Figure* added) {
	int tx1 = added->getX1();
	int ty1 = added->getY1();
	int tx2 = added->getX2();
	int ty2 = added->getY2();
	// 그룹의 기준 좌표 설정
	if (tx1 < x1) x1 = tx1; // 새로운 Figure의 왼쪽위 좌표가 더 작으면 업데이트 
	if (ty1 < y1) y1 = ty1;
	if (tx2 > x2) x2 = tx2; // 새로운 Figure의 오른쪽아래 좌표가 더 크면 업데이트
	if (ty2 > y2) y2 = ty2;
	added->setMyGroup(this); // 그룹에 추가된 리스트의 그룹 지정
	myFigList.push_back(added);
}

void FigGroup::updateFigListPosition() {
	// FigGroup의 기준 좌표로 그룹 내 Figure들 상대 좌표로 업데이트
	for (auto i = myFigList.begin(); i != myFigList.end(); i++) {
		// 왼쪽 위(x1, y1) 기준으로 상대좌표 구함
		(*i)->setX1((*i)->getX1() - x1);
		(*i)->setY1((*i)->getY1() - y1);
		(*i)->setX2((*i)->getX2() - x1);
		(*i)->setY2((*i)->getY2() - y1);
	}
}

bool FigGroup::isIncluded(int x, int y) {
	if ((x1 < x && x < x2) && (y1 < y && y < y2)) return true;
	else return false;
}

void FigGroup::draw() {
	MyPoint bp = this->getBasePosition();
	Graphics* g = (this->parent_)->getGraphics();
	g->setColor(Graphics::PEN_GRAY);
	g->setFill(Graphics::BRUSH_INVISIBLE);
	g->drawGroup(bp.x + x1, bp.y + y1, x2 - x1, y2 - y1);
	for (list<Figure*>::iterator i = myFigList.begin(); i != myFigList.end(); i++) {
		(*i)->draw();
	}
}

list<Figure*>::iterator FigGroup::getMyFigListBegin() {
	return myFigList.begin();
}
list<Figure*>::iterator FigGroup::getMyFigListEnd() {
	return myFigList.end();
}
