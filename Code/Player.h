#pragma once

#include "keyboard.h"
#include <string>
#include <iostream>
#include "PainterEngine_Application.h"

using namespace std;

// �ߵ�һ��
struct SnakeBlock
{
	int x; // x����
	int y; // y����
	px_color color;
	int food;
	SnakeBlock* next;
};

// ��СΪ�����С�����������ײ���Ч��
//extern SnakeBlock* world_space[][];

class Snake
{
public:
	/**
	* @brief ����һ���ߣ�֮����Ҫִ��Init()��ʼ��
	* @param num �ߵĳ�ʼ����
	* @param color �ߵĳ�ʼ��ɫ
	*/
	Snake()
	{
		snakeHead = NULL;
		//if (snakeHead == NULL)
		//{
		//	cerr << "Err. [Snake::Snake] snakeHead = new SnakeBlock fail" << endl;
		//}

		defaultColor = PX_COLOR(255, 30, 132, 244);

		chainLength = 0;
		lastDir = Direct::unassign;

		//snakeHead->color = defaultColor;
		//snakeHead->food = num;
		//snakeHead->next = NULL;

		////snakeHead->x = MAP_SIZE_X / 3;
		////snakeHead->y = MAP_SIZE_Y / 4;
	}

	~Snake();

	/**
	* @brief ��ʼ��һ���ߣ�ֻ���ڳ�ʼ��������ִ��
	* @param num �ߵĳ�ʼ����
	* @param color �ߵĳ�ʼ��ɫ
	*/
	void Init(int num = 10, px_color color = PX_COLOR(255, 30, 132, 244))
	{
		snakeHead = new SnakeBlock;
		if (snakeHead == NULL)
		{
			cerr << "Err. [Snake::ReInit] snakeHead == NULL" << endl;
		}

		defaultColor = color;

		chainLength = 1;
		lastDir = Direct::unassign;

		snakeHead->color = defaultColor;
		snakeHead->food = num;
		snakeHead->next = NULL;
	}

	// ִ��һ�ξ��� dir �����ƶ�һ��
	void Move(Direct dir);

	/**
	* @param order �߽ڵ�������0��ʾ��1�ڣ�-1��ʾ������һ��
	* @return ����ָ���߽ڵ�ָ�룬���򷵻�NULL
	*/
	SnakeBlock* Get(int order);

	/**
	* @brief ����β���߽ڣ���ʹsnakeLength + 1
	* @param snakeBlock	�Ѹ��߽���ӵ���β
	* @return 0 �ɹ�; 1 ��ȡ��β����
	*/
	int AddToTail(SnakeBlock* snakeBlock);

	/**
	* @brief ��order����ʼ���ɾ�������߽ڣ�orderҲ��ɾ��
	* @param order �߽ڵ�������0��ʾ��1�ڣ�-1��ʾ������һ��
	* @return ɾ���Ľ���
	*/
	int Del(int order);

	/**
	* @brief ɾ������Ϊ(x,y)����֮��������߽�
	* @return ɾ���Ľ���
	*/
	int Del(int x, int y);

	/**
	* @brief ����ϴ��ߵ��ƶ�����
	* @return 
	*/
	Direct Get_Dir_Last()
	{
		return lastDir;
	}


	/**
	* @brief ���(x,y)���Ƿ�����
	* @return ���򷵻��߽ڵ�ָ�룬���򷵻�NULL
	*/
	SnakeBlock* GetSnakeBlockPos(int x, int y);
private:
	SnakeBlock* snakeHead;
	Direct lastDir; // �ϴ��ƶ��ķ���
	px_color defaultColor;
	int chainLength; // �ߵĳ��ȣ�������ʳ�������ĳ��ȣ�
};

class Player
{
public:
	/**
	* @brief ����һλ���
	* @param pid ���ID
	* @param _keyMap ��λӳ��
	* @param num �߳�ʼ����
	* @param color �ߵ���ɫ
	*/
	Player(uint32_t pid, KeyMap _keyMap, int num = 10, px_color color = PX_COLOR(255, 30, 132, 244))
	{
		snake.Init(num, color);
		ID = pid;
		T = 20;
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
			snake.Move(dir);
		}
	}

	KeyMap keyMap;

	string name;

	uint32_t ID;

	int T; // �˶�����

	Snake snake;
private:
	Direct dir; // ������÷����ƶ�
	int nowTick;
};
