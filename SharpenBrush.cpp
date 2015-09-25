//
// SharpenBrush.cpp
//
// The implementation of Sharpen Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <algorithm>
#include "SharpenBrush.h"

extern float frand();

SharpenBrush::SharpenBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void SharpenBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	BrushMove(source, target);
}

void SharpenBrush::SetColor(const Point source) {

	// Option 1 : With Convolution
	// Tested, has a better result than w/o convolution
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	GLdouble SharpenKernel[25] =
	{
		-1, -1, -1, -1, -1,
		-1, 2, 2, 2, -1,
		-1, 2, 8, 2, -1,
		-1, 2, 2, 2, -1,
		-1, -1, -1, -1, -1,
	};

	GLfloat red = 0.0;
	GLfloat green = 0.0;
	GLfloat blue = 0.0;
	int index = 0;
	GLubyte tempColor[3];
	GLubyte color[3];

	GLfloat color1[3];
	GLfloat tempColor1[3];


	for (int k = -2; k <= 2; k += 1) {
		for (int l = -2; l <= 2; l += 1) {
			memcpy(tempColor, pDoc->GetOriginalPixel(source.x + k, source.y + l), 3);
			// We strictly need to convert to float!!!
			// I spent a lot of time finding the solution
			for (int n = 0; n < 3; n++)
			{
				tempColor1[n] = (float)tempColor[n];
			}

			red += tempColor1[0] * SharpenKernel[index];
			green += tempColor1[1] * SharpenKernel[index];
			blue += tempColor1[2] * SharpenKernel[index];
			++index;
		}
	}

	double factor = 1.0 / 8.0;
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

	// Option 2 : Without Convolution
	//// IMPLEMENTATION OF SHARPENING
	//// We just multiply the center value by a large amount
	//// instead of multiplying to a kernel.

	//ImpressionistDoc* pDoc = GetDocument();
	//ImpressionistUI* dlg = pDoc->m_pUI;

	//GLfloat  red = 0;
	//GLfloat  green = 0;
	//GLfloat  blue = 0;
	//
	//GLubyte tempColorRGB[3]; 
	//GLubyte colorResult[3];

	//GLfloat tempColorRGB1[3];
	//GLfloat tempColorHSV[3];
	//GLfloat colorHSV1[3];
	//GLfloat colorHSV2[3];
	//GLfloat colorHSVMid[3];
	//GLfloat colorRGB[3];

	//// Extract the middle part of the window 
	//// (it's the star when it comes to sharpening)
	//memcpy(tempColorRGB, pDoc->GetOriginalPixel(source.x, source.y), 3);
	//
	//// We strictly need to convert to float!!!
	//// I spent a lot of time finding the solution
	//for (int n = 0; n < 3; n++)
	//{
	//	tempColorRGB1[n] = (float)tempColorRGB[n];
	//}

	//// Convert RGB to HSV
	//pDoc->RGBtoHSV(tempColorRGB1, colorHSVMid);

	//for (int k = -1; k <= 1; k++) {
	//	for (int l = -1; l <= 1; l++) {
	//		memcpy(tempColorRGB, pDoc->GetOriginalPixel(source.x + l, source.y + k), 3);

	//		// We strictly need to convert to float!!!
	//		// I spent a lot of time finding the solution
	//		for (int n = 0; n < 3; n++)
	//		{
	//			tempColorRGB1[n] = (float)tempColorRGB[n];
	//		}
	//		
	//		//Convert RGB to HSV
	//		pDoc->RGBtoHSV(tempColorRGB1, tempColorHSV);

	//		// For channel saturation and value, get all the sum
	//		// EXCEPT the middle part.
	//		if (k == 0 && l == 0)
	//			continue;

	//		if (k == -1 && l == -1) {
	//			colorHSV2[1] = tempColorHSV[1];
	//			colorHSV2[2] = tempColorHSV[2];
	//			continue;
	//		}
	//
	//		colorHSV2[1] += tempColorHSV[1];
	//		colorHSV2[2] += tempColorHSV[2];
	//	}
	//}

	//// Sharpening is done here
	//for (int m = 1; m <= 2; m++) {
	//	colorHSV1[m] = colorHSVMid[m] + (8 * colorHSVMid[m] - colorHSV2[m]) / 4.0;
	//	// If saturation is >= 1, truncate to 1;
	//	if (m == 1 && colorHSV1[m] >= 1) colorHSV1[m] = 1;
	//}

	//// Hue doesn't change (the color)
	//colorHSV1[0] = colorHSVMid[0];
	//if (colorHSV1[1] >= 1) colorHSV1[1] = 1;

	//pDoc->HSVtoRGB(colorHSV1, colorRGB);

	//// Change to GLubyte before setting color to brush
	//colorResult[0] = (GLubyte)colorRGB[0];
	//colorResult[1] = (GLubyte)colorRGB[1];
	//colorResult[2] = (GLubyte)colorRGB[2];

	//glColor3ubv(colorResult);

}

void SharpenBrush::BrushMove(const Point source, const Point target)
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

void SharpenBrush::BrushEnd(const Point source, const Point target)
{
}

