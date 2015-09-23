#ifndef CONVOLUTIONWINDOW_h
#define CONVOLUTIONWINDOW_h

#include "impressionistDoc.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <Fl/Fl_Float_Input.H>

class ConvolutionWindow {
public:
	ConvolutionWindow();
	~ConvolutionWindow();
	void show(ImpressionistDoc* doc, int size);
	static void cb_do(Fl_Widget* o, void* v);

private:
	int kernelSize;
	float** kernel;
	ImpressionistDoc* m_pDoc;

	Fl_Window* m_convolutionWindow;
	Fl_Button* m_OKButton;
	Fl_Light_Button* m_NormaliseButton;
	Fl_Float_Input*** m_KernelInput;
};

#endif