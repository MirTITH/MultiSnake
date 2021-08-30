#pragma once
#include "PainterEngine_Application.h"
#include "keyboard.h"

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
	* @param x,y ����
	* @param num �ߵĳ�ʼ����
	* @param color �ߵĳ�ʼ��ɫ
	*/
	void Init(int x, int y, int num = 10, px_color color = PX_COLOR(255, 30, 132, 244));

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
	Direct GetLastDir()
	{
		return lastDir;
	}

	/**
	* @brief ����ϴ��ߵķ��ƶ�����
	* @return
	*/
	Direct GetReverseLastDir();


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