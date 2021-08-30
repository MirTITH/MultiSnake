#include "Player.h"

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
	int newHead_x; //����ͷ��λ��
	int newHead_y; //����ͷ��λ��
	int tail_x; //����β��λ��
	int tail_y; //����β��λ��

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

	// �ƶ���
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
	
	// ����ֳ
	if (snakeHead->food > 0)
	{
		SnakeBlock* newTailBlock = new SnakeBlock; // �µ���β��
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
	int delNum = 0; // ɾ���ĸ���

	// Ѱ�ҵ�һ�������������߽�
	while (!(p->x == x && p->y == y))
	{
		if (p == NULL) return 0; // ˵��û�����������ģ�ɾ����0��

		p = p->next;
	}

	// ��ʼɾ��
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

	// Ѱ�ҵ�һ�������������߽�
	while (!(p->x == x && p->y == y))
	{
		if (p == NULL) return NULL; // ˵��û�����������ģ�ɾ����0��

		p = p->next;
	}

	return p;
}