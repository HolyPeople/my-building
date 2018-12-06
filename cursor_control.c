#include "cursor_control.h"

// Ŀ���� x,y��ǥ�� �̵�
void gotoxy(int x, int y) {
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Ŀ���� x ��ǥ�� ����
int wherex() {
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);

	return BufInfo.dwCursorPosition.X;
}

// Ŀ���� y��ǥ�� ����
int wherey() {
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);

	return BufInfo.dwCursorPosition.Y;
}

//Ŀ�� �����
void setcursortype(int cur_t) {
	CONSOLE_CURSOR_INFO ccInfo;

	if (cur_t == 0)		// NOCURSOR
	{
		ccInfo.dwSize = 20;
		ccInfo.bVisible = FALSE;
	}
	else if (cur_t == 1)	// SOLIDCURSOR
	{
		ccInfo.dwSize = 100;
		ccInfo.bVisible = TRUE;
	}
	else				// NORMALCURSOR
	{
		ccInfo.dwSize = 20;
		ccInfo.bVisible = TRUE;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ccInfo);
}

//���� �����ϱ�
BOOL gettext(int left, int top, int right, int bottom, void *destin) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordBufSize = { right - left + 1, bottom - top + 1 };
	COORD coordBufCoord = { 0, 0 };
	SMALL_RECT region = { left, top, right, bottom };

	return ReadConsoleOutput(hConsole, destin, coordBufSize, coordBufCoord, &region);
}

// ������ ���� �ǵ�����
BOOL puttext(int left, int top, int right, int bottom, void *source) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordBufSize = { right - left + 1, bottom - top + 1 };
	COORD coordBufCoord = { 0, 0 };
	SMALL_RECT region = { left, top, right, bottom };

	return WriteConsoleOutput(hConsole, source, coordBufSize, coordBufCoord, &region);
}

// x, y ��ǥ ������ �ƽ�Ű�ڵ带 ����
int getscr(int x, int y) {
	CHAR_INFO dest;

	gettext(x, y, x, y, &dest);

	return dest.Char.AsciiChar;
}

// x, y ��ǥ ������ �Ӽ�(����)�� ����
int getattr(int x, int y) {
	CHAR_INFO dest;

	gettext(x, y, x, y, &dest);

	return dest.Attributes;
}

int getcolor(int x, int y) {
	short   attr;
	DWORD   dummy;
	COORD   pos = { x, y };

	ReadConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), &attr, 1, pos, &dummy);

	return (attr & 0xf);
}

int getbkcolor(int x, int y) {
	short   attr;
	DWORD   dummy;
	COORD   pos = { x, y };

	ReadConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), &attr, 1, pos, &dummy);

	return (attr & 0xf0) >> 4;
}

// ���� ���� : textattr(���ڻ�|����<<4)
void textattr(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(color));
}

// ���� ���� ���� setcolor(���ڻ�);
void setcolor(int textcolor) {
	WORD    attr;
	DWORD   dummy;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &BufInfo);
	ReadConsoleOutputAttribute(hConsole, &attr, 1, BufInfo.dwCursorPosition, &dummy);

	attr = textcolor | (attr & 0xf0);
	SetConsoleTextAttribute(hConsole, (WORD)(attr));
}

// ��� ���� ���� setbkcolor(����);
void setbkcolor(int color) {

	WORD    attr;
	DWORD   dummy;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &BufInfo);
	ReadConsoleOutputAttribute(hConsole, &attr, 1, BufInfo.dwCursorPosition, &dummy);

	attr = (attr & 0xf) | (color << 4);
	SetConsoleTextAttribute(hConsole, (WORD)(attr));
}

int getkey() {

	int ch;
	if ((ch = getch()) == 0xE0)
		ch = getch();
	return ch;
}
