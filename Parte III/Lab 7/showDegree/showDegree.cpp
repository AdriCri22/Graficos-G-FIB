#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::getDegreeInfo() 
{
	if (scene()->objects().size() > 0) {
		const Object &obj =scene()->objects()[0];
		int nVertsFace = 0;
		for (int j = 0; j < obj.faces().size(); j++) 
			nVertsFace += obj.faces()[j].numVertices();
		int nVerts = obj.vertices().size();
		degree = (double) nVertsFace/nVerts;
	}
}

void ShowDegree::onPluginLoad()
{
	getDegreeInfo();
}

void ShowDegree::onObjectAdd()
{
	getDegreeInfo();
}

void ShowDegree::postFrame()
{
	QFont font;
    font.setPixelSize(16);
    painter.begin(glwidget());
    painter.setFont(font);
    painter.drawText(20, 20, QString(QString::number(degree))); 
    painter.end();
}
