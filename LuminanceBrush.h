#ifndef LUMINANCEBRUSH_H
#define LUMINANCEBRUSH_H

#include "ImpBrush.h"

class LuminanceBrush : public ImpBrush
{
public:
	LuminanceBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

	void setWidth(int w);
	void setHeight(int h);
	float getLuminanceXY(int x, int y);

private:
	int width;
	int height;
};

#endif