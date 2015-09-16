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
	glLineWidth(width);

	
	startCoord = new Point(target.x, target.y);
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
	endCoord = new Point(target.x, target.y);

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
			lineAngle = DetermineAngle(*startCoord, *endCoord);
			break;
		case GRADIENT:
			startGradient = Point(0, 0);
			endGradient = Point(getGradientOfX(source), getGradientOfY(source));
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
	// Disable alpha blending
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);
}

// We now have a specific function that can draw a line just by feeding the parameters, 
// esp. line angle because we have many stroke direction option to change the angle 
void LineBrush::DrawLine(const Point source, const Point target, const int size, const int angle)
{
	int halfSize = size / 2;

	glBegin(GL_LINES);
	SetColor(source);

		// Because a line is made of two points,
		// we have to supply the location of two points.
		glVertex2d(target.x - (cos(angle * M_PI / 180) * halfSize), target.y - (sin(angle * M_PI / 180.0) * halfSize));
		glVertex2d(target.x + (cos(angle * M_PI / 180) * halfSize), target.y + (sin(angle * M_PI / 180.0) * halfSize));

	glEnd();
}

int LineBrush::getGradientOfX(const Point source){
	
	// Sobel Mask of X
	int Sx[3][3] = 
	{
		{ -1, 0, 1 },
		{ -2, 0, 2 },
		{ -1, 0, 1 }

	};

	double Gx = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			Gx += Sx[i][j] * getPixelIntensity(source.x + j - 1,
											   source.y - i + 1);
		}
	}
	return (int) Gx;
}

int LineBrush::getGradientOfY(const Point source){

	// Sobel Mask of Y
	int Sy[3][3] =
	{
		{ 1, 2, 1 },
		{ 0, 0, 0 },
		{ -1, -2, -1 }

	};

	double Gy = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			Gy += Sy[i][j] * getPixelIntensity(source.x + j - 1,
											   source.y - i + 1);
		}
	}
	return (int)Gy;
}

// Get pixel intensity according to human eye
int LineBrush::getPixelIntensity(int x, int y) {
	ImpressionistDoc* pDoc = GetDocument();
	unsigned char color[3];
	memcpy(color, pDoc->GetOriginalPixel(x, y), 3);
	return (0.299*color[0] + 0.587*color[1] + 0.144*color[2]);
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