#include "myrect.h"
#include "graphics.h"
#include "frame.h"
#include "PainterFrame.h"
MyRect::MyRect() {
//����ֽ��ϴ�.
}
/*MyRect::MyRect(Frame* parent_,int x1, int y1, int x2, int y2) :Figure(parent_,x1,y1,x2,y2){

}*/
MyRect::MyRect(int x1, int y1, int x2, int y2,int thick) : Figure(x1, y1, x2, y2, thick) {
}
void MyRect::draw() {
	MyPoint bp = this->getBasePosition();
	Graphics* g = (this->parent_)->getGraphics();
	g->setColor(Graphics::PEN_RED);
	g->setFill(Graphics::BRUSH_INVISIBLE); //������� (�������� setTransparent�� ����)
	for (int i = 0; i < thick; i++) {
		g->drawRectangle(bp.x + x1-i, bp.y + y1-i, x2 - x1+i*2, y2 - y1+i*2);
	}
}

bool MyRect::isIncluded(int x, int y) {
	if ((x1 < x && x < x2) && (y1 < y && y < y2)) return true;
	else return false;
}