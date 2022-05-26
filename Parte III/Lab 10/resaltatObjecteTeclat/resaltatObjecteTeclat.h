#ifndef _RESALTATOBJECTETECLAT_H
#define _RESALTATOBJECTETECLAT_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class ResaltatObjecteTeclat: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();

	 void keyPressEvent(QKeyEvent *e);

  private:
	QOpenGLShaderProgram* program;
	QOpenGLShader* vs;
	QOpenGLShader* fs;

	bool created;
	GLuint cubeVAO;
	GLuint verticesVBO;
	GLuint colorVBO;
};

#endif