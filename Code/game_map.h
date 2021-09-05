#pragma once

#include "PainterEngine_Application.h"
#include "snake.h"
#include "Player.h"

#define MAP_DISPLAY_X 1000
#define MAP_DISPLAY_Y 720

#define MAP_SIZE_X (MAP_DISPLAY_X / 8)
#define MAP_SIZE_Y (MAP_DISPLAY_Y / 8)

const int MAP_EDGE_TO_SCREEN_L = (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X) / 2;// ��ͼ��߽��Ӧ����Ļ����
const int MAP_EDGE_TO_SCREEN_U = (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y) / 2;// ��ͼ�ϱ߽��Ӧ����Ļ����
const int MAP_EDGE_TO_SCREEN_R = PX_APPLICATION_SURFACE_WIDTH - 1 - (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X) / 2;// ��ͼ�ұ߽��Ӧ����Ļ����
const int MAP_EDGE_TO_SCREEN_D = PX_APPLICATION_SURFACE_HEIGHT - 1 - (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y) / 2;// ��ͼ�±߽��Ӧ����Ļ����

/**
* @brief ����ͼ�ϵĵ�ӳ�䵽��Ļ��
*/
px_int MapToScreen_x(int x);

/**
* @brief ����ͼ�ϵĵ�ӳ�䵽��Ļ��
*/
px_int MapToScreen_y(int y);

// ��ͼ��һ��
typedef struct
{
	bool tryTake; // �����Ҫռ�øÿ飬�Ƚ�tryTake��Ϊtrue����ֵsnake_Player
	bool isExistSnake; // �Ƿ������
	Player* snake_Player; // �ô��ߵ����ID
	SnakeBlock* snakeBlock;

	bool isExistObstacle; // �Ƿ�����ϰ���
	px_color obstacle_color; // �ϰ������ɫ
}MapBlock;

class GameMap
{
public:
	/**
	* ��ͼ
	*/
	GameMap();

	/**
	* @return ��ͼ��x�᳤��
	*/
	int Size_x()
	{
		return MAP_DISPLAY_X;
	}

	/**
	* @return ��ͼ��y�᳤��
	*/
	int Size_y()
	{
		return MAP_DISPLAY_Y;
	}

	/**
	* @brief ���ͼ�����һ���߽�
	* @return 0 �ɹ���1 �ѱ���ռ�ã�2 �����ϰ���
	*/
	int AddSnakeBlock(Player* _snakePlayer, SnakeBlock* _snakeBlock);

	void Update()
	{
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			player[i].Tick();
		}

		// ��ͷ����ͷ��ײ
		for (int x = 0; x < PLAYER_NUM - 1; x++)
		{
			for (int y = x + 1; y < PLAYER_NUM; y++)
			{
				if (player[x].snake.Get(0)->x == player[y].snake.Get(0)->x && player[x].snake.Get(0)->y == player[y].snake.Get(0)->y)
				{
					player[x].snake.DelHead();
					player[y].snake.DelHead();
				}
			}
		}

		// ��ͷ����������ײ
		for (int s0 = 0; s0 < PLAYER_NUM; s0++)
		{
			for (int s1 = 0; s1 < PLAYER_NUM; s1++)
			{
				if (s1 == s0)
				{
					continue;
				}

				int i = 0;
				int x0 = player[s0].snake.Get(0)->x;
				int y0 = player[s0].snake.Get(0)->y;
				SnakeBlock* p = player[s1].snake.Get(0);

				while (p != NULL)
				{
					if (p->x == x0 && p->y == y0)
					{
						player[s0].snake.DelHead();
					}

					i++;
					p = player[s1].snake.Get(i);
				}
			}
		}

		// ��ͷ���Լ���ײ
		for (int s = 0; s < PLAYER_NUM; s++)
		{
			int i = 1;
			int x0 = player[s].snake.Get(0)->x;
			int y0 = player[s].snake.Get(0)->y;
			SnakeBlock* p = player[s].snake.Get(i);

			while (p != NULL)
			{
				if (p->x == x0 && p->y == y0)
				{
					player[s].snake.DelHead();
				}

				i++;
				p = player[s].snake.Get(i);
			}
		}

		/*for (int x = 0; x < MAP_SIZE_X; x++)
		{
			for (int y = 0; y < MAP_SIZE_Y; y++)
			{
				if (mapBlock[x][y].tryTake == true)
				{
					mapBlock[x][y].tryTake = false;
					mapBlock[x][y].isExistSnake = true;
				}
			}
		}*/
	}

	/**
	* @brief �ӵ�ͼ��ɾ��һ���߽�
	* @return ��ɾ�����߽ڣ������򷵻�NULL
	*/
	SnakeBlock* DelSnakeBlock(int x, int y);

	MapBlock GetMapBlock(int x, int y)
	{
		return mapBlock[x][y];
	}

	Player player[PLAYER_NUM];

private:
	MapBlock mapBlock[MAP_SIZE_X][MAP_SIZE_Y];
};