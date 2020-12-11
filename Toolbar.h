#pragma once
#include "Container.h"

class Toolbar:public Container
{
public:
	Toolbar();//기본생성자
	void addComponent(Component* added);
	bool isIncluded(int x, int y); //이 범위안에 속하는 버튼이 있는지
	void draw() override;//컴퍼넌트리스트 그리기
	void menuhandler(int x, int y);

private:
	
};

