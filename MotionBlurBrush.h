//
// MotionBlurBrush.h
//
// The header file for Motion Blur Brush. 
//

#ifndef MOTIONBLURBRUSH_H
#define MOTIONBLURBRUSH_H

#include "MotionBlurBrush.h"

class MotionBlurBrush : public ImpBrush
{
public:
	MotionBlurBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void SetColor(const Point source);
	char* BrushName(void);
};

#endif