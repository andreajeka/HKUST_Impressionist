//
// WithoutConvBlurBrush.cpp
//
// The implementation of Without Convolution Blur Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "WithoutConvBlurBrush.h"

extern float frand();

WithoutConvBlurBrush::WithoutConvBlurBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void WithoutConvBlurBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	BrushMove(source, target);
}

void WithoutConvBlurBrush::SetColor(const Point source) {
	
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	 //Use int instead of GLubyte. 
	 //Now the following code of lines work!!! :)
	int red;
	int green;
	int blue;
	GLubyte color[3];
	GLubyte tempColor[3];
	int atX = 0;
	int atY = 0;

	// Get a large window
	for (int k = -20; k <= 20; k += 5) {
		for (int l = -20; l <= 20; l += 5) {
			atX = source.x + l;
			atY = source.y + k;
			// Use painting pixel because we are blurring on the painting 
			// not according to the original paint
			memcpy(tempColor, pDoc->GetOriginalPixel(atX, atY), 3);
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
	color[0] = red / 100;
	color[1] = green / 100;
	color[2] = blue / 100;
	glColor3ubv(color);

}

void WithoutConvBlurBrush::BrushMove(const Point source, const Point target)
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

		for (int i = -size/2; i <= size/2; i++) {
			for (int j = -size/2; j <= size/2; j++) {
				SetColor(Point(source.x + i, source.y + j));
				glVertex2d(target.x + i, target.y + j);	
			}
		}

	glEnd();
}

void WithoutConvBlurBrush::BrushEnd(const Point source, const Point target)
{
}

