#pragma once

class skybox
{
public:

	void initSkyBox();
	void closeSkyBox();

	void renderSkyBox(float size);

private:
	enum {SKY_LEFT=0,SKY_BACK=1,SKY_RIGHT=2,SKY_FRONT=3,SKY_TOP=4,SKY_BOTTOM=5};
	unsigned int skyboxtextures[6];
	unsigned int loadTexture(string filename);
};