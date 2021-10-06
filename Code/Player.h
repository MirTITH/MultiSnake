#pragma once

#include "keyboard.h"
#include <string>
#include <iostream>
#include "PainterEngine_Application.h"
#include "snake.h"
#include "skill.h"

#define PLAYER_NUM 2 // ��ҵ�����

using namespace std;

class Player
{
public:
	/**
	* @brief ����һλ��ң�֮����Ҫ��ʼ��
	*/
	Player();

	/**
	* @brief ��ʼ��һλ���
	* @param pid ���ID
	* @param _keyMap ��λӳ��
	* @param x,y ����
	* @param num �߳�ʼ����
	* @param color �ߵ���ɫ
	*/
	void Init(uint32_t pid, KeyMap _keyMap, int x, int y, int num = 10, px_color color = PX_COLOR(255, 30, 132, 244));

	/**
	* @brief ���ļ�1�����ļ�T�κ����ƶ�һ��
	* @return void
	*/
	void Tick();

	void GetInput();

	string name;

	uint32_t ID;

	px_color defaultColor;

	Snake snake;

	/**
	* @brief �����˶�����
	* @param newT �µ�����
	* @param _tick �����ڳ�����ã���λtick��
	*/
	void SetT(int newT, int _tick);
private:
	/**
	* @brief �����˶����ڣ�ÿ��tickִ��һ��
	*/
	void UpdateT();

	/**
	* @brief ���ܣ�����
	*/
	void SpeedUp();

	Direct dir; // ������÷����ƶ�
	KeyInput input;// �������������
	KeyMap keyMap;
	int nowTick;
	int T; // ��ǰ�˶�����
	int defaultT; // Ĭ���˶�����
	int T_tick; // ��ʣ��ûص� defaultT
	bool isInited; // �Ƿ��ʼ��
	Skill skill_speed_up;
};
