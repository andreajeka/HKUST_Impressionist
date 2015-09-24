//
// GaussianBlurBrush.h
//
// The header file for Emboss Brush. 
//

#ifndef GAUSSIANBLURBRUSH_H
#define GAUSSIANBLURBRUSH_H

#include "GaussianBlurBrush.h"

class GaussianBlurBrush : public ImpBrush
{
public:
	GaussianBlurBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void SetColor(const Point source);
	char* BrushName(void);
};

#endif