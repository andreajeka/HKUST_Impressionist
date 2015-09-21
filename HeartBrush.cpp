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
	SetColor(source);

	glBegin(GL_POLYGON);
	
	for (int i = -20; i < 180; i++) {
		float theta = 2.0f * M_PI * float(i) / float(360); // get the current angle 
		float x = cosf(theta) * size / 2 + size / 2; // calculate the x component 
		float y = sinf(theta) * size / 2; // calculate the y component 

		glVertex2f(x, y); // output vertex 
	}

	for (int i = 0; i < 200; i++) {
		float theta = 2.0f * M_PI * float(i) / float(360); // get the current angle 
		float x = cosf(theta) * size / 2 - size / 2; // calculate the x component 
		float y = sinf(theta) * size / 2; // calculate the y component 

		glVertex2f(x, y); // output vertex 
	}

	glVertex2f(0, -size / 3 * 4); // output vertex 

	glEnd();

	glPopMatrix();
	glFlush();
}

void HeartBrush::BrushEnd(const Point source, const Point target) {}
