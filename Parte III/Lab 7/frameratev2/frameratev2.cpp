#include "frameratev2.h"
#include "glwidget.h"

void Frameratev2::onPluginLoad()
{
	timer.start();
	fps = 0;
}

void Frameratev2::preFrame()
{
	if (timer.hasExpired(1000)) {
		timer.start();
		cout << fps << endl;
		fps = 0;
	} else 
		fps++;
}