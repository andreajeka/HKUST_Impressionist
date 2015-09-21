//
// originalview.h
//
// The header file for original view of the input images
//

#ifndef ORIGINALVIEW_H
#define ORIGINALVIEW_H

#include <FL/Fl.H>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include "ImpBrush.h"

enum ImageDisplayType
{
	ORIGINAL_IMAGE = 0,
	EDGE_IMAGE,
	ANOTHER_IMAGE,
};


class ImpressionistDoc;

class OriginalView : public Fl_Gl_Window
{
public:
	OriginalView(int x, int y, int w, int h, const char *l);
	
	void draw();
	void refresh();

	void resizeWindow(int width, int height);

	void drawCursor(Point source);

	ImageDisplayType getDisplayType();
	void setDisplayType(ImageDisplayType type);

	ImpressionistDoc*	m_pDoc;

private:
	int	m_nWindowWidth, 
		m_nWindowHeight;
	Point coord;

	ImageDisplayType m_nImageDisplaytype;

};

#endif