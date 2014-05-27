#include "conf.h"
#include "tools.h"
#include "Engine\INIparser.h"

using namespace std;


string DATAfolder="../data/";

int screenwidth=1280;
int screenheight=720;

int how2showFPS=0;

bool screenFullScreen=false;






void GetEngineStartupConfig()
{
	INIparser myINI;
	if (!myINI.loadINI("engine.ini")) error("Unable to load 'engine.ini' !");

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
	
	if (myINI.getKeyValue("CORE","showFPS")=="onScreen")
	{
		how2showFPS=0;
	} else if (myINI.getKeyValue("CORE","showFPS")=="onWindowBar")
	{
		how2showFPS=1;
	} else if (myINI.getKeyValue("CORE","showFPS")=="off")
	{
		how2showFPS=2;
	} else error("engine.ini: corrupt 'showFPS' TAG ! ->"+myINI.getKeyValue("CORE","showFPS")+"?");


	myINI.close();
}
