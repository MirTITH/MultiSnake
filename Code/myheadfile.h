#pragma once

#include "PainterEngine_Application.h"

// ���λ��
typedef struct pointer_pos
{
	px_float x;
	px_float y;
}POINTER_POS;

enum class direct
{
	unassign,
	up,
	down,
	left,
	right
};

// ϵͳʱ�Ӽ�ʱ����
void Sys_tick_f();