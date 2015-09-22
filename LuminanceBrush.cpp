#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LuminanceBrush.h"

#include <iostream>
using namespace std;

extern float frand();

LuminanceBrush::LuminanceBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void LuminanceBrush::BrushBegin(const Point source, const Point target)
{
	glPointSize((GLfloat)1);
	BrushMove(source, target);
}

void LuminanceBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("Luminance Brush::BrushMove  document is NULL\n");
		return;
	}


	glPushMatrix();
	glTranslatef(target.x, target.y, 0);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int newX = x - width / 2;
			int newY = y - height / 2;
			glBegin(GL_POINTS);

			SetColor(source, getLuminanceXY(x, y));
			glVertex2d(newX, newY);

			glEnd();
		}
	}

	glPopMatrix();
}

void LuminanceBrush::BrushEnd(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	int size = pDoc->getSize();
	glPointSize((GLfloat)size);
}

float LuminanceBrush::getLuminanceXY(int x, int y) {
	ImpressionistDoc* pDoc = GetDocument();
	unsigned char* colourXY = pDoc->m_ucLuminanceBrush + 3 * (y*width + x);
	float luminance = 0.299 * colourXY[0] + 0.587 * colourXY[1] + 0.114 * colourXY[2];
	return luminance / 255.0f;
}

void LuminanceBrush::setWidth(int w) {
	width = w;
}

void LuminanceBrush::setHeight(int h) {
	height = h;
}
