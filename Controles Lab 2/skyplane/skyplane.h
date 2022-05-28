#ifndef _SKYPLANE_H
#define _SKYPLANE_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Skyplane: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 bool paintGL();
  private:
    QOpenGLShaderProgram* program;
    QOpenGLShaderProgram* program2;
    QOpenGLShader *fs, *vs, *fs2, *vs2;
    GLuint textureId0, VAO;
};

#endif
