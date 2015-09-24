//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

class ImpressionistDoc;

class PaintView : public Fl_Gl_Window
{
public:
	PaintView(int x, int y, int w, int h, const char* l);

	void initSetup();
	void draw();
	void displayBackground();
	void autoDraw(int spacing, bool randomSize);
	int handle(int event);

	void mouseMove(Point coord);

	void refresh();
	void resizeWindow(int width, int height);

	void SaveCurrentContent();
	void savePreviousStrokes();
	void RestoreContent();

	ImpressionistDoc *m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	ImpBrush* rightClickDirectionLine;
	Point firstCoord;

	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nStartRow, 
			m_nEndRow,
			m_nStartCol, 
			m_nEndCol,
			m_nWindowWidth, 
			m_nWindowHeight;

};

#endif