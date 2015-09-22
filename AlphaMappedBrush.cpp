#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "AlphaMappedBrush.h"

#include <iostream>
using namespace std;

extern float frand();

AlphaMappedBrush::AlphaMappedBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void AlphaMappedBrush::BrushBegin(const Point source, const Point target)
{
	glPointSize((GLfloat)1);
	BrushMove(source, target);
}

void AlphaMappedBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("Alpha-mapped Brush::BrushMove  document is NULL\n");
		return;
	}


	glPushMatrix();
	glTranslatef(target.x, target.y, 0);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int newX = x - width / 2;
			int newY = y - height / 2;
			glBegin(GL_POINTS);

			SetColor(source, getAlphaXY(x, height - 1 - y));
			glVertex2d(newX, newY);

			glEnd();
		}
	}

	glPopMatrix();
}

void AlphaMappedBrush::BrushEnd(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	int size = pDoc->getSize();
	glPointSize((GLfloat)size);
}

float AlphaMappedBrush::getAlphaXY(int x, int y) {
	ImpressionistDoc* pDoc = GetDocument();
	unsigned char* colourXY = pDoc->m_ucAlphaMappedBrush + 4 * (y*width + x);
	float alpha = (float)(colourXY[3]);
	return alpha / 255.0f;
}

void AlphaMappedBrush::setWidth(int w) {
	width = w;
}

void AlphaMappedBrush::setHeight(int h) {
	height = h;
}
