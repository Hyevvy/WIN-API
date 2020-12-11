#include "Rbutton.h"
#include "graphics.h"
#include "frame.h"
Rbutton::Rbutton() {

//	Ellipse(hDC_, x_, y_, x_ + width_, y_ + height_);
//비어있습니다. 
//TODO: 라디오버튼만들기
}
Rbutton::Rbutton(std::string type) {
	typestr = type;
}

void Rbutton::draw() {
	OutputDebugStringW(L"알버튼드로우 호출");
	Graphics* g =(this->parent_)->getGraphics();
	g->setColor(Graphics::PEN_BLACK);
	//getIsRgbdown()
	if(this->isRgbDown){ 
		g->setFill(Graphics::BRUSH_BLACK);
		OutputDebugStringW(L"알버튼눌렸다\n");
	//눌렸다.
	}
	else g->setFill(Graphics::BRUSH_WHITE);
	Ellipse(hDC_, x_, y_+10, x_ + width_-20, y_ + height_-10);
	g->setFill(Graphics::BRUSH_WHITE);
	Rectangle(hDC_, x_+width_-20, y_, x_ + width_+30, y_ + height_);
	TextOutA(hDC_, x_ + 10, y_ + 5, typestr.c_str(), strlen(typestr.c_str()));
	
}
bool Rbutton::isIncluded(int x, int y) {
	//라디오버튼을 눌렀을때만 (원의 범위)
	int r = (x_+width_-20 - x_) / 2; // 반지름
	int center_x = x_ + r; // 원의 왼쪽위 x좌표
	int center_y = y_+10 + r; // 원의 왼쪽위 y좌표
	int dist = sqrt((center_x - x) * (center_x - x) + (center_y - y) * (center_y - y));
	if (dist <= r) { 
		//OutputDebugStringW(L"라디오버튼눌렸다!!!\n");
		
		return true; }
	else return false;

}
