
#ifndef _gdlMiscGfx_
#define _gdlMiscGfx_

#include "Gdl.h"

void clrScr(u32 color)
{
	#ifndef GP32
		#ifdef use16b
			color = pc2gpColor(color);
		#endif
		
		for(clDeep *scr = scrStart;scr <= scrEnd; scr++) *scr = color;
	#else
		gp_clearFramebuffer16(pixel,pc2gpColor(color));
	#endif
}

#endif
