#include "Rbutton.h"
#include "graphics.h"
#include "frame.h"
Rbutton::Rbutton() {

//	Ellipse(hDC_, x_, y_, x_ + width_, y_ + height_);
//����ֽ��ϴ�. 
//TODO: ������ư�����
}
Rbutton::Rbutton(std::string type) {
	typestr = type;
}

void Rbutton::draw() {
	OutputDebugStringW(L"�˹�ư��ο� ȣ��");
	Graphics* g =(this->parent_)->getGraphics();
	g->setColor(Graphics::PEN_BLACK);
	//getIsRgbdown()
	if(this->isRgbDown){ 
		g->setFill(Graphics::BRUSH_BLACK);
		OutputDebugStringW(L"�˹�ư���ȴ�\n");
	//���ȴ�.
	}
	else g->setFill(Graphics::BRUSH_WHITE);
	Ellipse(hDC_, x_, y_+10, x_ + width_-20, y_ + height_-10);
	g->setFill(Graphics::BRUSH_WHITE);
	Rectangle(hDC_, x_+width_-20, y_, x_ + width_+30, y_ + height_);
	TextOutA(hDC_, x_ + 10, y_ + 5, typestr.c_str(), strlen(typestr.c_str()));
	
}
bool Rbutton::isIncluded(int x, int y) {
	//������ư�� ���������� (���� ����)
	int r = (x_+width_-20 - x_) / 2; // ������
	int center_x = x_ + r; // ���� ������ x��ǥ
	int center_y = y_+10 + r; // ���� ������ y��ǥ
	int dist = sqrt((center_x - x) * (center_x - x) + (center_y - y) * (center_y - y));
	if (dist <= r) { 
		//OutputDebugStringW(L"������ư���ȴ�!!!\n");
		
		return true; }
	else return false;

}
