#pragma once
#ifndef SNAKE_H
#define SNAKE_H

//#include "AI.h"
#include <time.h>
//#include <SDL.h>
//#include <iostream>
//#include <Windows.h>
#include "AI.h"
#include "public.h"
//#include <vector>
//#include <queue>
#include "LCD.h"
//#include "LED.h"

void display();         // 显示
int move(int x, int y); //蛇的移动
void newfood();         //刷新食物
int initialize();
int game();
int gamewithai();
void displayt();

//class snake
//{
//private:
//	short Width, Height;
//	std::vector<std::vector<short>> snakemap = std::vector<std::vector<short>>(Height, std::vector<short>(Width));
//	std::queue<short> snakebody;
//public:
//	snake() = default;
//	~snake() = default;
//	int move(Direction);//移动函数 返回值0 移动成功 返回值1 移动非法 返回值-1 出现其他错误
//	const std::vector<std::vector<short>>& map();
//
//};

#endif