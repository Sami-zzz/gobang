#pragma once
#include <string.h>
#include <limits.h>

//���Ӵ���
#define C_NONE 0
#define C_BLACK 1
#define C_WHITE 2

//���ʹ��� �±� Ȩ��
#define OTHER 0//0,�������Ͳ�����
#define WIN 1//100000,��Ӯ
#define LOSE 2//-10000000,��Ӯ
#define FLEX4 3//50000,�׻�
#define flex4 4//-80000,�ڻ�
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

enum gameResult; //ʤ�����

typedef struct evaluation {
    int score;
    gameResult result; 
    int STAT[3]; //����ʤ������
}EVALUATION;

typedef struct position {//����λ��
    int x;
    int y;
}POSITION;

typedef struct points {//10���������λ��
    POSITION pos[10];
    int score[10];//�˴����ӵľ��Ʒ���
}SOMEPOINTS;

typedef struct dec {
    POSITION best;//���λ��
    int eval;//���Ʒ���
}DECISION;

extern DECISION decision;//������ӵ�


void init_tuple6type(); //��ʼ�������б���Ԫ��

EVALUATION evaluate(int(*board)[15]); //�Ե�ǰ��������

int analyse(int(*board)[15], int depth, int alpha, int beta); //����Сֵ����������Alpha-Beta��֦

SOMEPOINTS seekPoints(int(*board)[15]); //�ֲ������;�̬��������

void copyBoard(int(*A)[15], int(*B)[15]);  //��������

void reverseBoard(int(*A)[15], int(*B)[15]);  //��ת������ɫ


