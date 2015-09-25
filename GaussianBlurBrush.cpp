//
// GaussianBlurBrush.cpp
//
// The implementation of Gaussian Blur Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "GaussianBlurBrush.h"

extern float frand();

GaussianBlurBrush::GaussianBlurBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void GaussianBlurBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	BrushMove(source, target);
}

void GaussianBlurBrush::SetColor(const Point source) {

	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	GLdouble GaussianKernel[9] =
	{	0.0625, 0.125, 0.0625,
		0.125, 0.25, 0.125,
		0.0625, 0.125, 0.0625,
	};

	GLfloat red = 0.0;
	GLfloat green = 0.0;
	GLfloat blue = 0.0;
	int index = 0;
	GLubyte tempColor[3];
	GLubyte color[3];

	GLfloat color1[3];
	GLfloat tempColor1[3];


	for (int k = -1; k <= 1; k += 1) {
		for (int l = -1; l <= 1; l += 1) {
			memcpy(tempColor, pDoc->GetOriginalPixel(source.x + k, source.y + l), 3);
			// We strictly need to convert to float!!!
			// I spent a lot of time finding the solution
			for (int n = 0; n < 3; n++)
			{
				tempColor1[n] = (float)tempColor[n];
			}

			red += tempColor1[0] * GaussianKernel[index];
			green += tempColor1[1] * GaussianKernel[index];
			blue += tempColor1[2] * GaussianKernel[index];
			++index;
		}
	}

	if (red > 255) red = 255;
	if (green > 255) green = 255;
	if (blue > 255) blue = 255;
	if (red < 0) red = 0;
	if (green < 0) green = 0;
	if (blue < 0) blue = 0;

	color1[0] = red;
	color1[1] = green;
	color1[2] = blue;

	// Change to GLubyte before setting color to brush
	color[0] = (GLubyte)color1[0];
	color[1] = (GLubyte)color1[1];
	color[2] = (GLubyte)color1[2];

	glColor3ubv(color);
}

void GaussianBlurBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	// Set to one, we want to get color per pixel
	glPointSize(1.0);

	glBegin(GL_POINTS);

	for (int i = -size / 2; i <= size / 2; i++) {
		for (int j = -size / 2; j <= size / 2; j++) {
			SetColor(Point(source.x + i, source.y + j));
			glVertex2d(target.x + i, target.y + j);
		}
	}

	glEnd();
}

void GaussianBlurBrush::BrushEnd(const Point source, const Point target)
{
}

