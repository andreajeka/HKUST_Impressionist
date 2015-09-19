//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();

	float alphaValue = m_pDoc->getAlpha();

	GLubyte color[4];

	memcpy(color, pDoc->GetOriginalPixel(source), 3);

	//Dissect every color to r,g,b, and a so it is easier to include alpha
	GLubyte red = static_cast<GLubyte> (color[0]);
	GLubyte green = static_cast<GLubyte> (color[1]);
	GLubyte blue = static_cast<GLubyte> (color[2]);

	// converts the alpha value to a GLubyte
	GLubyte alpha = static_cast<GLubyte>(alphaValue * 255.0f); 

	glColor4ub(red, green, blue, alpha);
}

void ImpBrush::EnableAlphaBlending() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void ImpBrush::DisableAlphaBlending() {
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);
}