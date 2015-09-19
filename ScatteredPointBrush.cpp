//
// ScatteredPointBrush.cpp
//
// The implementation of Scattered Point Brush. It is a kind of PointBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
PointBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	
	// Enable alpha blending before the brush moves
    EnableAlphaBlending();

	// Set the lowest size to one to get the scattered point effect
	glPointSize((float)1.0);

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();

	// We cannot use seeded rand() function because it does not 
	// work like the sample program although intuitively it should
	// be more interesting and give more random scattering if it is used.
	//srand(time(0));

	// 4 seems like a good number
	for (int i = 0; i < size*4; i++) {
		// Get random numbers to set scatter location in the brush area
		int randomX = rand() % size + (-size / 2);
		int randomY = rand() % size + (-size / 2);

		// We need to set a new Point source for the brush as well to 
		// match the location of the source and the target point
		Point newSource(source.x + randomX, source.y + randomY);
		Point newTarget(target.x + randomX, target.y + randomY);

		PointBrush::BrushMove(newSource, newTarget);
	}
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	// Disable alpha blending
	DisableAlphaBlending();
}