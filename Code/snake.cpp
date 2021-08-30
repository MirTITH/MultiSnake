#include "snake.h"
#include <iostream>
#include "game_map.h"

using namespace std;

Snake::~Snake()
{
	SnakeBlock* p = snakeHead;
	SnakeBlock* next_p = p->next;
	while (next_p != NULL)
	{
		delete p;
		p = next_p;
		next_p = p->next;
	}
	delete p;
}

void Snake::Init(int x, int y, int num, px_color color)
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
	snakeHead->x = x;
	snakeHead->y = y;
}

SnakeBlock* Snake::Get(int order)
{
	SnakeBlock* pointer = snakeHead;

	if (order > 0)
	{
		for (int i = 0; i < order; i++)
		{
			pointer = pointer->next;
			if (pointer == NULL) break;
		}
	}
	else if (order < 0)
	{
		if (chainLength + order < 0) return NULL;
		pointer = snakeHead;
		for (int i = 0; i < chainLength + order; i++)
		{
			pointer = pointer->next;
			if (pointer == NULL) break;
		}
	}

	return pointer;
}

void Snake::Move(Direct dir)
{
	int newHead_x; //新蛇头的位置
	int newHead_y; //新蛇头的位置
	int tail_x; //旧蛇尾的位置
	int tail_y; //旧蛇尾的位置

	switch (dir)
	{
	case Direct::unassign:
		cerr << "Err. [Snake::Move(Direct dir)] dir==Direct::unassign" << endl;
		return;
		break;
	case Direct::up:
		newHead_x = snakeHead->x;
		newHead_y = snakeHead->y - 1;
		break;
	case Direct::down:
		newHead_x = snakeHead->x;
		newHead_y = snakeHead->y + 1;
		break;
	case Direct::left:
		newHead_x = snakeHead->x - 1;
		newHead_y = snakeHead->y;
		break;
	case Direct::right:
		newHead_x = snakeHead->x + 1;
		newHead_y = snakeHead->y;
		break;
	default:
		cerr << "Err. [Snake::Move(Direct dir)] switch (dir) default" << endl;
		return;
		break;
	}

	lastDir = dir;

	if (newHead_x < 0) newHead_x += MAP_SIZE_X;
	if (newHead_y < 0) newHead_y += MAP_SIZE_Y;
	if (newHead_x >= MAP_SIZE_X) newHead_x -= MAP_SIZE_X;
	if (newHead_y >= MAP_SIZE_Y) newHead_y -= MAP_SIZE_Y;

	// 移动蛇
	if (chainLength > 1)
	{
		SnakeBlock* p = Get(-2);
		tail_x = p->next->x;
		tail_y = p->next->y;

		p->next->next = snakeHead;
		snakeHead = p->next;
		p->next = NULL;

		snakeHead->x = newHead_x;
		snakeHead->y = newHead_y;
	}
	else
	{
		tail_x = snakeHead->x;
		tail_y = snakeHead->y;

		snakeHead->x = newHead_x;
		snakeHead->y = newHead_y;
	}

	// 蛇增殖
	if (snakeHead->food > 0)
	{
		SnakeBlock* newTailBlock = new SnakeBlock; // 新的蛇尾节
		if (newTailBlock == NULL)
		{
			cerr << "Err. [Snake::Move(Direct dir)] newTailBlock == NULL" << endl;
			return;
		}

		newTailBlock->color = snakeHead->color;
		newTailBlock->food = snakeHead->food - 1;
		newTailBlock->next = NULL;
		newTailBlock->x = tail_x;
		newTailBlock->y = tail_y;
		snakeHead->food = 0;

		AddToTail(newTailBlock);
	}
}

int Snake::AddToTail(SnakeBlock* snakeBlock)
{
	SnakeBlock* tailBlock = Get(-1);
	if (tailBlock == NULL)
	{
		cerr << "Err. [Snake::AddToTail(SnakeBlock* snakeBlock)] tailBlock == NULL" << endl;
		return 1;
	}

	tailBlock->next = snakeBlock;
	chainLength++;

	return 0;
}

int Snake::Del(int order)
{
	SnakeBlock* p = Get(order);
	int delNum = 0;

	if (p == NULL)
	{
		cerr << "Err. [Snake::Del(int order)] Get(" << order << ") == NULL" << endl;
		return 0;
	}

	SnakeBlock* next_p = p->next;


	while (next_p != NULL)
	{
		delete p;
		delNum++;
		p = next_p;
		next_p = p->next;
	}
	delete p;
	delNum++;

	return delNum;
}

int Snake::Del(int x, int y)
{
	SnakeBlock* p = snakeHead;
	int delNum = 0; // 删除的个数

	// 寻找第一个满足条件的蛇节
	while (!(p->x == x && p->y == y))
	{
		if (p == NULL) return 0; // 说明没有满足条件的，删除了0个

		p = p->next;
	}

	// 开始删除
	SnakeBlock* next_p = p->next;

	while (next_p != NULL)
	{
		delete p;
		delNum++;
		p = next_p;
		next_p = p->next;
	}
	delete p;
	delNum++;

	return delNum;
}

SnakeBlock* Snake::GetSnakeBlockPos(int x, int y)
{
	SnakeBlock* p = snakeHead;

	// 寻找第一个满足条件的蛇节
	while (!(p->x == x && p->y == y))
	{
		if (p == NULL) return NULL; // 说明没有满足条件的，删除了0个

		p = p->next;
	}

	return p;
}

Direct Snake::GetReverseLastDir()
{
	switch (lastDir)
	{
	case Direct::unassign:
		return Direct::unassign;
		break;
	case Direct::up:
		return Direct::down;
		break;
	case Direct::down:
		return Direct::up;
		break;
	case Direct::left:
		return Direct::right;
		break;
	case Direct::right:
		return Direct::left;
		break;
	default:
		cerr << "Err. [Snake::GetReverseLastDir()] switch (lastDir) default" << endl;
		break;
	}
}