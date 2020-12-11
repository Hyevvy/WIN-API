#include "RadioGroup.h"
#include <cstdio>
#include "frame.h"
#define pragma warning (disable:4996)
RadioGroup::RadioGroup() {
//����ֽ��ϴ�.
}
RadioGroup::RadioGroup(int x, int y, int width, int height) : Container(x, y, width, height)
{
}
void RadioGroup::draw() {
	OutputDebugStringW(L"�����׷��� ��ο� ����\n");
	for (std::list<Component*>::iterator i = myComponentList.begin(); i != myComponentList.end(); i++) {
		(*i)->draw();
	}
}

bool RadioGroup::isIncluded(int x, int y) {

	for (auto i = myComponentList.rbegin(); i != myComponentList.rend(); i++) {
		if ((*i)->isIncluded(x, y)) {
			return true;
		}
	}
	return false;
}
void RadioGroup::addComponent(Component* added) {
	OutputDebugStringW(L"�����׷��� �ֵ����۳�Ʈ �۵�\n");
	added->setBounds(this->x_+myComponentList.size()*60, this->y_, this->width_, this->height_);
	OutputDebugStringW(L"���Դ�");
	myComponentList.push_back(added);
	added->setHDC(hDC_);
	added->setParent(parent_);
}

void RadioGroup::Rgbhandler(int x, int y) {
	OutputDebugStringW(L"Rgb��鷯�۵�\n");
	
	/*if(this)
		OutputDebugStringW(L"��������\n");*/
	char temp[100];
	sprintf_s(temp, "size : %d\n", this->myComponentList.size());
	OutputDebugStringA(temp);

	for (auto i = myComponentList.rbegin(); i != myComponentList.rend(); i++) {
		OutputDebugStringW(L"for���� �۵�\n");
		if ((*i)->isIncluded(x, y)) {
			OutputDebugStringW(L"if���� �۵�\n");
			(*i)->IsRgbdown(true); 
			if ((*i)->getTypestr() == "�簢��") {
				//OutputDebugStringW(L"Ÿ�Ծ����� ����1\n");
				parent_->setFigure(1);

			}
			else if ((*i)->getTypestr() == "����") {
				parent_->setFigure(2);
		
			}
			else if ((*i)->getTypestr() == "����") {
				parent_->setFigure(3);
			}
		}
		else (*i)->IsRgbdown(false);

	}

}