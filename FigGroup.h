#pragma once
#include <list>
#include "figure.h"
using namespace std;
class FigGroup : public Figure
{
public:
	FigGroup();
	void addFigure(Figure*);
	bool isIncluded(int x, int y) override;
	void draw() override;
	void updateFigListPosition();
	list<Figure*>::iterator getMyFigListBegin();
	list<Figure*>::iterator getMyFigListEnd();
private:
	list<Figure*> myFigList;
};

