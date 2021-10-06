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

// ��ͼ��һ�飬ֻ�������ϰ���
typedef struct
{
	//bool tryTake; // �����Ҫռ�øÿ飬�Ƚ�tryTake��Ϊtrue����ֵsnake_Player
	//bool isExistSnake; // �Ƿ������
	//Player* snake_Player; // �ô��ߵ����ID
	//SnakeBlock* snakeBlock;

	int foodNum;
	px_color food_color;

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

	///**
	//* @brief ���ͼ�����һ���߽�
	//* @return 0 �ɹ���1 �ѱ���ռ�ã�2 �����ϰ���
	//*/
	//int AddSnakeBlock(Player* _snakePlayer, SnakeBlock* _snakeBlock);

	/**
	* @brief ÿһ��tick����һ�Σ������ߵ�tick�����Լ���ײ�ж�
	*/
	void Update();

	///**
	//* @brief �ӵ�ͼ��ɾ��һ���߽�
	//* @return ��ɾ�����߽ڣ������򷵻�NULL
	//*/
	//SnakeBlock* DelSnakeBlock(int x, int y);

	MapBlock GetMapBlock(int x, int y)
	{
		return mapBlock[x][y];
	}

	/**
	* @brief �������ʳ��
	*/
	void GenerateFood();

	void DelFood(int x, int y);

	int GetFood(int x, int y);

	Player player[PLAYER_NUM];

private:
	MapBlock mapBlock[MAP_SIZE_X][MAP_SIZE_Y];

	int totalFoodNum; // ��ʳ��ĸ�������

	//int generateFood_T; //����ʳ�������
};