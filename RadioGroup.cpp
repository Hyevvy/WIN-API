#include "RadioGroup.h"
#include <cstdio>
#include "frame.h"
#define pragma warning (disable:4996)
RadioGroup::RadioGroup() {
//비어있습니다.
}
RadioGroup::RadioGroup(int x, int y, int width, int height) : Container(x, y, width, height)
{
}
void RadioGroup::draw() {
	OutputDebugStringW(L"라디오그룹의 드로우 실행\n");
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
	OutputDebugStringW(L"라디오그룹의 애드컴퍼넌트 작동\n");
	added->setBounds(this->x_+myComponentList.size()*60, this->y_, this->width_, this->height_);
	OutputDebugStringW(L"들어왔다");
	myComponentList.push_back(added);
	added->setHDC(hDC_);
	added->setParent(parent_);
}

void RadioGroup::Rgbhandler(int x, int y) {
	OutputDebugStringW(L"Rgb헨들러작동\n");
	
	/*if(this)
		OutputDebugStringW(L"ㅇㅇㅇㅇ\n");*/
	char temp[100];
	sprintf_s(temp, "size : %d\n", this->myComponentList.size());
	OutputDebugStringA(temp);

	for (auto i = myComponentList.rbegin(); i != myComponentList.rend(); i++) {
		OutputDebugStringW(L"for문안 작동\n");
		if ((*i)->isIncluded(x, y)) {
			OutputDebugStringW(L"if문안 작동\n");
			(*i)->IsRgbdown(true); 
			if ((*i)->getTypestr() == "사각형") {
				//OutputDebugStringW(L"타입얻기까지 성공1\n");
				parent_->setFigure(1);

			}
			else if ((*i)->getTypestr() == "원형") {
				parent_->setFigure(2);
		
			}
			else if ((*i)->getTypestr() == "선분") {
				parent_->setFigure(3);
			}
		}
		else (*i)->IsRgbdown(false);

	}

}