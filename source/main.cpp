
#include "gdl.h"

#include "./gfx/star.h"
#include "./gfx/tile10.h"
#include "./gfx/tile54.h"
#include "./gfx/zeldaTiles.h"
#include "./gfx/zeldaTiles.map.h"
//#include "./gfx/PRZYSTAN.map.h"
//#include "./gfx/PRZYSTAN_Tiles.h"
#include "./gfx/course8.mod.h"

void drawOutZone(outzone*out)
{	gp_drawLine16(out->x,out->y,out->x+out->width,out->y,0,pixel);
	gp_drawLine16(out->x,out->y,out->x,out->y+out->height,0,pixel);
	gp_drawLine16(out->x+out->width,out->y,out->x+out->width,out->y+out->height,0,pixel);
	gp_drawLine16(out->x,out->y+out->height,out->x+out->width,out->y+out->height,0,pixel);
}


u32 freq=1, freqTable[] = { 22,33,40,50,66,80,133 };

//char blitspeed[256]; u32 blitspeedsz = 0;

u32 doBlitSpeedTest(void)
{	int*pos = (int*)malloc(10240);
	u32 totaltick=0, tickNbr, nb, c, n;
	
	for(c=0;c<4;c++)
	{	for(n=0;n<128;n++)
		{	pos[n]=		(rand()%380)-30;
			pos[n+128]=	(rand()%300)-30;
			pos[n+256]=	(rand()%starFrmNb);
		};
		nb=64;
		tickNbr = GetTickCount();
		while(nb--)
		{	drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
		};
	
		tickNbr = GetTickCount()-tickNbr;
		totaltick += tickNbr;
	};
	totaltick >>= 2;
	free(pos);
	//sprintf(blitspeed,"draw %i star in %i ticks",64*96,tickNbr);
	//blitspeedsz = strlen(blitspeed);
	return totaltick;
}

	void screenTest(void)
	{	saveBlitLimit();
		fullBlitLimit();
		clrScr(0);
		mkprints(84,100,".. please wait ..");
		mkprints(70,120,"test blit & lcd speed");
		mkprints(102,130," . %i mhz .",currentFrequency);
		Gdl_flip();
		clrScr(0);
		mkprints(84,100,".. please wait ..");
		mkprints(70,120,"test blit & lcd speed");
		mkprints(102,130," . %i mhz .",currentFrequency);
		Gdl_flip();

		u32 time = GetTickCount();
		u32 nb=64;
		
		while(nb--)
			{ while ((rLCDCON1 >> 18) !=   1) asm volatile("nop\n""nop\n""nop\n");
			  while ((rLCDCON1 >> 18) != 319) asm volatile("nop\n""nop\n""nop\n");
			  while ((rLCDCON1 >> 18) !=   1) asm volatile("nop\n""nop\n""nop\n");
			  while ((rLCDCON1 >> 18) != 319) asm volatile("nop\n""nop\n""nop\n");
			};
			
		tick = GetTickCount();
		time = tick - time;

		u32 frmDelay = time>>=7;
		shell.print("\n frmDellay %i\nfps %i",frmDelay,1000/frmDelay);
		Gdl_flip(); Gdl_flip();
		u32 tme = doBlitSpeedTest();

		u32 maxBlitPerFrm = (96*64*frmDelay)/tme;
		shell.print("\n maxBlit %i",maxBlitPerFrm);
		//Gdl_showMsg("%iMhz, %ifps (%ims), maxBlt %i",currentFrequency,1000/frmDelay,frmDelay,maxBlitPerFrm);
		clrScr(0);
		mkprints(10,230,"%iMhz, %ifps (%ims), maxBlt %i",currentFrequency,1000/frmDelay,frmDelay,maxBlitPerFrm);
		 Gdl_flip(); clrScr(0);
		mkprints(10,230,"%iMhz, %ifps (%ims), maxBlt %i",currentFrequency,1000/frmDelay,frmDelay,maxBlitPerFrm);
		 Gdl_flip();
		//gp_drawString(10,230,blitspeedsz,blitspeed,color,pixel);
		loadBlitLimit();
	}

//#include "gpstdio.h"

int main()
{	/*const char txt_ex[] = {"This is a file I/O sample.\nYou can access SMART MEDIA CARD with these FILE I/O APIs.\nhahahahahahahahahahaha"};
	ERR_CODE err_code;
	F_HANDLE h_file;
	
	GpFatInit();
	err_code = GpFileCreate("gp:\\test.txt", NOT_IF_EXIST, &h_file);
	err_code = GpFileWrite(h_file, txt_ex, strlen(txt_ex));
	GpFileClose(h_file);
	*/
	Gdl_initGp32(freqTable[freq],85);
	//initgpsdk();
	char debug[256];
	clDeep color = pc2gpColor(0xf6f30a);
/*	initgpsdk();
	const char * txt_ex = "This is a file I/O sample.\nYou can access SMART MEDIA CARD with these FILE I/O APIs.\nhahahahahahahahahahaha";
	F_HANDLE h_file;
	Gdl_showMsg("init fat..");
	
	GpDirCreate("gp:\\testdir\\",0);
	GpDirCreate("gp:\\testdir",0);
	Gdl_showMsg("create and write file!");
	GpFileCreate("gp:\\test.txt", NOT_IF_EXIST, &h_file);
	GpFileWrite(h_file, txt_ex, strlen(txt_ex));
	GpFileClose(h_file);
	*/
	

	
/*	clrScr(0);
  char buffer[255];
  char text[128];
  int  err;
  GPFILE *gpfile; 
  
    gpfile = smc_fopen("dev0:\\gpmm\\filetest.dat","r");
   if (gpfile)  gp_drawString(10,10,18,"smc_fopen :OK     ",0xF800,pixel);
    else         gp_drawString(10,10,18,"smc_fopen :ERROR  ",0xF800,pixel);

    err = smc_filesize(gpfile);
    sprintf (text,"filetest.dat size: %i ",err);
    gp_drawString(10,20,strlen(text),text,0xF800,pixel);

    err = smc_fread(buffer, 12, 1, gpfile);
    if (err == 12 )  gp_drawString(10,30,25,"Loading of 12 byte OK    ",0xF800,pixel);
    else gp_drawString(10,30,25,"Loading of 12 byte ERROR   ",0xF800,pixel);

    err = smc_ftell(gpfile);
    if (err == 12 )  gp_drawString(10,40,20,"smc_ftell:  OK     ",0xF800,pixel);
    else gp_drawString(10,40,20,"smc_ftell:  ERROR   ",0xF800,pixel);

    smc_fseek(gpfile, 20,SEEK_SET);
    err = smc_fread(buffer, 10, 1, gpfile);
    gp_drawString(10,60,10,"0123456789",0xF800,pixel);
    gp_drawString(10,70,10,buffer,0xF800,pixel);

    smc_fclose(gpfile);

    gpfile = smc_fopen("dev0:\\delete.me","w");
    if (gpfile) {
      int size=0;
      gp_drawString(10,80,10,"writing... ",0xF800,pixel);      
      char buffer1[20]="1234567890";
      char buffer2[20]="abcdefghij";
      size=smc_fwrite((u8*)buffer1 ,10, 1,gpfile);
      if (size == 10) gp_drawString(10,90,12,"10 bytes ok     ",0xF800,pixel);
      size=smc_fwrite((u8*)buffer2 ,10, 1,gpfile);
      if (size == 10) gp_drawString(10,100,12,"10 bytes ok     ",0xF800,pixel);
		mkprints(10,110,"now close ..",0xF800,pixel);
		Gdl_flip();
      smc_fclose(gpfile);
    }*/


//  while (1) { if (gp_getButton()&BUTTON_A) gp_Reset();  }




	u32 fps,oldfps=0xffff,dbgSize=0,old_tick=0;
	map myMap, myMap2;	
	unCrunchGfm(zeldaTiles,zeldaTilesFrmNb);
	unCrunchGfm(tile10,tile10FrmNb);
	unCrunchGfm(tile54,tile54FrmNb);
	//unCrunchGfm(PRZYSTAN_Tiles,PRZYSTAN_TilesFrmNb);

	outzone * out = createOutzone(116,10,200,210);
	outzone * out2= createOutzone(10,10,104,210);
	//myMap.set((u16*)zeldaTilesMap,zeldaTiles,zeldaTilesFrmNb,16,16,80,60,0,0,/*out*/0,0);
	myMap.set((u16*)zeldaTilesMap,zeldaTiles,zeldaTilesFrmNb,16,16,80,60,0,0,out,0);
	//myMap2.set((u16*)PRZYSTAN,PRZYSTAN_Tiles,PRZYSTAN_TilesFrmNb,32,32,20,16,0,0,out2,0);
	
	myMap2.set((u16*)zeldaTilesMap,zeldaTiles,zeldaTilesFrmNb,16,16,80,60,0,0,out2,0);
	myMap2.setScroll(433,296);

	unCrunchGfm(star,starFrmNb);
	anim * mystar =  setAnim(star,starFrmNb,80);
	anim * t10 = setAnim(tile10,tile10FrmNb,150);
	anim * t54 = setAnim(tile54,tile54FrmNb,320);
	
	myMap.setAnimatedTile(10,t10);
	myMap.setAnimatedTile(54,t54);
	myMap2.setAnimatedTile(10,t10);
	myMap2.setAnimatedTile(54,t54);
	
//	setBlitLimit(100,100,200,200);

	u32 xxx=110,yyy=110;setBlitLimit(out);

	//console myshell;
	//myshell.set(-1,-1,20,10);	
	

	screenTest();
	//shell.print("----------\n@0h@1e@0l@1l@0o @1w@0o@1r@0l@1d");
	 while (1)
		 {	fps = countFps();
			if(fps && (fps != oldfps || tick - old_tick > 1000) )
			{	sprintf(debug,"%i/%ifps . %iMhz . %i",fps,currentFps,freqTable[freq],tick>>10);
				dbgSize = strlen(debug);
				oldfps = fps;
				old_tick = tick;
				//shell.print("@0tick@2..@1%i\n",tick>>10);
			}
				//clrScr(0);
				myMap2.draw90();
				myMap.draw90();
				drawOutZone(out);
				drawOutZone(out2);
				
				static u32 hway=2, wway=8;
				u32 rtn = myMap.scroll(hway|wway,1);
				if(rtn)
				{	if(rtn&1) hway=2;
					if(rtn&2) hway=1;
					if(rtn&4) wway=8;
					if(rtn&8) wway=4;
				}

				static u32 zhway=2, zwway=8;
				rtn = myMap2.scroll(zhway|zwway,1);
				if(rtn)
				{	if(rtn&1) zhway=2;
					if(rtn&2) zhway=1;
					if(rtn&4) zwway=8;
					if(rtn&8) zwway=4;
				}

				//drawOutZone(out);
			/*	
				drawAnim(&mystar,10,230);
				drawAnim(&mystar,10,10);
				drawAnim(&mystar,30,30);
				
			*/	playAnim(&mystar,xxx,yyy);

				gp_drawString (120,12,dbgSize,debug,color,pixel);
				//gp_drawString(10,230,blitspeedsz,blitspeed,color,pixel);
				//*scrEnd[nflip] = pink;
				Gdl_flip();
			if( gp_getButton() & BUTTON_START ) gp_Reset();
			if(	gp_getButton() & BUTTON_SELECT )
			{	//gp_startSoundmixer(0); // The modrenderer works at 22050 khz 
				//gp_startModfile(course8); // adds mod to mixer
				drawGdlShell ^= 1;
				while(gp_getButton() & BUTTON_SELECT);
			}
			
			if( !(gp_getButton() & BUTTON_L ))
			{	if( gp_getButton() & BUTTON_UP )		myMap.scroll(1,1);
				if( gp_getButton() & BUTTON_DOWN )		myMap.scroll(2,1);
				if( gp_getButton() & BUTTON_LEFT )		myMap.scroll(4,1);
				if( gp_getButton() & BUTTON_RIGHT )	myMap.scroll(8,1);
			}	else
				{	if( gp_getButton() & BUTTON_UP ) yyy--;
					if( gp_getButton() & BUTTON_DOWN ) yyy++;
					if( gp_getButton() & BUTTON_LEFT ) xxx--;
					if( gp_getButton() & BUTTON_RIGHT ) xxx++;
				}
			
			//if( gp_getButton() & BUTTON_R ) setBlitLimit(out);
			if( gp_getButton() & BUTTON_A )
			{	if(freqTable[freq] < 133) freq++; else freq = 0;
				while(gp_getButton() & BUTTON_A);
				gp_setCpuspeed(freqTable[freq]);
				currentFrequency = freqTable[freq];
				currentFps  = 	gp_initFramebuffer(screenBuffer[nflip],16,screenRefreshRate);
				//currentFps +=	gp_initFramebuffer(screenBuffer[1],16,screenRefreshRate);
				//currentFps>>=1;
				shell.print("\n@2* @1%iMhz@0.@1%iHz",currentFrequency,currentFps);
				screenTest();

				//
				//if( gp_getButton() & BUTTON_B ) screenTest();
			}
		 };
}
