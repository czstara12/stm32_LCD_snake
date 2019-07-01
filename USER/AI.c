#include "AI.h"

Direction ai(short const map[][WIDTH] //地图
			 ,
			 short size //蛇长
			 ,
			 short x, short y //蛇头坐标
			 ,
			 int qiantao //嵌套模式 0表示正常搜寻 属于入口调用 1表示路径搜索 用于判断目标与起始地是否有同路 2表示模拟搜索 用于嵌套搜索给出路径
)

{
	if (qiantao == 0 || qiantao == 2)
	{
		int waynum = 0;
		if (map[y - 1][x] == 0 || map[y - 1][x] == 1 || map[y - 1][x] == -1)
			waynum++;
		if (map[y][x - 1] == 0 || map[y][x - 1] == 1 || map[y][x - 1] == -1)
			waynum++;
		if (map[y + 1][x] == 0 || map[y + 1][x] == 1 || map[y + 1][x] == -1)
			waynum++;
		if (map[y][x + 1] == 0 || map[y][x + 1] == 1 || map[y][x + 1] == -1)
			waynum++;
		if (waynum == 0)
			return d_error;
		if (waynum == 1)
		{
			if (map[y - 1][x] == 0 || map[y - 1][x] == 1 || map[y - 1][x] == -1)
				return d_up;
			else if (map[y][x - 1] == 0 || map[y][x - 1] == 1 || map[y][x - 1] == -1)
				return d_left;
			else if (map[y + 1][x] == 0 || map[y + 1][x] == 1 || map[y + 1][x] == -1)
				return d_down;
			else if (map[y][x + 1] == 0 || map[y][x + 1] == 1 || map[y][x + 1] == -1)
				return d_right;
			else
				return d_error;
		}
	}
	//if (size > (WIDTH - 2)*(HEIGHT - 2)*0.95)
	//	return ai2(map, size, x, y);
	//}
	/*if (size > (HEIGHT - 2)*(WIDTH - 2) * 95 / 100)
	{
		int foodx = 0, foody = 0;
		for (foodx = 0; map[foody][foodx] != -1; foodx++)
			for (foody = 0; map[foody][foodx] != -1; foody++)
				return ai2(map, size, foodx, foody);
	}*/

	DFSmap dmap[HEIGHT][WIDTH];
	DFSmap *p_start = NULL;

	short const *pa;
	DFSmap *pb;
	for (pa = map[0], pb = dmap[0]; pb <= &dmap[HEIGHT - 1][WIDTH - 1]; pa++, pb++)
	{
		pb->active = pb->d = pb->nopen = pb->s = pb->sign = pb->w = pb->a = false;
		if (*pa != 0)
		{
			if (*pa == -1)
			{
				pb->active = true;
				pb->sign = true;
			}
			else if (*pa == size)
			{
				p_start = pb;
				pb->nopen = false;
			}
			else if (qiantao == 1 && *pa == 1)
			{
				pb->nopen = false;
				pb->active = true;
				pb->sign = true;
			}
			else
				pb->nopen = true;
		}
	}

	int num = 1;
	if (p_start == NULL)
	{
		//std::cerr << "错误" << __FILE__ << __LINE__ << __FUNCTION__ << std::endl;
		exit(-1);
	}
	while (p_start->sign == false && num != 0)
	{
		num = 0;
		DFSmap *pdmap;
		for (pdmap = &dmap[0][0]; pdmap <= &dmap[HEIGHT - 1][WIDTH - 1]; pdmap++)
		{
			if (pdmap->active == true)
			{
				num++;
				if ((pdmap - WIDTH)->nopen == false)
					if ((pdmap - WIDTH)->sign == false)
					{
						(pdmap - WIDTH)->s = true;
						(pdmap - WIDTH)->active = true;
					}
				if ((pdmap - 1)->nopen == false)
					if ((pdmap - 1)->sign == false)
					{
						(pdmap - 1)->d = true;
						(pdmap - 1)->active = true;
					}
				if ((pdmap + 1)->nopen == false)
					if ((pdmap + 1)->sign == false)
					{
						(pdmap + 1)->a = true;
						(pdmap + 1)->active = true;
					}
				if ((pdmap + WIDTH)->nopen == false)
					if ((pdmap + WIDTH)->sign == false)
					{
						(pdmap + WIDTH)->w = true;
						(pdmap + WIDTH)->active = true;
					}
				pdmap->active = false;
				pdmap->sign = true;
			}
		}
	}
	// if (num == 0) {//没有搜索到直接路径 食物生成在蛇圈以外
	// 	//if (qiantao == 0)
	// 		//MessageBox(NULL, "没路了1", "error", MB_OK);
	// 	return d_error;
	// }
	// else if (qiantao == 1)
	// {
	// 	if (p_start->w == true)return d_up;
	// 	else if (p_start->a == true)return d_left;
	// 	else if (p_start->s == true)return d_down;
	// 	else if (p_start->d == true)return d_right;
	// }
	// else if (simulate(map, p_start, size, x, y) == 0)
	// 	;//MessageBox(NULL, "没路了2", "error", MB_OK);
	// else
	// 	if (p_start->w == true)return d_up;
	// 	else if (p_start->a == true)return d_left;
	// 	else if (p_start->s == true)return d_down;
	// 	else if (p_start->d == true)return d_right;

	// if (p_start->w == true)
	// 	return d_up;
	// else if (p_start->a == true)
	// 	return d_left;
	// else if (p_start->s == true)
	// 	return d_down;
	// else if (p_start->d == true)
	// 	return d_right;

	if (qiantao == 1 || qiantao == 2) //模拟函数用来判断模拟情况 防止反复归递
	{
		if (p_start->w == true)
			return d_up;
		else if (p_start->a == true)
			return d_left;
		else if (p_start->s == true)
			return d_down;
		else if (p_start->d == true)
			return d_right;
	}
	else if (num == 0)
	{ //没有搜索到直接路径 食物生成在蛇圈以外
		return ai2(map, size, x, y);
	}
	else if ((rand() % 2 == 0 ? simulate(map, p_start, size, x, y) : simulate2(map, p_start, size, x, y)) == 0) //这个走法危险 无法追尾 解决方法 以最远的路程追尾
	{

		return ai2(map, size, x, y);
	}
	else //剩的就是既能找到又安全的路了
	{
		if (p_start->w == true)
			return d_up;
		else if (p_start->a == true)
			return d_left;
		else if (p_start->s == true)
			return d_down;
		else if (p_start->d == true)
			return d_right;
	}

	return d_error;
}
int simulate(const short map[][WIDTH], DFSmap *p_start, short size, short x, short y)
{
	short vir_map[HEIGHT][WIDTH], endx = 0, endy = 0;
	for (int h = 0; h < HEIGHT; h++)
		for (int w = 0; w < WIDTH; w++)
			vir_map[h][w] = map[h][w];
	//Direction dire;
	DFSmap *pn = p_start;
	short *pv = &vir_map[y][x];
	while (1)
	{
		if (pn->w == true)
		{
			pn -= WIDTH;
			pv -= WIDTH;
		}
		else if (pn->a == true)
		{
			pn -= 1;
			pv -= 1;
		}
		else if (pn->s == true)
		{
			pn += WIDTH;
			pv += WIDTH;
		}
		else if (pn->d == true)
		{
			pn += 1;
			pv += 1;
		}
		if (*pv != -1)
		{
			*pv = size + 1;
			for (int a = 0; a < HEIGHT; a++)
				for (int b = 0; b < WIDTH; b++)
					vir_map[a][b] = (vir_map[a][b] > 0 ? vir_map[a][b] - 1 : vir_map[a][b]);
		}
		else
		{
			*pv = size + 1;
			break;
		}
	} //模拟走一遍
	for (short h = 0; h < HEIGHT; h++)
		for (short w = 0; w < WIDTH; w++)
			if (vir_map[h][w] == 1)
			{
				endx = w;
				endy = h;
				h = HEIGHT;
				w = WIDTH;
			}
	if (ai(vir_map, size + 1, endx, endy, 1) != d_error)
		return 1;
	else
		return 0;
}

Direction ai2(short const map[][WIDTH] //地图
			  ,
			  short size //蛇长
			  ,
			  short x, short y)
{
	short ai2map[HEIGHT][WIDTH];
	for (int he = 0; he < HEIGHT; he++)
		for (int wi = 0; wi < WIDTH; wi++)
		{
			if (map[he][wi] == 0)
				ai2map[he][wi] = 0;
			else if (map[he][wi] == 1)
				ai2map[he][wi] = 1;
			else if (map[he][wi] == -1)
				ai2map[he][wi] = 0;
			else
				ai2map[he][wi] = -1;
		}
	int num = 0, count = 0;
	do
	{
		num = 0;
		count++;
		for (int he = 0; he < HEIGHT; he++)
			for (int wi = 0; wi < WIDTH; wi++)
			{
				if (ai2map[he][wi] == count)
				{
					if (he > 0) //这四个判断条件正常情况下不会失败 加它是为了去掉警告
						ai2map[he - 1][wi] = ai2map[he - 1][wi] == 0 ? count + 1 : ai2map[he - 1][wi];
					if (wi > 0)
						ai2map[he][wi - 1] = ai2map[he][wi - 1] == 0 ? count + 1 : ai2map[he][wi - 1];
					if (wi < WIDTH)
						ai2map[he][wi + 1] = ai2map[he][wi + 1] == 0 ? count + 1 : ai2map[he][wi + 1];
					if (he < HEIGHT)
						ai2map[he + 1][wi] = ai2map[he + 1][wi] == 0 ? count + 1 : ai2map[he + 1][wi];
					num++;
				}
			}
	} while (num != 0);
	//Direction retdir = d_error;
	if (ai2map[y - 1][x] >= ai2map[y][x - 1] && ai2map[y - 1][x] != -1) //1
	{
		if (ai2map[y - 1][x] >= ai2map[y + 1][x]) //1
		{
			if (ai2map[y - 1][x] >= ai2map[y][x + 1])
				return d_up;
			else
				return d_right;
		}
		else //3
		{
			if (ai2map[y + 1][x] >= ai2map[y][x + 1])
				return d_down;
			else
				return d_right;
		}
	}
	else //2
	{
		if (ai2map[y][x - 1] >= ai2map[y + 1][x] && ai2map[y][x - 1] != -1) //2
		{
			if (ai2map[y][x - 1] >= ai2map[y][x + 1])
				return d_left;
			else
				return d_right;
		}
		else //3
		{
			if (ai2map[y + 1][x] >= ai2map[y][x + 1] && ai2map[y + 1][x] != -1)
				return d_down;
			else if (ai2map[y][x + 1] != -1)
				return d_right;
		}
	}
	return d_error;
}

int simulate2(const short map[][WIDTH], DFSmap *p_start, short size, short x, short y)
{
	short vir_map[HEIGHT][WIDTH]; // endx, endy;
	for (int h = 0; h < HEIGHT; h++)
		for (int w = 0; w < WIDTH; w++)
			vir_map[h][w] = map[h][w];
	//Direction dire;
	//short * pv = &vir_map[y][x];
	while (1)
	{
		switch (ai(vir_map, size, x, y, 2))
		{
		case d_up:
			y = y - 1;
			break;
		case d_down:
			y = y + 1;
			break;
		case d_left:
			x = x - 1;
			break;
		case d_right:
			x = x + 1;
			break;
		case d_error:
			exit(1);
		}
		if (vir_map[y][x] == 0 || vir_map[y][x] == 1)
		{
			vir_map[y][x] = size + 1;
			for (int a = 0; a < HEIGHT; a++)
				for (int b = 0; b < WIDTH; b++)
					vir_map[a][b] = (vir_map[a][b] > 0 ? vir_map[a][b] - 1 : vir_map[a][b]);
		}
		else if (vir_map[y][x] == -1)
		{
			size++;
			vir_map[y][x] = size;
			break;
		}

		//if (*pv != -1)
		//{
		//	*pv = size + 1;
		//	for (int a = 0; a < HEIGHT; a++)
		//		for (int b = 0; b < HEIGHT; b++)
		//			vir_map[a][b] = (vir_map[a][b] > 0 ? vir_map[a][b] - 1 : vir_map[a][b]);
		//}
		//else
		//{
		//	*pv = size + 1;
		//	break;
		//}
	} //模拟走一遍
	//for (short h = 0; h < HEIGHT; h++)
	//	for (short w = 0; w < WIDTH; w++)
	//		if (vir_map[h][w] == 1)
	//		{
	//			endx = w;
	//			endy = h;
	//			h = HEIGHT;
	//			w = WIDTH;
	//		}
	if (ai(vir_map, size, x, y, 1) != d_error)
		return 1;
	else
		return 0;
	return 0;
}