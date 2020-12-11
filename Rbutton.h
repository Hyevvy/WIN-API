#pragma once
#include "button.h"
#include <string>
class Frame;
class Rbutton:public Button
{
public:
	Rbutton();
	Rbutton(std::string type);
	bool isIncluded(int x, int y) override;
	Button* rbtn;
	void draw()override;
	
protected:
	
};

