#include "ConvolutionWindow.h"

#include <FL/fl_ask.H>

#include <iostream>
using namespace std;

#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )


ConvolutionWindow::ConvolutionWindow() {
	m_convolutionWindow = NULL;
	m_OKButton = NULL;
	m_NormaliseButton = NULL;
	m_KernelInput = NULL;
	kernel = NULL;
	kernelSize = 3;
	m_pDoc = NULL;
}

void ConvolutionWindow::cb_do(Fl_Widget* o, void* v) {
	ConvolutionWindow* self = ((ConvolutionWindow*)(o->user_data()));

	float sum = 0;

	self->kernel = new float*[self->kernelSize];
	for (int i = 0; i < self->kernelSize; i++) {
		self->kernel[i] = new float[self->kernelSize];
		for (int j = 0; j < self->kernelSize; j++) {
			self->kernel[i][j] = 0;
			sscanf(self->m_KernelInput[i][j]->value(), "%f", &(self->kernel[i][j]));
			sum += self->kernel[i][j];
		}
	}

	if (self->m_NormaliseButton->value()) {
		
		for (int i = 0; i < self->kernelSize; i++) {
			for (int j = 0; j < self->kernelSize; j++) {
				self->kernel[i][j] /= sum;
			}
		}
	}

	self->m_pDoc->doConvolution(self->kernel, self->kernelSize);

	for (int i = 0; i < self->kernelSize; i++) {
		delete[] self->kernel[i];
	}
	delete[] self->kernel;
}

void ConvolutionWindow::show(ImpressionistDoc* doc, int size) {
	m_pDoc = doc;
	kernelSize = size;

	m_convolutionWindow = new Fl_Window(max(kernelSize * 45 + 20, 200), kernelSize * 35 + 50, "Kernel");
	
		m_OKButton = new Fl_Button(10, 10, 80, 20, "Do it");
		m_OKButton->user_data((void*)(this));
		m_OKButton->callback(cb_do);

		m_NormaliseButton = new Fl_Light_Button(100, 10, 90, 20, "Normalize");

		m_KernelInput = new Fl_Float_Input**[kernelSize];
		for (int i = 0; i < kernelSize; i++) {
			m_KernelInput[i] = new Fl_Float_Input*[kernelSize];
			for (int j = 0; j < kernelSize; j++) {
				m_KernelInput[i][j] = new Fl_Float_Input(10 + 45 * i, 40 + 35 * j, 35, 25);
				m_KernelInput[i][j]->value("0");
			}
		}

	m_convolutionWindow->end();
	m_convolutionWindow->show();
}