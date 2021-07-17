#pragma once
#include <string.h>
#include <limits.h>

//棋子代号
#define C_NONE 0
#define C_BLACK 1
#define C_WHITE 2

//棋型代号 下标 权重
#define OTHER 0//0,其他棋型不考虑
#define WIN 1//100000,白赢
#define LOSE 2//-10000000,黑赢
#define FLEX4 3//50000,白活
#define flex4 4//-80000,黑活
#define BLOCK4 5//400
#define block4 6//-80000
#define FLEX3 7//400
#define flex3 8//-8000
#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2

enum gameResult; //胜负结果

typedef struct evaluation {
    int score;
    gameResult result; 
    int STAT[3]; //储存胜负棋形
}EVALUATION;

typedef struct position {//落子位置
    int x;
    int y;
}POSITION;

typedef struct points {//10个最佳落子位置
    POSITION pos[10];
    int score[10];//此处落子的局势分数
}SOMEPOINTS;

typedef struct dec {
    POSITION best;//最佳位置
    int eval;//局势分数
}DECISION;

extern DECISION decision;//最佳落子点


void init_tuple6type(); //初始化棋形判别六元组

EVALUATION evaluate(int(*board)[15]); //对当前局势评估

int analyse(int(*board)[15], int depth, int alpha, int beta); //极大极小值搜索中运用Alpha-Beta剪枝

SOMEPOINTS seekPoints(int(*board)[15]); //局部搜索和静态评价启发

void copyBoard(int(*A)[15], int(*B)[15]);  //复制棋盘

void reverseBoard(int(*A)[15], int(*B)[15]);  //反转棋盘颜色


