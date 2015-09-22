#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleStarBrush.h"
#include <math.h>

extern float frand();

CircleStarBrush::CircleStarBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void CircleStarBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void CircleStarBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleStarBrush::BrushMove  document is NULL\n");
		return;
	}

	int brushSize = pDoc->getSize();
	float alphaValue = pDoc->getAlpha();

	glPushMatrix();
	glTranslatef(target.x, target.y, 0); // move (0, 0) to the tip of mouse cursor
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(20);

	glBegin(GL_LINE_LOOP);
	SetColor(source, alphaValue);
	for (int i = 0; i < 360; i++) {
		float theta = 2.0f * M_PI * float(i) / float(360); // get the current angle 
		float x = cosf(theta) * brushSize * 3; // calculate the x component 
		float y = sinf(theta) * brushSize * 3; // calculate the y component 

		glVertex2f(x, y); // output vertex 
	}
	glEnd();

	float scale = brushSize * 5 / 2;

	// draw polygon inside
	glBegin(GL_POLYGON);
	for (int i = 0; i < 5; i++) {
		double angle = i * 2 * M_PI / 5;
		glVertex2d(cos(angle) / 2 * scale, sin(angle) / 2 * scale);
	}
	glEnd();

	for (int i = 0; i < 5; i++) {
		glBegin(GL_TRIANGLES);
		double a = i * 2 * M_PI / 5;
		double b = (i + 1) * 2 * M_PI / 5;
		double c = (i * 2 + 1) * M_PI / 5;
		glVertex2d(cos(a) / 2 * scale, sin(a) / 2 * scale);
		glVertex2d(cos(b) / 2 * scale, sin(b) / 2 * scale);
		glVertex2d(cos(c) * scale, sin(c) * scale);
		glEnd();
	}

	glPopMatrix();
}

void CircleStarBrush::BrushEnd(const Point source, const Point target)
{
}
