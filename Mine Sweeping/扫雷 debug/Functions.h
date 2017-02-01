#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <random>
#include <ctime>
#include <windows.h>
#include <fstream>
using namespace std;

struct Pos//坐标
{
	int x;
	int y;
};

enum key
{
	_none,
	_up,
	_down,
	_left,
	_right,
	_defuse
};


enum Color     //定义颜色
{ 
	DARKBLUE = 1,
	DARKGREEN,
	DARKTEAL, 
	DARKRED,
	DARKPINK,
	DARKYELLOW,
	GRAY, 
	DARKGRAY,
	BLUE,
	GREEN,
	TEAL, 
	RED,
	PINK,
	YELLOW,
	WHITE
};


typedef default_random_engine randomer;
randomer rander((unsigned)time(0));

int random(int num1, int num2)
{
	if (num1 > num2)//生成随机数时一个参数必须小于第二个
	{
		num1 ^= num2;
		num2 ^= num1;
		num1 ^= num2;//交换2个参数
	}
	uniform_int_distribution<int> uni(num1,num2);
	return uni(rander);
}

void SetColor(const Color c = WHITE)//改变输出字体颜色的函数
{
	static HANDLE handle;
	if (handle == NULL)
	{
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	SetConsoleTextAttribute(handle,  c);
}

inline void SetPos(const short x, const short y)//可以改变控制台光标位置的函数
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y });
}
void SetCourseSize(const DWORD/*unsigned long*/ size/*百分点*/)//可以改变控制台光标厚度的函数
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = size;
	info.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

key KeyHit()//按键检测
{
	key press = _none;
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'w':
			case 'W':
				press = _up; break;
			case 'a':
			case 'A':
				press = _left; break;
			case 'S':
			case 's':
				press = _down; break;
			case 'd':
			case 'D':
				press = _right; break;
			case ' ':
				press = _defuse;
		}
	}
	return press;
}

inline int sabs(int num)//绝对值函数
{
	return num > 0 ? num : -num;
}
#endif