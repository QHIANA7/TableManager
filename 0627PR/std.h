#pragma once
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "app.h"
#include "title.h"
#include "setting.h"
#include "setting_table.h"
#include "setting_menu.h"

void gotoxy(int x, int y);
void console_size_set(int cols, int lines);