#ifndef _gdlInit_
#define _gdlInit_

/*** include & define standart thing ***/

#ifdef GP32
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "gp32.h"
#endif

#undef u8
#undef u16
#undef s8
#undef s16
#undef u32
#undef s32

#define  u8 unsigned  char
#define  s8  signed   char
#define u16 unsigned short
#define s16  signed  short
#define u32 unsigned  int
#define s32  signed   int

#ifdef GP32
	#define tickPerSecond 1024
	#define WIDTH  240
	#define HEIGHT 320
	#define need90Rotate
//	GPFILE *gdlfopen(const char *path, const char *mode);
//	void gdlfprintf(GPFILE *stream, const char * format, ...);

	//#define fopen		gdlfopen
	//#define fprintf	gdlfprintf
#else
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#define tickPerSecond 1000
	
		extern u32 WIDTH, HEIGHT;
#endif

/*** init gdl with selected options.. ***/

    #ifdef WIN32
           #ifndef useSdl
            #define usePtc
           #endif
    #endif

    #ifdef GP2X
           #ifndef useSdl
            #define useRlyeh
           #endif
    #endif

	#ifdef GP32	
			#define use16b
			u32 GetTickCount(void);
			//#define GetTickCount gp_getRTC
			#define keyArraySize 512
		    #define kspace 32
		    #define kenter 13
		    #define kstart 13
		    #define kctrl  17
		    #define kfin   35
		    #define kshift 17
		    #define kleft  37
		    #define kup    38
		    #define kright 39
		    #define kdown  40
		    #define kesc   27
	#endif

#ifdef  useSdl
            #include <SDL.h>
            #ifdef use32bIfPossible
              #ifdef WIN32
                #define use32b
              #else
                #define use16b
              #endif
            #else     
              #define use16b
            #endif
            #define GetTickCount SDL_GetTicks
            #define keyArraySize 512
#endif

#ifdef useRlyeh
            #include "./output/graphic/fbuffer/rlyeh/minimal.h"
            #define use16b
            #define GetTickCount gp2x_timer_read
#endif

#ifdef usePtc
            #include <windows.h>
            #define use32b
            #define keyArraySize 512
            #include "./output/graphic/fbuffer/ptc/tinyPtc.h"
#endif

#ifdef  use16b
       #define clDeep     u16
       #define clDeepDec  1
       #define clDeepSze  2
       #define deepByte    16
#else
       #define clDeep     u32
       #define clDeepDec  2
       #define clDeepSze  4
       #define deepByte    32
#endif

#ifdef usePtc
    #define kspace 32
    #define kenter 13
    #define kstart 13
    #define kctrl  17
    #define kfin   35
    #define kshift 17
    #define kleft  37
    #define kup    38
    #define kright 39
    #define kdown  40
    #define kesc   27
#endif

#ifdef useSdl
    #define kspace SDLK_SPACE
    #define kenter SDLK_RETURN
    #define kstart SDLK_RETURN
    #define kctrl  0
    #define kfin   SDLK_END
    #define kshift 0
    #define kleft  SDLK_LEFT
    #define kup    SDLK_UP
    #define kright SDLK_RIGHT
    #define kdown  SDLK_DOWN
    #define kesc   SDLK_ESCAPE
#endif

#define killKeyFront() keyUp(0xffff)


#endif
