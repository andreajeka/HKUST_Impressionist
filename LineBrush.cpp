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
	startCoord = NULL;
	endCoord = NULL;
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

	//
	startCoord = new Point(target.x, target.y);
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

	//// For stroke direction cases:
	//// 1. Setting angle for stroke direction and slider case
	//if (dlg->m_StrokeDirectionTypeChoice->value == SLIDER_OR_RIGHTMOUSE) {
	//	if (endCoord == NULL)
	//		endCoord = new Point(target.x, target.y);
	//	else {

	//	}
	//}



}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// Disable alpha blending
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);


}

// We now have a specific function that can draw a line just by feeding the parameters, 
// esp. line angle because we have many stroke direction option to change the angle 
void LineBrush::DrawLine(const Point source, const Point target, const int width, const int angle)
{
	int halfWidth = width / 2;

	glBegin(GL_LINES);
	SetColor(source);

		// Because a line is made of two points,
		// we have to supply the location of two points.
		glVertex2d(target.x - (cos(angle * M_PI / 180) * halfWidth), target.y - (sin(angle * M_PI / 180.0) * halfWidth));
		glVertex2d(target.x + (cos(angle * M_PI / 180) * halfWidth), target.y + (sin(angle * M_PI / 180.0) * halfWidth));

	glEnd();
}

int LineBrush::DetermineAngle(const Point start, const Point end)
{
	double xDifference = end.x - start.x;
	double yDifference = end.y - start.y;

	// atan2 returns in rad
	// need to use round() to round up instead of rounding down due to compiler's auto truncation 
	int angleInDeg = round(atan2(yDifference, xDifference) / M_PI * 180);

	if (angleInDeg < 0)
		angleInDeg += 360;
	return angleInDeg;
}