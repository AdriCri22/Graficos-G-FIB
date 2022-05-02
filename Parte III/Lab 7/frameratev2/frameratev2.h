#ifndef _FRAMERATEV2_H
#define _FRAMERATEV2_H

#include "plugin.h" 
#include <QElapsedTimer>

class Frameratev2: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
  private:
    QElapsedTimer timer;
	int fps;
};

#endif
