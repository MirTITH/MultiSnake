#pragma once

#define cursor_r_default 15
#define cursor_color PX_COLOR(200, 102, 204, 255)

// ��ʼ���Զ�����
void cursor_init();

// �����Զ�����
void cursor_draw(px_surface* psurface);

void cursor_CURSORDOWN();
void cursor_CURSORUP();
void cursor_CURSORRDOWN();
void cursor_CURSORRUP();