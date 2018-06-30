#pragma once
#include<iostream>
#include<Windows.h>
#include"resource.h"
//#include<gdiplus.h>
using namespace std;
//#pragma comment (lib,"gdiplus.lib")//加载gdi+库
//using namespace Gdiplus;//使用gdi+命名空间
#define LIMIT 300
#define HIGHT 150
#define JUMPLEFTFLAG 0
#define JUMPRIGHTFLAG 1
#define TOUCHFLYFLAGL 2
#define JUMPUP 0
#define JUMPDOWN 1
#define JUMPFLY 2
#define JUMPROCKET 3
#define JUMPLEFT 2
#define JUMPRIGHT 3
#define JUMPMONSTER 4
#define NOJUMP 0
#define PLAYER_MOVE_TIMER 0
#define TABLE_FIS_TIMER 1
#define BACK_MOVE_TIMER 2
#define GAME_OVER_TIMER 3
#define TABLE_MOVE_RIGHT 0
#define TABLE_MOVE_LEFT 1
#define NO_ITEM 0
#define FLY_ITEM 1
#define MONSTER_ITEM 2
#define NO_MONSTER_ITEM 3
#define MONSTER2_ITEM 4
#define NO_MONSTER2_ITEM 5
#define BLACK_HOLE_ITEM 6
#define NO_BLACK_HOLE_ITEM 7
#define ROCKET_ITEM    8
#define ONCE_TABLE 1

