#pragma once
#include "PainterEngine_Application.h"
#include "keyboard.h"
#include <iostream>

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
		isInited = false;
		snakeHead = NULL;
		defaultColor = PX_COLOR(255, 30, 132, 244);
		lastDir = Direct::unassign;

		clog << hex << this << " Snake created." << endl;
	}

	~Snake();

	/**
	* @brief ��ʼ��һ���ߣ������ڴ���������ִ��
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
	* @return �ߵĳ��ȣ�������ʳ������
	*/
	int GetLength();

	/**
	* @brief ����β���߽ڣ���ʹsnakeLength + 1
	* @param snakeBlock	�Ѹ��߽���ӵ���β
	* @return 0 �ɹ�; 1 ��ȡ��β����-1 δ��ʼ��
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
	bool isInited; // �Ƿ��ʼ��
	//int chainLength; // �ߵĳ��ȣ�������ʳ�������ĳ��ȣ�
};