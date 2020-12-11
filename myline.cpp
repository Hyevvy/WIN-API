#include "myline.h"
#include "PainterFrame.h"
#include "graphics.h"
#include "frame.h"
#include <algorithm>
MyLine::MyLine() {
//비어있습니다.
}
MyLine::MyLine(int x1, int y1, int x2, int y2,int thick) :Figure(x1, y1, x2, y2,thick) {
}
/*MyLine::MyLine(Frame* parent_, int x1, int y1, int x2, int y2):Figure(parent_, x1, y1, x2, y2) {
}*/
void MyLine::draw() {
	MyPoint bp = this->getBasePosition();
	Graphics* g = (this->parent_)->getGraphics();
	g->setColor(Graphics::PEN_BLACK);
	g->setFill(Graphics::BRUSH_WHITE);
	for (int i = 0; i < thick; i++) {
		g->drawLine(bp.x + x1 - i, bp.y + y1 - i, x2 - x1 + i * 2, y2 - y1 + i * 2);
	}
}
bool MyLine::isIncluded(int x, int y) {
	int left = min(x1, x2);
	int top = min(y1,y2);
	return left < x && x < left + x2
		&& top < y && y < top + y2;
}
