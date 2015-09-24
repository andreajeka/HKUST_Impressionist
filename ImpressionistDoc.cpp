// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>
#include <iostream>
#include <algorithm>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Inherit from ImpBrush
#include "PointBrush.h"
#include "LineBrush.h"
#include "CircleBrush.h"
#include "TriangleBrush.h"
#include "HeartBrush.h"
#include "CircleStarBrush.h"
#include "AlphaMappedBrush.h"
#include "BlurBrush.h"
#include "LuminanceBrush.h"

// Inherit from PointBrush
#include "ScatteredPointBrush.h"

// Inherit from CircleBrush
#include "ScatteredCircleBrush.h"

// Inherit from LineBrush
#include "ScatteredLineBrush.h"

#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth				= -1;
	m_ucBitmap				= NULL;
	m_ucBitmapBackup		= NULL;
	m_ucPainting			= NULL;
	m_ucEdge				= NULL;
	m_ucLoadedEdge			= NULL;
	m_ucPreviousPainting	= NULL;
	m_ucAlphaMappedBrush	= NULL;
	m_ucGradientBitmap		= NULL;
	m_ucBackground			= NULL;
	m_ucDissolveImage		= NULL;

	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]				= new PointBrush( this, "Points" );
	ImpBrush::c_pBrushes[BRUSH_LINES]				= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		= new ScatteredLineBrush(this, "Scattered Lines");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	= new ScatteredCircleBrush(this, "Scattered Circles");
	ImpBrush::c_pBrushes[TRIANGLE]					= new TriangleBrush(this, "Triangle");
	ImpBrush::c_pBrushes[HEART]						= new HeartBrush(this, "Heart");
	ImpBrush::c_pBrushes[CIRCLESTAR]				= new CircleStarBrush(this, "Circle Star");
	ImpBrush::c_pBrushes[ALPHAMAPPED]				= new AlphaMappedBrush(this, "Alpha-mapped");
	ImpBrush::c_pBrushes[BLUR]						= new BlurBrush(this, "Blur");
	ImpBrush::c_pBrushes[LUMINANCE]					= new LuminanceBrush(this, "Luminance");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;

	// Deactivate some attrs at start-up
	m_pUI->m_StrokeDirectionTypeChoice->deactivate();
	m_pUI->m_LineWidthSlider->deactivate();
	m_pUI->m_LineAngleSlider->deactivate();
	m_pUI->m_AutoEdgeClippingButton->deactivate();
	m_pUI->m_ManEdgeClippingButton->deactivate();
	m_pUI->m_AnotherGradientButton->deactivate();
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];

	m_pUI->m_StrokeDirectionTypeChoice->deactivate();
	m_pUI->m_LineWidthSlider->deactivate();
	m_pUI->m_LineAngleSlider->deactivate();
	m_pUI->m_AutoEdgeClippingButton->deactivate();
	m_pUI->m_ManEdgeClippingButton->deactivate();
	m_pUI->m_AnotherGradientButton->deactivate();

	if (type == BRUSH_LINES || type == BRUSH_SCATTERED_LINES) {
		m_pUI->m_StrokeDirectionTypeChoice->activate();
		m_pUI->m_LineWidthSlider->activate();
		m_pUI->m_LineAngleSlider->activate();
		m_pUI->m_AutoEdgeClippingButton->activate();
		m_pUI->m_ManEdgeClippingButton->activate();
		m_pUI->m_AnotherGradientButton->activate();
	}
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	int size = m_pUI->getSize();
	if (m_pUI->sizeRandIsOn()) {
		// Get better size randomization
		int randomSize = (size - 5) + (rand() % (int)(size - (size - 5) + 1));
		printf("Random num is = %d", randomSize);
		return randomSize;
	}
	else return size;
	
}

//------------------------------------------------
// Return the brush line width
//------------------------------------------------
int ImpressionistDoc::getLineWidth()
{
	return m_pUI->getLineWidth();
}

//-------------------------------------------------
// Set the brush line width
//-------------------------------------------------
void ImpressionistDoc::setLineWidth(int width)
{
	m_pUI->setLineWidth(width);
}

//------------------------------------------------
// Return the brush line angle
//------------------------------------------------
int ImpressionistDoc::getLineAngle()
{
	return m_pUI->getLineAngle();
}

//-------------------------------------------------
// Set the brush line angle
//-------------------------------------------------
void ImpressionistDoc::setLineAngle(int angle)
{
	m_pUI->setLineAngle(angle);
}

//------------------------------------------------
// Return the brush alpha value
//------------------------------------------------
float ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}

//-------------------------------------------------
// Set the brush alpha value
//-------------------------------------------------
void ImpressionistDoc::setAlpha(float value)
{
	m_pUI->setAlpha(value);
}

//--------------------------------------------------
// Return the state of the auto edge clipping button
//--------------------------------------------------
bool ImpressionistDoc::autoEdgeClippingIsOn()
{
	return m_pUI->autoEdgeClippingIsOn();
}

//----------------------------------------------------
// Return the state of the manual edge clipping button
//----------------------------------------------------
bool ImpressionistDoc::manEdgeClippingIsOn()
{
	return m_pUI->manEdgeClippingIsOn();
}

//----------------------------------------------------
// Return the state of the size rand. button
//----------------------------------------------------
bool ImpressionistDoc::sizeRandIsOn()
{
	return m_pUI->sizeRandIsOn();
}


//------------------------------------------------
// Return the spacing value
//------------------------------------------------
int ImpressionistDoc::getSpacing()
{
	return m_pUI->getSpacing();
}

//-------------------------------------------------
// Set the spacing value
//-------------------------------------------------
void ImpressionistDoc::setSpacing(int value)
{
	m_pUI->setSpacing(value);
}

//------------------------------------------------
// Return the edge threshold value
//------------------------------------------------
int ImpressionistDoc::getEdgeThreshold()
{
	return m_pUI->getEdgeThreshold();
}

//-------------------------------------------------
// Set the edge threshold value
//-------------------------------------------------
void ImpressionistDoc::setEdgeThreshold(int value)
{
	m_pUI->setEdgeThreshold(value);
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}	

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;
	if ( m_ucEdge ) delete[] m_ucEdge;
	if ( m_ucPreviousPainting ) delete[] m_ucPreviousPainting;
	if ( m_ucBitmapBackup ) delete[] m_ucBitmapBackup;
	if ( m_ucBackground ) delete[] m_ucBackground;
	if ( m_ucDissolveImage ) delete[] m_ucDissolveImage;

	m_ucBitmap		= data;

	m_ucEdge		= new GLubyte[3 * width * height];

	// allocate space for dissolve image
	m_ucDissolveImage = new unsigned char[width*height * 3];

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	// allocate space for storing previous image
	m_ucPreviousPainting = new unsigned char[width*height * 3];
	memset(m_ucPreviousPainting, 0, width*height * 3);

	// allocate space for backup
	m_ucBitmapBackup = new unsigned char[width*height * 3];
	memcpy(m_ucBitmapBackup, m_ucBitmap, width*height * 3);

	// allocate space for background in paint view
	m_ucBackground = new unsigned char[width*height * 4];
	memset(m_ucBackground, 0, width*height * 4);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();

	return 1;
}

void ImpressionistDoc::loadDissolveImage(char *iname) {
	unsigned char* data;
	int width, height;

	if ((data = readBMP(iname, width, height)) == NULL) {
		fl_alert("Can't load bitmap file");
	}

	// resize and load data to dissolve
	resize(data, m_ucDissolveImage, width, height, m_nWidth, m_nHeight);

	delete[]data;
}

//---------------------------------------------------------
// Load the specified brush image
// This is called by the UI when the load alpha brush button 
// is pressed.
//---------------------------------------------------------
void ImpressionistDoc::loadAlphaMappedBrush(char *iname)
{
	unsigned error;
	unsigned width, height;

	if (m_ucAlphaMappedBrush) delete[] m_ucAlphaMappedBrush;

	error = lodepng_decode32_file(&m_ucAlphaMappedBrush, &width, &height, iname);
	if (error) fl_alert("error %u: %s\n", error, lodepng_error_text(error));

	// init alpha brush
	AlphaMappedBrush* a = dynamic_cast<AlphaMappedBrush*>(ImpBrush::c_pBrushes[ALPHAMAPPED]);
	a->setWidth(width);
	a->setHeight(height);
}

//---------------------------------------------------------
// Load a luminance brush
//---------------------------------------------------------
void ImpressionistDoc::loadLuminanceBrush(char *iname)
{
	unsigned char* data;
	int width, height;

	if ((data = readBMP(iname, width, height)) == NULL) {
		fl_alert("Can't load bitmap file");
	}

	m_ucLuminanceBrush = data;
	
	// init alpha brush
	LuminanceBrush* a = dynamic_cast<LuminanceBrush*>(ImpBrush::c_pBrushes[LUMINANCE]);
	a->setWidth(width);
	a->setHeight(height);
}

//---------------------------------------------------------
// Load the specified edge image
// This is called by the UI when the load edge image button 
// is pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadEdgeImage(char *iname)
{
	unsigned char* data;
	int width, height;

	if ((data = readBMP(iname, width, height)) == NULL) {
		fl_alert("Can't load bitmap file");
		return 0;
	}

	if (width != m_nWidth || height != m_nHeight) {
		fl_alert("Image size differs from the original image");
		delete[] data;
		return 0;
	}

	m_ucLoadedEdge = data;

	return 1;
}

//---------------------------------------------------------
// Load the specified mural image
// This is called by the UI when the load mural image button 
// is pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadMuralImage(char *iname)
{
	unsigned char* data;
	int width, height;

	if ((data = readBMP(iname, width, height)) == NULL) {
		fl_alert("Can't load bitmap file");
		return 0;
	}

	if (!m_ucBitmap) {
		fl_alert("Add an original one first!");
		return 0;
	}

	if (width > m_nWidth || height > m_nHeight) {
		fl_alert("Image size has to be smaller or equals to original image!");
		delete[] data;
		return 0;
	}

	// Get the difference of the image in original view to the loaded mural image
	int dimDiffX= (m_nWidth - width) / 2; 
	int dimDiffY = (m_nHeight - height) / 2;

	// Replace the pixels in the original view with the smaller dimension of loaded mural image
	for (int i = 0; i < height; i++) {
		memcpy(m_ucBitmap + ((dimDiffX + i) * m_nWidth + dimDiffY) * 3, data + i * 3 * width, 3 * width);
	}

	m_pUI->m_origView->refresh();

	return 1;
}

//---------------------------------------------------------
// Load the specified brush image
// This is called by the UI when the load alpha brush button 
// is pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadGradientImage(char *iname)
{
	// try to open the image to read
	unsigned char* data;
	int width, height;

	if ((data = readBMP(iname, width, height)) == NULL) {
		fl_alert("Can't load bitmap file");
		return 0;
	}
	if (width != m_nWidth || height != m_nHeight) {
		fl_alert("Image size differs from the original image");
		delete[] data;
		return 0;
	}

	m_ucGradientBitmap = data;

	return 1;
}

bool ImpressionistDoc::hasGradientImage() {
	return (m_ucGradientBitmap != NULL);
}

//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

void ImpressionistDoc::doConvolution(float **kernel, int kernelSize) {
	for (int x = 0; x < m_nWidth; x++)
	for (int y = 0; y < m_nHeight; y++)
	{
		double red = 0.0, green = 0.0, blue = 0.0;

		//multiply every value of the filter with corresponding image pixel 
		for (int filterX = 0; filterX < kernelSize; filterX++)
		for (int filterY = 0; filterY < kernelSize; filterY++)
		{
			int imageX = (x - 3 / 2 + filterX + m_nWidth) % m_nWidth;
			int imageY = (y - 3 / 2 + filterY + m_nHeight) % m_nHeight;
			red += m_ucBitmapBackup[imageY * m_nWidth * 3 + imageX * 3] * kernel[filterX][filterY];
			green += m_ucBitmapBackup[imageY * m_nWidth * 3 + imageX * 3 + 1] * kernel[filterX][filterY];
			blue += m_ucBitmapBackup[imageY * m_nWidth * 3 + imageX * 3 + 2] * kernel[filterX][filterY];
		}

		//truncate values smaller than zero and larger than 255 
		m_ucBitmap[y * m_nWidth * 3 + x * 3] = min(max(int(red), 0), 255);
		m_ucBitmap[y * m_nWidth * 3 + x * 3 + 1] = min(max(int(green), 0), 255);
		m_ucBitmap[y * m_nWidth * 3 + x * 3 + 2] = min(max(int(blue), 0), 255);
	}

	m_pUI->m_origView->refresh();
}

void ImpressionistDoc::changeBackgroundBrightness(int alpha) {
	for (int i = 0; i < this->m_nPaintHeight; i++) {
		for (int j = 0; j < this->m_nPaintWidth; j++) {
			int k = i * m_nPaintWidth + j;
			memcpy(m_ucBackground + 4 * k, m_ucBitmap + 3 * k, 3);
			m_ucBackground[4 * k + 3] = alpha;
		}
	}
}

void ImpressionistDoc::undo() {
	memcpy(m_ucPainting, m_ucPreviousPainting, m_nPaintWidth * m_nPaintHeight * 3);
	m_pUI->m_paintView->redraw();
}

//----------------------------------------------------------------
// Display the original image
// This is called by the UI when the original image menu item 
// is chosen 
//-----------------------------------------------------------------
void ImpressionistDoc::displayOrigImg()
{
	m_pUI->m_origView->setDisplayType(ORIGINAL_IMAGE);
	m_pUI->m_origView->refresh();
}

//----------------------------------------------------------------
// Display the image filtered with edge detection
// This is called by the UI when the edge image menu item 
// is chosen 
//-----------------------------------------------------------------
void ImpressionistDoc::displayEdgeImg()
{
	GenerateEdgeDetectedImg(m_pUI->getEdgeThreshold());
	m_pUI->m_origView->setDisplayType(EDGE_IMAGE);
	m_pUI->m_origView->refresh();
}

//----------------------------------------------------------------
// 
//-----------------------------------------------------------------
void ImpressionistDoc::swapCanvas()
{
	std::swap(m_ucBitmap, m_ucPainting);
	m_pUI->m_origView->refresh();
	m_pUI->m_paintView->refresh();
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPaintingPixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nWidth)
		x = m_nWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nHeight)
		y = m_nHeight - 1;

	return (GLubyte*)(m_ucPainting + 3 * (y*m_nWidth + x));
}


//------------------------------------------------------------------
// Check whether a pixel in edge image is an edge pixel
//------------------------------------------------------------------
GLboolean ImpressionistDoc::isEdgePixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nWidth)
		x = m_nWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nHeight)
		y = m_nHeight - 1;

	if (m_ucEdge[3 * (y*m_nWidth + x)] > 0) return true;
	else return false;
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

//------------------------------------------------------------------
// I know it is to stupid to copy and paste but it is the fastest way...
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetGradientPixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nWidth)
		x = m_nWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nHeight)
		y = m_nHeight - 1;

	return (GLubyte*)(m_ucGradientBitmap + 3 * (y*m_nWidth + x));
}

int ImpressionistDoc::GetGradientOfX(const Point source)
{
	// Sobel Mask of X
	int Sx[3][3] =
	{
		{ -1, 0, 1 },
		{ -2, 0, 2 },
		{ -1, 0, 1 }

	};

	double Gx = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			Gx += Sx[i][j] * GetPixelIntensity(source.x + j - 1,
				source.y - i + 1);
		}
	}
	return (int)Gx;
}

int ImpressionistDoc::GetGradientOfY(const Point source)
{
	// Sobel Mask of Y
	int Sy[3][3] =
	{
		{ 1, 2, 1 },
		{ 0, 0, 0 },
		{ -1, -2, -1 }

	};

	double Gy = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			Gy += Sy[i][j] * GetPixelIntensity(source.x + j - 1,
				source.y - i + 1);
		}
	}
	return (int)Gy;
}

// Get pixel intensity according to human eye
int ImpressionistDoc::GetPixelIntensity(int x, int y) 
{
	unsigned char color[3];
	memcpy(color, GetOriginalPixel(x, y), 3);
	return (0.299*color[0] + 0.587*color[1] + 0.144*color[2]);
}

void ImpressionistDoc::GenerateEdgeDetectedImg(int threshold) 
{
	int combinedGradientSum = 0;
	int Gx = 0;
	int Gy = 0;
	int loc = 0;

	// Iterate each pixels in image
	for (int i = 0; i < m_nPaintWidth; i++)
	{
		for (int j = 0; j < m_nPaintHeight; j++)
		{
			// We need to use a mapped version of position
			// that represents a pixel. It is multiplied by
			// 3 because it consist of 3 channels R,G,B
			loc = (j * m_nPaintWidth + i);

			Gx = GetGradientOfX(Point(i,j));
			Gy = GetGradientOfY(Point(i,j));
			combinedGradientSum = sqrt(double(Gx*Gx) + double(Gy*Gy));

			// Set to white(255 = highest) if gradient is bigger than threshold
			if (combinedGradientSum > threshold) combinedGradientSum = 255;

			// Set to black(0 = lowest) if gradient is smaller than threshold
			if (combinedGradientSum <= threshold) combinedGradientSum = 0;

			// Because we have to set the 3 channels of RGB, that means all 
			// 3 consecutive block of m_ucEdge should be filled with the same number
			// to get either black (0,0,0) or white (255,255,255)
			m_ucEdge[3 * loc] = m_ucEdge[3 * loc + 1] = m_ucEdge[3 * loc + 2] = combinedGradientSum;
		}
	}
}

// The the following 3 functions are not good practice but we don't have time...
int ImpressionistDoc::GetGradientOfX_DiffImg(const Point source)
{
	// Sobel Mask of X
	int Sx[3][3] =
	{
		{ -1, 0, 1 },
		{ -2, 0, 2 },
		{ -1, 0, 1 }

	};

	double Gx = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			Gx += Sx[i][j] * GetPixelIntensity_DiffImg(source.x + j - 1,
				source.y - i + 1);
		}
	}
	return (int)Gx;
}

int ImpressionistDoc::GetGradientOfY_DiffImg(const Point source)
{
	// Sobel Mask of Y
	int Sy[3][3] =
	{
		{ 1, 2, 1 },
		{ 0, 0, 0 },
		{ -1, -2, -1 }

	};

	double Gy = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			Gy += Sy[i][j] * GetPixelIntensity_DiffImg(source.x + j - 1,
				source.y - i + 1);
		}
	}
	return (int)Gy;
}

int ImpressionistDoc::GetPixelIntensity_DiffImg(int x, int y)
{
	unsigned char color[3];
	memcpy(color, GetGradientPixel(x, y), 3);
	return (0.299*color[0] + 0.587*color[1] + 0.144*color[2]);
}

void ImpressionistDoc::resize(unsigned char* input, unsigned char* output, int sourceWidth, int sourceHeight, int targetWidth, int targetHeight)
{
	int x, y;
	float x_ratio = (float)(sourceWidth) / targetWidth;
	float y_ratio = (float)(sourceHeight) / targetHeight;
	float x_diff, y_diff;

	for (int i = 0; i < targetHeight; i++) {
		y = (int)(y_ratio * i);
		y_diff = (y_ratio * i) - y;

		for (int j = 0; j < targetWidth; j++) {
			x = (int)(x_ratio * j);
			x_diff = (x_ratio * j) - x;

			for (int k = 0; k < 3; k++) {
				unsigned char up = input[3 * (y * sourceWidth + x) + k] * (1 - x_diff) + input[3 * (y * sourceWidth + x + 1) + k] * (x_diff);
				unsigned char down = input[3 * ((y + 1) * sourceWidth + x) + k] * (1 - x_diff) + input[3 * ((y + 1) * sourceWidth + x + 1) + k] * (x_diff);
				output[3 * (i * targetWidth + j) + k] = up * (1 - y_diff) + down * y_diff;
			}
		}
	}
}
