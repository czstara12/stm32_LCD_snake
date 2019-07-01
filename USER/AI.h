#pragma once
#ifndef AI_H
#define AI_H

#include "public.h"
#include <stdlib.h>
//#include <iostream>

typedef struct
{
	bool w, s, a, d, sign, active, nopen;
} DFSmap;
Direction ai(short const map[][WIDTH] //地图
			 ,
			 short size //蛇长
			 ,
			 short x, short y, int qiantao);
int simulate(const short map[][WIDTH], DFSmap *p_start, short size, short x, short y);
Direction ai2(short const map[][WIDTH] //地图
			  ,
			  short size //蛇长
			  ,
			  short x, short y);
int simulate2(const short map[][WIDTH], DFSmap *p_start, short size, short x, short y);

#endif // !AI_H