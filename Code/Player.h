#pragma once

#include "keyboard.h"
#include <string>
#include <iostream>
#include "PainterEngine_Application.h"
#include "snake.h"

using namespace std;

class Player
{
public:
	/**
	* @brief ����һλ��ң�֮����Ҫ��ʼ��
	*/
	Player()
	{
		ID = 0;
		T = 20;
		dir = Direct::up;
		nowTick = 0;
		keyMap = { 0 };
	}

	/**
	* @brief ��ʼ��һλ���
	* @param pid ���ID
	* @param _keyMap ��λӳ��
	* @param x,y ����
	* @param num �߳�ʼ����
	* @param color �ߵ���ɫ
	*/
	void Init(uint32_t pid, KeyMap _keyMap, int x, int y, int num = 10, px_color color = PX_COLOR(255, 30, 132, 244))
	{
		snake.Init(x, y, num, color);
		ID = pid;
		T = 50;
		dir = Direct::up;
		name = "id_" + to_string(ID);
		keyMap = _keyMap;
		nowTick = 0;
	}

	/**
	* @brief ���ļ�1�����ļ�T�κ����ƶ�һ��
	* @return void
	*/
	void Tick()
	{
		nowTick++;
		if (nowTick >= T)
		{
			nowTick = 0;

			Direct temp = input.GetDir();
			if (temp != Direct::unassign && temp != snake.GetReverseLastDir())
			{
				dir = temp;
			}
			snake.Move(dir);
		}
	}

	void GetInput();

	KeyMap keyMap;

	string name;

	uint32_t ID;

	int T; // �˶�����

	Snake snake;

	KeyInput input;// �������������
private:
	Direct dir; // ������÷����ƶ�
	int nowTick;
};
