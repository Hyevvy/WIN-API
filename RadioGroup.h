#pragma once
#include "Container.h"
class RadioGroup:public Container//라디오그룹은 컨테이너를 상속받는다.
{
public:
	RadioGroup();
	RadioGroup(int x, int y, int width_, int height);
	void draw()override;//라디오버튼 그리기
	bool isIncluded(int x, int y);//순수가상함수라 무조건 재정의해야함.
	void addComponent(Component* added);
	void Rgbhandler(int x, int y);
protected:

};

