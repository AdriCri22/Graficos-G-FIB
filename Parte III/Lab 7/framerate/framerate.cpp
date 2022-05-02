#include "framerate.h"
#include "glwidget.h"

void Framerate::onPluginLoad()
{
	timer.start();
	fps = 0;
}

void Framerate::postFrame()
{	
	if (timer.elapsed() < 1000.0)
		fps++;
	else {
		timer.start();
		cout << fps << endl;
		fps = 0;
	}
}

