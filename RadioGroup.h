#pragma once
#include "Container.h"
class RadioGroup:public Container//�����׷��� �����̳ʸ� ��ӹ޴´�.
{
public:
	RadioGroup();
	RadioGroup(int x, int y, int width_, int height);
	void draw()override;//������ư �׸���
	bool isIncluded(int x, int y);//���������Լ��� ������ �������ؾ���.
	void addComponent(Component* added);
	void Rgbhandler(int x, int y);
protected:

};

