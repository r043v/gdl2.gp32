
extern const char * _add_;
extern const char * _write_;
extern const char * _readb_;
extern const char * _writeb_;

const char * lastLogFile = 0 ;
#define dbgDftFile "gp:\\debug.log"

#include "Gdl.h"
#include <stdarg.h>
/*
void log(const char * info,const char * path, int lineReturn)
{	const char * openMethod = _add_ ;
	if(!info)    openMethod = _write_ ;
	if(!path)
		{	if(!lastLogFile)	path = dbgDftFile ;
				else			path = lastLogFile ;
		}

	FILE *f = fopen(path,openMethod);
	if(info)
		{	if(lineReturn)	fprintf(f,"%s\n",info);
			 else			fprintf(f,"%s",info);
		}

	fclose(f);
	lastLogFile = path ;
	return;
}

void mem2log(void * src, u32 size, const char * path)
{    const char * openMethod = _add_ ;
     if(!path)
		{	if(!lastLogFile)	path = dbgDftFile ;
				else			path = lastLogFile ;
		}
   	FILE *f = fopen(path,openMethod);
	if(src)
		{  fwrite(src,size,1,f);
		}

	fclose(f);
	lastLogFile = path ;
	return;
}

// a printf who write in the log
void printl(const char * format, ...)
{		va_list va;
		va_start(va, format);
		vsprintf(dbg,format,va);
		va_end(va);
		log(dbg,lastLogFile,0);
}

// the same, but who insert a line return
void printlr(const char * format, ...)
{		va_list va;
		va_start(va, format);
		vsprintf(dbg,format,va);
		va_end(va);
		log(dbg,lastLogFile,1);
}*/
