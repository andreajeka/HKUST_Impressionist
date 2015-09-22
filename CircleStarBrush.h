#ifndef CIRCLESTARBRUSH_H
#define CIRCLESTARBRUSH_H

#include "ImpBrush.h"

class CircleStarBrush : public ImpBrush
{
public:
	CircleStarBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif