#pragma once
#include "Container.h"

class Toolbar:public Container
{
public:
	Toolbar();//�⺻������
	void addComponent(Component* added);
	bool isIncluded(int x, int y); //�� �����ȿ� ���ϴ� ��ư�� �ִ���
	void draw() override;//���۳�Ʈ����Ʈ �׸���
	void menuhandler(int x, int y);

private:
	
};

