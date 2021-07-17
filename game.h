#pragma once
#include <graphics.h>

typedef struct node { //棋盘每个节点的数据储存
    int x; //左上顶点坐标
    int y;
    int model; //格子边框样式
    int value; //是否落子（0代表无, 黑棋1, 白棋2）
    bool isnew; //是否显示选择框 
    COLORREF color; //格子颜色
}NODE;

void initNode(); //初始化每个节点

void drawNode(NODE* node); //画棋盘的节点

void drawBoard(); //绘制整个棋盘

void mapToBoard(NODE(*A)[15], int(*B)[15]); //将棋盘数据简化为简单棋盘

int winner(); //胜负判断

void gameOver1(int win); //人机对战结束

void gameOver2(int win); //玩家PK结束

int game1(); //人机对战

int game2(); //玩家PK

int startGame(); //游戏初始化