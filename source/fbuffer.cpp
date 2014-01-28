
#ifndef _gdlfbuffer_
#define _gdlfbuffer_

#include "gdl.h"

	#ifndef GP32
		u32 WIDTH, HEIGHT;
	#endif

    u32 tick=0;		// curent tick will be copied here
    clDeep *pixel=0;
   
    #ifdef usePtc
        int fwidth,fheight;
    #endif
    
    #ifdef useSdl
        SDL_Surface *screen = NULL;
        SDL_Joystick *joy = NULL;
    #endif

extern u32 done;

void	(*_onKey)	    (int key, int pushed)=0;
void	(*_onClick)		(int button, int clicked)=0;
void	(*_onMove)		(void)=0;
void	(*_onExit)      (void)=0;
void	(*_onWhell)		(int way)=0;
void	(*_onFocus)		(int focus)=0;
void	(*_onFileDrop)	(const char*path)=0;

u32 Gdl_processMsg(u32 msg, u32 arg1, u32 arg2);

u32 mouseLeftState=0;
u32 mouseMidlState=0;
u32 mouseRightState=0;
u32 mousex, mousey ;
u32 isAppActive = 1;
u32 isMouseHere = 0;

u32 screenRefreshRate=85;
u32 currentFrequency =33;

void Gdl_updateMsg(void) // will manage event and launch callback
{    
    #ifdef usePtc
           ptc_getMsg();
    #endif

    #ifdef useSdl
    SDL_Event event;
	/* Check for events */
	while (SDL_PollEvent (&event))
	{     u32 key;
       switch (event.type)
		{
			case SDL_KEYDOWN:
				key = event.key.keysym.sym;
			/* if press Ctrl + C, terminate program */
               // if ( (key == SDLK_c) && (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) ) done = 1;
                  if(key < keyArraySize)
        		  {	if(_onKey) _onKey(key,1);
              		lastKey[key]=keyArray[key];
                    keyArray[key]=1;
        		  }
				break;
			case SDL_KEYUP:
                 key = event.key.keysym.sym;
                  if(key < keyArraySize)
        		  {	if(_onKey) _onKey(key,0);
              		lastKey[key]=keyArray[key];
                    keyArray[key]=0;
        		  }
				break;
			case SDL_JOYBUTTONDOWN:
				/* if press Start button, terminate program */
				if ( event.jbutton.button == 8 )
					done = 1;
				break;
			case SDL_JOYBUTTONUP:
				break;
		    case SDL_MOUSEMOTION:
                mousex = event.motion.x;
                mousey = event.motion.y;
                isMouseHere = 1;
                if(_onMove) _onMove();
                break;
            case SDL_MOUSEBUTTONDOWN:
                isMouseHere = 1; 
                switch(event.button.button)
                {  case SDL_BUTTON_LEFT:   mouseLeftState=1;  if(_onClick)_onClick(-1,1); break;
                   case SDL_BUTTON_MIDDLE: mouseMidlState=1;  if(_onClick)_onClick( 0,1); break;
                   case SDL_BUTTON_RIGHT : mouseRightState=1; if(_onClick)_onClick( 1,1); break;
                }; break;
            case SDL_MOUSEBUTTONUP:
                isMouseHere = 1; 
                switch(event.button.button)
                {  case SDL_BUTTON_LEFT:   mouseLeftState=0;  if(_onClick)_onClick(-1,0); break;
                   case SDL_BUTTON_MIDDLE: mouseMidlState=0;  if(_onClick)_onClick( 0,0); break;
                   case SDL_BUTTON_RIGHT : mouseRightState=0; if(_onClick)_onClick( 1,0); break;
                }; break;
            case SDL_ACTIVEEVENT:
                if(event.active.state != SDL_APPMOUSEFOCUS)
                   isAppActive = event.active.gain;
                else isMouseHere = event.active.gain;
                break;
			case SDL_QUIT:
				done = 1;
				break;
			default:
				break;
		}
	}
    #endif
}

u32 Gdl_processMsg(u32 msg, u32 arg1, u32 arg2)
{
 #ifdef usePtc
    switch(msg)
	 { /* a key was pushed */	
        case WM_KEYDOWN:
    		{ u32 key = (arg1&0xFF);
              if(key < 256)
    		  {	if(_onKey) _onKey(key,1);
          		keyArray[key+512]=keyArray[key]; keyArray[key]=1;
    		  }
            }
		break;
     /* a key was released */
		case WM_KEYUP:
			 { u32 key = (arg1&0xFF);
              if(key < 256)
    		  {	if(_onKey) _onKey(key,0);
          		keyArray[key+512]=keyArray[key]; keyArray[key]=0;
    		  }
            }
		break;
	/* mouse left click */
		case WM_LBUTTONDOWN:
			if(_onClick) _onClick(-1,1);
			mouseLeftState=1;
		break;
	/* mouse left click end */
		case WM_LBUTTONUP:
			if(_onClick) _onClick(-1,0);
			mouseLeftState=0;
		break;
	/* mouse right click */
		case WM_RBUTTONDOWN:
			if(_onClick) _onClick(1,1);
			mouseRightState = 1 ;
		break;
	/* mouse right click end */
		case WM_RBUTTONUP:
			if(_onClick) _onClick(1,0);
			mouseRightState = 0 ;
		break;
	/* mouse middle click */
		case WM_MBUTTONDOWN:
			if(_onClick) _onClick(0,1);
			mouseMidlState = 1 ;
		break;
	/* mouse middle click end */
		case WM_MBUTTONUP:
			if(_onClick) _onClick(0,0);
			mouseMidlState = 0 ;
		break;
    /* a file is dropped onto the app */
		case WM_DROPFILES: 
			{	char *path = (char*)malloc(512);
				u32 nb = DragQueryFile((HDROP)arg1,0xffffffff,path,256);
				for(u32 n=0;n<nb;n++)
					{	DragQueryFile((HDROP)arg1,n,path,256);
						if(_onFileDrop) _onFileDrop(path);
					}
				DragFinish((HDROP)arg1); // say at wdows we have finish
				free(path);
			}
		break;
    /* mouse has move */
		case WM_MOUSEMOVE:
            isMouseHere = 1;
			mouseLeftState = (((int)arg1) & MK_LBUTTON);
			if(_onMove) _onMove();
		break;
    /* whell rolled */
		case 0x020A : 
			{	int way = ((int)arg1) < 0 ; // way == 1 -> whell go down
				if(_onWhell) _onWhell(way);
			}
		break;
    /* focus killed */
		case WM_KILLFOCUS:
            isAppActive = 0;
			if(_onFocus) _onFocus(0);
		break;
    /* focus set */
		case WA_CLICKACTIVE:
		case WA_ACTIVE:
		case WM_SETFOCUS:
             isAppActive = 1;
			if(_onFocus) _onFocus(1);
		break;
    /* app closed */
		case WM_CLOSE:
             Gdl_exit(1);
		break;
	/* full screen switch */
        case 0x42424242:
             
        break;
	/* mouse leave windows */
		case WM_NCMOUSEMOVE:
        //case WM_CAPTURECHANGED:
            isMouseHere = 0; 
			//if(_onMouseOut) _onMouseOut();
		break;
		default: return 0;
  };
  #endif
  return 1;
}

 /* Gdl callback definition */

void Gdl_iniCallback( void	(*onKey)	    (int key, int pushed)=0,
					  void	(*onClick)		(int button, int clicked)=0,
					  void	(*onMove)		(void)=0,
					  void	(*onExit)       (void)=0,
					  void	(*onWhell)		(int way)=0,
					  void	(*onFocus)		(int focus)=0,
 					  void	(*onFileDrop)	(const char*path)=0
#ifdef usePtc
					  ,void  (*onAfterZoom)	(void*bf,u32 w,u32 h,u32 pitch)=0
#endif
      )
  { if(onKey)      _onKey       = onKey;
    if(onClick)    _onClick     = onClick;
    if(onFocus)    _onFocus     = onFocus;
    if(onMove)     _onMove      = onMove;
    if(onFileDrop) _onFileDrop  = onFileDrop;
    if(onExit)     _onExit      = onExit;
    if(onWhell)    _onWhell     = onWhell;
	#ifdef usePtc
		if(onAfterZoom) ptc_setAfterZoomCallBack(onAfterZoom);
	#endif
  }

void inikey(void);

#ifdef GP32
	clDeep * screenBuffer[2];
	clDeep * screenBufferEnd[2];
	u32		 nflip=1;
	u32 GetTickCount(void) { return (gp_getRTC())<<4; }
	//#define GetTickCount gp_getRTC
#endif



u32 Gdl_init(void)
{	
	#ifndef GP32
		char * title = "GdlApp";
		return Gdl_init(title,640,480);
	#else
		return Gdl_initGp32(currentFrequency,screenRefreshRate);
	#endif
}

u32 currentFps=0;

#ifdef GP32
	u32  Gdl_initGp32(u32 frequency,u32 screenRate)
	{	//gp_setCpuspeed(frequency);
		return Gdl_init(0,frequency,screenRate);
	}
#endif

console shell;
u32 drawGdlShell = 0;

u32 Gdl_init(char* appTitle, u32 width, u32 height) // open you a framebuffer
{   
	#ifndef GP32
		HEIGHT = height; WIDTH = width;
	#endif
	
    inikey();

	#ifdef GP32
		gpEnableCache();
		screenRefreshRate = height;
		currentFrequency = width;
		gp_setCpuspeed(currentFrequency);
		screenBuffer[0] = (clDeep*)FRAMEBUFFER1;
		screenBuffer[1] = (clDeep*)FRAMEBUFFER2;
		screenBufferEnd[0] = &( (screenBuffer[0])[(320*240)-1] );
		screenBufferEnd[1] = &( (screenBuffer[1])[(320*240)-1] );
		pixel =  screenBuffer[nflip];

		currentFps  = 	gp_initFramebuffer(screenBuffer[0],16,screenRefreshRate);
		currentFps +=	gp_initFramebuffer(screenBuffer[1],16,screenRefreshRate);
		currentFps>>=1;
		gp_initRTC();
		shell.set(-1,-1,16,10);
		shell.print("@0g@1d@0l @1i@0n@1i@0t @2ok\n");
		//printlr("current fps : %i",currentFps);
	#endif

    #ifdef useSdl
    	if(SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
        {  fprintf (stderr, "sdl init error (%s)\n",SDL_GetError()); return 0;
    	}

    	screen = SDL_SetVideoMode (WIDTH, HEIGHT, deepByte, SDL_SWSURFACE/*|SDL_NOFRAME*/ );// SDL_SWSURFACE);

    	if(!screen)
        {	fprintf (stderr, "error on set %ix%i.%i video mode (%s)\n",
                      WIDTH,HEIGHT,deepByte,SDL_GetError()); return 0;
    	}
        SDL_WM_SetCaption(appName,0);
	   //SDL_ShowCursor(SDL_DISABLE);
    
    	if(SDL_NumJoysticks() > 0)
        {	joy = SDL_JoystickOpen(0);
    		if(!joy)
            {	fprintf (stderr, "sdl link to joystick error (%s)\n",SDL_GetError()); return 0;
    		}
    	}

    	pixel = (clDeep*)(screen->pixels);
    	SDL_UnlockSurface(screen);
   	#endif
   	
   	#ifdef useRlyeh
   	       gp2x_init(1000, deepByte, 11025,16,1,60);
           pixel = gp2x_screen15;
   	#endif
   	
   	#ifdef usePtc
           fwidth  = WIDTH;
           fheight = HEIGHT;
           pixel = (clDeep*)malloc(WIDTH*HEIGHT*4);
   	       
		   if(!ptc_open(appTitle,&fwidth,&fheight))
		   {	showMsg("cannot render the backbuffer :|\n\nneed a minimum of :\n\t* 16b color deep\n\t* direct X 5 or more",appTitle);
				Gdl_exit();
		   }

   	       ptc_iniMsgCallBack(&Gdl_processMsg);
   	#endif

	#ifndef GP32
		#ifdef startAppWithFullPower
		   Gdl_setAppPower(1);
		 #else
		   Gdl_setAppPower(0);
		#endif   
	#endif
   	//atexit (Gdl_exit);
   	fullBlitLimit();
    return 1;
}

u32 letMeUseSomePower = 0;
void Gdl_setAppPower(u32 value)
{	letMeUseSomePower = (value>0);
}

u32 flipVar[4] = {0,0,0,0};

void Gdl_flip(void) // flip the framebuffer
{	//if(!pixel) return;
 
 	#ifdef GP32
		if(drawGdlShell) shell.draw();
 		//gp_waitDMA(0);
		//gp_waitDMA(1);
		if(!flipVar[nflip])
		{	flipVar[0] = ((u32)(screenBuffer[0]))>>22; flipVar[0] <<= 21;
			flipVar[0]  |= ( (((u32)(screenBuffer[0]))&0x3FFFFF)>>1 );

			flipVar[1] = ((u32)(screenBuffer[1]))>>22; flipVar[1] <<= 21;
			flipVar[1]  |= ( (((u32)(screenBuffer[1]))&0x3FFFFF)>>1 );

			flipVar[2] = (((u32)(screenBuffer[0]))&0x3FFFFF)>>1;
			flipVar[3] = (((u32)(screenBuffer[1]))&0x3FFFFF)>>1;
			flipVar[2] += 320*240;
			flipVar[3] += 320*240;
			rLCDSADDR3 = (0<<11) | 240 ;
		}

		 while(((rLCDCON5>>17)&3)==2); // wait for active line  
		 while(((rLCDCON5>>17)&3)!=2); // wait for active line to end - start of front porch and hsync

		rLCDSADDR1 = flipVar[nflip];
		rLCDSADDR2 = flipVar[2+nflip] ;
 
		//u32 miss = (rLCDCON1 >> 18);
		//if(currentFrequency<=80) if(miss > currentFrequency) gp_setCpuspeed(133);
		while ((rLCDCON1 >> 18) !=   1) asm volatile("nop\n""nop\n""nop\n");
		while ((rLCDCON1 >> 18) != 319) asm volatile("nop\n""nop\n""nop\n");
		//if(currentFrequency<=80) if(miss > currentFrequency) gp_setCpuspeed(currentFrequency);
		
//		gp_setFramebuffer(pixel,1);//!(gp_getButton() & BUTTON_R ));
		nflip ^= 1 ;
		pixel = screenBuffer[nflip];
		//fullBlitLimit();
		tick = GetTickCount();
 	#endif
 
    #ifdef useSdl
      SDL_LockSurface(screen);
      //SDL_UpdateRect(screen, 0, 0, 0, 0);
  	  SDL_Flip(screen);
      SDL_UnlockSurface(screen);
      Gdl_updateMsg();
      if(letMeUseSomePower){
             #ifdef sleepWhenNoFocus
                    SDL_Delay(10*(!isAppActive));
             #else
                    SDL_Delay(0);
             #endif
      } else SDL_Delay(10);
      tick = GetTickCount();
    #endif

   	#ifdef useRlyeh
   	  gp2x_video_flip();
      pixel = gp2x_screen15;
      resetScreenSize();
      tick = GetTickCount();
   	#endif

    #ifdef usePtc
      ptc_update(pixel);
      
      if(letMeUseSomePower){
         #ifdef sleepWhenNoFocus
                Sleep(10*(!isAppActive));
         #else
                Sleep(0);
         #endif
         tick = GetTickCount();
      } else { static u32 oldTick=tick;
               do { Sleep(1); tick = GetTickCount(); }
               while(tick - oldTick < 13);
               oldTick = tick;
             }
    #endif
}

/*void myAtExit(void)
{	Gdl_exit(1);
}*/

void Gdl_Sleep(u32 timeInMs)
{
	#ifdef useSdl
      SDL_Delay(timeInMs);
   	#endif
       
    #ifdef useRlyeh
		
    #endif

    #ifdef usePtc
      Sleep(timeInMs);
    #endif
}

void Gdl_exit(u32 exitProcess) // close the framebuffer
{//   log();
//	log("close gdl..\n");
	if(keyArray) { free(keyArray); keyArray=0; }
  //  log("key array cleaned\n");

	#ifdef useSdl
       	SDL_Quit();
   	#endif

    #ifdef useRlyeh
		gp2x_deinit();
    #endif

    #ifdef usePtc
      if(pixel)
	  {	ptc_close();
		free(pixel);
	  }
    #endif
	
//	log("framebuffer closed\n");

	if(exitProcess)
	{//	log("execute on exit event\n");	
		if(_onExit) _onExit();
		#ifndef GP32
		 else Gdl_fadeAndStopSong();
		 #else
		 gp_Reset();
		#endif
	//	log("on exit event launch\n");	
		#ifdef GP2X
			chdir("/usr/gp2x"); //go to menu
			execl("gp2xmenu","gp2xmenu",NULL);
		#endif
	//	log("close process\n");
		#ifdef WIN32
			ExitProcess(0);
		#endif
	}
}

#endif
