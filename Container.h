#pragma once
#include <list>
#include "Component.h"
class Container:public Component //�����̳ʴ� ���۳�Ʈ�� ����
{
protected:
	std::list<Component*> myComponentList;

public:
	Container();//�⺻������
	Container(int x, int y, int width, int height);
	virtual void draw()=0; //component ������ �� �׸��� 

};

