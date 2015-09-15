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
	int width = pDoc->getLineWidth();
	int angle = pDoc->getLineAngle();

	glLineWidth(width);
	glBegin(GL_LINES);
		SetColor(source);

		// Because a line is made of two points,
		// we have to supply the location of two points.
		if (angle )
		glVertex2d(target.x - (cos(angle * M_PI / 180) * halfSize), target.y - (sin(angle * M_PI / 180.0) * halfSize));
		glVertex2d(target.x + (cos(angle * M_PI / 180) * halfSize), target.y + (sin(angle * M_PI / 180.0) * halfSize));

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

