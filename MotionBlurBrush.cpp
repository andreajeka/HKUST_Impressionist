//
// MotionBlurBrush.cpp
//
// The implementation of Motion Blur Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "MotionBlurBrush.h"

extern float frand();

MotionBlurBrush::MotionBlurBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void MotionBlurBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	BrushMove(source, target);
}

void MotionBlurBrush::SetColor(const Point source) {

	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	GLdouble MotionBlur[81] =
	{
		1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1,
	};

	GLfloat red = 0.0;
	GLfloat green = 0.0;
	GLfloat blue = 0.0;
	int index = 0;
	GLubyte tempColor[3];
	GLubyte color[3];

	GLfloat color1[3];
	GLfloat tempColor1[3];


	for (int k = -4; k <= 4; k += 1) {
		for (int l = -4; l <= 4; l += 1) {
			memcpy(tempColor, pDoc->GetOriginalPixel(source.x + k, source.y + l), 3);
			// We strictly need to convert to float!!!
			// I spent a lot of time finding the solution
			for (int n = 0; n < 3; n++)
			{
				tempColor1[n] = (float)tempColor[n];
			}

			red += tempColor1[0] * MotionBlur[index];
			green += tempColor1[1] * MotionBlur[index];
			blue += tempColor1[2] * MotionBlur[index];
			++index;
		}
	}

	double factor = 1.0 / 9.0;
	double bias = 0.0;

	red = min(max(int(factor * red + bias), 0), 255);
	green = min(max(int(factor * green + bias), 0), 255);
	blue = min(max(int(factor * blue + bias), 0), 255);

	color1[0] = red;
	color1[1] = green;
	color1[2] = blue;

	// Change to GLubyte before setting color to brush
	color[0] = (GLubyte)color1[0];
	color[1] = (GLubyte)color1[1];
	color[2] = (GLubyte)color1[2];

	glColor3ubv(color);
}

void MotionBlurBrush::BrushMove(const Point source, const Point target)
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

void MotionBlurBrush::BrushEnd(const Point source, const Point target)
{
}

