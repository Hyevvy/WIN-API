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
//����ֽ��ϴ�.
}
PainterFrame::PainterFrame(std::wstring title, int width, int height):Frame(title, width, height) {

}
void PainterFrame::initialize() {
	Toolbar* toolbar = new Toolbar();
	RadioGroup* rgroup = new RadioGroup(330,0,30,30);
	this->addToolbar(toolbar);
	this->addRgroup(rgroup);
	Button* thick1 = new Button("�β� �ּ�");
	Button* thick2 = new Button("�β� �߰�");
	Button* thick3 = new Button("�β� �ִ�");
	Button* group = new Button("�׷�ȭ");
	Rbutton* radioRect = new Rbutton("�簢��");
	Rbutton* radioCircle = new Rbutton("����");
	Rbutton* radioLine = new Rbutton("����");
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
	// TODO: ���⿡ ���� �ڵ� �߰�.
	//OutputDebugString(L"Event\n");
	// �̺�Ʈ�� ������ �ľ��ؼ� �簢�� �׸��⸦ ���⼭ ���ش�.
	//��ư�� ���ȴ��� ���� Ȯ���ϰ� ��ǥ�� ��´�.

	if (Frame::eventHandler(e)) {
		// ��ư ����
		return true;
	}
	//�Ʒ��� Frame���� �޴� ���ٵ��� ó������ ���� ����̴�.
	else {
		// ��ư �ȴ���. ����� Ŭ�������� ���� ó��.
		if (e.isLButtonDown()) {
			checkedRgb = nullptr;
			start.x = e.getX();
			start.y = e.getY();
			if (e.isCtrlPressed()) {
				// ���� ����
				selectedFigure = findIncludedFigure(start.x, start.y);
			}
		}
		else if (e.isLButtonUp()) {
			end.x = e.getX();
			end.y = e.getY();
			if (ispushedGrouping) { 
				grouping();
				invalidate();
				ispushedGrouping = false;//�ѹ��� �׷��εǵ��Ϥ���
			}

			else if (selectedFigure) {
				// ���� ������ ������ �̵�.
				selectedFigure->changePosition(start.x, start.y, end.x, end.y);
				invalidate();
				selectedFigure = nullptr;
			}
			else {
					Figure* temp = nullptr;
					
					if(figtype_==1){// �簢��
					//	OutputDebugStringW(L"figtype�� 1");
						temp = new MyRect(start.x, start.y, end.x, end.y, thick_);
					}
					else if (figtype_ == 2) { //����
					//	OutputDebugStringW(L"figtype�� 2");
						temp = new MyCircle(start.x, start.y, end.x, end.y, thick_);
					}
					else if (figtype_ == 3) {
					//	OutputDebugStringW(L"figtype�� 3");
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
	// sx, sy ~ ex, ey ���� ���� ���ԵǾ� ������ true
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
	// ��ư�׸���
	Frame::repaint();

	// Figure �׸���
	for (list<Figure*>::iterator i = mylist.begin(); i != mylist.end(); i++) {
		(*i)->draw();
	}
}

void PainterFrame::grouping() {
	FigGroup* f = new FigGroup();
	for (auto i = mylist.begin(); i != mylist.end(); i++) {
		// ���� ���� ���ԵǾ� ������ add
		if (this->isInside(*i, start.x, start.y, end.x, end.y)) {
			f->addFigure(*i);
		}
	}
	// �׷쿡 ���Ե� figure���� mylist���� ����
	for (auto i = f->getMyFigListBegin(); i != f->getMyFigListEnd(); i++) {
		mylist.remove(*i);
	}
	f->updateFigListPosition(); // �׷��� ���Ե� figure�� �׷� �� ��� ��ǥ�� �ٲ��ش�
	addFigure(f);
}