/*
Copyright Shitful Game inc.
Shitful : programming
Feu : Art
Time : 3 hours
*/
#include <iostream>
#include <string>
#include <conio.h>
#include "Functions.h"
using namespace std;
void __init__();  //所有的初始化都在这个函数里

inline Pos changepos(Pos p)
{
	return Pos{ p.x + 3,p.y + 3 };
}

inline Pos changepos(short x,short y)
{
	return Pos{ x + 3,y + 3 };
}

enum Unit
{
	null,//超出棋盘外
	safe,//无地雷
	searched_safe,//已经确认的无地雷
	mine//地雷
}units[9][9];

int main()
{
	__init__();
	string name;
	int width = 0;
	cout << "Please write down your name:";
	getline(cin, name);
	while (width <= 3 || width >= 10) //期棋盘是正方形，格子数在9到100之间
	{
		cout << "Please enter the width(height) of the map:";
		cin >> width;
		if (width >= 10)
		{
			cout << "Too large." << endl;
			continue;
		}
		else if (width <= 3)
		{
			cout << "Too small." << endl;
			continue;
		}
		else
			break;
	}
	int n_mine = 0;
	while (n_mine < 0.1 * width * width || n_mine > 0.85 * width * width) //雷数限制在总格子数的十分之三到85%之间
	{
		cout << "Please enter the number of your mines(not exactly):";
		cin >> n_mine;
		if (n_mine < 0.1 * width * width)
		{
			cout << "Too few." << endl;
			continue;
		}
		else if (n_mine > 0.85 * width * width)
		{
			cout << "Too many." << endl;
			continue;
		}
		else
			break;
	}
	cout << "Game begin in 3 seconds.";
	Sleep(1000);
	cout << '.';
	Sleep(1000);
	cout << '.';
	Sleep(1000);
	system("cls");

	Pos Ply_pos = { 0,0 };
	SetCourseSize(100);//方便玩家辨别光标位置
	for (int i = 0; i < width; ++i)//绘制棋盘
	{
		SetPos(0, 3 + i);
		cout << i + 1;
		SetPos(3 + i, 0);
		cout << i + 1;
		SetPos(3 + i, 1);
		cout << '-';
		SetPos(1, 3 + i);
		cout << '|';


		SetPos(3, 3 + i);
		for (int n = 0; n < width; ++n)
			cout << '?';
	}

	SetPos(0, 13);
	cout << "Press space to defuse the mine.";

	int rand = 0;//初始化棋盘内的物件
	int num_safe = 0, s;
	for (int i = 0; i < width; ++i)
	{
		for (int n = 0; n < width; ++n)
		{
			rand = random(1, width*width);
			if (rand <= n_mine)//生成地雷，但数量不一定是n_mine
				units[i][n] = mine;
			else
				units[i][n] = safe, ++num_safe;
		}
	}
	s = num_safe;  //这个s用于最后的成绩输出
	SetPos(16, 0);
	cout << "Total mines:" << width*width - num_safe;

	for (int i = 0; i < 9; ++i)    
	{
		for (int n = 0; n < 9; ++n)
		{
			if (i > width || n > width)
				units[i][n] = null;
		}
	}
	SetPos(3, 3);

	bool gg = false;

	while (!gg)
	{
		Sleep(1);
		switch (KeyHit())
		{
		case _up:
			if (Ply_pos.y != 0)
				--Ply_pos.y, SetPos(3 + Ply_pos.x, 3 + Ply_pos.y);//谁什么要+3：因为控制台的3,3对应了玩家坐标的0,0
			break;
		case _down:
			if (Ply_pos.y != width - 1)
				++Ply_pos.y, SetPos(3 + Ply_pos.x, 3 + Ply_pos.y);
			break;
		case _left:
			if (Ply_pos.x != 0)
				--Ply_pos.x, SetPos(3 + Ply_pos.x, 3 + Ply_pos.y);
			break;
		case _right:
			if (Ply_pos.x != width - 1)
				++Ply_pos.x, SetPos(3 + Ply_pos.x, 3 + Ply_pos.y);
			break;
		case _defuse:
			if (units[Ply_pos.x][Ply_pos.y] == mine)
			{
				gg = true;
				SetColor(DARKRED);//换上醒目的深红色
				for (int i = 0; i < 9; ++i)
				{
					for (int n = 0; n < 9; ++n)
					{
						if (units[i][n] == mine)
						{
							SetPos(3 + i, 3 + n);
							cout << 'X';
						}
					}
				}
				SetPos(0, 14);
				cout << "Game Over.";
				Sleep(5000);
			}
			if (units[Ply_pos.x][Ply_pos.y] == safe)
			{
				--num_safe;//原来num_safe等于总安全的格子数，扫到一个安全格子就减少1
				units[Ply_pos.x][Ply_pos.y] = searched_safe;//防止点已经点过的格子加分
				SetPos(3 + Ply_pos.x, 3 + Ply_pos.y);
				int num = 0;
				for (int i = 0; i < 9; ++i)//遍历数组,找出找出的安全的格子周围8格的地雷的个数
				{
					for (int n = 0; n < 9; ++n)
					{
						if (sabs(i - Ply_pos.x) <= 1 && sabs(n - Ply_pos.y) <= 1 && units[i][n] == mine)
							++num;
					}
				}
				SetPos(3 + Ply_pos.x, 3 + Ply_pos.y);
				if (num != 0)
				{
					SetColor(YELLOW);//换上保护眼睛的绿色
					cout << num;
				}
				if (num == 0)
				{
					SetColor(GREEN);
					cout << '0';
				}

				if (num_safe <= 0)//安全的格子全部找出来了,就赢了
				{
					SetPos(0, 15);
					SetColor(YELLOW);
					cout << "You win.";
					SetColor(DARKRED);//换上醒目的深红色
					for (int i = 0; i < 9; ++i)
					{
						for (int n = 0; n < 9; ++n)
						{
							if (units[i][n] == mine)
							{
								SetPos(3 + i, 3 + n);
								cout << 'X';
							}
						}
					}
					Sleep(5000);
					gg = true;
				}
				SetPos(3 + Ply_pos.x, 3 + Ply_pos.y);
			}
		}
	}
	system("cls");
	SetColor();//变回原来的白色
	cout << "Marks printed in Marks.txt.\n";
	cout << "Press any key to exit.";

	ofstream of;//输出玩家信息
	of.open("Marks.txt", ios::app);
	of << "\nPlayer name: " << name << endl;
	of << "Total units: " << width*width << endl;
	of << "Total mines: " << width*width - s << endl;
	of << "Comfirmed units: " << s - num_safe << endl;
	of << "Complete pecentage: " << ((double)(s - num_safe) / s) * 100 << '%' << endl << endl;
	of.close();
	_getch();
	return 0;
}


void __init__()
{
	randomer rand((unsigned)time(0));
	SetWindowTextA(GetConsoleWindow(), "扫雷");
}