#ifndef ALPHAMAPPEDBRUSH_H
#define ALPHAMAPPEDBRUSH_H

#include "ImpBrush.h"

class AlphaMappedBrush : public ImpBrush
{
public:
	AlphaMappedBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

	void setWidth(int w);
	void setHeight(int h);
	float getAlphaXY(int x, int y);

private:
	int width;
	int height;
};

#endif