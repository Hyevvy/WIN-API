#pragma once
#include <string>
#include <Windows.h>
#include "Component.h"
using namespace std;
class Frame;
class Button:public Component//버튼도 컴퍼넌트의 일종
{
public:
	Button();
	Button(string a);
	void draw();
	bool isIncluded(int x, int y) override;
	//virtual void setRgbPushed(bool)=0;
	//virtual void setisRgbDown(bool);
protected:

};

