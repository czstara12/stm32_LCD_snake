#pragma once
#ifndef PUBLIC_H
#define PUBLIC_H

#define WIDTH 24
#define HEIGHT 32 //长宽

typedef enum
{
    false = 0,
    true = 1
} bool;

typedef enum
{
    d_up,
    d_down,
    d_left,
    d_right,
    d_error
} Direction; //方向

#endif