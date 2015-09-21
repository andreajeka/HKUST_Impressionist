#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "HeartBrush.h"

#include <math.h>

#include <iostream>
using namespace std;

extern float frand();

HeartBrush::HeartBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void HeartBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void HeartBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("HeartBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize(); // get brush size

	glPushMatrix();
	glTranslatef(target.x, target.y, 0); // move (0, 0) to the tip of mouse cursor

	// the implementation is flawed, need to be changed later
	glBegin(GL_POLYGON);
	SetColor(source);
	for (float x = -1.139; x <= 1.139; x += 0.001) {
		float delta = cbrt(x*x) * cbrt(x*x) - 4 * x*x + 4;
		float y1 = (cbrt(x*x) + sqrt(delta)) / 2;
		float y2 = (cbrt(x*x) - sqrt(delta)) / 2;
		glVertex2f(x * size, y1 * size);
		glVertex2f(x * size, y2 * size);
	}

	glEnd();

	glPopMatrix();
	glFlush();
}

void HeartBrush::BrushEnd(const Point source, const Point target) {}
