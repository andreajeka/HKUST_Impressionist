//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	
	// Enable alpha blending before the brush moves
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	int brushSize = pDoc->getSize();
	int radius = brushSize / 2;

	glBegin(GL_TRIANGLE_FAN);
		SetColor(source);

		for (int i = 0; i < 360; i++)
		{
			double degInRad = i * M_PI / 180.0;
			glVertex2d(cos(degInRad)*radius + target.x, sin(degInRad)*radius + target.y);
		}

	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// Disable alpha blending
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);
}
