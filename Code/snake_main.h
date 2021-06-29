#pragma once

#include "PainterEngine_Application.h"
#include "keyboard.h"

#define MAP_SIZE_X (PX_APPLICATION_SURFACE_HEIGHT / 2)
#define MAP_SIZE_Y (PX_APPLICATION_SURFACE_WIDTH / 2)

struct Snake
{
	int x;// x����
	int y;// y����
	direct Dir;// ���з���
	int food; //��һ�ڵ�ʳ����
	px_color color; //��ɫ 
	Snake* next;
};

class Player
{
public:
	Player(int PlayerID); //PlayerID Ϊ 1 �� 2
	~Player();
	void get_input();
	KeyInput input;// �������������
	KeyMap keymap;// ��λӳ��
	Snake* snake(int length);// ͷlength=0��βlength = -1������NULL��ʾ������
	void snake_addtotail(Snake* NewSnake); // ��β������
	int snake_delfromhead(int num);// ��ͷ��ɾ��num�ڣ����سɹ�ɾ���Ľ���

	/*
		�ƶ����˺���Ҫִ��T�κ�Ż��ƶ�һ��
		����״̬
			0 δ�ƶ�
			1 �ɹ��ƶ�һ��
	*/
	int move(); 
	int T; //�������ں�ǰ��һ��
private:
	Snake* snake_head = NULL; //��ͷ
};

