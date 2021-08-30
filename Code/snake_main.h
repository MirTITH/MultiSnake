#pragma once

#include "PainterEngine_Application.h"
#include "keyboard.h"

#define MAP_SIZE_X (PX_APPLICATION_SURFACE_HEIGHT / 2)
#define MAP_SIZE_Y (PX_APPLICATION_SURFACE_WIDTH / 2)

struct Snake_Unit
{
	int x;// x����
	int y;// y����
	Direct Dir = Direct::unassign;// ���з���
	int food; //��һ�ڵ�ʳ����
	px_color color; //��ɫ 
	Snake_Unit* next;
};

class Player
{
public:
	Player(int PlayerID); //PlayerID Ϊ 1 �� 2
	~Player();
	void get_input();
	KeyInput input;// �������������
	KeyMap keymap;// ��λӳ��
	Snake_Unit* snake(int length);// ͷlength=0��βlength = -1������NULL��ʾ������
	void snake_addtotail(Snake_Unit* NewSnake); // ��β������
	int snake_delfromhead(int num);// ��ͷ��ɾ��num�ڣ����سɹ�ɾ���Ľ���

	/*
		�ƶ����˺���Ҫִ��T�κ�Ż��ƶ�һ��
		����״̬
			0 δ�ƶ�
			1 �ɹ��ƶ�һ��
	*/
	int move(); 
	int T = 1; //�������ں�ǰ��һ��
private:
	Snake_Unit* snake_head = NULL; //��ͷ
	int timer = 0;
};

int Snake_main_init();

class Snake
{
public:
	Snake(int x, int y, int length, px_color color);
	~Snake();

	// ͷlength=0��βlength = -1������NULL��ʾ������
	Snake_Unit* Get(int length);

	// ��ȡ�ߵĳ���
	int Length();

	// ��β������
	void AddToTail(Snake_Unit* NewSnake); 
	
	// ��ͷ��ɾ��num�ڣ����سɹ�ɾ���Ľ���
	int DelFromHead(int num);

	// ���趨�ķ����ƶ�����Ҫִ��T�β��ƶ�һ��
	int move();

	Direct dir = Direct::up; //��ͷ���з���
	int T = 10; //�������ں�ǰ��һ��
private:
	Snake_Unit* snake_head = NULL; //��ͷ
	int timer = 0;
};
