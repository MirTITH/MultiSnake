#include "myheadfile.h"
#include "PainterEngine_Application.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include "cursor.h"
#include "keyboard.h"
#include "snake_main.h"
#include <chrono>

using namespace std;

PX_Application App;
POINTER_POS cursor = { 0,0 };
POINTER_POS ball_pos = { PX_APPLICATION_SURFACE_HEIGHT / 2, PX_APPLICATION_SURFACE_WIDTH / 2 };
char text[20];

CRITICAL_SECTION g_cs;

Player player1(1);
Player player2(2);

//POINTER_POS pt_last = { 0,0 };

px_bool PX_ApplicationInitialize(PX_Application *pApp,px_int screen_width,px_int screen_height)
{
	PX_ApplicationInitializeDefault(&pApp->runtime, screen_width, screen_height);
	if (!PX_FontModuleInitialize(&pApp->runtime.mp_resources, &pApp->fm)) return PX_FALSE;//��ģ
	if (!PX_LoadFontModuleFromFile(&pApp->fm, "../../Resource/gbk_32.pxf")) return PX_FALSE;//����������ģ
	cursor_init();

	InitializeCriticalSection(&g_cs);//��ʼ���ٽ���
	thread sys_tick(Sys_tick_f);
	sys_tick.detach();
	return PX_TRUE;
}

px_void PX_ApplicationUpdate(PX_Application *pApp,px_dword elpased)
{
	
}

px_void PX_ApplicationRender(PX_Application *pApp,px_dword elpased)
{
	px_surface *pRenderSurface=&pApp->runtime.RenderSurface;
	//GetCursorPos(&pt); //Windows ��������ȡ����������
	//Sleep(1000);

	player1.get_input();
	player2.get_input();

	PX_RuntimeRenderClear(&pApp->runtime, PX_COLOR(255, 255, 255, 255));
	PX_GeoDrawRect(pRenderSurface, 0, 0, 1279, 799, PX_COLOR(255, 55, 44, 77));
	for (int i = 0; ; i++)
	{
		if (player1.snake(i) == NULL) break;

		PX_GeoDrawCircle(pRenderSurface, 2*player1.snake(i)->x, 2 * player1.snake(i)->y, (px_int)2, 1, PX_COLOR(255, 145, 224, 200));
	}
	for (int i = 0; ; i++)
	{
		if (player2.snake(i) == NULL) break;

		PX_GeoDrawCircle(pRenderSurface, 2 * player2.snake(i)->x, 2 * player2.snake(i)->y, (px_int)2, 1, PX_COLOR(255, 224, 115, 200));
	}
	PX_GeoDrawCircle(pRenderSurface, (px_int)ball_pos.x, (px_int)ball_pos.y, (px_int)5, 4, PX_COLOR(255, 145, 224, 200));

	
	//sprintf_s(text,"P1:%d P2:%d", player1.input.GetDir(), player2.input.GetDir());
	PX_FontModuleDrawText(pRenderSurface, &pApp->fm, 10, 100, PX_ALIGN_LEFTTOP, text, PX_COLOR(255, 255, 255, 255));

	cursor_draw(pRenderSurface); //�뱣�����������
}

px_void PX_ApplicationPostEvent(PX_Application *pApp,PX_Object_Event e)
{
	PX_ApplicationEventDefault(&pApp->runtime, e);
	
	switch (e.Event)
	{
	case PX_OBJECT_EVENT_CURSORMOVE:
		cursor.x = PX_Object_Event_GetCursorX(e);
		cursor.y = PX_Object_Event_GetCursorY(e);
		break;
	case PX_OBJECT_EVENT_CURSORDRAG:
		cursor.x = PX_Object_Event_GetCursorX(e);
		cursor.y = PX_Object_Event_GetCursorY(e);
		break;
	case PX_OBJECT_EVENT_CURSORDOWN:
		cursor_CURSORDOWN();
		break;
	case PX_OBJECT_EVENT_CURSORUP:
		cursor_CURSORUP();
		break;
	case PX_OBJECT_EVENT_CURSORRDOWN:
		cursor_CURSORRDOWN();
		break;
	case PX_OBJECT_EVENT_CURSORRUP:
		cursor_CURSORRUP();
		break;
	default:
		break;
	}

	//if (e.Event == PX_OBJECT_EVENT_KEYDOWN)
	//{
	//	keyboard.put(PX_Object_Event_GetKeyDown(e));
	//	/*switch ()
	//	{
	//	case 87:
	//		ball_pos.y -= 5;
	//		break;
	//	case 83:
	//		ball_pos.y += 5;
	//		break;
	//	case 65:
	//		ball_pos.x -= 5;
	//		break;
	//	case 68:
	//		ball_pos.x += 5;
	//		break;
	//	default:
	//		break;
	//	}*/
	//	
	//}

	//pt_last.x = pt.x;
	//pt_last.y = pt.y;

	
}

void Sys_tick_f()
{
	chrono::system_clock::time_point until;
	while (true)
	{
		until = chrono::system_clock::now();
		until += chrono::milliseconds(1);
		EnterCriticalSection(&g_cs);
		player1.move();
		player2.move();
		LeaveCriticalSection(&g_cs);
		while (until > chrono::system_clock::now());
		//this_thread::sleep_until(until);
	}
}