#include "Toolbar.h"
#include "frame.h"
Toolbar::Toolbar() {
	//비어있습니다.
}
void Toolbar::addComponent(Component* added) {
	//OutputDebugStringW(L"툴바의 애드컴퍼넌트 작동\n");
		added->setBounds(myComponentList.size() * 80, 0, 80, 30);
		myComponentList.push_back(added);
		added->setHDC(hDC_);
		added->setParent(parent_);
}
void Toolbar::menuhandler(int x, int y) {
	//OutputDebugStringW(L"메뉴헨들러작동\n");
	for (auto i = myComponentList.rbegin(); i != myComponentList.rend(); i++) {
	//	OutputDebugStringW(L"for문안 작동\n");
		if ((*i)->isIncluded(x, y)) {
		//	OutputDebugStringW(L"if문안 작동\n");
			if ((*i)->getTypestr() == "두께 최소")
				parent_->setThick(1);
			else if ((*i)->getTypestr() == "두께 중간")
				parent_->setThick(2);
			else if ((*i)->getTypestr() == "두께 최대")
				parent_->setThick(3);
			else if ((*i)->getTypestr() == "그룹화")
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
	//OutputDebugStringW(L"툴바의 드로우 실행");
	for (std::list<Component*>::iterator i = myComponentList.begin(); i != myComponentList.end(); i++) {
		(*i)->draw();
	}
}
