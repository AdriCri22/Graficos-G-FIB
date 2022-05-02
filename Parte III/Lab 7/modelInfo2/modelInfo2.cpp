#include "modelInfo2.h"
#include "glwidget.h"

void ModelInfo2::getModelInfo() {
	objects = scene()->objects().size();
	vertices = 0; faces = 0;
	int triangles = 0, noTriangles = 0;
	for (int i = 0; i < objects; i++) {
		vertices += scene()->objects()[i].vertices().size();
		faces += scene()->objects()[i].faces().size();
		for (int j = 0; j < scene()->objects()[i].faces().size(); j++) {
			if (scene()->objects()[i].faces()[j].numVertices() == 3)
				triangles++;
			else
				noTriangles++;
		}
	}

	pTriangles = triangles / (noTriangles + triangles) * 100;
}

void ModelInfo2::onPluginLoad()
{
	getModelInfo();
}

void ModelInfo2::postFrame()
{
	QFont font;
    font.setPixelSize(15);
    painter.begin(glwidget());
    painter.setFont(font);
	int x = 20;
	int y = 20;
	int add = 25;
    painter.drawText(x, y, QString("Objectes: %1").arg(objects)); 
    //painter.drawText(x, y, QString("Objectes: " + QString::number(objects))); 
    painter.drawText(x, y+add, QString("Poligons: %1").arg(faces)); 
	//painter.drawText(x, y+add, QString("Poligons: " + QString::number(faces))); 
    painter.drawText(x, y+add*2, QString("Vertexs: %1").arg(vertices)); 
    //painter.drawText(x, y+add*2, QString("Vertexs: " + QString::number(vertices)));
    painter.drawText(x, y+add*3, QString("Percentatge de triangles: %1%").arg(pTriangles)); 
    //painter.drawText(x, y+add*3, QString("Percentatge de triangles: " + QString::number(pTriangles) + "%"));              
    painter.end();
}

void ModelInfo2::onObjectAdd()
{
	getModelInfo();
}

