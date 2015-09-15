//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <math.h>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// Enable alpha blending before the brush moves
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int width = pDoc->getLineWidth();
	glLineWidth((GLfloat)width);

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}


	int size = pDoc->getSize();
	int halfSize = size / 2;

	int angle = pDoc->getLineAngle();

	glBegin(GL_LINES);
		SetColor(source);

		// Because a line is made of two points,
		// we have to supply the location of two points.
		glVertex2d(target.x - (cos(angle * M_PI / 180) * halfSize), target.y - (sin(angle * M_PI / 180.0) * halfSize));
		glVertex2d(target.x + (cos(angle * M_PI / 180) * halfSize), target.y + (sin(angle * M_PI / 180.0) * halfSize));

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// Disable alpha blending
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);
}

