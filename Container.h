#pragma once
#include <list>
#include "Component.h"
class Container:public Component //컨테이너는 컴퍼넌트의 일종
{
protected:
	std::list<Component*> myComponentList;

public:
	Container();//기본생성자
	Container(int x, int y, int width, int height);
	virtual void draw()=0; //component 가져온 거 그리기 

};

