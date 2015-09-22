// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>
#include <iostream>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Inherit from ImpBrush
#include "PointBrush.h"
#include "LineBrush.h"
#include "CircleBrush.h"
#include "TriangleBrush.h"
#include "HeartBrush.h"

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

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucEdge		= NULL;
	m_ucPreviousPainting = NULL;
	m_ucAlphaMappedBrush = NULL;

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
	m_pUI->m_EdgeClippingButton->deactivate();
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
	m_pUI->m_EdgeClippingButton->deactivate();
	m_pUI->m_AnotherGradientButton->deactivate();

	if (type == BRUSH_LINES || type == BRUSH_SCATTERED_LINES) {
		m_pUI->m_StrokeDirectionTypeChoice->activate();
		m_pUI->m_LineWidthSlider->activate();
		m_pUI->m_LineAngleSlider->activate();
		m_pUI->m_EdgeClippingButton->activate();
		m_pUI->m_AnotherGradientButton->activate();
	}
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
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

//-------------------------------------------------
// Set the brush alpha value
//-------------------------------------------------
void ImpressionistDoc::clipEdge()
{
	//
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

	m_ucBitmap		= data;

	m_ucEdge		= new GLubyte[3 * width * height];

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	// allocate space for storing previous image
	m_ucPreviousPainting = new unsigned char[width*height * 3];
	memset(m_ucPreviousPainting, 0, width*height * 3);

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
	if (error) printf("error %u: %s\n", error, lodepng_error_text(error));
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

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
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
