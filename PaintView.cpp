//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include "LineBrush.h"
#include "RightClickDirectionLine.h"
#include <iostream>

#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;
int angle;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}

void PaintView::initSetup()
{
#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
#endif // !MESA

	if (!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		ortho();

		glClear(GL_COLOR_BUFFER_BIT);

	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y = 0;

	// Main window width and height
	m_nWindowWidth = w();
	m_nWindowHeight = h();

	int drawWidth, drawHeight;
	drawWidth = min(m_nWindowWidth, m_pDoc->m_nPaintWidth);
	drawHeight = min(m_nWindowHeight, m_pDoc->m_nPaintHeight);

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if (startrow < 0) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth = drawWidth;
	m_nDrawHeight = drawHeight;

	m_nStartRow = startrow;
	m_nEndRow = startrow + drawHeight;
	m_nStartCol = scrollpos.x;
	m_nEndCol = m_nStartCol + drawWidth;
}

void PaintView::draw()
{
	initSetup();
	// Implement edge clipping here using stencil buffer
	// There are two steps:
	// 1. Initialize stencil buffer by setting color buffer masks to false
	//    and then setting appropriate ref value to stencil buffer by failing 
	//    the stencil test every time.
	// 2. Use the initialized stencil buffer and stencil test to write only 
	//    in the locations where stencil value is 1
	if (!valid()) {
		
		// Quick explanation: 
		// Stencil buffer gives an option to which 
		// fragments should be drawn and which shouldn't
		// more info: https://en.wikipedia.org/wiki/Stencil_buffer

		/************** Step 1 **************/
		glEnable(GL_STENCIL_TEST);

		/* Basically glStencilMask allows us to set a bitmask that is 
		   ANDed with the stencil value about to be written to the buffer */
		/*----------------------------------------------------------------*/
		// 0xFF means we set all stencil values to 1 per bit, no mask  
		glStencilMask(0xFF);
		// clear stencil buffer witih 0s
		glClear(GL_STENCIL_BUFFER_BIT);

		/* Configure Stencil Testing*/
		/* a. glStencilFunc describes what OpenGL should do
			  with the content of the stencil buffer
		/* b. glStencilOp describes how we can update
		      the stencil buffer
		/*------------------------------------------------*/
		// Force drawing to stencil by declaring stencil test function fails
		// This means we draw 1s on test fail (always)
		glStencilFunc(GL_NEVER, 1, 0xFF);
		// replace stencil buffer values to ref=1, 2nd parameter of glStencilFunc
		glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);

		// Disable all color channels so stencil buffer won't affect 
		// the content of the color buffer
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		// Draw stencil shape
		glBegin(GL_TRIANGLE_STRIP);
			// Get the vertices for the paint view 
			glVertex2f(0, m_nWindowHeight - m_nDrawHeight); // bottom left 
			glVertex2f(m_nDrawWidth, m_nWindowHeight - m_nDrawHeight); //  bottom right
			glVertex2f(0, m_nWindowHeight); // top left
			glVertex2f(m_nDrawWidth, m_nWindowHeight); // top right

		glEnd();
		
		/************** Step 2 **************/
		// Enable color
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		// no more modifying of stencil buffer on stencil
		glStencilMask(0);

		// stencil test: only pass stencil test at stencilValue less than 0 
		// and write actual content to color buffer only at stencil shape locations.
		glStencilFunc(GL_LESS, 0, 0xFF);
	}

	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{
		RestoreContent(); // restore content upon refresh
	}

	if (m_pDoc->m_ucPainting && isAnEvent)
	{
		// Clear it after processing.
		isAnEvent = 0;

		Point source(coord.x + m_nStartCol, m_nEndRow - coord.y);
		Point target(coord.x, m_nWindowHeight - coord.y);
		// This is the event handler
		switch (eventToDo)
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->m_pCurrentBrush->BrushBegin(source, target);
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentBrush->BrushMove(source, target);
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd(source, target);

			SaveCurrentContent();
			RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
			firstCoord = target;

			// Implement the right mouse stroke direction here
			rightClickDirectionLine = new RightClickDirectionLine(m_pDoc, "Right Click Direction Line");
			rightClickDirectionLine->BrushBegin(source, target);
			break;
		case RIGHT_MOUSE_DRAG:

			// We need to release the current content because 
			// each mouse drag refers to a different angle
			RestoreContent();

			rightClickDirectionLine->BrushMove(source, target);
			break;
		case RIGHT_MOUSE_UP:
			RestoreContent();

			rightClickDirectionLine->BrushEnd(source, target);
			angle = LineBrush::DetermineAngle(firstCoord, target);
			m_pDoc->setLineAngle(angle);
			delete rightClickDirectionLine;
			rightClickDirectionLine = NULL;

			break;
		default:
			printf("Unknown event!!\n");
			break;
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}

void PaintView::autoDraw(int spacing, bool randomSize) 
{
	initSetup();

	int canvasWidth = m_pDoc->m_nWidth;
	int canvasHeight = m_pDoc->m_nHeight;
		
	m_pDoc->m_pCurrentBrush->BrushBegin(Point(0, 0), Point(0, 0));

	for (int i = 0; i < canvasWidth; i += spacing) {
		for (int j = 0; j < canvasHeight; j += spacing) {
			m_pDoc->m_pCurrentBrush->BrushMove(Point(i, j), Point(i, j));
		}
	}

	m_pDoc->m_pCurrentBrush->BrushEnd(Point(canvasWidth - 1, canvasHeight - 1), 
									  Point(canvasWidth - 1, canvasHeight - 1));
	SaveCurrentContent();
	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA
}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		mouseMove(coord);
		redraw();
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		mouseMove(coord);
		break;
	default:
		return 0;
		break;

	}

	return 1;
}

void PaintView::mouseMove(Point coord) 
{
	m_nWindowHeight = h();

	int drawWidth, drawHeight;
	drawHeight = min(m_nWindowHeight, m_pDoc->m_nPaintHeight);

	int startrow = m_pDoc->m_nPaintHeight - drawHeight;
	if (startrow < 0) startrow = 0;

	m_nEndRow = startrow + drawHeight;

	Point source(coord.x, m_nEndRow - coord.y);

	m_pDoc->m_pUI->m_origView->drawCursor(source);
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );

	memcpy(m_pDoc->m_ucPreviousPainting, m_pDoc->m_ucPainting, m_nDrawWidth * m_nDrawHeight * 3);
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}

// read data from m_pPaintBitstart to frame buffer
void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK); // specify which color buffers are to be drawn into

	glClear( GL_COLOR_BUFFER_BIT ); // clear buffers to preset values

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight ); // starting point for pixel write op
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); // how to store the pixels
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, m_nDrawHeight, GL_RGB, GL_UNSIGNED_BYTE, m_pPaintBitstart); // write to frame buffer

//	glDrawBuffer(GL_FRONT);
}
