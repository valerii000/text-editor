#ifndef DEFINES_H
#define DEFINES_H

#define let auto
#define u8 unsigned char
#define i8 signed char
#define u16 unsigned short
#define i16 signed short
#define u32 unsigned int
#define i32 signed int
#define u64 unsigned long long
#define i64 signed long long
#define f32 float
#define f64 double
#define usize size_t
#define ssize ssize_t
#define loop while (true)

#define COLOR_ORANGE 8

#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <unordered_map>
#include <sstream>
#include <functional>
#include <dirent.h>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <map>

inline void message(const std::string& s)
{
	WINDOW* mes = newwin(1, COLS, LINES - 1, 0);
	waddstr(mes, s.c_str());
	wrefresh(mes);
	getch();

	delwin(mes);
}

/*
inline void message_big(const std::string& s)
{
	u16 lines = s.length() / COLS + 1;
	WINDOW* mes = newwin(lines, COLS, LINES - lines - 1, 0);
	u16 pos = 0;
	for (u16 i = 0; i < lines; i++)
	{
		std::string substr = s.substr(pos, COLS);
		waddstr(mes, substr.c_str());
		pos += COLS;
		if (i < lines - 1) wmove(mes, i + 1, 0);
	}
	wrefresh(mes);
	getch();
	delwin(mes);
}
*/

/*
inline void message_big(const std::string& s)
{
	u16 lines = 1;
	u16 pos = 0;
	for (u16 i = 0; i < s.length(); i++)
	{
		if (s[i] == '\n')
		{
			lines++;
			pos = 0;
		}
		else
		{
			pos++;
			if (pos > COLS)
			{
				lines++;
				pos = 1;
			}
		}
	}
	WINDOW* mes = newwin(lines, COLS, LINES - lines - 1, 0);
	u16 row = 0;
	u16 col = 0;
	for (u16 i = 0; i < s.length(); i++)
	{
		if (s[i] == '\n')
		{
			row++;
			col = 0;
			wmove(mes, row, col);
		}
		else
		{
			waddch(mes, s[i]);
			col++;
			if (col >= COLS)
			{
				row++;
				col = 0;
				wmove(mes, row, col);
			}
		}
	}
	wrefresh(mes);
	getch();
	delwin(mes);
}
*/

#endif
