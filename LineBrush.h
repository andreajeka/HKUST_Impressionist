//
// LineBrush.h
//
// The header file for Line Brush. 
//

#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include "ImpBrush.h"

class LineBrush : public ImpBrush
{
public:
	LineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	static int DetermineAngle(const Point source, const Point target);
	void DrawLine(const Point source, const Point target, const int size, const int angle);

	char* BrushName(void);

	// We need to create a specific attr interface to ease the calculation 
	// of stroke direction
	Point startCoord;
};

#endif