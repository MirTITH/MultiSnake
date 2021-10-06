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
		defaultColor_head = PX_COLOR(255, 255, 255, 255);
		defaultColor_body = PX_COLOR(255, 30, 132, 244);
		color_body = defaultColor_body;
		color_head = defaultColor_head;
		lastDir = Direct::unassign;
		playerID = 0;

		clog << hex << this << " Snake created." << endl;
	}

	~Snake();

	/**
	* @brief ��ʼ��һ���ߣ������ڴ���������ִ��
	* @param x,y ����
	* @param num �ߵĳ�ʼ����
	* @param color �ߵĳ�ʼ��ɫ
	*/
	void Init(uint32_t _playerID, int x, int y, int num = 10, px_color color = PX_COLOR(255, 30, 132, 244));

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
	* @brief ɾ����ͷ
	* @return 0 �ɹ���1ʧ��
	*/
	int DelHead();

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

	/**
	* @brief ��ȡ��ɫ
	*/
	px_color GetColor(int order);
private:
	SnakeBlock* snakeHead;
	Direct lastDir; // �ϴ��ƶ��ķ���
	px_color defaultColor_head;
	px_color defaultColor_body;
	px_color color_head;
	px_color color_body;
	bool isInited; // �Ƿ��ʼ��
	uint32_t playerID;
	//int chainLength; // �ߵĳ��ȣ�������ʳ�������ĳ��ȣ�
};