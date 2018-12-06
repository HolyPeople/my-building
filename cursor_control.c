#include "cursor_control.h"

// 커서를 x,y좌표로 이동
void gotoxy(int x, int y) {
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 커서의 x 좌표를 조사
int wherex() {
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);

	return BufInfo.dwCursorPosition.X;
}

// 커서의 y좌표를 조사
int wherey() {
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);

	return BufInfo.dwCursorPosition.Y;
}

//커서 숨기기
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

//영역 저장하기
BOOL gettext(int left, int top, int right, int bottom, void *destin) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordBufSize = { right - left + 1, bottom - top + 1 };
	COORD coordBufCoord = { 0, 0 };
	SMALL_RECT region = { left, top, right, bottom };

	return ReadConsoleOutput(hConsole, destin, coordBufSize, coordBufCoord, &region);
}

// 저장한 영역 되돌리기
BOOL puttext(int left, int top, int right, int bottom, void *source) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordBufSize = { right - left + 1, bottom - top + 1 };
	COORD coordBufCoord = { 0, 0 };
	SMALL_RECT region = { left, top, right, bottom };

	return WriteConsoleOutput(hConsole, source, coordBufSize, coordBufCoord, &region);
}

// x, y 좌표 지점의 아스키코드를 조사
int getscr(int x, int y) {
	CHAR_INFO dest;

	gettext(x, y, x, y, &dest);

	return dest.Char.AsciiChar;
}

// x, y 좌표 지점의 속성(색상)을 조사
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

// 색상 설정 : textattr(글자색|배경색<<4)
void textattr(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(color));
}

// 글자 색상 설정 setcolor(글자색);
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

// 배경 색상 설정 setbkcolor(배경색);
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
