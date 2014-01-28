#ifndef _gdlio_
#define _gdlio_
#include "Gdl.h"
#include <stdarg.h>
/*
const char * _add_		= "a";
const char * _write_	= "w";
const char * _readb_	= "rb";
const char * _writeb_	= "wb";

u32 fileExist(const char*path)
{	FILE *f = fopen(path,_readb_);
	if(f) { fclose(f); return 1; }
	else return 0 ;
}

u32 getSize(FILE *f)
{ int last, size ;
  last = ftell(f) ;  fseek(f,0,SEEK_END) ;
  size = ftell(f) ;
  fseek(f,last,SEEK_SET) ; return size;
}

unsigned char * loadFile(const char *path, u32*size)
{ FILE *f ; int sz ; unsigned char * fl ;
  //printf("\n loading %s",path) ;
  f = fopen(path,_readb_) ;
  if(!f) { if(size) *size=0; return 0; } //{ printf(" .. file open error !\n") ; system("pause") ; }
  else {	sz = getSize(f) ;
			if(size) *size=sz;
         //printf(" (%iko)\n",sz>>10) ;
       }
  fl = (unsigned char*)malloc(sz) ; addFreeEntry(fl) ;
  fread(fl,sz,1,f) ;    fclose(f) ;
  return fl ;
}

u32 writeFile(const char *path, void*buffer, u32 size)
{	FILE *f = fopen(path,_writeb_) ;
	if(!f) return 0 ;
	fwrite(buffer,size,1,f);fclose(f);
	return 1;
}

u32 isAPath(char*path)
{	if(fileExist(path)) return 1 ;
	u32 pathSize = strlen(path);
	if(pathSize>255) return 0;
	if(path[1]==':' && path[2]=='\\') return 1;
	char * p = path ;
	if(pathSize>4)
	{	p += (pathSize-4) ;
		for(u32 n=0;n<5;n++) if(*p++ == '.') return 1;
	}	return 0 ;
}
	


*/	void gdlfprintf(FILE *stream, const char * format, ...)
	{	va_list va;
		va_start(va, format);
		vsprintf(dbg,format,va);
		va_end(va);
		//fwrite(dbg,strlen(dbg),1,stream);
	}
#endif

