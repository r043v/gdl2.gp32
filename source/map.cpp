
#include "map.h"

outzone*createOutzone(u32 x, u32 y, u32 sx, u32 sy)
{	outzone*out = (outzone*)malloc(sizeof(outzone));
	out->x = x;
	out->y = y;
	out->start[0]  = xy2buf((screenBuffer[0]),x,y);
	out->end[0]    = xy2buf((screenBufferEnd[0]),(x+sx),(y+sy));
	out->start[1]  = xy2buf((screenBuffer[1]),x,y);
	out->end[1]    = xy2buf((screenBufferEnd[1]),(x+sx),(y+sy));
	out->width  = sx;
	out->height = sy;
	return out;
}

void setBlitLimit(outzone*out)
{	if(out) setBlitLimit(out->x,out->y,out->x+out->width,out->y+out->height);
	 else fullBlitLimit();
}

void map::setOutZone(outzone*out)
{	this->out = out;
	//
		if(!out)
		{
			#ifndef	need90Rotate
				this->uncutDrawx = WIDTH>>xTileDec;
				this->pixelMorex = WIDTH-(uncutDrawx<<xTileDec);
				this->uncutDrawy = HEIGHT>>yTileDec;
				this->pixelMorey = HEIGHT-(uncutDrawy<<yTileDec);
				this->maxScrollx = (tileSizex*sizeInTilex) - WIDTH  ;
				this->maxScrolly = (tileSizey*sizeInTiley) - HEIGHT ;
			#else
				this->uncutDrawx = HEIGHT>>xTileDec;
				this->pixelMorex = HEIGHT-(uncutDrawx<<xTileDec);
				this->uncutDrawy = WIDTH>>yTileDec;
				this->pixelMorey = WIDTH-(uncutDrawy<<yTileDec);
				this->maxScrollx = (tileSizex*sizeInTilex) - HEIGHT  ;
				this->maxScrolly = (tileSizey*sizeInTiley) - WIDTH ;
			#endif
		} else {
			this->uncutDrawx = (out->width)>>xTileDec;
			this->pixelMorex = (out->width)-(uncutDrawx<<xTileDec);
			this->uncutDrawy = (out->height)>>yTileDec;
			this->pixelMorey = (out->height)-(uncutDrawy<<yTileDec);
			this->maxScrollx = (tileSizex*sizeInTilex) - out->width  ;
			this->maxScrolly = (tileSizey*sizeInTiley) - out->height ;	
		}
/*	#else
		if(!out)
		{		
		} else {
			this->uncutDrawx = (out->height)>>xTileDec;
			this->pixelMorex = (out->height)-(uncutDrawx<<xTileDec);
			this->uncutDrawy = (out->width)>>yTileDec;
			this->pixelMorey = (out->width)-(uncutDrawy<<yTileDec);
			this->maxScrollx = (tileSizex*sizeInTilex) - out->height  ;
			this->maxScrolly = (tileSizey*sizeInTiley) - out->width ;	
		}
	#endif*/
}

void map::moveOutZone(u32 x, u32 y)
{	this->out->x = x;
	this->out->y = y;

	out->start[0]  = xy2buf((screenBuffer[0]),x,y);
	out->end[0]    = xy2buf((screenBufferEnd[0]),x+out->width,y+out->height);
	out->start[1]  = xy2buf((screenBuffer[0]),x,y);
	out->end[1]    = xy2buf((screenBufferEnd[0]),x+out->width,y+out->height);
}

u32 map::set(arDeep*array,clDeep**tileset,u32 tileNumber,u32 tileSizex,u32 tileSizey,u32 sizex,u32 sizey,u32 scrollx,u32 scrolly, outzone*out, u32 copyArray)
{	u32 size = sizex*sizey ;
	if(!array || !tileset || !size) return 0 ;

	// copy the array (so we'll can modify it)
	if(copyArray)
	{	this->array = (arDeep*)malloc(size<<arDeepDec);
		memcpy(this->array,array,size<<arDeepDec);
	} else this->array = array;

	this->tileset = tileset	;
	this->tileNumber = tileNumber ;
	this->tileSizex = tileSizex ;
	this->tileSizey = tileSizey ;
	this->scrollx = scrollx ;
	this->scrolly = scrolly ;
	this->sizeInTilex = sizex;
	this->sizeInTiley = sizey;

	// precompute some usefull value
	xTileDec = computeDec(tileSizex); // tile size is multiple of 2, so can use >> or << instead of / or *
	yTileDec = computeDec(tileSizey);

	this->sizeInPixelx = sizex<<xTileDec;
	this->sizeInPixely = sizey<<yTileDec;
	this->firstTileBlitx = (scrollx>>xTileDec);
	this->firstTileBlity = (scrolly>>yTileDec);
	this->currentDecx = scrollx-(firstTileBlitx<<xTileDec);
	this->currentDecy = scrolly-(firstTileBlity<<yTileDec);

	setOutZone(out);

	this->pixelessx = pixelMorex+currentDecx;
	this->pixelessy = pixelMorey+currentDecy;
	this->morex = pixelessx >= tileSizex;
	this->morey = pixelessy >= tileSizey;

	 if(morex) pixelessx -= tileSizex;
	 if(morey) pixelessy -= tileSizey;

	this->tiledrawx = uncutDrawx+morex+(pixelessx!=0);
	this->tiledrawy = uncutDrawy+morey+(pixelessy!=0);

	this->Animate = (anim**)malloc(tileNumber*4);
	memset(this->Animate,0,tileNumber*4);

	//Gdl_showMsg("%i - %i .. %i %i",this->tiledrawx,this->tiledrawy,uncutDrawx,uncutDrawy);

	return 1;
}

u32 map::setScroll(u32 x, u32 y)
{	scrollx = x;
	scrolly = y;
	return scroll(0,0);
}

u32 map::scroll(u32 way, u32 pawa)
{	u32 cpt, rtn=0;
	if(way&1)	// up
		for(cpt=0;cpt<pawa;cpt++)
		{	if(scrolly) scrolly--;
			 else rtn |= 1;
		};

	if(way&2)	// down
		for(cpt=0;cpt<pawa;cpt++)
		{	if(scrolly < maxScrolly) scrolly++;
			 else rtn |= 2;
		};

	if(way&4)	// left
		for(cpt=0;cpt<pawa;cpt++)
		{	if(scrollx) scrollx--;
			 else rtn |= 4;
		};

	if(way&8)	// right
		for(cpt=0;cpt<pawa;cpt++)
		{	if(scrollx < maxScrollx) scrollx++;
			 else rtn |= 8;
		};

	this->firstTileBlitx = (scrollx>>xTileDec);
	this->firstTileBlity = (scrolly>>yTileDec);
	this->currentDecx = scrollx-(firstTileBlitx<<xTileDec);
	this->currentDecy = scrolly-(firstTileBlity<<yTileDec);
	
	this->pixelessx = pixelMorex+currentDecx;
	this->pixelessy = pixelMorey+currentDecy;
	this->morex = pixelessx >= tileSizex;
	this->morey = pixelessy >= tileSizey;

	 if(morex) pixelessx -= tileSizex;
	 if(morey) pixelessy -= tileSizey;

	this->tiledrawx = uncutDrawx+morex+(pixelessx!=0);
	this->tiledrawy = uncutDrawy+morey+(pixelessy!=0);

	return rtn;
}

void map::setAnimatedTile(u32 tile,anim * Anim)
{	if(!tile || !Anim || tile >= tileNumber) return ;
	Animate[tile] = Anim;
}

void map::draw90(void)
{		internalSaveBlitLimit();

	if(out) setBlitLimit(out);
	 else fullBlitLimit();

			u32 cptx,cpty;
			int blitPosx,blitPosy ;

			u32 tile;
/*
			// left clipped colon (from up to down)
				if(out)	
				{	blitPosx = (out->x) - currentDecx;
					blitPosy = (out->y) - currentDecy;
				} else	{	blitPosx = -currentDecx;
							blitPosy = -currentDecy;
						}

				for(cpty=0;cpty<tiledrawy;cpty++) // show first colon in clipped
				{	tile = array[firstTileBlitx+sizeInTilex*(firstTileBlity+cpty)];
					if(tile)
					{	if(!Animate[tile])	drawGfm(tileset[tile],blitPosx,blitPosy);
						 else				playAnim(&Animate[tile],blitPosx,blitPosy);
					}	blitPosy += tileSizey;
				};

			// right clipped colon

				if(out)	
				{	blitPosx = out->x + out->width - pixelessx;
					blitPosy = out->y - currentDecy;
				} else	{	blitPosx = HEIGHT - pixelessx;
							blitPosy = -currentDecy;
						}

				for(cpty=0;cpty<tiledrawy;cpty++)
				{	tile = array[firstTileBlitx+tiledrawx-1+sizeInTilex*(firstTileBlity+cpty)];
					if(tile)
					{	if(!Animate[tile])	drawGfm(tileset[tile],blitPosx,blitPosy);
						 else				playAnim(&Animate[tile],blitPosx,blitPosy);
						
					}	blitPosy += tileSizey;
				};
*/
			// up clipped line
				if(out)	
				{	blitPosx = (out->x) - currentDecx;// + tileSizex;
					blitPosy = (out->y) - currentDecy;
				} else	{	blitPosx = tileSizex-currentDecx;
							blitPosy = -currentDecy;
						}

				for(cptx=0;cptx<=uncutDrawx+morex;cptx++) // show first colon in clipped
				{	
					tile = array[firstTileBlitx+cptx+sizeInTilex*firstTileBlity];
					if(tile)
					{	if(!Animate[tile])	drawGfm(tileset[tile],blitPosx,blitPosy);
						 else				playAnim(&Animate[tile],blitPosx,blitPosy);
						
					}	blitPosx += tileSizex;
				};
			
			// down clipped line
				if(out)	
				{	blitPosx = (out->x) - currentDecx;// + tileSizex;
					blitPosy = (out->y) + out->height - pixelessy;
				} else	{	blitPosx = tileSizex-currentDecx;
							blitPosy = WIDTH - pixelessy;
						}

				for(cptx=0;cptx<=uncutDrawx+morex;cptx++)
				{	
					tile = array[firstTileBlitx+cptx+sizeInTilex*(firstTileBlity+tiledrawy - 1)];
					if(tile)
					{	if(!Animate[tile])	drawGfm(tileset[tile],blitPosx,blitPosy);
						 else				playAnim(&Animate[tile],blitPosx,blitPosy);
						
					}	blitPosx += tileSizex;
				};

			// show map center, unclipped

	clDeep *screen;
	if(out)	screen = out->start[nflip];
	 else	screen = pixel;//+WIDTH-1;
	clDeep *scr ;

	screen -= (currentDecx)*WIDTH;
	screen += currentDecy-tileSizey;

	if(!out)
	{	screen += WIDTH;
		screen--;
	}

if( !(gp_getButton() & BUTTON_L ))
			for(cptx=0;cptx<=uncutDrawx+morex;cptx++)
			{	
				scr = screen;screen += (WIDTH<<xTileDec);
				for(cpty=1;cpty<uncutDrawy+morey;cpty++)
				{	
					scr -= tileSizey;
					tile = array[firstTileBlitx+cptx+sizeInTilex*(firstTileBlity+cpty)];
					if(tile)
					{	if(!Animate[tile])	udrawGfm(tileset[tile],scr);
						 else				playAnim(&Animate[tile],scr);
					}//	tileOff++;
					
					//return;
				};
			};

		
/*
return;			for(cpty=1;cpty<uncutDrawy+morey;cpty++)
			{	screen += WIDTH<<yTileDec;
				scr = screen;
				u32 tileOff = firstTileBlitx+1;
				for(cptx=1;cptx<uncutDrawx+morex;cptx++)
				{	scr += tileSizex;
					tile = array[firstTileBlitx+cptx+sizeInTilex*(firstTileBlity+cpty)];
					if(tile)
					{	if(!Animate[tile])	udrawGfm(tileset[tile],scr);
						 else				playAnim(&Animate[tile],scr);
					}	tileOff++;
				};
			};
*/
	internalLoadBlitLimit();
}
/*
void map::draw(void)
{	internalSaveBlitLimit();

	if(out) setBlitLimit(out->start[nflip],out->end[nflip],out->x,out->x+out->width);
	 else fullBlitLimit();

			clDeep *screen = out->start[nflip];
			clDeep *scr ;

			u32 cptx,cpty,blitPosx,blitPosy ;

			u32 tile;

			// left clipped colon (from up to down)
				blitPosx = (out->x) - currentDecx;
				blitPosy = (out->y) - currentDecy;

				for(cpty=0;cpty<tiledrawy;cpty++) // show first colon in clipped
				{	tile = array[firstTileBlitx+sizeInTilex*(firstTileBlity+cpty)];
					if(tile)
					{	if(!Animate[tile])	drawGfm(tileset[tile],blitPosx,blitPosy);
						 else				playAnim(&Animate[tile],blitPosx,blitPosy);
						
					}	blitPosy += tileSizey;
				};

			// right clipped colon
				blitPosx = out->x + out->width - pixelessx;
				blitPosy = out->y - currentDecy;
					
				for(cpty=0;cpty<tiledrawy;cpty++)
				{	tile = array[firstTileBlitx+tiledrawx-1+sizeInTilex*(firstTileBlity+cpty)];
					if(tile)
					{	if(!Animate[tile])	drawGfm(tileset[tile],blitPosx,blitPosy);
						 else				playAnim(&Animate[tile],blitPosx,blitPosy);
						
					}	blitPosy += tileSizey;
				};

				
			// up clipped line
				blitPosx = (out->x) - currentDecx + tileSizex;
				blitPosy = (out->y) - currentDecy;

				for(cptx=1;cptx<uncutDrawx+morex;cptx++) // show first colon in clipped
				{	
					tile = array[firstTileBlitx+cptx+sizeInTilex*firstTileBlity];
					if(tile)
					{	if(!Animate[tile])	drawGfm(tileset[tile],blitPosx,blitPosy);
						 else				playAnim(&Animate[tile],blitPosx,blitPosy);
						
					}	blitPosx += tileSizex;
				};
			
			// down clipped line
				blitPosx = (out->x) - currentDecx + tileSizex;
				blitPosy = (out->y) + out->height - pixelessy;

				for(cptx=1;cptx<uncutDrawx+morex;cptx++)
				{	
					tile = array[firstTileBlitx+cptx+sizeInTilex*(firstTileBlity+tiledrawy - 1)];
					if(tile)
					{	if(!Animate[tile])	drawGfm(tileset[tile],blitPosx,blitPosy);
						 else				playAnim(&Animate[tile],blitPosx,blitPosy);
						
					}	blitPosx += tileSizex;
				};

			// show map center, unclipped
				screen -= currentDecy*WIDTH;
				screen -= currentDecx;

			for(cpty=1;cpty<uncutDrawy+morey;cpty++)
			{	screen += WIDTH<<yTileDec;
				scr = screen;
				u32 tileOff = firstTileBlitx+1;
				for(cptx=1;cptx<uncutDrawx+morex;cptx++)
				{	scr += tileSizex;
					tile = array[firstTileBlitx+cptx+sizeInTilex*(firstTileBlity+cpty)];
					if(tile)
					{	if(!Animate[tile])	udrawGfm(tileset[tile],scr);
						 else				playAnim(&Animate[tile],scr);
					}	tileOff++;
				};
			};

	internalLoadBlitLimit();
}
*/
u32 map::getMapTile(u32 x, u32 y)
{	x >>= this->xTileDec ;
	y >>= this->yTileDec ;
	return array[y*sizeInTilex+x];
}

void map::setMapTile(u32 tile, u32 x, u32 y)
{	if(tile >= this->tileNumber) return ;
	x >>= this->xTileDec ;
	y >>= this->yTileDec ;
	array[y*sizeInTilex+x] = tile ;
}

u32 map::getOutZoneTile(u32 x, u32 y)
{	return getMapTile(x+scrollx,y+scrolly);
}

void map::setOutZoneTile(u32 tile, u32 x, u32 y)
{	if(tile >= this->tileNumber) return ;
	setMapTile(tile,x+scrollx,y+scrolly);
}

u32 map::getScreenTile(u32 x, u32 y)
{	if( (x < out->x) || (y < out->y) ) return 0xffff;
	if(   (x >= out->x + out->width)
	   || (y >= out->y + out->height)) return 0xffff;
	
	int xx = x+scrollx;
	int yy = y+scrolly;
	xx -= currentDecx; xx -= out->x;
	yy -= currentDecy; yy -= out->y;
	return getMapTile(xx,yy);
}

void map::setScreenTile(u32 tile, u32 x, u32 y)
{	if(tile >= this->tileNumber) return ;
	setMapTile(tile,x+scrollx-currentDecx-out->x,y+scrolly-currentDecy-out->y);
}

