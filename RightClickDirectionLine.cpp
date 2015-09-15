//
// RightClickDirectionLine.cpp
// The implementation of Right Click Direction Line. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "RightClickDirectionLine.h"
#include "PaintView.h"

RightClickDirectionLine::RightClickDirectionLine(ImpressionistDoc*	pDoc, char*	name) :
ImpBrush(pDoc, name)
{
	startCoord = NULL;
}

void RightClickDirectionLine::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// We use target as the initial coordinate because intuitively
	// at the beginning, when we click once we get the brush coordinate
	// and that is actually the target coordinate (depends on the scenario)
	startCoord = new Point(target);
	
	// By default we set the smallest size
	glPointSize(1);

	// By default we set it as red color
	glColor3f(1.0, 0.0, 0.0);

	BrushMove(source, target);
}

void RightClickDirectionLine::BrushMove(const Point source, const Point target)
{

	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("RightClickDirectionLine::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINES);
		// Set the initial coordinate as source because now 
		// we are in a different scenario where we move the brush
		glVertex2d(startCoord->x, startCoord->y);
		glVertex2d(target.x, target.y);
	glEnd();

}

void RightClickDirectionLine::BrushEnd(const Point source, const Point target)
{
	// Immediately deallocate initialCoord pointer and set to null;
	delete startCoord;
	startCoord = NULL;
}
