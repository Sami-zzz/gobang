#pragma once
#include <graphics.h>

typedef struct node { //����ÿ���ڵ�����ݴ���
    int x; //���϶�������
    int y;
    int model; //���ӱ߿���ʽ
    int value; //�Ƿ����ӣ�0������, ����1, ����2��
    bool isnew; //�Ƿ���ʾѡ��� 
    COLORREF color; //������ɫ
}NODE;

void initNode(); //��ʼ��ÿ���ڵ�

void drawNode(NODE* node); //�����̵Ľڵ�

void drawBoard(); //������������

void mapToBoard(NODE(*A)[15], int(*B)[15]); //���������ݼ�Ϊ������

int winner(); //ʤ���ж�

void gameOver1(int win); //�˻���ս����

void gameOver2(int win); //���PK����

int game1(); //�˻���ս

int game2(); //���PK

int startGame(); //��Ϸ��ʼ��