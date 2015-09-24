//
// WithoutConvBlurBrush.h
//
// The header file for Without Convolution Blur Brush. 
//

#ifndef WITHOUTCONVBLURBRUSH_H
#define WITHOUTCONVBLURBRUSH_H

#include "ImpBrush.h"

class WithoutConvBlurBrush : public ImpBrush
{
public:
	WithoutConvBlurBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void SetColor(const Point source);
	char* BrushName(void);
};

#endif