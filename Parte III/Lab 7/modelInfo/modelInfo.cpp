#include "modelInfo.h"
#include "glwidget.h"

void ModelInfo::onPluginLoad()
{
	
}

void ModelInfo::preFrame()
{
	
}

void ModelInfo::postFrame()
{
	int n = scene()->objects().size();
	int vertices = 0, faces = 0, triangles = 0, noTriangles = 0;
	for (int i = 0; i < n; i++) {
		vertices += scene()->objects()[i].vertices().size();
		faces += scene()->objects()[i].faces().size();
		for (int j = 0; j < scene()->objects()[i].faces().size(); j++) {
			if (scene()->objects()[i].faces()[j].numVertices() == 3)
				triangles++;
			else
				noTriangles++;
		}
	}

	cout << "nombre objectes: " << n << endl;
	cout << "nombre vertex: " << vertices << endl;
	cout << "nombre de polígons: " << faces << endl;
	cout << "% triangles: " << triangles / (noTriangles + triangles) * 100 << endl;
}

void ModelInfo::onObjectAdd()
{
	
}

bool ModelInfo::drawScene()
{
	return false; // return true only if implemented
}

bool ModelInfo::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo::mouseMoveEvent(QMouseEvent *)
{
	
}

