//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>
#include <iostream>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads another image for dissolving
//------------------------------------------------------------------
void ImpressionistUI::cb_load_dissolve_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	ImpressionistUI *self = whoami(o);

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadDissolveImage(newfile);
	}

	int width = pDoc->m_nWidth;
	int height = pDoc->m_nHeight;
	GLubyte color[3];

	for (int i = 0; i < 100; i++) {

		for (int w = 0; w < width; w++) {
			for (int h = 0; h < height; h++) {
				for (int k = 0; k < 3; k++) {
					color[k] = (GLubyte)((pDoc->m_ucBitmapBackup[3 * h * width + w * 3 + k] * (100 - i)
						+ pDoc->m_ucDissolveImage[3 * h * width + w * 3 + k] * (i)) / 100);
					pDoc->m_ucBitmap[3 * h * width + w * 3 + k] = color[k];
				}
			}
		}

		self->m_origView->refresh();
		Fl::check();
	}

	for (int i = 0; i < 100; i++) {

		for (int w = 0; w < width; w++) {
			for (int h = 0; h < height; h++) {
				for (int k = 0; k < 3; k++) {
					color[k] = (GLubyte)((pDoc->m_ucDissolveImage[3 * h * width + w * 3 + k] * (100 - i)
						+ pDoc->m_ucBitmapBackup[3 * h * width + w * 3 + k] * (i)) / 100);
					pDoc->m_ucBitmap[3 * h * width + w * 3 + k] = color[k];
				}
			}
		}

		self->m_origView->refresh();
		Fl::check();
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads an edge image
//------------------------------------------------------------------
void ImpressionistUI::cb_load_edge_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadEdgeImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads a mural image
//------------------------------------------------------------------
void ImpressionistUI::cb_load_mural_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadMuralImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads a gradient image
//------------------------------------------------------------------
void ImpressionistUI::cb_load_gradient_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadGradientImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//-------------------------------------------------------------
// Display the colur wheel for colour blending
//-------------------------------------------------------------
void ImpressionistUI::cb_color_blending(Fl_Menu_* o, void* v) {
	fl_color_chooser("Please choose a colour", whoami(o)->blendColour[0], whoami(o)->blendColour[1], whoami(o)->blendColour[2]);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Undo the most recent brush stroke
//------------------------------------------------------------
void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->undo();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for COMP4411, Fall 2015 by Andrea Juliati Kurniasari");
}

//------------------------------------------------------------
// Display the original image
// Called by the UI when the original menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_display_original_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	pDoc->displayOrigImg();
}

//------------------------------------------------------------
// Display the image filtered to get image with edge detected
// Called by the UI when the original menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_display_edge_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	if (pDoc->m_ucBitmap == NULL) {
		fl_alert("Please load an image first in your original view!");
		return;
	}
	pDoc->displayEdgeImg();
}

//------------------------------------------------------------
// 
//------------------------------------------------------------
void ImpressionistUI::cb_swap_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	if (pDoc->m_ucBitmap == NULL) {
		fl_alert("Please load an image first in your original view!");
		return;
	}
	pDoc->swapCanvas();
}

//------------------------------------------------------------
// 
//------------------------------------------------------------
void ImpressionistUI::cb_convolution(Fl_Menu_* o, void* v)
{
	char s[10];
	strcpy(s, fl_input("Please enter an odd number for kernel size"));
	int kernelSize = atoi(s);
	whoami(o)->m_convolutionWindow->show(whoami(o)->getDocument(), kernelSize);
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;


	pDoc->setBrushType(type);
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads an alpha mapped brush
//------------------------------------------------------------------
void ImpressionistUI::cb_load_alpha_mapped_brush(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.png", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAlphaMappedBrush(newfile);
		pDoc->setBrushType(ALPHAMAPPED);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads a luminance brush
//------------------------------------------------------------------
void ImpressionistUI::cb_load_luminance_brush(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadLuminanceBrush(newfile);
		pDoc->setBrushType(LUMINANCE);
	}
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of stroke direction to use to the one chosen in 
// the stroke direction choice.  
// Called by the UI when a stroke direction is chosen in the stroke
// direction choice
//-------------------------------------------------------------
void ImpressionistUI::cb_strokeDirectionChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize = int(((Fl_Slider *)o)->value());
}

//-----------------------------------------------------------
// Updates the brush line width to use from the value of the 
// line width slider (only for line brush)
// Called by the UI when the line width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth = int(((Fl_Slider *)o)->value());
}

//-----------------------------------------------------------
// Updates the brush line angle to use from the value of the
// line angle slider (only for line brush)
// Called by the UI when the line angle slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle = int(((Fl_Slider *)o)->value());
}

//-----------------------------------------------------------
// Updates the brush alpha value to use from the value of the
// alpha slider
// Called by the UI when the alpha slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = float(((Fl_Slider *)o)->value());
}

//-----------------------------------------------------------
// Updates the brush spacing size to use from the value of the
// spacng slider
// Called by the UI when the spacing slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_spacingSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSpacing = int(((Fl_Slider *)o)->value());
}

//-----------------------------------------------------------
// Updates the brush edge threshold value to use from the value
// the edge threshold slider
// Called by the UI when the edge threshold slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_edgeThresholdSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nEdgeThreshold = int(((Fl_Slider *)o)->value());
}


//------------------------------------------------------------
// 
// 
//------------------------------------------------------------
void ImpressionistUI::cb_auto_edge_clipping_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	ImpressionistUI* pUI = pDoc->m_pUI;
	if (pUI->m_AutoEdgeClippingButton->value() != 1) {
		pUI->autoEdgeClippingClicked = FALSE;
		pUI->m_ManEdgeClippingButton->activate();
	}
	else {
		pUI->autoEdgeClippingClicked = TRUE; 
		pUI->m_ManEdgeClippingButton->deactivate();
		pDoc->GenerateEdgeDetectedImg(pUI->getEdgeThreshold());
	}
}

//------------------------------------------------------------
// 
// 
//------------------------------------------------------------
void ImpressionistUI::cb_man_edge_clipping_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	ImpressionistUI* pUI = pDoc->m_pUI;
	if (pUI->m_ManEdgeClippingButton->value() != 1){
		pUI->manEdgeClippingClicked = FALSE;
		pUI->m_AutoEdgeClippingButton->activate();
	}
	else {
		pUI->manEdgeClippingClicked = TRUE;
		pUI->m_AutoEdgeClippingButton->deactivate();
		if (pDoc->m_ucLoadedEdge == NULL) {
			fl_alert("Load an edge image first!");
			pUI->m_ManEdgeClippingButton->value(0);
			pUI->manEdgeClippingClicked = FALSE;
			pUI->m_AutoEdgeClippingButton->activate();
		}
		else pDoc->m_ucEdge == pDoc->m_ucLoadedEdge;
	}
}

//------------------------------------------------------------
// 
// 
//------------------------------------------------------------
void ImpressionistUI::cb_another_gradient_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	ImpressionistUI* pUI = pDoc->m_pUI;
	if (!pDoc->hasGradientImage()) {
		fl_message("No Gradient Image");
		// need to find some ways to turn of the button...
		return;
	}
		
	pUI->anotherGradientClicked = (bool)pUI->m_AnotherGradientButton->value();
}

//------------------------------------------------------------
// 
// 
//------------------------------------------------------------
void ImpressionistUI::cb_size_rand_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	ImpressionistUI* pUI = pDoc->m_pUI;
	if (pUI->m_SizeRandButton->value() == 1) {
		pUI->sizeRandClicked = TRUE;
	}
	else {
		pUI->sizeRandClicked = FALSE;
	}
}

//------------------------------------------------------------
// 
// 
//------------------------------------------------------------
void ImpressionistUI::cb_crazy_angle_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	ImpressionistUI* pUI = pDoc->m_pUI;
	if (pUI->m_CrazyAngleButton->value() == 1) {
		pUI->crazyAngleClicked = TRUE;
	}
	else {
		pUI->crazyAngleClicked = FALSE;
	}
}

//------------------------------------------------------------
// 
// 
//------------------------------------------------------------
void ImpressionistUI::cb_paint_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	ImpressionistUI* pUI = pDoc->m_pUI;
	pUI->m_paintView->autoDraw(pDoc->sizeRandIsOn());
}

//------------------------------------------------------------
// 
// 
//------------------------------------------------------------
void ImpressionistUI::cb_do_it_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	if (pDoc->m_ucBitmap == NULL) {
		fl_alert("Please load an image first in your original view!");
		return;
	}
	pDoc->displayEdgeImg();
}

//------------------------------------------------------------
// 
// 
//------------------------------------------------------------
void ImpressionistUI::cb_add_background_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->changeBackgroundBrightness(pDoc->m_pUI->m_DimLevelSlider->value());
	pDoc->m_pUI->m_paintView->refresh();
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

//------------------------------------------------
// Return the brush line width
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}

//-------------------------------------------------
// Set the brush line width
//-------------------------------------------------
void ImpressionistUI::setLineWidth(int width)
{
	m_nLineWidth = width;

	if (width <= 40)
		m_LineWidthSlider->value(m_nLineWidth);
}

//------------------------------------------------
// Return the brush line angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;
}

//-------------------------------------------------
// Set the brush line angle
//-------------------------------------------------
void ImpressionistUI::setLineAngle(int angle)
{
	m_nLineAngle = angle;

	if (angle <= 359)
		m_LineAngleSlider->value(m_nLineAngle);
}

//------------------------------------------------
// Return the brush alpha value
//------------------------------------------------
float ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}

//-------------------------------------------------
// Set the brush alpha value
//-------------------------------------------------
void ImpressionistUI::setAlpha(float value)
{
	m_nAlpha = value;

	if (value <= 1.00)
		m_AlphaSlider->value(m_nAlpha);
}

//------------------------------------------------
// Return the spacing value
//------------------------------------------------
int ImpressionistUI::getSpacing()
{
	return m_nSpacing;
}

//-------------------------------------------------
// Set the spacing value
//-------------------------------------------------
void ImpressionistUI::setSpacing(int value)
{
	m_nSpacing = value;

	if (value <= 16)
		m_SpacingSlider->value(m_nSpacing);
}

//------------------------------------------------
// Return the edge threshold value
//------------------------------------------------
int ImpressionistUI::getEdgeThreshold()
{
	return m_nEdgeThreshold;
}

//-------------------------------------------------
// Set the edge threshold value
//-------------------------------------------------
void ImpressionistUI::setEdgeThreshold(int value)
{
	m_nEdgeThreshold = value;

	if (value <= 500)
		m_EdgeThresholdSlider->value(m_nEdgeThreshold);
}

//-------------------------------------------------
// Get the colour for blending
//-------------------------------------------------
double ImpressionistUI::getBlendColour(int index)
{
	return blendColour[index];
}

//-------------------------------------------------
// 
//-------------------------------------------------
bool ImpressionistUI::autoEdgeClippingIsOn()
{
	return autoEdgeClippingClicked;
}

//-------------------------------------------------
// 
//-------------------------------------------------
bool ImpressionistUI::manEdgeClippingIsOn()
{
	return manEdgeClippingClicked;
}

//-------------------------------------------------
// 
//-------------------------------------------------
bool ImpressionistUI::anotherGradientIsOn()
{
	return anotherGradientClicked;
}

//-------------------------------------------------
// 
//-------------------------------------------------
bool ImpressionistUI::sizeRandIsOn()
{
	return sizeRandClicked;
}

//-------------------------------------------------
// 
//-------------------------------------------------
bool ImpressionistUI::crazyAngleIsOn()
{
	return crazyAngleClicked;
}


// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes, 0, FL_MENU_DIVIDER },

		{ "&Clear Canvas",	FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas},
		{ "&Undo",			FL_ALT + 'z', (Fl_Callback *)ImpressionistUI::cb_undo, 0, FL_MENU_DIVIDER },
		
		{ "&Colors...", FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_color_blending },
		{ "&Paintly...", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },

		{ "Load Edge Image...", FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_load_edge_image },
		{ "Load Mural Image...", FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_load_mural_image },
		{ "Load Gradient Image...", FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_gradient_image, 0, FL_MENU_DIVIDER },

		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Display",		0, 0, 0, FL_SUBMENU },
		{ "&Original Image...", FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_display_original_image },
		{ "&Edge Image...", FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_display_edge_image },
		{ "&Dissolve...", FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_dissolve_image },
		{ "&Swap Canvas", FL_ALT + 's', (Fl_Callback * )ImpressionistUI::cb_swap_canvas },
		{ "&Convolution", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_convolution },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Triangle",			FL_ALT+'t', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)TRIANGLE},
  {"Heart",				FL_ALT+'h', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)HEART},
  {"Circle Star",		FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)CIRCLESTAR},
  {"Alpha-mapped",		FL_ALT+'a', (Fl_Callback *)ImpressionistUI::cb_load_alpha_mapped_brush},
  {"Luminance",			FL_ALT+'u', (Fl_Callback *)ImpressionistUI::cb_load_luminance_brush },
  { "Filter: Unconvolved Blur",		FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)WOCONVBLUR },
  { "Filter: Unconvolved Sharpen",	FL_ALT + 'n', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)WOCONVSHARPEN },
  { "Filter: Emboss",	FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)EMBOSS },
  { "Filter: Gaussian Blur ", FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *) GAUSSIANBLUR},
  { "Filter: Motion Blur ", FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)MOTIONBLUR },
  {0}
};

// Stroke directioon choice menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionTypeMenu[NUM_STROKEDIRECTION_TYPE+1] = {
  {"Slider/Right Mouse",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)SLIDER_OR_RIGHTMOUSE},
  { "Gradient",				FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)GRADIENT},
  { "Brush Direction",		FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)BRUSH_DIRECTION},
  {0}
};

//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values
	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_nAlpha = 1.00;
	m_nSpacing = 4;
	m_nEdgeThreshold = 100;
	blendColour[0] = 1;
	blendColour[1] = 1;
	blendColour[2] = 1;
	autoEdgeClippingClicked = FALSE;
	manEdgeClippingClicked = FALSE;
	anotherGradientClicked = FALSE;
	sizeRandClicked = FALSE;
	crazyAngleClicked = FALSE;
	m_convolutionWindow = new ConvolutionWindow();

	// brush dialog definition
	m_brushDialog = new Fl_Window(500, 380, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,220,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		// Add a clear canvas button to the dialog
		m_ClearCanvasButton = new Fl_Button(330,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add a stroke direction type choice to the dialog
		m_StrokeDirectionTypeChoice = new Fl_Choice(115, 45, 150, 25, "&Stroke Direction");
		m_StrokeDirectionTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_StrokeDirectionTypeChoice->menu(strokeDirectionTypeMenu);
		m_StrokeDirectionTypeChoice->callback(cb_strokeDirectionChoice);

		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 400, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add line width slider to the dialog
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 400, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_LineWidthSlider->labelfont(FL_COURIER);
		m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_lineWidthSlides);

		// Add line width slider to the dialog
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 400, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_LineAngleSlider->labelfont(FL_COURIER);
		m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLineAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_lineAngleSlides);

		// Add Alpha slider to the dialog
		m_AlphaSlider = new Fl_Value_Slider(10, 170, 400, 20, "Alpha");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.0);
		m_AlphaSlider->maximum(1.00);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nAlpha);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_alphaSlides);

		// Add edge clipping light button to the dialog
		m_AutoEdgeClippingButton = new Fl_Light_Button(10, 200, 150, 25, "Auto &Edge Clipping");
		m_AutoEdgeClippingButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_AutoEdgeClippingButton->callback(cb_auto_edge_clipping_button);

		// Add manual edge clipping light button to the dialog
		// Manual edge clipping allows edge clipping through edge image
		m_ManEdgeClippingButton = new Fl_Light_Button(170, 200, 150, 25, "&Man Edge Clipping");
		m_ManEdgeClippingButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_ManEdgeClippingButton->callback(cb_man_edge_clipping_button);

		// Add auto edge clipping light button to the dialog
		// Automatic edge clipping allows edge clipping through auto-generated edge image
		m_AnotherGradientButton = new Fl_Light_Button(330, 200, 150, 25, "&Another Gradient");
		m_AnotherGradientButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_AnotherGradientButton->callback(cb_another_gradient_button);

		// Create a group for spacing slider, size rand. buttom, and paint button
		m_PaintGroupBox = new Fl_Box(FL_THIN_UP_BOX, 10, 230, 470, 40, "");

		// Add spacing slider to the dialog
		m_SpacingSlider = new Fl_Value_Slider(20, 240, 140, 20, "Spacing");
		m_SpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_SpacingSlider->type(FL_HOR_NICE_SLIDER);
		m_SpacingSlider->labelfont(FL_COURIER);
		m_SpacingSlider->labelsize(12);
		m_SpacingSlider->minimum(1);
		m_SpacingSlider->maximum(16);
		m_SpacingSlider->step(1);
		m_SpacingSlider->value(m_nSpacing);
		m_SpacingSlider->align(FL_ALIGN_RIGHT);
		m_SpacingSlider->callback(cb_spacingSlides);

		// Add size rand light button to the dialog
		m_SizeRandButton = new Fl_Light_Button(220,238, 87, 23, "Size &Rand.");
		m_SizeRandButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_SizeRandButton->callback(cb_size_rand_button);

		// Add crazy angle light button to the dialog
		m_CrazyAngleButton = new Fl_Light_Button(315, 238, 100, 23, "&Crazy Angle");
		m_CrazyAngleButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_CrazyAngleButton->callback(cb_crazy_angle_button);

		// Add paint button to the dialog
		m_PaintButton = new Fl_Button(423, 238, 50, 23, "&Paint");
		m_PaintButton->user_data((void*)(this));
		m_PaintButton->callback(cb_paint_button);

		// Create a group for edge threshold slider and do it button
		m_DoItGroupBox = new Fl_Box(FL_THIN_UP_BOX, 10, 275, 470, 40, "");

		// Add edge threshold slider to the dialog
		m_EdgeThresholdSlider = new Fl_Value_Slider(20, 285, 280, 20, "Edge Threshold");
		m_EdgeThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_EdgeThresholdSlider->type(FL_HOR_NICE_SLIDER);
		m_EdgeThresholdSlider->labelfont(FL_COURIER);
		m_EdgeThresholdSlider->labelsize(12);
		m_EdgeThresholdSlider->minimum(0);
		m_EdgeThresholdSlider->maximum(500);
		m_EdgeThresholdSlider->step(1);
		m_EdgeThresholdSlider->value(m_nEdgeThreshold);
		m_EdgeThresholdSlider->align(FL_ALIGN_RIGHT);
		m_EdgeThresholdSlider->callback(cb_edgeThresholdSlides);

		// Add do it button to the dialog
		m_DoItButton = new Fl_Button(420, 285, 50, 20, "&Do it");
		m_DoItButton->user_data((void*)(this));
		m_DoItButton->callback(cb_do_it_button);

		// Create a group for dimlevel slider and add button
		m_DimLevelGroupBox = new Fl_Box(FL_THIN_UP_BOX, 10, 320, 470, 40, "");

		// Add dim level slider to the dialog
		m_DimLevelSlider = new Fl_Value_Slider(20, 330, 280, 20, "Dim Level");
		m_DimLevelSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_DimLevelSlider->type(FL_HOR_NICE_SLIDER);
		m_DimLevelSlider->labelfont(FL_COURIER);
		m_DimLevelSlider->labelsize(12);
		m_DimLevelSlider->minimum(0);
		m_DimLevelSlider->maximum(255);
		m_DimLevelSlider->step(1);
		m_DimLevelSlider->value(255);
		m_DimLevelSlider->align(FL_ALIGN_RIGHT);

		// Add dim level button to the dialog
		m_DimLevelButton = new Fl_Button(420, 330, 50, 20, "A&dd");
		m_DimLevelButton->user_data((void*)(this));
		m_DimLevelButton->callback(cb_add_background_button);

    m_brushDialog->end();	

}
