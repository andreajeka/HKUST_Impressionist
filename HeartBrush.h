#ifndef HEARTBRUSH_H
#define HEARTBRUSH_H

#include "impBrush.h"

class HeartBrush : public ImpBrush {
public:
	HeartBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif