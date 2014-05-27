#pragma once

#include "../conf.h"
#include <windows.h>
#include <malloc.h>
#include "mmsystem.h"
#include "mmreg.h"
#include "math.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../tools.h"
#include "../main.h"
#include "glGraph.h"
#include "SDLgraph.h"




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




/*
void glTexturedImage::BuidFontSprite(const char *c, int numchars, int relativesize) 
{

int base;
int fs=-24;

unsigned int charsizeX=14;
unsigned int charsizeY=24;

if(relativesize==1) 
{
	fs=-24;
	charsizeX=14;
	charsizeY=24;
}
if(relativesize==2) 
{
	fs=-34;
	charsizeX=24;
	charsizeY=34;
}




	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	fs,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font





    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                // Set The Clear Color To Black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear Screen And Depth Buffer




	w = charsizeX * numchars;
	h = charsizeY;

	glViewport(0,0,w,h);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	glColor3f(1.0f,0.0f,0.0f);
	
	//glRasterPos2f(-1.0f, -1.0f);
	glRasterPos2f(-1, -1+0.5);


	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(numchars, GL_UNSIGNED_BYTE, c);	// Draws The Display List Text
	glPopAttrib();				



	
	
	
	

	 // Have OpenGL generate a texture object handle for us
        glGenTextures(1, &GLtextureID );
    

		
        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, GLtextureID );
        
        // Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,0x812f);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,0x812f);
		
        glTexImage2D( GL_TEXTURE_2D, 0,4, w,h, 0, 
                      GL_RGBA, GL_UNSIGNED_BYTE,  0);

	

	// TO TEXTURE

	// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0,0, w, h, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                // Set The Clear Color To Black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear Screen And Depth Buffer
 
		glViewport(0,0,screenwidth,screenheight);







 glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

    glMatrixMode( GL_PROJECTION );
	glPushMatrix();
    glLoadIdentity();
	
	
	glViewport( 0, 0,w, h );


    glOrtho( 0, w, h, 0, -1, 1 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
	
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);



	 glDisable(GL_LIGHTING);


	 
	glEnable( GL_TEXTURE_2D ); // Need this to display a texture

	// Bind the texture to which subsequent calls refer to
    glBindTexture( GL_TEXTURE_2D,GLtextureID );

	int x=0;
	int y=0;
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







	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0,0, w, h, 0);


		glViewport(0,0,screenwidth,screenheight);









		  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                // Set The Clear Color To Black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear Screen And Depth Buffer








glDeleteLists(base, 96);							// Delete All 96 Characters
}


*/









void  glTexturedImage::KillTexture()									// Delete The Font List
{
	
	if(GLtextureID) glDeleteTextures( 1, &GLtextureID );
}






