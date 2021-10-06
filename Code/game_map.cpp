#include "game_map.h"

px_int MapToScreen_x(int x)
{
	return (PX_APPLICATION_SURFACE_WIDTH - MAP_DISPLAY_X + MAP_DISPLAY_X / MAP_SIZE_X) / 2 + MAP_DISPLAY_X * x / MAP_SIZE_X;
}

px_int MapToScreen_y(int y)
{
	return (PX_APPLICATION_SURFACE_HEIGHT - MAP_DISPLAY_Y + MAP_DISPLAY_Y / MAP_SIZE_Y) / 2 + MAP_DISPLAY_Y * y / MAP_SIZE_Y;
}

GameMap::GameMap()
{
	for (int x = 0; x < MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			//mapBlock[x][y].tryTake = false;
			mapBlock[x][y].isExistObstacle = false;
			//mapBlock[x][y].isExistSnake = false;
			mapBlock[x][y].obstacle_color = PX_COLOR(255, 0, 0, 0);
			//mapBlock[x][y].snakeBlock = NULL;
			//mapBlock[x][y].snake_Player = NULL;

			mapBlock[x][y].foodNum = 0;
			mapBlock[x][y].food_color = PX_COLOR(255, 0, 158, 0);
			totalFoodNum = 0;
		}
	}
}

//int GameMap::AddSnakeBlock(Player* _snakePlayer, SnakeBlock* _snakeBlock)
//{
//	if (mapBlock[_snakeBlock->x][_snakeBlock->y].isExistSnake)
//	{
//		return 1;
//	}
//
//	if (mapBlock[_snakeBlock->x][_snakeBlock->y].isExistObstacle)
//	{
//		return 2;
//	}
//
//	if (mapBlock[_snakeBlock->x][_snakeBlock->y].tryTake == false)
//	{
//		mapBlock[_snakeBlock->x][_snakeBlock->y].tryTake = true;
//		mapBlock[_snakeBlock->x][_snakeBlock->y].isExistSnake = false;
//		mapBlock[_snakeBlock->x][_snakeBlock->y].snakeBlock = _snakeBlock;
//		mapBlock[_snakeBlock->x][_snakeBlock->y].snake_Player = _snakePlayer;
//	}
//	else
//	{
//		mapBlock[_snakeBlock->x][_snakeBlock->y].snake_Player->snake.DelHead();
//		_snakePlayer->snake.DelHead();
//		mapBlock[_snakeBlock->x][_snakeBlock->y].tryTake = false;
//		mapBlock[_snakeBlock->x][_snakeBlock->y].isExistSnake = false;
//		mapBlock[_snakeBlock->x][_snakeBlock->y].snakeBlock = NULL;
//		mapBlock[_snakeBlock->x][_snakeBlock->y].snake_Player = NULL;
//	}
//
//	return 0;
//}

void GameMap::Update()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player[i].Tick();
	}
	
	// ʳ�����

	if (totalFoodNum < 2)
	{
		GenerateFood();
	}

	// �Ե�ʳ��
	for (int s = 0; s < PLAYER_NUM; s++)
	{
		SnakeBlock* p = player[s].snake.Get(0);

		if (mapBlock[p->x][p->y].foodNum != 0)
		{
			p->food += mapBlock[p->x][p->y].foodNum;
			mapBlock[p->x][p->y].foodNum = 0;
			totalFoodNum--;
		}

		if (mapBlock[p->x+1][p->y].foodNum != 0)
		{
			p->food += mapBlock[p->x+1][p->y].foodNum;
			mapBlock[p->x+1][p->y].foodNum = 0;
			totalFoodNum--;
		}

		if (mapBlock[p->x-1][p->y].foodNum != 0)
		{
			p->food += mapBlock[p->x-1][p->y].foodNum;
			mapBlock[p->x-1][p->y].foodNum = 0;
			totalFoodNum--;
		}

		if (mapBlock[p->x][p->y+1].foodNum != 0)
		{
			p->food += mapBlock[p->x][p->y+1].foodNum;
			mapBlock[p->x][p->y+1].foodNum = 0;
			totalFoodNum--;
		}

		if (mapBlock[p->x][p->y-1].foodNum != 0)
		{
			p->food += mapBlock[p->x][p->y-1].foodNum;
			mapBlock[p->x][p->y-1].foodNum = 0;
			totalFoodNum--;
		}
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
}

void GameMap::GenerateFood()
{
	while (true)
	{
		int x = rand() % MAP_SIZE_X;
		int y = rand() % MAP_SIZE_Y;

		if (mapBlock[x][y].foodNum == 0)
		{
			mapBlock[x][y].foodNum = 5;
			totalFoodNum++;
			break;
		}
	}
}

//SnakeBlock* GameMap::DelSnakeBlock(int x, int y)
//{
//	SnakeBlock* result = mapBlock[x][y].snakeBlock;
//	mapBlock[x][y].isExistSnake = false;
//	mapBlock[x][y].snakeBlock = NULL;
//	mapBlock[x][y].snake_Player = NULL;
//	return result;
//}