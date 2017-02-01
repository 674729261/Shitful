#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <random>
#include <ctime>
#include <windows.h>
#include <fstream>
using namespace std;

struct Pos//����
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


enum Color     //������ɫ
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
	if (num1 > num2)//���������ʱһ����������С�ڵڶ���
	{
		num1 ^= num2;
		num2 ^= num1;
		num1 ^= num2;//����2������
	}
	uniform_int_distribution<int> uni(num1,num2);
	return uni(rander);
}

void SetColor(const Color c = WHITE)//�ı����������ɫ�ĺ���
{
	static HANDLE handle;
	if (handle == NULL)
	{
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	SetConsoleTextAttribute(handle,  c);
}

inline void SetPos(const short x, const short y)//���Ըı����̨���λ�õĺ���
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y });
}
void SetCourseSize(const DWORD/*unsigned long*/ size/*�ٷֵ�*/)//���Ըı����̨����ȵĺ���
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = size;
	info.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

key KeyHit()//�������
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

inline int sabs(int num)//����ֵ����
{
	return num > 0 ? num : -num;
}
#endif