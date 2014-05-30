#define NO_SDL_GLEXT

#include "../conf.h"
#ifdef OS_WIN
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "mmsystem.h"
#include "mmreg.h"
#endif
#ifdef OS_OSX
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#endif
#ifdef OS_LIN
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include "../tools.h"
#include "../main.h"
#include "GLgraph.h"
#include "SDLgraph.h"

using namespace std;


bool CreateImage(int ww, int hh, glImage &myImage)
{
	myImage.width=ww;
	myImage.height=hh;
	
	myImage.pixels = new unsigned char [ww*hh*4];

	if(!myImage.pixels) return false;

	memset((char*)myImage.pixels,0,ww*hh*4);

	return true;
}

void FlipFromSDL(SDL_Surface* mySDLimage, glImage theImage)
{
		for (int y=0;y<mySDLimage->h;y++)
		for(int x=0;x<mySDLimage->w;x++)
		{

			Uint32 col=SDLgetpixel32(mySDLimage,x,y);
		    glputpixel32(x,y,col,theImage);
		}
}


void FreeImage(glImage &myImage)
{
	 delete [] myImage.pixels;
}


void glputpixel32(int x, int y, unsigned int color, glImage myImage)
{
	unsigned char *p = (unsigned char *)myImage.pixels + (y * myImage.width + x) * 4;

     *(unsigned int *)p = color;
}

unsigned int glgetpixel32(int x, int y, glImage myImage)
{
    unsigned int *p = (unsigned int *)myImage.pixels;
  
	return p[(y*myImage.width+x)*4];
}







void glTexturedImage::createSprite(glImage myImage)
{
	

	 // Have OpenGL generate a texture object handle for us
        glGenTextures(1, &GLtextureID );
    

		
        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, GLtextureID );
        
        // Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,0x812f);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,0x812f);
		
        glTexImage2D( GL_TEXTURE_2D, 0,4, myImage.width, myImage.height, 0, 
                      GL_RGBA, GL_UNSIGNED_BYTE, myImage.pixels );

		w=myImage.width;
		h=myImage.height;


}

void glTexturedImage::FreeImage(glImage &myImage)
{
	 delete [] myImage.pixels;
	 if(GLtextureID) glDeleteTextures( 1, &GLtextureID );
}


void glTexturedImage::putSprite(int x, int y)
{


    glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

    glMatrixMode( GL_PROJECTION );
	glPushMatrix();
    glLoadIdentity();
	
	
	glViewport( 0, 0,screenwidth, screenheight );


    glOrtho( 0, screenwidth, screenheight, 0, -1, 1 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
	
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);



	 glDisable(GL_LIGHTING);


	 
	glEnable( GL_TEXTURE_2D ); // Need this to display a texture

	// Bind the texture to which subsequent calls refer to
    glBindTexture( GL_TEXTURE_2D,GLtextureID );


    glBegin( GL_QUADS );

		glColor3f(1,1,1);

        // Top-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f((float) x+0,(float) y+0, 0 );
    
        // Bottom-left vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f((float) x+w,(float) y+0, 0 );
    
        // Bottom-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f((float) x+w,(float) y+h, 0 );
    
        // Top-right vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f((float) x+0,(float) y+h, 0 );

    glEnd();

		
//	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);


	 

	glDisable( GL_TEXTURE_2D );

	


	glMatrixMode(GL_PROJECTION);	
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();


}


void glTexturedImage::putSpriteRotated(int x, int y, float angle)
{


    glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

    glMatrixMode( GL_PROJECTION );
	glPushMatrix();
    glLoadIdentity();
	
	

	
	glViewport( 0, 0,screenwidth, screenheight );
    glOrtho( 0, screenwidth, screenheight, 0, -1, 1 );
    
		
	glTranslatef((float)x-(float)w / 2,(float)y - (float)h / 2,0);
	
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    


	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);



	 glDisable(GL_LIGHTING);


	 
	glEnable( GL_TEXTURE_2D ); // Need this to display a texture

	// Bind the texture to which subsequent calls refer to
    glBindTexture( GL_TEXTURE_2D,GLtextureID );
	

	glTranslatef((float)w / 2,(float)h / 2,0);


	glRotatef(angle,0,0,1);
	
	glTranslatef((float)w / -2 ,(float)h / -2 ,0);

	
    glBegin( GL_QUADS );

		glColor3f(1,1,1);


		// Top-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f((float) 0,(float) 0, 0 );
    
        // Bottom-left vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f((float) w,(float) 0, 0 );
    
        // Bottom-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f((float) w,(float) h, 0 );
    
        // Top-right vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f((float) 0,(float) h, 0 );
		
    glEnd();

		
//	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);


	 

	glDisable( GL_TEXTURE_2D );

	


	glMatrixMode(GL_PROJECTION);	
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();


}


void glTexturedImage::putSpriteScaledRotated(int x, int y, float angle, float scalefactor)
{


    glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

    glMatrixMode( GL_PROJECTION );
	glPushMatrix();
    glLoadIdentity();
	
	

	
	glViewport( 0, 0,screenwidth, screenheight );
    glOrtho( 0, screenwidth, screenheight, 0, -1, 1 );
    
		
	glTranslatef((float)x-(float)w / 2,(float)y - (float)h / 2,0);
	
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    


	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);



	 glDisable(GL_LIGHTING);


	 
	glEnable( GL_TEXTURE_2D ); // Need this to display a texture

	// Bind the texture to which subsequent calls refer to
    glBindTexture( GL_TEXTURE_2D,GLtextureID );
	

	glTranslatef((float)w / 2,(float)h / 2,0);


	glRotatef(angle,0,0,1);
	
	glTranslatef((float)w / -2 ,(float)h / -2 ,0);

	glScalef(scalefactor,scalefactor,1);
	
    glBegin( GL_QUADS );

		glColor3f(1,1,1);


		// Top-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f((float) 0,(float) 0, 0 );
    
        // Bottom-left vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f((float) w,(float) 0, 0 );
    
        // Bottom-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f((float) w,(float) h, 0 );
    
        // Top-right vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f((float) 0,(float) h, 0 );
		
    glEnd();

		
//	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);


	 

	glDisable( GL_TEXTURE_2D );

	


	glMatrixMode(GL_PROJECTION);	
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();


}





void putStaticSprite(int x, int y, glImage myImage)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0,screenwidth,screenheight,0);

	glRasterPos2i(x,y);

	glDrawPixels(myImage.width,myImage.height,GL_RGBA,GL_UNSIGNED_BYTE,myImage.pixels);

}









void  glTexturedImage::KillTexture()									// Delete The Font List
{
	
	if(GLtextureID) glDeleteTextures( 1, &GLtextureID );
}






