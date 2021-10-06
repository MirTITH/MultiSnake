#include "game_ui.h"

string text[PLAYER_NUM];

/**
* @brief ������Ϸʱ����
*/
void Draw_Playing(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;

	// ���Ʊ���
	PX_GeoDrawRect(pRenderSurface, MAP_EDGE_TO_SCREEN_L, MAP_EDGE_TO_SCREEN_U, MAP_EDGE_TO_SCREEN_R, MAP_EDGE_TO_SCREEN_D, PX_COLOR(255, 55, 44, 77));

	DrawSnake(pApp);// ������

	DrawPlayerInfo(pApp);// ���������Ϣ

	cursor_draw(pRenderSurface); //������꣬�뱣�����������
}

void DrawSnake(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	for (int pOrder = 0; pOrder < PLAYER_NUM; pOrder++)
	{
		SnakeBlock* snakeBlock;
		for (int i = 0; ; i++)
		{
			snakeBlock = gameMap.player[pOrder].snake.Get(i);
			if (snakeBlock == NULL) break;
			// ������
			PX_GeoDrawCircle(pRenderSurface, MapToScreen_x(snakeBlock->x), MapToScreen_y(snakeBlock->y), (px_int)2, 1, snakeBlock->color);
		}
	}
}

void DrawPlayerInfo(PX_Application* pApp)
{
	px_surface* pRenderSurface = &pApp->runtime.RenderSurface;
	text[0] = "P1\n\n����: " + to_string(gameMap.player[0].snake.GetLength());
	text[1] = "P2\n\n����: " + to_string(gameMap.player[1].snake.GetLength());
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, 10, 40, PX_ALIGN_LEFTTOP, text[0].c_str(), gameMap.player[0].defaultColor);
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, PX_APPLICATION_SURFACE_WIDTH - 130, 40, PX_ALIGN_LEFTTOP, text[1].c_str(), gameMap.player[1].defaultColor);
}