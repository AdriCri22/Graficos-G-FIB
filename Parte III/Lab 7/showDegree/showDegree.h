#ifndef _SHOWDEGREE_H
#define _SHOWDEGREE_H

#include "plugin.h"
#include <QPainter>

class ShowDegree: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
	 void onObjectAdd();

  private:
    QPainter painter;
	double degree;
	void getDegreeInfo();
};

#endif
