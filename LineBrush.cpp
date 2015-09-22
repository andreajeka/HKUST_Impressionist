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
#include <iostream>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{

}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int width = pDoc->getLineWidth();
	glLineWidth(width);
	
	startCoord = Point(target.x, target.y);
	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int lineAngle = 0;

	int strokeDirectionChoice = dlg->m_StrokeDirectionTypeChoice->value();
	Point startGradient, endGradient;
	int perpendicularAngle = 0;

	// For stroke direction cases:
	// 1. Setting angle for stroke direction and slider case has been solved inside paintview.cpp
	// 2. Setting angle from brush direction stroke
	// 3. Setting angle from gradient
	switch (strokeDirectionChoice) 
	{
		case SLIDER_OR_RIGHTMOUSE:
			lineAngle = pDoc->getLineAngle();
			break;
		case BRUSH_DIRECTION:
			lineAngle = DetermineAngle(startCoord, target);
			startCoord = target;
			break;
		case GRADIENT:
			startGradient = Point(0, 0);
			if (pDoc->m_pUI->anotherGradientIsOn())
				endGradient = Point(pDoc->GetGradientOfX_DiffImg(source), pDoc->GetGradientOfY_DiffImg(source));
			else
				endGradient = Point(pDoc->GetGradientOfX(source), pDoc->GetGradientOfY(source));

			// DetermineAngle(startGradient, endGradient) is the gradient direction
			perpendicularAngle = DetermineAngle(startGradient, endGradient) + 90;
			if (perpendicularAngle >= 360)
				perpendicularAngle -= 180;
			lineAngle = perpendicularAngle;
			break;
		default:
			break;
	}

	DrawLine(source, target, size, lineAngle);
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
}

// We now have a specific function that can draw a line just by feeding the parameters, 
// esp. line angle because we have many stroke direction option to change the angle 
void LineBrush::DrawLine(const Point source, const Point target, const int size, const int angle)
{
	ImpressionistDoc* pDoc = GetDocument();
	int halfSize = size / 2;
	float alphaValue = pDoc->getAlpha();

	//TODO calculate ege clipping here
	// still looking for algorithm

	glBegin(GL_LINES);
	SetColor(source, alphaValue);

		// Because a line is made of two points,
		// we have to supply the location of two points.
		glVertex2d(target.x - (cos(angle * M_PI / 180) * halfSize), target.y - (sin(angle * M_PI / 180.0) * halfSize));
		glVertex2d(target.x + (cos(angle * M_PI / 180) * halfSize), target.y + (sin(angle * M_PI / 180.0) * halfSize));

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