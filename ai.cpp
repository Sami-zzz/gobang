#include "ai.h"


enum gameResult { R_BLACK, R_WHITE, R_DRAW};

DECISION decision;//�������

int tuple6type[4][4][4][4][4][4];//���ͱ�ʶ����,0����,1����,2����,3�߽�

void init_tuple6type() {
    memset(tuple6type, 0, sizeof(tuple6type));
    //����5,aiӮ
    tuple6type[2][2][2][2][2][2] = WIN;
    tuple6type[2][2][2][2][2][0] = WIN;
    tuple6type[0][2][2][2][2][2] = WIN;
    tuple6type[2][2][2][2][2][1] = WIN;
    tuple6type[1][2][2][2][2][2] = WIN;
    tuple6type[3][2][2][2][2][2] = WIN;
    tuple6type[2][2][2][2][2][3] = WIN;
    //����5,ai��
    tuple6type[1][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][0] = LOSE;
    tuple6type[0][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][2] = LOSE;
    tuple6type[2][1][1][1][1][1] = LOSE;
    tuple6type[3][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][3] = LOSE;
    //�׻�4
    tuple6type[0][2][2][2][2][0] = FLEX4;
    //�ڻ�4
    tuple6type[0][1][1][1][1][0] = flex4;
    //�׻�3
    tuple6type[0][2][2][2][0][0] = FLEX3;
    tuple6type[0][0][2][2][2][0] = FLEX3;
    tuple6type[0][2][0][2][2][0] = FLEX3;
    tuple6type[0][2][2][0][2][0] = FLEX3;
    //�ڻ�3
    tuple6type[0][1][1][1][0][0] = flex3;
    tuple6type[0][0][1][1][1][0] = flex3;
    tuple6type[0][1][0][1][1][0] = flex3;
    tuple6type[0][1][1][0][1][0] = flex3;
    //�׻�2
    tuple6type[0][2][2][0][0][0] = FLEX2;
    tuple6type[0][2][0][2][0][0] = FLEX2;
    tuple6type[0][2][0][0][2][0] = FLEX2;
    tuple6type[0][0][2][2][0][0] = FLEX2;
    tuple6type[0][0][2][0][2][0] = FLEX2;
    tuple6type[0][0][0][2][2][0] = FLEX2;
    //�ڻ�2
    tuple6type[0][1][1][0][0][0] = flex2;
    tuple6type[0][1][0][1][0][0] = flex2;
    tuple6type[0][1][0][0][1][0] = flex2;
    tuple6type[0][0][1][1][0][0] = flex2;
    tuple6type[0][0][1][0][1][0] = flex2;
    tuple6type[0][0][0][1][1][0] = flex2;
    //�׻�1
    tuple6type[0][2][0][0][0][0] = FLEX1;
    tuple6type[0][0][2][0][0][0] = FLEX1;
    tuple6type[0][0][0][2][0][0] = FLEX1;
    tuple6type[0][0][0][0][2][0] = FLEX1;
    //�ڻ�1
    tuple6type[0][1][0][0][0][0] = flex1;
    tuple6type[0][0][1][0][0][0] = flex1;
    tuple6type[0][0][0][1][0][0] = flex1;
    tuple6type[0][0][0][0][1][0] = flex1;

    int p1, p2, p3, p4, p5, p6, x, y, ix, iy;//x:��5�кڸ���,y:��5�а׸���; ix:��5�кڸ���,iy:��5�а׸���
    for (p1 = 0; p1 < 4; ++p1) {
        for (p2 = 0; p2 < 3; ++p2) {
            for (p3 = 0; p3 < 3; ++p3) {
                for (p4 = 0; p4 < 3; ++p4) {
                    for (p5 = 0; p5 < 3; ++p5) {
                        for (p6 = 0; p6 < 4; ++p6) {
                            x = y = ix = iy = 0;

                            if (p1 == 1)x++;
                            else if (p1 == 2)y++;

                            if (p2 == 1) { x++; ix++; }
                            else if (p2 == 2) { y++; iy++; }

                            if (p3 == 1) { x++; ix++; }
                            else if (p3 == 2) { y++; iy++; }

                            if (p4 == 1) { x++; ix++; }
                            else if (p4 == 2) { y++; iy++; }

                            if (p5 == 1) { x++; ix++; }
                            else if (p5 == 2) { y++; iy++; }

                            if (p6 == 1)ix++;
                            else if (p6 == 2)iy++;

                            if (p1 == 3 || p6 == 3) {//�б߽�
                                if (p1 == 3 && p6 != 3) {//��߽�
                                    //�׳�4
                                    if (ix == 0 && iy == 4) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //�ڳ�4
                                    if (ix == 4 && iy == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //����3
                                    if (ix == 0 && iy == 3) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //����3
                                    if (ix == 3 && iy == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //����2
                                    if (ix == 0 && iy == 2) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //����2
                                    if (ix == 2 && iy == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                                else if (p6 == 3 && p1 != 3) {//�ұ߽�
                                   //�׳�4
                                    if (x == 0 && y == 4) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //�ڳ�4
                                    if (x == 4 && y == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //����3
                                    if (x == 3 && y == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //����3
                                    if (x == 0 && y == 3) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //����2
                                    if (x == 2 && y == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //����2
                                    if (x == 0 && y == 2) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                            }
                            else {//�ޱ߽�
                               //�׳�4
                                if ((x == 0 && y == 4) || (ix == 0 && iy == 4)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                }
                                //�ڳ�4
                                if ((x == 4 && y == 0) || (ix == 4 && iy == 0)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                }
                                //����3
                                if ((x == 0 && y == 3) || (ix == 0 && iy == 3)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                }
                                //����3
                                if ((x == 3 && y == 0) || (ix == 3 && iy == 0)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                }
                                //����2
                                if ((x == 0 && y == 2) || (ix == 0 && iy == 2)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                }
                                //����2
                                if ((x == 2 && y == 0) || (ix == 2 && iy == 0)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = block2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

EVALUATION evaluate(int(*board)[15]) {
    
    int weight[17] = { 0,1000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3 };//������Ȩ��
    int type;
    int stat[4][17];//ͳ��4��������ÿ�����͵ĸ���
    memset(stat, 0, sizeof(stat));

    int STAT[17];//�����������͵ķ���ĸ���
    memset(STAT, 0, sizeof(STAT));

    int A[17][17];//�����߽�����������,3��ʾ�߽�
    for (int i = 0; i < 17; ++i)
        A[i][0] = 3;
    for (int i = 0; i < 17; ++i)
        A[i][16] = 3;
    for (int j = 0; j < 17; ++j)
        A[0][j] = 3;
    for (int j = 0; j < 17; ++j)
        A[16][j] = 3;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            A[i + 1][j + 1] = board[i][j];
        }
    }

    //�жϺ�������
    for (int i = 1; i <= 15; ++i) {
        for (int j = 0; j < 12; ++j) {
            type = tuple6type[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
            stat[0][type]++;
        }
    }

    //�ж���������
    for (int j = 1; j <= 15; ++j) {
        for (int i = 0; i < 12; ++i) {
            type = tuple6type[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
            stat[1][type]++;
        }
    }
    //�ж���������������
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            type = tuple6type[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
            stat[2][type]++;
        }
    }
    //�ж���������������
    for (int i = 0; i < 12; ++i) {
        for (int j = 5; j < 17; ++j) {
            type = tuple6type[A[i][j]][A[i + 1][j - 1]][A[i + 2][j - 2]][A[i + 3][j - 3]][A[i + 4][j - 4]][A[i + 5][j - 5]];
            stat[3][type]++;
        }
    }
    
    EVALUATION eval;//�������
    memset(eval.STAT, 0, sizeof(eval.STAT));

    int score = 0;
    for (int i = 1; i < 17; ++i) {
        score += (stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i]) * weight[i];//�Ʒ�
        int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];//ͳ�����з����ϲ������͵ĸ���
        if (i == WIN)
            eval.STAT[WIN] = count;
        else if (i == LOSE)
            eval.STAT[LOSE] = count;

    }
    eval.result = R_DRAW;

    //��Ӯ
    if (eval.STAT[WIN] > 0)eval.result = R_WHITE;
    //��Ӯ
    else if (eval.STAT[LOSE] > 0)eval.result = R_BLACK;

    eval.score = score;
    return eval;
}

int analyse(int(*board)[15], int depth, int alpha, int beta) {
    gameResult RESULT = evaluate(board).result;
    if (depth == 0 || RESULT != R_DRAW) {//���ģ�����ӿ��Էֳ���Ӯ��ֱ�ӷ��ؽ��
        if (depth == 0) { //���������һ��
            SOMEPOINTS P;
            P = seekPoints(board);//ֱ��Ѱ����ѵĿ�������λ��
            return P.score[0];//�������λ�ö�Ӧ����߷�
        }
        else {
            return evaluate(board).score; //���ص�ǰ���ֵ
        }
    }
    else if (depth % 2 == 0) {//max��,AI��(��)����

        int sameBoard[15][15];
        copyBoard(board, sameBoard);
        SOMEPOINTS P = seekPoints(sameBoard);

        for (int i = 0; i < 10; ++i) {
            sameBoard[P.pos[i].x][P.pos[i].y] = C_WHITE;//ģ��AI������
            int a = analyse(sameBoard, depth - 1, alpha, beta);//�ݹ�����
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;//��ԭ����
            if (a > alpha) {
                alpha = a;
                if (depth == 4) {//�������

                    decision.best.x = P.pos[i].x; //AI����λ��
                    decision.best.y = P.pos[i].y;
                    decision.eval = a;
                }
            }
            if (beta <= alpha)break;//��֦
        }
        return alpha;
    }
    else {//min��,��ҷ�(��)����

        int rBoard[15][15];
        reverseBoard(board, rBoard);
        SOMEPOINTS P = seekPoints(rBoard); //Ѱ�Һ��ӵ����λ�ã���Ҫ��ת������ɫ

        int sameBoard[15][15];
        copyBoard(board, sameBoard);

        for (int i = 0; i < 10; ++i) {
 
            sameBoard[P.pos[i].x][P.pos[i].y] = C_BLACK;
            int a = analyse(sameBoard, depth - 1, alpha, beta);
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            if (a < beta)beta = a;
            if (beta <= alpha)break;//��֦
        }
        return beta;
    }
}

SOMEPOINTS seekPoints(int(*board)[15]) {
    bool B[15][15];//�ֲ�����,ÿ���ǿյ㸽��8����������3�����
    int worth[15][15];
    SOMEPOINTS best_points;

    memset(B, 0, sizeof(B));
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board[i][j] != C_NONE) {
                for (int k = -3; k <= 3; ++k) {
                    if (i + k >= 0 && i + k < 15) {
                        B[i + k][j] = true;
                        if (j + k >= 0 && j + k < 15)B[i + k][j + k] = true;
                        if (j - k >= 0 && j - k < 15)B[i + k][j - k] = true;
                    }
                    if (j + k >= 0 && j + k < 15)B[i][j + k] = true;
                }
            }
        }
    }

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            worth[i][j] = -INT_MAX;
            if (board[i][j] == C_NONE && B[i][j] == true) { //�Ծֲ�������ÿ��λ������
                board[i][j] = C_WHITE;
                worth[i][j] = evaluate(board).score;
                board[i][j] = C_NONE;
            }
        }
    }

    int w;
    for (int k = 0; k < 10; ++k) { //�Է��������ǰʮ��λ��
        w = -INT_MAX;
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                if (worth[i][j] > w) {
                    w = worth[i][j];
                    best_points.pos[k].x = i;
                    best_points.pos[k].y = j;

                }
            }
        }
        best_points.score[k] = w;
        worth[best_points.pos[k].x][best_points.pos[k].y] = -INT_MAX;//�������һ��,������һ���λ�úͷ���
    }
    return best_points;
}

void copyBoard(int(*A)[15], int(*B)[15]) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (A[i][j] == C_NONE)B[i][j] = C_NONE;
            else if (A[i][j] == C_BLACK)B[i][j] = C_BLACK;
            else B[i][j] = C_WHITE;
        }
    }
}

void reverseBoard(int(*A)[15], int(*B)[15]) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (A[i][j] == C_NONE)B[i][j] = C_NONE;
            else if (A[i][j] == C_BLACK)B[i][j] = C_WHITE;
            else B[i][j] = C_BLACK;
        }
    }
}


