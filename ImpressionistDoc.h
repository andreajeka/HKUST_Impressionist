// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include "loadpng.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	void	loadDissolveImage(char *iname);
	int		loadEdgeImage(char *iname);
	int		loadMuralImage(char *iname);
	void	loadAlphaMappedBrush(char *iname);
	void	loadLuminanceBrush(char *iname);
	int		loadGradientImage(char *iname);
	bool	hasGradientImage();
	int		saveImage(char *iname);			// called by the UI to save image

	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	doConvolution(float **kernel, int kernelSize);
	void	changeBackgroundBrightness(int alpha);
	void	undo();							// called by UI to undo changes
	void	setBrushType(int type);			// called by the UI to set the brushType
	int		getSize();						// get the size of the brush
	void	setSize(int size);				// set the size of the brush
	int		getLineWidth();
	void	setLineWidth(int width);
	int		getLineAngle();
	void	setLineAngle(int angle);
	float	getAlpha();
	void	setAlpha(float value);
	bool	autoEdgeClippingIsOn();
	bool	manEdgeClippingIsOn();
	bool	sizeRandIsOn();
	int		getSpacing();
	void	setSpacing(int value);
	int		getEdgeThreshold();
	void	setEdgeThreshold(int value);
	char*	getImageName();					// get the current image name

	void	displayOrigImg();
	void	displayEdgeImg();
	void	swapCanvas();
	

// Attributes
public:
	// Dimensions of original window. (dimension of the image??)
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps 
	unsigned char*	m_ucBitmap;
	unsigned char*  m_ucBitmapBackup;
	unsigned char*	m_ucGradientBitmap;
	unsigned char*	m_ucPainting;
	unsigned char*  m_ucPreviousPainting;
	unsigned char*  m_ucAlphaMappedBrush;
	unsigned char*  m_ucLuminanceBrush;
	unsigned char*  m_ucEdge;
	unsigned char*  m_ucLoadedEdge;
	unsigned char*  m_ucBackground;
	unsigned char*  m_ucDissolveImage;

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
	// Get the color of the picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y ); 
	GLubyte* GetOriginalPaintingPixel(int x, int y);
	GLubyte* GetOriginalPixel( const Point p );  
	GLubyte* GetGradientPixel( int x, int y );

	int GetGradientOfX_DiffImg(const Point source);
	int GetGradientOfY_DiffImg(const Point source);
	int GetPixelIntensity_DiffImg(int x, int y);

	int			GetGradientOfX(const Point source);
	int			GetGradientOfY(const Point source);
	int			GetPixelIntensity(int x, int y);
	GLboolean	isEdgePixel(int x, int y);
	void		GenerateEdgeDetectedImg(int threshold);
	void		ReferToLoadedEdgeImg();

private:
	char			m_imageName[256];
	void resize(unsigned char* input, unsigned char* output, int sourceWidth, int sourceHeight, int targetWidth, int targetHeight);
};

extern void MessageBox(char *message);

#endif
