#include <iostream>
#include "keyboard.h"
#include "PainterEngine_Application.h"

using namespace std;

void KeyInput::up(bool IsDown)
{
	if (IsDown && key_up) // ��������
	{
		if (GetDirKeyNum() == 1)
		{
			dir = direct::up;
		}
	}
	else if (IsDown && !key_up) // ����˲��
	{
		dir = direct::up;
	}
	else // δ����
	{
	}

	key_up = IsDown;
	return;
}

void KeyInput::down(bool IsDown)
{
	if (IsDown && key_down) // ��������
	{
		if (GetDirKeyNum() == 1)
		{
			dir = direct::down;
		}
	}
	else if (IsDown && !key_down) // ����˲��
	{
		dir = direct::down;
	}
	else // δ����
	{
	}

	key_down = IsDown;
	return;
}

void KeyInput::left(bool IsDown)
{
	if (IsDown && key_left) // ��������
	{
		if (GetDirKeyNum() == 1)
		{
			dir = direct::left;
		}
	}
	else if (IsDown && !key_left) // ����˲��
	{
		dir = direct::left;
	}
	else // δ����
	{
	}

	key_left = IsDown;
	return;
}

void KeyInput::right(bool IsDown)
{
	if (IsDown && key_right) // ��������
	{
		if (GetDirKeyNum() == 1)
		{
			dir = direct::right;
		}
	}
	else if (IsDown && !key_right) // ����˲��
	{
		dir = direct::right;
	}
	else // δ����
	{
	}

	key_right = IsDown;
	return;
}

direct KeyInput::GetDir()
{
	if (GetDirKeyNum() != 0)
	{
		return dir;
	}

	return direct::unassign;
}

int KeyInput::GetDirKeyNum()
{
	int result = 0;
	if (key_right) result++;
	if (key_left) result++;
	if (key_up) result++;
	if (key_down) result++;
	return result;
}