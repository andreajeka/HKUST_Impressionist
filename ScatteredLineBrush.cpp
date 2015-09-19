//
// ScatteredLineBrush.cpp
//
// The implementation of Scattered Line Brush. It is a kind of LineBrush. 

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"

extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
LineBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int width = pDoc->getLineWidth();
	glLineWidth(width);

	startCoord = Point(target.x, target.y);
	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int lineAmount = 4;
	int size = pDoc->getSize();

	for (int i = 0; i < lineAmount; i++) {
		// Get random numbers to set scatter location in the brush area
		int randomX = rand() % size + (-size / 2);
		int randomY = rand() % size + (-size / 2);

		// We need to set a new Point source for the brush as well to 
		// match the location of the source and the target point
		Point newSource(source.x + randomX, source.y + randomY);
		Point newTarget(target.x + randomX, target.y + randomY);

		LineBrush::BrushMove(newSource, newTarget);
	}
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
}

