#pragma once

#include "myheadfile.h"

//typedef struct student {
//	int score;
//	struct student* next;
//} LinkList;

// ����ӳ��
typedef struct key_map
{
	int up;//��
	int down;//��
	int left;//��
	int right;//��
	int accelerate;//����
	int slowdown;//����
	int skill_1;//С����
	int skill_2;//����
}KeyMap;

class KeyInput
{
public:
	void up(bool IsDown);
	void down(bool IsDown);
	void left(bool IsDown);
	void right(bool IsDown);
	direct GetDir();//��ȡ����
	int GetDirKeyNum(); //��ȡͬʱ���µķ��������
private:
	bool key_up = false;
	bool key_down = false;
	bool key_left = false;
	bool key_right = false;
	direct dir = direct::unassign;
};
