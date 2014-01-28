// transparent blit routine for Gdl²
// (C) 2k4/2k7 by r043v, cannot be used for any commercial purpose

#ifndef _gdlblt_
#define _gdlblt_

#include "gdl.h"

blitLimit savedBlitLimit;
blitLimit internalBlitLimit;

// currentBlitLimit
clDeep	  *scrStart[2];
clDeep		*scrEnd[2];
int frmWidth, frmWidthStart, frmWidthEnd;

void fullBlitLimit(void)
{	scrStart[0] = screenBuffer[0];
	scrStart[1] = screenBuffer[1];
	scrEnd[0] = screenBufferEnd[0];
	scrEnd[1] = screenBufferEnd[1];
	frmWidth  = WIDTH;
	frmWidthStart = 0;
	frmWidthEnd   = WIDTH;
}

void drawBlitLimit(void)
{	
}

void saveBlitLimit(blitLimit*limit)
{	if(!limit) limit = &savedBlitLimit;
	for(u32 c=0;c<2;c++)
	{	limit->scrStart[c]	= scrStart[c];
		limit->scrEnd[c]	=	scrEnd[c];
	}
    limit->frmWidth			= frmWidth;
    limit->frmWidthStart	= frmWidthStart;
    limit->frmWidthEnd   	= frmWidthEnd;
}

void loadBlitLimit(blitLimit*limit)
{	if(!limit) limit = &savedBlitLimit;
	for(u32 c=0;c<2;c++)
	{	scrStart[c]	=	limit->scrStart[c];
		scrEnd[c]	=	limit->scrEnd[c];
	}
    frmWidth		= limit->frmWidth;
    frmWidthStart	= limit->frmWidthStart;
    frmWidthEnd  	= limit->frmWidthEnd;
}

void internalSaveBlitLimit(void)
{	saveBlitLimit(&internalBlitLimit);
}

void internalLoadBlitLimit(void)
{	loadBlitLimit(&internalBlitLimit);
}

/*
void setBlitLimit(clDeep *start, clDeep *end, u32 widthStart, u32 widthEnd)
{      scrStart  = start;
       scrEnd    = end  ;
       frmWidth  = widthEnd-widthStart;
       frmWidthStart = widthStart;
       frmWidthEnd   = widthEnd;
}
*/

blitLimit * createBlitLimit(u32 x, u32 y, u32 sx, u32 sy)
{	y = 239-y; u32 y1 = y-sy; u32 x1 = x+sx;

	blitLimit * limit = (blitLimit*)malloc(sizeof(blitLimit));

	for(u32 c=0;c<2;c++)
	{	limit->scrStart[c]	= &( (screenBuffer[c])[x*240 + y] );
		limit->scrEnd[c]	= &( (screenBuffer[c])[x1*240 + y1]); 
	}
    limit->frmWidth			= y-y1;
    limit->frmWidthStart	= y1;
    limit->frmWidthEnd   	= y;
	
	return limit;
}

void setBlitLimit(u32 x, u32 y, u32 x1, u32 y1)
{	if(x>319||x1>319||y>239||y1>239) Gdl_showMsg("setBlitLimit error! %i %i %i %i",x,y,x1,y1);
	y1 = 239-y1; y = 239-y;
	scrStart[0]	= &( (screenBuffer[0])[x*240 + y] );
	scrStart[1]	= &( (screenBuffer[1])[x*240 + y] );
	scrEnd[0]	= &( (screenBuffer[0])[x1*240 + y1] ); //xy2buf(screenBufferEnd[0],x1,y1);
	scrEnd[1]	= &( (screenBuffer[1])[x1*240 + y1] ); //xy2buf(screenBufferEnd[1],x1,y1);
	frmWidth  = y-y1;
    frmWidthStart = y1;
    frmWidthEnd   = y;
}

void drawGfm(clDeep *Gfm, int x, int y)
{    
     #ifdef use32b
      int sx = Gfm[2]>>16 ; u32 sy = Gfm[2]&65535 ;
     #else
      int sx = Gfm[0]; int sy = Gfm[1];
     #endif
     
	 #ifdef GP32
	 	{ int tmp=x ; x=(239-y)-sy; y=tmp; }
	 #endif

     if(x >= frmWidthStart && x + sx < frmWidthEnd)
		{	udrawGfm(Gfm,&pixel[y*WIDTH+x]) ;
            return;
        }

     if(x < (frmWidthStart-sx) || x > frmWidthEnd) return ;// out of screen on x
		
     if(x >= frmWidthStart) // clip right only
     {   u32 max = frmWidthEnd-x ;  u32 lnb, sze ;
         clDeep *scr = &pixel[y*WIDTH+x] ;
		 if(scr > scrEnd[nflip]) return ; // out of screen at down
         
         u32 upClip = (scr + sy*WIDTH > scrEnd[nflip]) ; // is clipped at down ?

         #ifdef use32b
          Gfm += 3;
         #else
          Gfm += 2;
         #endif
         
         if(scr < scrStart[nflip]) // is clipped at up ?
         {  if(scr + sy*WIDTH < scrStart[nflip]) return ; // out of screen at up
            do{ lnb = *Gfm++ ;
                while(lnb--) { Gfm++ ; Gfm += *Gfm++ ; };
                scr += WIDTH ; sy-- ;
            } while(scr < scrStart[nflip]) ;
         }

         clDeep *screen = scr ; u32 c = 0 ; clDeep * lend ;
         while(c < sy)
         {  lnb = *Gfm++ ; lend = scr + max ;
            while(lnb--) { scr += *Gfm++ ; sze = *Gfm++ ;
                           if(scr + sze < lend) asm_memcpy(scr,Gfm,sze<<clDeepDec) ;
                           else if(scr < lend) asm_memcpy(scr,Gfm,(lend-scr)<<clDeepDec) ;
                           Gfm += sze ;    scr+=sze ;
            };  scr = screen + WIDTH*(++c) ;
            if(upClip) if(scr > scrEnd[nflip]) return ;
         };
     } else if(x+sx < frmWidthEnd) { // clip left only
         u32 lnb, sze ; clDeep *s = &pixel[y*WIDTH + frmWidthStart] ;

         if(s > scrEnd[nflip]) return ; // out of screen at up
         u32 upClip = (s + sy*WIDTH > scrEnd[nflip]) ; // is clipped at up ?

         #ifdef use32b
          Gfm += 3;
         #else
          Gfm += 2;
         #endif         

         if(s < scrStart[nflip]) // is clipped at down ?
         {  if(s + sy*WIDTH < scrStart[nflip]) return ; // out of screen at down
            do{ lnb = *Gfm++ ;
                while(lnb--) { Gfm++ ; Gfm += *Gfm++ ; };
                s += WIDTH ; sy-- ;
            } while(s < scrStart[nflip]) ;
         }
         
         clDeep*scr = s+x ;
         scr -= frmWidthStart ;
         clDeep *screen = scr ;
         u32 c=0 ; u32 size ;
         
         while(c < sy)
         {  lnb = *Gfm++ ;
            while(lnb--) { scr += *Gfm++ ; sze = *Gfm++ ;
                           if(scr >= s)   asm_memcpy(scr,Gfm,sze<<clDeepDec) ;
                           else if(scr + sze > s) { size = (scr + sze)-s ;
                                                    asm_memcpy(s,Gfm+(sze-size),size<<clDeepDec) ;
                                                  }
                           Gfm += sze ;    scr+=sze ;
            };  scr = screen + WIDTH*(++c) ; s = scr+frmWidthStart ; s -= x ;
            if(upClip) if(s > scrEnd[nflip]) return ;
         };
     } else return ;
}


void udrawGfm(clDeep*Gfm,clDeep*scr)
{
   #ifdef use32b
    Gfm+=2 ; u32 sy = (*Gfm++)&65535 ;
   #else 
    Gfm++; u32 sy = *Gfm++;
   #endif
    
    u32 lnb, sze ;
    
    if(scr > scrEnd[nflip]) return ; // out of screen at up
    u32 upClip = (scr + sy*WIDTH > scrEnd[nflip]) ; // is clipped at up ?

    if(scr < scrStart[nflip]) // is clipped at down ?
    {  if(scr + sy*WIDTH < scrStart[nflip]) return ; // out of screen at down
       do{    lnb = *Gfm++ ;
              while(lnb--) { Gfm++ ; Gfm += *Gfm++ ; };
              scr += WIDTH ; sy-- ;
       } while(scr < scrStart[nflip]) ;
    }

    clDeep *screen = scr ;
    u32 c = 0 ;
    
    if(upClip)
     {  while(c < sy)
        {  lnb = *Gfm++ ;
           while(lnb--)	{	scr += *Gfm++ ; sze = *Gfm++ ;
								asm_memcpy(scr,Gfm,sze*2);
								Gfm += sze; scr += sze;
							};  scr = screen + WIDTH*(++c) ;
           if(scr > scrEnd[nflip]) return ;
        };
     }
    else
     {  while(c < sy)
        {  lnb = *Gfm++ ;
           while(lnb--){	scr += *Gfm++ ; sze = *Gfm++ ;
							asm_memcpy(scr,Gfm,sze*2);
							Gfm += sze; scr += sze;
						};  scr = screen + WIDTH*(++c) ;
        };
     }
} 

void udraw4bGfm(u8*Gfm,clDeep*scr,clDeep*mypal)
{
#ifdef use32b
  Gfm+=3 ;  u32 clNum=*Gfm++ ; Gfm+=4 ;
  u32 sx   = *(u16*)Gfm ; Gfm+=2 ;
  u32 sy   = *(u16*)Gfm ; Gfm+=2 ;
  Gfm+=4 ;
  u32*pal;
  if(mypal) pal = mypal;
   else		pal = (u32*)Gfm;
  Gfm+=(4*clNum);

  u32 cnt=0, c, jump, size, p1, p2 ;

  //printf("\n\nout size : %i\n%i colors { %x",outSize,clNum,*pal) ;
  //for(int c=1;c<clNum;c++) printf(",%x",pal[c]) ; printf(" }\nsize : %i*%i",sx,sy) ;

	clDeep * s;

  while(cnt++ < sy)
  {    c = *Gfm++ ; //printf("\n* line %i, %i sublines",cnt,c) ;
       s = scr;
	   while(c--) { jump = *Gfm++ ;
					size = *Gfm++ ;
					scr+=jump;
                    while(size > 1) { p1 = (*Gfm)>>4 ; p2 = (*Gfm)&15 ;
                                      size-=2 ;
									  *scr++ = pal[p1] ; *scr++ = pal[p2] ;
                                      ++Gfm ;
                                    };
                    if(size!=0) { //printf(" + %x",*data);
									*scr++ = pal[*Gfm++] ;
								}
                  };
	   scr = s+WIDTH;
  };
#endif
} 

#ifdef use16b

// devkitarm is not 4bytes aligned ?

u32 readu32(u8*data)
{	u32 out = *data++;
		out += (*data++)<<8;//*(u32*)data ;
		out += (*data++)<<16;
		out += (*data)<<24;
	return out;
}

u16 readu16(u8*data)
{	u16 out = *data++;
		out += (*data++)<<8;
	return out;
}

 // convert a 4b Gfm to a 16b Gfm
 
u16 * data2Gfm(u8*data) // convert a 4b Gfm to a 16b Gfm
{ //
	data+=3 ;  u32 clNum=*data++ ; data+=4 ;
	//Gdl_showMsg("enter data2Gfm! color %i",clNum);
  u32 sx   = readu16(data); data+=2 ;
  u32 sy   = readu16(data); data+=2 ;
 // Gdl_showMsg("size : %ix%i",sx,sy);
  
  //Gdl_showMsg("get out size .. data = 0x%x",data);
  u32 outSize = readu32(data); data+=4;
	
	//Gdl_showMsg("outSize %i",outSize);

  //outSize-=12;
  outSize>>=1; // 16b size is 12b and 2x smaller than 32b Gfm
//	Gdl_showMsg("allocate %i bytes",outSize);
  u16 pal[16];
  u16 *Gfm =  (u16*)malloc(outSize) ;

//Gdl_showMsg("%i.%i.%i   %i",sx,sy,clNum,outSize);

  {  int*pal32 = (int*)data;
     for(u32 n=0;n<clNum;n++)
           pal[n] = pc2gpColor(readu32((u8*)&pal32[n]));
  }

	//Gdl_showMsg("pal create!");

  data+=(4*clNum);
  u16 *o = Gfm;
  u32 cnt=0, c, jump, size, p1, p2 ;

  *o++ = sx;
  *o++ = sy;

  while(cnt++ < sy)
  {    *o++ = c = *data++ ; //printf("\n* line %i, %i sublines",cnt,c) ;
       while(c--) { jump = *data++ ; size = *data++ ; *o++ = jump ; *o++ = size ;
                    while(size > 1) { p1 = (*data)>>4 ; p2 = (*data)&15 ;
                                      size-=2 ; *o++ = pal[p1] ; *o++ = pal[p2] ;
                                      ++data ;
                                    };
                    if(size) *o++ = pal[(*data++)] ;
                  };
  };  return Gfm ;
}

#else

clDeep * Gfm2array(clDeep *Gfm)
{ int sx = Gfm[2]>>16, sy = Gfm[2]&0xffff ;
  clDeep *array=(clDeep *)malloc(sx*sy*4) ; clDeep *o=array ;
  memset(array,0xFF,sx*sy*4) ;
  int cnt=0, c ; clDeep *gPtr = Gfm + 3 ;
  int size ;
  while(cnt<sy)
  {    c = *gPtr++ ;
       while(c--) { array += *gPtr++ ; size = *gPtr++ ;
                    asm_memcpy(array,gPtr,size*4) ;
                    gPtr+=size ; array+=size ;
                  }; array = o + sx*(++cnt) ;
  }; return o ;
}

 // convert a 4b Gfm to a 32b Gfm
clDeep * data2Gfm(unsigned char *data)
{ //unsigned char *d = data ;
  data+=3 ; u32 clNum=*data++ ; data+=4 ;
  u32 sx   = *(short*)data ; data+=2 ;
  u32 sy   = *(short*)data ; data+=2 ;
  int outSize = *(int*)data ; data+=4 ;
  //printf("\n%i colors %i*%i out size %i",clNum,sx,sy,outSize) ;
  clDeep *Gfm =  (clDeep*)malloc(outSize) ;
  clDeep *pal =  (clDeep*)malloc(4*clNum) ;
  asm_memcpy(pal,data,4*clNum) ; data+=(4*clNum) ;
  clDeep *o = Gfm ;
  u32 cnt=0, c, jump, size, p1, p2 ;

  //printf("\n\nout size : %i\n%i colors { %x",outSize,clNum,*pal) ;
  //for(int c=1;c<clNum;c++) printf(",%x",pal[c]) ; printf(" }\nsize : %i*%i",sx,sy) ;

  *o++ = 0x6d6647 ;              // put signature "Gfm\0"
  *o++ = outSize ;               // put Gfm object size
  *o++ = sx<<16 | (sy & 65535) ; // put frame size x and y

  while(cnt++ < sy)
  {    *o++ = c = *data++ ; //printf("\n* line %i, %i sublines",cnt,c) ;
       while(c--) { jump = *data++ ; size = *data++ ; *o++ = jump ; *o++ = size ;
                    //printf("\n jmp %i sze %i | ",jump,size) ;
                    if(jump > sx || size > sx) {
                      //printf("\njump or size error ... pos %i",data-d) ;
                      //return 0 ;
                    }

                    while(size > 1) { p1 = (*data)>>4 ; p2 = (*data)&15 ;
                                      //printf(",%x,%x",p1,p2) ;
                                      size-=2 ; *o++ = pal[p1] ; *o++ = pal[p2] ;

                                      if(p1 >= clNum || p2 >= clNum) {
                                       //printf("\ndata error, out of pal ! ... pos %i ... data %i | %x | %c",data-d,*data,*data,*data) ;
                                        //return 0 ;
                                      }

                                      ++data ;
                                    };
                    if(size!=0) { //printf(" + %x",*data);
									*o++ = pal[(*data++)] ;
								}
                  };
  };
  *o = 0x2a2a2a2a ;
  addFreeEntry(Gfm);
  return Gfm ;
}

#endif

/*void logCldArray(u8 *Ar)
{ int sx=*Ar++, sy=*Ar++;
  printl("\n%i*%i",sx,sy);
  for(int y=0;y<sy;y++)
  { printl("\n");
    for(int x=0;x<sx;x++)
     if(Ar[x+y*sx]) printl("%i",Ar[x+y*sx]) ;
      else printl(" ");
  };
}*/

void unCrunchGfm(clDeep ** gfm, u32 frmNb)
{	
	#ifndef need90Rotate
		for(u32 c=0;c<frmNb;c++)
			gfm[c] = data2Gfm((u8*)(gfm[c]));
	#else
		// G.m4k'r not actually ready for sprite rotate, so do it in paint and invert frameset way at hand..
		clDeep ** frm = (clDeep**)malloc(4*frmNb);
		for(u32 c=0;c<frmNb;c++)
			frm[frmNb-1-c] = data2Gfm((u8*)(gfm[c]));
		asm_memcpy(gfm,frm,4*frmNb);
		free(frm);
	#endif
}

// do a box & a pixel by pixel test to detect colide (between 2 colide buffer, see a bit highter)
int colide(u8*s1,int x1,int y1,u8*s2,int x2,int y2)
{ int sx1=*s1++, sy1=*s1++ ;
  int sx2=*s2++, sy2=*s2++ ;

  if(x2<=x1+sx1 && x2+sx2>=x1)
   if(y2<=y1+sy1 && y2+sy2>=y1)
    {  int x,y ; // we are here if there is a box colide
       int spr1x=0,spr1y=0,spr2x=0,spr2y=0,szx,szy ;
        // compute the colide box
		if(x1 < x2) spr1x = x2 - x1 ;
		else if(x2 < x1) spr2x = x1 - x2 ;
			
		if(y1 < y2) spr1y = y2 - y1 ;
		else if(y2 < y1) spr2y = y1 - y2 ;
			
		if(x1 + sx1 >= x2 + sx2)
		{	if(x1 > x2) szx = (x2 + sx2) - x1 ;
			 else szx = sx2 ;
		} else if(x1 + sx1 < x2 + sx2) szx = (x1 + sx1) - x2 ;
			
		if(y1 + sy1 >= y2 + sy2)
		{	if(y1 > y2) szy = (y2 + sy2) - y1 ;
			 else szy = sy2 ;
		} else if(y1 + sy1 < y2 + sy2) szy = (y1 + sy1) - y2 ;

		if(szx > sx1) szx=sx1 ;
		if(szy > sy1) szy=sy1 ;

        u8*ps1 = s1+spr1x+spr1y*sx1 ;
        u8*ps2 = s2+spr2x+spr2y*sx2 ;

        // and do the pixel/pixel test
       	for(x=0;x<szx;x++)
       	 for(y=0;y<szy;y++)
		  if(ps1[x+y*sx1] && ps2[x+y*sx2]) return 1 ;
    }  return 0 ;
}

u8 *Gfm2cldArray(int *Gfm) // create a raw buffer used to compute colide (yet not a 1bit buffer..)
{ u32 sx = Gfm[2]>>16, sy = Gfm[2]&0xffff ;
  u8 *array=(u8*)malloc(sx*sy+2) ; u8 *o=array+2 ;
  *array++=sx; *array++=sy;  memset(o,0,sx*sy) ; // take care, sprite size must be < to 256 pixels!
  u32 cnt=0, c, size ; int *gPtr = Gfm + 3 ;
  while(cnt<sy)
  {    c = *gPtr++ ;
       while(c--) { array += *gPtr++ ; size = *gPtr++ ;
                    memset(array,1,size) ;
                    gPtr+=size ; array+=size ;
                  }; array = o + sx*(++cnt) ;
  };

  //logCldArray(o-2);
  return o-2 ;
}

#endif
