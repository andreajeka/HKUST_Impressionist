//
// WithoutConvSharpenBrush.h
//
// The header file for Without Convolution Sharpen Brush. 
//

#ifndef WITHOUTCONVSHARPENBRUSH_H
#define WITHOUTCONVSHARPENBRUSH_H

#include "ImpBrush.h"

class WithoutConvSharpenBrush : public ImpBrush
{
public:
	WithoutConvSharpenBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void SetColor(const Point source);
	char* BrushName(void);
};

#endif