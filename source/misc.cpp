#ifndef _gdlmisc_
#define _gdlmisc_

#include "Gdl.h"
#include <stdarg.h>

void Gdl_showMsg(const char * format, ...)
{		va_list va;
		va_start(va, format);
		vsprintf(dbg,format,va);
		va_end(va);
	#ifdef GP32
		 clDeep   color = pc2gpColor(0xf6f30a);
		 u32 stringSize = strlen(dbg);
		 while (!(gp_getButton() == BUTTON_L))
		 {		clrScr(0);
				gp_drawString (10,10,stringSize,dbg,color,pixel);
				gp_drawString (14,20,7,"press L",color,pixel);
				Gdl_flip();
		 };
		 while(gp_getButton()&BUTTON_L);
	#endif
}

u16 pc2gpColor(u32 color)
{      register u32 r,g,b;
       r = (color>>19)&0x1f;
       g = (color>> 11)&0x1f;
       b = (color>>3)&0x1f;
       return (r<<11)|(g<<6)|(b<<1)|0;  
}

// count frame per second .. only launch this routine one time per frame !
u32 countFps(void)
{  	static u32 tm=0, fps=0, fps_count=0 ;
	u32 time = GetTickCount();
  	fps++ ;  if(tm + tickPerSecond <= time) { fps_count=fps; fps=0; tm=time; }
    return fps_count ;
}

u32 computeDec(u32 value)
{	u32 v=1, dec=0;
	while(v<value) { v<<=1; dec++; }
	return dec ;
}

u32 divide(u32 divadeWhat, u32 byHowMany)
{	if(!byHowMany) return 0;
	u32 nb=0;
	while(divadeWhat>=byHowMany)
		{	divadeWhat-=byHowMany;
			nb++;
		};
	return nb;
}

#define myabs(n) if(n<0)n=-n

// ------------------ //

/* this code is not mine,
 just get the Bresenham line algorithm and change it to directly poke into the framebuffer,
 also change it to blit a colored line instead of a single color
 yet also add clipping
*/

void ligne(int xi,int yi,int xf,int yf, clDeep *line) {
clDeep *p = pixel + xi + yi*WIDTH ;
int dx,dy,i,xinc,yinc,cumul,x,y ;
x = xi ;
y = yi ;
dx = xf - xi ;
dy = yf - yi ;
xinc = ( dx > 0 ) ? 1 : -1 ;
yinc = ( dy > 0 ) ? 1 : -1 ;
dx = abs(dx) ;
dy = abs(dy) ;
*p = *line++ ;
if ( dx > dy ) {
  cumul = dx>>1 ;
  for ( i = 1 ; i <= dx ; i++ ) {
    p += xinc ;
    cumul += dy ;
    if (cumul >= dx) {
      cumul -= dx ;
      p += yinc*WIDTH ;
    }
    *p = *line++ ;     } }
  else {
  cumul = dy>>1 ;
  for ( i = 1 ; i <= dy ; i++ ) {
    p += yinc*WIDTH ;
    cumul += dx ;
    if ( cumul >= dy ) {
         cumul -= dy ;
         p += xinc ;
       }
    *p = *line++ ;
     } }
}

/*

void _ligne(int xi,int yi,int xf,int yf, clDeep *line) {
clDeep *p = pixel + xi + yi*WIDTH ;
int dcx, xclip=0 ;
if(xf<0){ xclip=1 ;
          dcx=xi ;
} else if(xf > (int)(WIDTH-1)){
          xclip=1 ;
          dcx = (WIDTH-1)-xi ;
       }
int dx,dy,i,xinc,yinc,cumul,x,y ;
x = xi ;
y = yi ;
dx = xf - xi ;
dy = yf - yi ;
xinc = ( dx > 0 ) ? 1 : -1 ;
yinc = ( dy > 0 ) ? 1 : -1 ;
myabs(dx);
myabs(dy);
*p = *line++ ;
if ( dx > dy ) {
  cumul = dx>>1 ;
  for ( i = 1 ; i <= dx ; i++ ) {
    p += xinc ;  if(xclip) if(!dcx--) return ;
    cumul += dy ;
    if (cumul >= dx) {
      cumul -= dx ;
      p += yinc*WIDTH ;
    }
    *p = *line++ ;     } }
  else {
  cumul = dy>>1 ;
  for ( i = 1 ; i <= dy ; i++ ) {
    p += yinc*WIDTH ;
    cumul += dx ;
    if ( cumul >= dy ) {
         cumul -= dy ;
         p += xinc ; if(xclip) if(!dcx--) return ;
       }
    *p = *line++ ;
     } }
}
*/
#ifdef includeMathTable

	#include "./tablesMath.h"
	// show a colored line from a point, an angle and a size, is clipped but start point must be in screen
	void aline(int x, int y, int angle, int size, clDeep *line)
	{  int xx, yy, za = 128-angle ; // 90°-angle -> (512/360)*90 - angle -> 128-angle
	   xx = x + ((size*COS(angle))>>16) ;
	   yy = y + ((size*SIN(angle))>>16) ;
	   if(yy > ((int)HEIGHT)-1){ xx += (TAN(za)*(yy-(HEIGHT-1)))>>16 ; yy=HEIGHT-1 ; }
		else if(yy < 0) { xx -= (TAN(za)*(-yy))>>16 ; yy=0 ; }
	   ligne(x,y,xx,yy,line) ;
	}

u32 getRotatePos(int x, int y, int angle, int size)
{  int xx, yy ; // 90°-angle -> (512/360)*90 - angle -> 128-angle
   xx = x + ((size*COS(angle))>>16) ;
   yy = y + ((size*SIN(angle))>>16) ;
   return (xx<<16)|(yy&0xffff);
}

void savelineMove(int x,int y,int xx,int yy,int*mx,int*my)
{	clDeep *p = pixel + x + y*WIDTH ;
	int dx,dy,i,xinc,yinc,cumul;
	dx = xx - x ;
	dy = yy - y ;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	myabs(dx) ;
	myabs(dy) ;

	printlr("line from %i.%i to %i.%i dx %i dy %i",x,y,xx,yy,dx,dy);
	
	if(dx>dy)
	{	cumul = dx>>1 ;
		for (i=1 ; i<=dx ; i++)
		{	  *mx++ = xinc ;
			  *my++ = 0;
				//printlr("x move_ %i",xinc);
			  cumul += dy ;
			  if (cumul >= dx)
				{	cumul -= dx ;
					*my++ = yinc*WIDTH ;
					*mx++ = 0;
					//printlr("y move_ %i",yinc);
				}
		}
	}
	  else
	{ cumul = dy>>1 ;
	  for (i=1 ; i<=dy ; i++)
	  {	*my++ = yinc;
	    *mx++ = 0;
		//printlr("y move %i",yinc);
		cumul += dx ;
		if(cumul >= dy)
		{ cumul -= dy ;
		  *mx++ = xinc ;
		  *my++ = 0;
		  //printlr("x move %i",xinc);
		}
	  }
	}

	  *mx++ = *my++ = 0xffff;
}



#endif

/*
void logAsciiTable(void)
{ log("\n\n.. asciiTable ..\n\n");
  for(u32 x=0;x<256;x++)
	printlr("%i\t[%c]",x,x);
}*/

/*{ u32 lineSize = 16; u32 n=0, x=0;
  log("\n\n.. asciiTable ..\n\n");
  for(x=0;x<lineSize;x++)
  { if(x<10) printl("  %i",x);
     else    printl(" %i",x);
  }
  log("\n");
  while(n<256)
  { for(x=0;x<lineSize;x++) printl("  %c",(n+x)-127);
	log("\n");
	n+=lineSize;	
  };
}*/

#endif
