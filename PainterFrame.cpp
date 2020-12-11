#include "PainterFrame.h"
#include "button.h"
#include "mycircle.h"
#include "myrect.h"
#include "myline.h"
#include "FigGroup.h"
#include "Toolbar.h"
#include "RadioGroup.h"
#include "Rbutton.h"
PainterFrame::PainterFrame() {
//비어있습니다.
}
PainterFrame::PainterFrame(std::wstring title, int width, int height):Frame(title, width, height) {

}
void PainterFrame::initialize() {
	Toolbar* toolbar = new Toolbar();
	RadioGroup* rgroup = new RadioGroup(330,0,30,30);
	this->addToolbar(toolbar);
	this->addRgroup(rgroup);
	Button* thick1 = new Button("두께 최소");
	Button* thick2 = new Button("두께 중간");
	Button* thick3 = new Button("두께 최대");
	Button* group = new Button("그룹화");
	Rbutton* radioRect = new Rbutton("사각형");
	Rbutton* radioCircle = new Rbutton("원형");
	Rbutton* radioLine = new Rbutton("선분");
	toolbar->addComponent(thick1);
	toolbar->addComponent(thick2);
	toolbar->addComponent(thick3);
	toolbar->addComponent(group);
	rgroup->addComponent(radioRect);
	rgroup->addComponent(radioCircle);
	rgroup->addComponent(radioLine);
	invalidate();
}

bool PainterFrame::eventHandler(MyEvent e)
{
	// TODO: 여기에 구현 코드 추가.
	//OutputDebugString(L"Event\n");
	// 이벤트의 종류를 파악해서 사각형 그리기를 여기서 해준다.
	//버튼이 눌렸는지 먼저 확인하고 좌표를 얻는다.

	if (Frame::eventHandler(e)) {
		// 버튼 눌림
		return true;
	}
	//아래는 Frame에서 메뉴 툴바등이 처리되지 않은 경우이다.
	else {
		// 버튼 안눌림. 빈공간 클릭했으니 도형 처리.
		if (e.isLButtonDown()) {
			checkedRgb = nullptr;
			start.x = e.getX();
			start.y = e.getY();
			if (e.isCtrlPressed()) {
				// 눌린 도형
				selectedFigure = findIncludedFigure(start.x, start.y);
			}
		}
		else if (e.isLButtonUp()) {
			end.x = e.getX();
			end.y = e.getY();
			if (ispushedGrouping) { 
				grouping();
				invalidate();
				ispushedGrouping = false;//한번만 그룹핑되도록ㄷㄷ
			}

			else if (selectedFigure) {
				// 눌린 도형이 있으면 이동.
				selectedFigure->changePosition(start.x, start.y, end.x, end.y);
				invalidate();
				selectedFigure = nullptr;
			}
			else {
					Figure* temp = nullptr;
					
					if(figtype_==1){// 사각형
					//	OutputDebugStringW(L"figtype은 1");
						temp = new MyRect(start.x, start.y, end.x, end.y, thick_);
					}
					else if (figtype_ == 2) { //원형
					//	OutputDebugStringW(L"figtype은 2");
						temp = new MyCircle(start.x, start.y, end.x, end.y, thick_);
					}
					else if (figtype_ == 3) {
					//	OutputDebugStringW(L"figtype은 3");
						temp = new MyLine(start.x, start.y, end.x, end.y, thick_);
					}
					if (temp != nullptr) {
						addFigure(temp);
					//	temp->setRgbPushed(true);
						temp->draw();
					}
			}
		}
		return true;
	}
}
void PainterFrame::addFigure(Figure* added) {
	added->setParent(this);
	mylist.push_back(added);
}

bool PainterFrame::isInside(Figure* item, int sx, int sy, int ex, int ey) {
	// sx, sy ~ ex, ey 범위 내에 포함되어 있으면 true
	for (int i = sx; i < ex; i++) {
		for (int j = sy; j < ey; j++) {
			if (item->isIncluded(i, j)) {
				return true;
			}
		}
	}
	return false;
}

Figure* PainterFrame::findIncludedFigure(int x, int y) {
		for (auto i = mylist.rbegin(); i != mylist.rend(); i++) {
			if ((*i)->isIncluded(x, y)) {
				return *i;
			}
		}
		return nullptr;
	
}
void PainterFrame::repaint(){
	// 버튼그리기
	Frame::repaint();

	// Figure 그리기
	for (list<Figure*>::iterator i = mylist.begin(); i != mylist.end(); i++) {
		(*i)->draw();
	}
}

void PainterFrame::grouping() {
	FigGroup* f = new FigGroup();
	for (auto i = mylist.begin(); i != mylist.end(); i++) {
		// 범위 내에 포함되어 있으면 add
		if (this->isInside(*i, start.x, start.y, end.x, end.y)) {
			f->addFigure(*i);
		}
	}
	// 그룹에 포함된 figure들은 mylist에서 제외
	for (auto i = f->getMyFigListBegin(); i != f->getMyFigListEnd(); i++) {
		mylist.remove(*i);
	}
	f->updateFigListPosition(); // 그룹의 포함된 figure들 그룹 내 상대 좌표로 바꿔준다
	addFigure(f);
}