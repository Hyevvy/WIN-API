#include "mycircle.h"
#include "graphics.h"
#include "frame.h"
#include "PainterFrame.h"
#include <cmath>
MyCircle::MyCircle() {
//비어있습니다.
}
MyCircle::MyCircle(int x1, int y1, int x2, int y2, int thick) :Figure( x1, y1, x2, y1 + x2 - x1,thick) {
	
}
/*MyCircle::MyCircle(Frame* parent_,int x1, int y1, int x2, int y2) :Figure(parent_, x1, y1, x2, y2) {

}*/
void MyCircle::draw() {
	//Ellipse(hDC_, x1, y1, x2, y2);
	MyPoint bp = this->getBasePosition();
	Graphics* g = (this->parent_)->getGraphics();
	g->setColor(Graphics::PEN_BLUE);
	g->setFill(Graphics::BRUSH_YELLOW);
//	g->drawCircle(bp.x + x1, bp.y + y1, x2-x1, y2-y1);
	for (int i = 0; i < thick; i++) {
		g->drawCircle(bp.x + x1 - i, bp.y + y1 - i, x2 - x1 + i * 2, y2 - y1 + i * 2);
	}
}

bool MyCircle::isIncluded(int x, int y) {
	// center점과 입력점 사이의 거리가 반지름 보다 작으면 true
	int r = (x2 - x1) / 2;
	int center_x = x1 + r;
	int center_y = y1 + r;
	int dist = sqrt((center_x - x) * (center_x - x) + (center_y - y) * (center_y - y));
	if (dist <= r) return true;
	else return false;
}
