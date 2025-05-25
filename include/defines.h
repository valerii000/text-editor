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
	mvaddstr(LINES - 1, 0, s.c_str());
	refresh();
	getch();
}

#endif
