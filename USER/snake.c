// snake.cpp: 定义控制台应用程序的入口点。
#include "snake.h"

static short map[HEIGHT][WIDTH] = {0}; // 地图
static short size;					   // 蛇的长度
static Direction dire, diren;		   // 方向
static short x, y;					   // 蛇头位置
static clock_t mark;				   // 时间标记
//SDL_Renderer *ren;//刷子
//SDL_Rect rec;//框子
static bool end = false;
//static bool quit = false;
//SDL_Event event;//事件
//SDL_Window * window;
static int banai = 0; //防止死循环

int initialize()
{
	//SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);//初始化SDL
	//window = SDL_CreateWindow("snake.by starstory", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, HEIGHT * 20, WIDTH * 20 , SDL_WINDOW_SHOWN);//创建SDL窗口
	srand((unsigned)time(NULL)); //初始化随机数
	mark = clock();				 //标记时间
	for (short *n = map[0]; n != map[HEIGHT]; n++)
		*n = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		map[0][i] = -2;
		map[HEIGHT - 1][i] = -2;
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		map[i][0] = -2;
		map[i][WIDTH - 1] = -2;
	} //占用地图边界

	//ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//刷子绑定窗口
	//SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	//SDL_RenderClear(ren);
	//SDL_RenderPresent(ren);//清屏
	size = 3;
	x = 3;
	y = 3;
	map[3][3] = 3;
	map[3][2] = 2;
	map[3][1] = 1;
	dire = d_right;
	diren = d_right;
	newfood(); //初始化一个食物
	display();
	return 0;
}
int gamewithai()
{

	//		display();
	//LED0 = !LED0;
	if ((dire = ai(map, size, x, y, 0)) == d_error)
	{
		//MessageBox(NULL, "没路了", "error", MB_OK);
		return 0;
	}
	if (banai > (WIDTH - 2) * (HEIGHT - 2) * 4)
	{
		//MessageBox(NULL, "死循环", "error", MB_OK);
		return 0;
	}
	//while (1)
	//LCD_Fill(120, 120, 159, 159, GREEN);
	end = false;
	switch (dire)
	{
	case d_up:
		if (move(x, y - 1) == 1)
			y = y - 1;
		else
			end = true;
		break;
	case d_down:
		if (move(x, y + 1) == 1)
			y = y + 1;
		else
			end = true;
		break;
	case d_left:
		if (move(x - 1, y) == 1)
			x = x - 1;
		else
			end = true;
		break;
	case d_right:
		if (move(x + 1, y) == 1)
			x = x + 1;
		else
			end = true;
		break;
	default:
		break;
	}
	if (end)
		return 0;
	display();
	return 1;
}
/*
int game()
{
	if (clock() - mark > CLOCKS_PER_SEC * 2 /9) {
		mark = clock();
		switch (dire) {
		case d_up:
			if (move(x, y - 1) == 1)
				y = y - 1;
			else
				end = true;
			break;
		case d_down:
			if (move(x, y + 1) == 1)
				y = y + 1;
			else
				end = true;
			break;
		case d_left:
			if (move(x - 1, y) == 1)
				x = x - 1;
			else
				end = true;
			break;
		case d_right:
			if (move(x + 1, y) == 1)
				x = x + 1;
			else
				end = true;
			break;
		}
		if (end)return 0;
		display();
	}
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w: if (diren == d_up || diren == d_down)
				break;
						 else
				dire = d_up;
				break;
			case SDLK_a: if (diren == d_left || diren == d_right)
				break;
						 else
				dire = d_left;
				break;
			case SDLK_s: if (diren == d_up || diren == d_down)
				break;
						 else
				dire = d_down;
				break;
			case SDLK_d: if (diren == d_left || diren == d_right)
				break;
						 else
				dire = d_right;
				break;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}
	if (quit)
		return 0;
	return 1;
}
 */
int move(int x, int y)
{ //蛇头向前进一个格
	diren = dire;
	if (map[y][x] == 0 || map[y][x] == 1)
	{
		map[y][x] = size + 1;
		banai++;
		for (int a = 0; a < HEIGHT; a++)
			for (int b = 0; b < WIDTH; b++)
				map[a][b] = (map[a][b] > 0 ? map[a][b] - 1 : map[a][b]);
	}
	else if (map[y][x] == -1)
	{
		size++;
		map[y][x] = size;
		banai = 0;
		newfood();
	}
	else
		return 0;
	return 1;
}

void display()
{
	int a = 0;
	int b = 0;
	LCD_Clear(BLACK);
	for (a = 0; a < HEIGHT; a++)
	{
		for (b = 0; b < WIDTH; b++)
		{
			switch (map[a][b])
			{
			case 0:
				break;
			case -1:
				LCD_Fill(b * 10 + 1, a * 10 + 1, b * 10 + 9, a * 10 + 9, RED);
				break;
			case -2:
				LCD_Fill(b * 10, a * 10, b * 10 + 10, a * 10 + 10, WHITE);
				break;
			default:
				if (size != map[a][b])
					LCD_Fill(b * 10 + 1, a * 10 + 1, b * 10 + 9, a * 10 + 9, GREEN);
				else
					LCD_Fill(b * 10 + 1, a * 10 + 1, b * 10 + 9, a * 10 + 9, BLUE);
				if (a < 1 || b < 1)
				{
					//std::cerr << "错误" << __FILE__ << __LINE__ << __FUNCTION__ << std::endl;
					exit(-1);
				}
				if (abs(map[a - 1][b] - map[a][b]) == 1 && map[a - 1][b] != 0)
				{
					LCD_Fill(b * 10 + 1, a * 10, b * 10 + 9, a * 10 + 1, GREEN);
				}
				if (abs(map[a + 1][b] - map[a][b]) == 1 && map[a + 1][b] != 0)
				{
					LCD_Fill(b * 10 + 1, a * 10 + 9, b * 10 + 9, a * 10 + 10, GREEN);
				}
				if (abs(map[a][b + 1] - map[a][b]) == 1 && map[a][b + 1] != 0)
				{
					LCD_Fill(b * 10 + 9, a * 10 + 1, b * 10 + 10, a * 10 + 9, GREEN);
				}
				if (abs(map[a][b - 1] - map[a][b]) == 1 && map[a][b - 1] != 0)
				{
					LCD_Fill(b * 10, a * 10 + 1, b * 10 + 1, a * 10 + 9, GREEN);
				}
				break;
			}
		}
	}
}
//void displayt()
//{
//	system("cls");
//	for (int a = 0; a < HEIGHT; a++) {
//		for (int b = 0; b < WIDTH; b++) {
//			std::cout.width(4);
//			std::cout << map[a][b];
//		}
//		std::cout << std::endl << std::endl;
//	}
//	Sleep(10);
//}
void newfood()
{ //随机一个新的食物
	int r = rand() % ((WIDTH - 2) * (HEIGHT - 2) - size);
	short *p;
	p = map[0];

	while (r >= 0)
	{
		if (*p == 0)
			r--;
		p++;
	}
	p--; //上方循环在r=0时p多自增了一次
	*p = -1;
}
