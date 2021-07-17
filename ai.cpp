#include "ai.h"


enum gameResult { R_BLACK, R_WHITE, R_DRAW};

DECISION decision;//最佳落子

int tuple6type[4][4][4][4][4][4];//棋型辨识数组,0无子,1黑子,2白子,3边界

void init_tuple6type() {
    memset(tuple6type, 0, sizeof(tuple6type));
    //白连5,ai赢
    tuple6type[2][2][2][2][2][2] = WIN;
    tuple6type[2][2][2][2][2][0] = WIN;
    tuple6type[0][2][2][2][2][2] = WIN;
    tuple6type[2][2][2][2][2][1] = WIN;
    tuple6type[1][2][2][2][2][2] = WIN;
    tuple6type[3][2][2][2][2][2] = WIN;
    tuple6type[2][2][2][2][2][3] = WIN;
    //黑连5,ai输
    tuple6type[1][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][0] = LOSE;
    tuple6type[0][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][2] = LOSE;
    tuple6type[2][1][1][1][1][1] = LOSE;
    tuple6type[3][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][3] = LOSE;
    //白活4
    tuple6type[0][2][2][2][2][0] = FLEX4;
    //黑活4
    tuple6type[0][1][1][1][1][0] = flex4;
    //白活3
    tuple6type[0][2][2][2][0][0] = FLEX3;
    tuple6type[0][0][2][2][2][0] = FLEX3;
    tuple6type[0][2][0][2][2][0] = FLEX3;
    tuple6type[0][2][2][0][2][0] = FLEX3;
    //黑活3
    tuple6type[0][1][1][1][0][0] = flex3;
    tuple6type[0][0][1][1][1][0] = flex3;
    tuple6type[0][1][0][1][1][0] = flex3;
    tuple6type[0][1][1][0][1][0] = flex3;
    //白活2
    tuple6type[0][2][2][0][0][0] = FLEX2;
    tuple6type[0][2][0][2][0][0] = FLEX2;
    tuple6type[0][2][0][0][2][0] = FLEX2;
    tuple6type[0][0][2][2][0][0] = FLEX2;
    tuple6type[0][0][2][0][2][0] = FLEX2;
    tuple6type[0][0][0][2][2][0] = FLEX2;
    //黑活2
    tuple6type[0][1][1][0][0][0] = flex2;
    tuple6type[0][1][0][1][0][0] = flex2;
    tuple6type[0][1][0][0][1][0] = flex2;
    tuple6type[0][0][1][1][0][0] = flex2;
    tuple6type[0][0][1][0][1][0] = flex2;
    tuple6type[0][0][0][1][1][0] = flex2;
    //白活1
    tuple6type[0][2][0][0][0][0] = FLEX1;
    tuple6type[0][0][2][0][0][0] = FLEX1;
    tuple6type[0][0][0][2][0][0] = FLEX1;
    tuple6type[0][0][0][0][2][0] = FLEX1;
    //黑活1
    tuple6type[0][1][0][0][0][0] = flex1;
    tuple6type[0][0][1][0][0][0] = flex1;
    tuple6type[0][0][0][1][0][0] = flex1;
    tuple6type[0][0][0][0][1][0] = flex1;

    int p1, p2, p3, p4, p5, p6, x, y, ix, iy;//x:左5中黑个数,y:左5中白个数; ix:右5中黑个数,iy:右5中白个数
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

                            if (p1 == 3 || p6 == 3) {//有边界
                                if (p1 == 3 && p6 != 3) {//左边界
                                    //白冲4
                                    if (ix == 0 && iy == 4) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //黑冲4
                                    if (ix == 4 && iy == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //白眠3
                                    if (ix == 0 && iy == 3) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //黑眠3
                                    if (ix == 3 && iy == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //白眠2
                                    if (ix == 0 && iy == 2) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //黑眠2
                                    if (ix == 2 && iy == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                                else if (p6 == 3 && p1 != 3) {//右边界
                                   //白冲4
                                    if (x == 0 && y == 4) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //黑冲4
                                    if (x == 4 && y == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //黑眠3
                                    if (x == 3 && y == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //白眠3
                                    if (x == 0 && y == 3) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //黑眠2
                                    if (x == 2 && y == 0) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //白眠2
                                    if (x == 0 && y == 2) {
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                            }
                            else {//无边界
                               //白冲4
                                if ((x == 0 && y == 4) || (ix == 0 && iy == 4)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                }
                                //黑冲4
                                if ((x == 4 && y == 0) || (ix == 4 && iy == 0)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                }
                                //白眠3
                                if ((x == 0 && y == 3) || (ix == 0 && iy == 3)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                }
                                //黑眠3
                                if ((x == 3 && y == 0) || (ix == 3 && iy == 0)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                }
                                //白眠2
                                if ((x == 0 && y == 2) || (ix == 0 && iy == 2)) {
                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                }
                                //黑眠2
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
    
    int weight[17] = { 0,1000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3 };//各棋型权重
    int type;
    int stat[4][17];//统计4个方向上每种棋型的个数
    memset(stat, 0, sizeof(stat));

    int STAT[17];//存在这种棋型的方向的个数
    memset(STAT, 0, sizeof(STAT));

    int A[17][17];//包括边界的虚拟大棋盘,3表示边界
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

    //判断横向棋型
    for (int i = 1; i <= 15; ++i) {
        for (int j = 0; j < 12; ++j) {
            type = tuple6type[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
            stat[0][type]++;
        }
    }

    //判断竖向棋型
    for (int j = 1; j <= 15; ++j) {
        for (int i = 0; i < 12; ++i) {
            type = tuple6type[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
            stat[1][type]++;
        }
    }
    //判断左上至右下棋型
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            type = tuple6type[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
            stat[2][type]++;
        }
    }
    //判断右上至左下棋型
    for (int i = 0; i < 12; ++i) {
        for (int j = 5; j < 17; ++j) {
            type = tuple6type[A[i][j]][A[i + 1][j - 1]][A[i + 2][j - 2]][A[i + 3][j - 3]][A[i + 4][j - 4]][A[i + 5][j - 5]];
            stat[3][type]++;
        }
    }
    
    EVALUATION eval;//评估结果
    memset(eval.STAT, 0, sizeof(eval.STAT));

    int score = 0;
    for (int i = 1; i < 17; ++i) {
        score += (stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i]) * weight[i];//计分
        int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];//统计所有方向上部分棋型的个数
        if (i == WIN)
            eval.STAT[WIN] = count;
        else if (i == LOSE)
            eval.STAT[LOSE] = count;

    }
    eval.result = R_DRAW;

    //白赢
    if (eval.STAT[WIN] > 0)eval.result = R_WHITE;
    //黑赢
    else if (eval.STAT[LOSE] > 0)eval.result = R_BLACK;

    eval.score = score;
    return eval;
}

int analyse(int(*board)[15], int depth, int alpha, int beta) {
    gameResult RESULT = evaluate(board).result;
    if (depth == 0 || RESULT != R_DRAW) {//如果模拟落子可以分出输赢，直接返回结果
        if (depth == 0) { //搜索到最后一层
            SOMEPOINTS P;
            P = seekPoints(board);//直接寻找最佳的可能落子位置
            return P.score[0];//返回最佳位置对应的最高分
        }
        else {
            return evaluate(board).score; //返回当前层分值
        }
    }
    else if (depth % 2 == 0) {//max层,AI方(白)决策

        int sameBoard[15][15];
        copyBoard(board, sameBoard);
        SOMEPOINTS P = seekPoints(sameBoard);

        for (int i = 0; i < 10; ++i) {
            sameBoard[P.pos[i].x][P.pos[i].y] = C_WHITE;//模拟AI方落子
            int a = analyse(sameBoard, depth - 1, alpha, beta);//递归搜索
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;//还原落子
            if (a > alpha) {
                alpha = a;
                if (depth == 4) {//搜索深度

                    decision.best.x = P.pos[i].x; //AI决策位置
                    decision.best.y = P.pos[i].y;
                    decision.eval = a;
                }
            }
            if (beta <= alpha)break;//剪枝
        }
        return alpha;
    }
    else {//min层,玩家方(黑)决策

        int rBoard[15][15];
        reverseBoard(board, rBoard);
        SOMEPOINTS P = seekPoints(rBoard); //寻找黑子的最佳位置，需要反转棋盘颜色

        int sameBoard[15][15];
        copyBoard(board, sameBoard);

        for (int i = 0; i < 10; ++i) {
 
            sameBoard[P.pos[i].x][P.pos[i].y] = C_BLACK;
            int a = analyse(sameBoard, depth - 1, alpha, beta);
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            if (a < beta)beta = a;
            if (beta <= alpha)break;//剪枝
        }
        return beta;
    }
}

SOMEPOINTS seekPoints(int(*board)[15]) {
    bool B[15][15];//局部搜索,每个非空点附近8个方向延伸3个深度
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
            if (board[i][j] == C_NONE && B[i][j] == true) { //对局部搜索的每个位置评估
                board[i][j] = C_WHITE;
                worth[i][j] = evaluate(board).score;
                board[i][j] = C_NONE;
            }
        }
    }

    int w;
    for (int k = 0; k < 10; ++k) { //对分数排序出前十个位置
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
        worth[best_points.pos[k].x][best_points.pos[k].y] = -INT_MAX;//清除掉上一点,计算下一点的位置和分数
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


