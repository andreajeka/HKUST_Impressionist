//
// EmbossBrush.h
//
// The header file for Emboss Brush. 
//

#ifndef EMBOSSBRUSH_H
#define EMBOSSBRUSH_H

#include "ImpBrush.h"

class EmbossBrush : public ImpBrush
{
public:
	EmbossBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void SetColor(const Point source);
	char* BrushName(void);
};

#endif