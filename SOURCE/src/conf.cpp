#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include "conf.h"
#include "tools.h"
#include "main.h"
#include "SystemTools/INIparser.h"

using namespace std;


string DATAfolder="../data/";

int screenwidth=1280;
int screenheight=720;

bool screenFullScreen=false;






void GetEngineStartupConfig()
{
	INIparser myINI;
	if (!myINI.loadINI(absoluteExecutablePath+"engine.ini")) error("Unable to load 'engine.ini' !");

	screenwidth = strnum(myINI.getKeyValue("CORE","width"));
	screenheight = strnum(myINI.getKeyValue("CORE","height"));

	if (myINI.getKeyValue("CORE","fullscreen")=="true")
	{
		screenFullScreen = true;
	} else if (myINI.getKeyValue("CORE","fullscreen")=="false")
	{
		screenFullScreen = false;
	} else error("engine.ini: corrupt 'fullscreen' TAG !");

	DATAfolder = myINI.getKeyValue("CORE","datapath");
	
	

	myINI.close();
}
