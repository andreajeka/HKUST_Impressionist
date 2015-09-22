#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "TriangleBrush.h"

#include <math.h>

extern float frand();

TriangleBrush::TriangleBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void TriangleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("TriangleBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize(); // get brush size
	float alphaValue = pDoc->getAlpha();

	glPushMatrix();
	glTranslatef(target.x, target.y, 0); // move (0, 0) to the tip of mouse cursor

	glBegin(GL_POLYGON);

	SetColor(source, alphaValue);
	for (int i = 0; i < 3; i++) {
		float theta = -M_PI / 6 + 2.0f * M_PI * float(i) / float(3); // get the current angle (start from -30 degree)
		float x = cosf(theta) * size / 2; // calculate the x component 
		float y = sinf(theta) * size / 2; // calculate the y component 

		glVertex2f(x, y); // output vertex 
	}

	glEnd();

	glPopMatrix();
}

void TriangleBrush::BrushEnd(const Point source, const Point target) {}
