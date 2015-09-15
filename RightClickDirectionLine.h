#ifndef RIGHTCLICKDIRECTIONLINE_H
#define RIGHTCLICKDIRECTIONLINE_H

//
// RightClickDirectionLine.h
// The header file for Line Brush. Inherit from ImpBrush
// We just want to make a very simple brush to display
// to the user the stroke they make 
//

#include "ImpBrush.h"

class RightClickDirectionLine : public ImpBrush
{
public:
	RightClickDirectionLine(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);

	Point* startCoord;
	// Return the name of the brush (not used in this version).
	char* BrushName(void);
};

#endif