#include "Toolbar.h"
#include "frame.h"
Toolbar::Toolbar() {
	//����ֽ��ϴ�.
}
void Toolbar::addComponent(Component* added) {
	//OutputDebugStringW(L"������ �ֵ����۳�Ʈ �۵�\n");
		added->setBounds(myComponentList.size() * 80, 0, 80, 30);
		myComponentList.push_back(added);
		added->setHDC(hDC_);
		added->setParent(parent_);
}
void Toolbar::menuhandler(int x, int y) {
	//OutputDebugStringW(L"�޴���鷯�۵�\n");
	for (auto i = myComponentList.rbegin(); i != myComponentList.rend(); i++) {
	//	OutputDebugStringW(L"for���� �۵�\n");
		if ((*i)->isIncluded(x, y)) {
		//	OutputDebugStringW(L"if���� �۵�\n");
			if ((*i)->getTypestr() == "�β� �ּ�")
				parent_->setThick(1);
			else if ((*i)->getTypestr() == "�β� �߰�")
				parent_->setThick(2);
			else if ((*i)->getTypestr() == "�β� �ִ�")
				parent_->setThick(3);
			else if ((*i)->getTypestr() == "�׷�ȭ")
				parent_->setPushedGrouping(true);
			break;
		}
	}
}
bool Toolbar::isIncluded(int x, int y) {
	for (auto i = myComponentList.rbegin(); i != myComponentList.rend(); i++) {
		if ((*i)->isIncluded(x, y)) {
			return true;
		}
	}
	return false;
}
void Toolbar::draw() {
	//OutputDebugStringW(L"������ ��ο� ����");
	for (std::list<Component*>::iterator i = myComponentList.begin(); i != myComponentList.end(); i++) {
		(*i)->draw();
	}
}
