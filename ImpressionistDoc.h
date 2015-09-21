// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image

	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	int		getSize();						// get the size of the brush
	void	setSize(int size);				// set the size of the brush
	int		getLineWidth();
	void	setLineWidth(int width);
	int		getLineAngle();
	void	setLineAngle(int angle);
	float	getAlpha();
	void	setAlpha(float value);
	void	clipEdge();
	int		getSpacing();
	void	setSpacing(int value);
	int		getEdgeThreshold();
	void	setEdgeThreshold(int value);
	char*	getImageName();					// get the current image name

	void	displayOrigImg();
	void	displayEdgeImg();
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;

	// Bitmaps for edge image
	unsigned char* m_ucEdge;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	

	// Size of the brush.
	int		m_nSize;	
	int		m_nLineWidth;
	int		m_nLineAngle;
	float	m_nAlpha;
	int		m_nSpacing;
	int		m_nEdgeThreshold;

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  

	int GetGradientOfX(const Point source);
	int GetGradientOfY(const Point source);
	int GetPixelIntensity(int x, int y);
	void GenerateEdgeDetectedImg(int threshold);

private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
