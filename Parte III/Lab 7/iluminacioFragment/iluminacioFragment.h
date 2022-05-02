#ifndef _ILUMINACIOFRAGMENT_H
#define _ILUMINACIOFRAGMENT_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class IluminacioFragment: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();
  private:
    QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs; 
};

#endif
