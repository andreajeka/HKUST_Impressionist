//
// ScatteredCircleBrush.cpp
//
// The implementation of ScatteredCircleBrush. It is a kind of CircleBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"
#include "math.h"

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
CircleBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// Enable alpha blending before the brush moves
	EnableAlphaBlending();

	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	int circleAmount = 4;
	int size = pDoc->getSize();

	for (int i = 0; i < circleAmount; i++) {
		// Get random numbers to set scatter location in the brush area
		int randomX = rand() % size + (-size / 2);
		int randomY = rand() % size + (-size / 2);

		// We need to set a new Point source for the brush as well to 
		// match the location of the source and the target point
		Point newSource(source.x + randomX, source.y + randomY);
		Point newTarget(target.x + randomX, target.y + randomY);

		CircleBrush::BrushMove(newSource, newTarget);
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	// Disable alpha blending
	DisableAlphaBlending();
}
