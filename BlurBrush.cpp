//
// BlurBrush.cpp
//
// The implementation of Blur Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "BlurBrush.h"

extern float frand();

BlurBrush::BlurBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void BlurBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	glPointSize((float)size);
	BrushMove(source, target);
}

void BlurBrush::SetColor(const Point source) {
	
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	//// 3x3 kernel
	//GLdouble WeightedMeanKernel[9] =
	//{ 1 / 9, 1 / 9, 1 / 9,
	//1 / 9, 1 / 9, 1 / 9,
	//1 / 9, 1 / 9, 1 / 9,
	//};

	/*int red = 0;
	int green = 0;
	int blue = 0;
	int index = 0;
	GLubyte tempColor[3];
	GLubyte color[3];

	GLdouble GaussianKernel[9] =
	{	0.0625, 0.125, 0.0625,
		0.125, 0.25, 0.125,
		0.0625, 0.125, 0.0625,
	};


	for (int k = -1; k <= 1; k++) {
		for (int l = -1; l <= 1; l++) {
			memcpy(tempColor, pDoc->GetOriginalPixel(source.x + l, source.y + k), 3);
			red += tempColor[0] * GaussianKernel[index];
			green += tempColor[1] * GaussianKernel[index];
			blue += tempColor[2] * GaussianKernel[index];
			index++;
		}
	}

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	glColor3ubv(color);*/

	// Use int instead of GLubyte. 
	// Now the following code of lines work!!! :)
	int red;
	int green;
	int blue;
	GLubyte color[3];
	GLubyte tempColor[3];
	int atX = 0;
	int atY = 0;

	// Get a large window
	for (int k = -20; k <= 20; k += 10) {
		for (int l = -20; l <= 20; l += 10) {
			atX = source.x + l;
			atY = source.y + k;
			// Use painting pixel because we are blurring on the painting 
			// not according to the original paint
			memcpy(tempColor, pDoc->GetOriginalPaintingPixel(atX, atY), 3);
			// First run
			if (l == -20 && k == -20) {
				red = tempColor[0];
				green = tempColor[1];
				blue = tempColor[2];
			}
			else {
				red += tempColor[0];
				green += tempColor[1];
				blue += tempColor[2];
			}
		}
	}

	// Use simple mean filtering
	color[0] = red / 25;
	color[1] = green / 25;
	color[2] = blue / 25;
	glColor3ubv(color);

}

void BlurBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	
	glBegin(GL_POINTS);
		SetColor(source);
		glVertex2d(target.x, target.y);

	glEnd();
}

void BlurBrush::BrushEnd(const Point source, const Point target)
{
}

