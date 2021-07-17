#include "game.h"
#include "ai.h"

#pragma comment (lib, "Winmm.lib")

NODE map[15][15];
COLORREF COLOR = RGB(255, 183, 111);

void initNode()
{
    for (int i = 75, k = 0; i <= 495; i = i + 30) {
        for (int j = 75, g = 0; j <= 495; j = j + 30) {
            map[k][g].x = j;
            map[k][g].y = i;
            map[k][g].value = 0;
            map[k][g].isnew = false;
            map[k][g].color = COLOR;
            if (k == 0 && g == 0) //���ݸ���λ���жϸ��ӱ߿�
            {
                map[k][g].model = 8;
            }
            else if (k == 0 && g == 14)
            {
                map[k][g].model = 7;
            }
            else if (k == 14 && g == 14)
            {
                map[k][g].model = 6;
            }
            else if (k == 14 && g == 0)
            {
                map[k][g].model = 5;
            }
            else if (k == 0)
            {
                map[k][g].model = 3;
            }
            else if (k == 14)
            {
                map[k][g].model = 4;
            }
            else if (g == 0)
            {
                map[k][g].model = 1;
            }
            else if (g == 14)
            {
                map[k][g].model = 2;
            }
            else  if ((k == 3 && g == 3) || (k == 3 && g == 11) || (k == 11 && g == 3) || (k == 11 && g == 11) || (k == 7 && g == 7))
            {
                map[k][g].model = 9;
            }
            else
            {
                map[k][g].model = 0;
            }
            g++;
        }
        k++;
    }

}

void drawNode(NODE* node)
{
    int x = node->x; //��õ�ǰ�ڵ�����
    int y = node->y;
    int model = node->model;
    int value = node->value;
    int isnew = node->isnew;
    COLORREF color = node->color;

    setfillcolor(color);
    solidrectangle(x, y, x + 30, y + 30);

    //���Ʊ߿�
    setlinecolor(BLACK);
    switch (model)
    {
    case 0:
        setlinestyle(PS_SOLID, 2);
        line(x + 15, y, x + 15, y + 30);
        line(x - 1, y + 15, x + 30, y + 15);
        break;
        //   *
        // * * *
        //   *
    case 3:
        setlinestyle(PS_SOLID, 2);
        line(x + 15, y + 15, x + 15, y + 30);
        setlinestyle(PS_SOLID, 3);
        line(x - 1, y + 15, x + 30, y + 15);
        break;
        // * * *
        //   *
        //   *
    case 4:
        setlinestyle(PS_SOLID, 2);
        line(x + 15, y, x + 15, y + 15);
        setlinestyle(PS_SOLID, 3);
        line(x - 1, y + 15, x + 30, y + 15);
        break;
        //   *
        //   *
        // * * *
    case 1:
        setlinestyle(PS_SOLID, 2);
        line(x + 14, y + 15, x + 30, y + 15);
        setlinestyle(PS_SOLID, 3);
        line(x + 15, y, x + 15, y + 30);
        break;
        // *
        // * * *
        // *
    case 2:
        setlinestyle(PS_SOLID, 2);
        line(x - 1, y + 15, x + 15, y + 15);
        setlinestyle(PS_SOLID, 3);
        line(x + 15, y, x + 15, y + 30);
        break;
        //     *
        // * * *
        //     *
    case 7:
        setlinestyle(PS_SOLID, 3);
        line(x - 1, y + 15, x + 15, y + 15);
        line(x + 15, y + 15, x + 15, y + 30);
        break;
        // * * *
        //     *
        //     *
    case 6:
        setlinestyle(PS_SOLID, 3);
        line(x + 15, y, x + 15, y + 15);
        line(x - 1, y + 15, x + 15, y + 15);
        break;
        //     *
        //     *
        // * * *
    case 5:
        setlinestyle(PS_SOLID, 3);
        line(x + 15, y, x + 15, y + 15);
        line(x + 15, y + 15, x + 30, y + 15);
        break;
        // *
        // *
        // * * *
    case 8:
        setlinestyle(PS_SOLID, 3);
        line(x + 15, y + 15, x + 30, y + 15);
        line(x + 15, y + 15, x + 15, y + 30);
        break;
        // * * *
        // *
        // *
    case 9:
        setlinestyle(PS_SOLID, 2);
        line(x + 15, y, x + 15, y + 30);
        line(x - 1, y + 15, x + 30, y + 15);
        setfillcolor(BLACK);
        setlinestyle(PS_SOLID, 2);
        fillcircle(x + 15, y + 15, 4);
        break;
        //   *
        // * O *
        //   *
    }

    //����ѡ���
    if (isnew)
    {
        setlinestyle(PS_SOLID, 2);
        setlinecolor(LIGHTGRAY);
        line(x + 1, y + 2, x + 8, y + 2);
        line(x + 2, y + 1, x + 2, y + 8);
        line(x + 29, y + 2, x + 22, y + 2);
        line(x + 29, y + 1, x + 29, y + 8);
        line(x + 2, y + 29, x + 8, y + 29);
        line(x + 2, y + 22, x + 2, y + 29);
        line(x + 29, y + 29, x + 22, y + 29);
        line(x + 29, y + 22, x + 29, y + 29);
    }

    //��������
    switch (value)
    {
    case 1:
        setfillcolor(BLACK);
        setlinecolor(BLACK);
        setlinestyle(PS_SOLID, 1);
        fillcircle(x + 15, y + 15, 12);
        break;
    case 2: 
        setfillcolor(WHITE);
        setlinecolor(BLACK);
        setlinestyle(PS_SOLID, 1);
        fillcircle(x + 15, y + 15, 12);
        break;
    
    }
}

void drawBoard()
{

    //����ÿһ���ڵ�
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            drawNode(&map[i][j]);
            if (map[i][j].isnew == true)
            {
                map[i][j].isnew = false; // ����һ������λ�õ�ѡ������
            }
        }
    }

    // ��������
    TCHAR strnum[19][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15") };
    TCHAR strabc[19][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,_T("N"),_T("O") };
    LOGFONT nowstyle;
    gettextstyle(&nowstyle);
    settextstyle(0, 0, NULL);
    settextcolor(BLACK);
    int number = 0;
    for (int i = 0; i < 15; i++)
    {
        outtextxy(85 + number, 60, strnum[i]);
        outtextxy(60, 85 + number, strabc[i]);
        number += 30;
    }

}

void mapToBoard(NODE(*A)[15], int(*B)[15])
{
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (A[i][j].value == C_NONE)B[i][j] = C_NONE;
            else if (A[i][j].value == C_WHITE)B[i][j] = C_WHITE;
            else B[i][j] = C_BLACK;
        }
    }
}

int winner()
{
    int iswin = 0;
    int dx[4] = { 1, 0, 1, 1 };  //���ַ��� 
    int dy[4] = { 0, 1, 1, -1 };
    bool isfull = true;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (map[i][j].value != 0) {
                int nowcolor = map[i][j].value;
                int length[4] = { 0, 0, 0, 0 };
                for (int k = 0; k < 4; k++) {
                    int nowi = i;
                    int nowj = j;
                    while (map[nowi][nowj].value == nowcolor && nowi >= 0 && nowi <= 14 && nowj >= 0 && nowj <= 14) {
                        length[k]++;
                        nowi += dx[k];
                        nowj += dy[k];
                    }
                }
                for (int k = 0; k < 4; k++) {
                    if (length[k] >= 5) {
                        if (nowcolor == C_BLACK) {
                            iswin = 1;
                        }
                        else {
                            iswin = 2;
                        }
                    }
                }
            }
            else {
                isfull = false;
            }
        }
    }
    if (isfull) {
        iswin = 3;
    }
    return iswin;
}

void gameOver1(int win) {

    Sleep(500);
    settextcolor(RED);
    settextstyle(50, 0, _T("����"));
    
    mciSendString(_T("close lomusic"), NULL, 0, NULL);
    mciSendString(_T("close winmusic"), NULL, 0, NULL);
    mciSendString(_T("close drmusic"), NULL, 0, NULL);
    
    if (win == 1) {
        outtextxy(250, 530, _T("��Ӯ��"));
        mciSendString(_T("open D:\\�ز�\\win.mp3 alias winmusic"), NULL, 0, NULL);
        mciSendString(_T("play winmusic"), NULL, 0, NULL);

    }
    else if (win == 2) {
        outtextxy(250, 530, _T("������"));
        mciSendString(_T("open D:\\�ز�\\lost.mp3 alias lomusic"), NULL, 0, NULL);
        mciSendString(_T("play lomusic"), NULL, 0, NULL);


    }
    else {
        outtextxy(250, 530, _T("ƽ��"));
        mciSendString(_T("open D:\\�ز�\\draw.mp3 alias drmusic"), NULL, 0, NULL);
        mciSendString(_T("play drmusic"), NULL, 0, NULL);
    }

    settextcolor(BLACK);
    settextstyle(20, 0, _T("����"));
    outtextxy(410, 560, _T("�����Լ���..."));
    
    while (1) {
        MOUSEMSG mouse = GetMouseMsg();
        if (mouse.mkLButton) {
            break;
        }
    }
    Sleep(500);
}

void gameOver2(int win) {

    Sleep(500);
    settextcolor(RED);
    settextstyle(40, 0, _T("����"));
    
    mciSendString(_T("close winmusic"), NULL, 0, NULL);
    mciSendString(_T("close drmusic"), NULL, 0, NULL);
    
    if (win == 1) {
        outtextxy(300, 530, _T("����ʤ"));
        mciSendString(_T("open D:\\�ز�\\win.mp3 alias winmusic"), NULL, 0, NULL);
        mciSendString(_T("play winmusic"), NULL, 0, NULL);
    }
    else if (win == 2) {
        outtextxy(300, 530, _T("����ʤ"));
        mciSendString(_T("open D:\\�ز�\\win.mp3 alias winmusic"), NULL, 0, NULL);
        mciSendString(_T("play winmusic"), NULL, 0, NULL);
    }
    else {
        outtextxy(250, 530, _T("ƽ��"));
        mciSendString(_T("open D:\\�ز�\\draw.mp3 alias drmusic"), NULL, 0, NULL);
        mciSendString(_T("play drmusic"), NULL, 0, NULL);
    }
    settextcolor(BLACK);
    settextstyle(20, 0, _T("����"));
    outtextxy(410, 560, _T("�����Լ���..."));

    while (1) {
        MOUSEMSG mouse = GetMouseMsg();
        if (mouse.mkLButton) {
            break;
        }
    }
    Sleep(500);
}

int game1() {
    Sleep(500);
    
    setbkcolor(COLOR);
    cleardevice();
    
    initNode();
    drawBoard();
    
    settextstyle(20, 10, 0, 0, 0, 1000, false, false, false);
    settextcolor(BLACK);
    settextstyle(25, 0, NULL);
    outtextxy(90, 530, _T("���ִ������"));

    int whoplay = 0;
    int oldi = 0;
    int oldj = 0;
    while (1) {
        if (whoplay == 0)
        {
            mciSendString(_T("close domusic"), NULL, 0, NULL);
            MOUSEMSG mouse = GetMouseMsg();
            if (mouse.x >= 75 && mouse.y >= 75 && mouse.x <= 525 && mouse.y <= 525) {
                //�ж���������ڵ�
                int j = (mouse.x - 75) / 30;
                int i = (mouse.y - 75) / 30;
                //�ж��Ƿ��ǿ�λ��
                if (map[i][j].value == 0)
                {
                    // ���������
                    if (mouse.mkLButton)
                    {
                        map[i][j].value = C_BLACK; // ����
                        map[i][j].isnew = true;    //����ѡ���
                        
                        whoplay = 1; //�ֵ���һ��
                        drawBoard();
                        mciSendString(_T("open D:\\�ز�\\down.mp3 alias domusic"), NULL, 0, NULL);
                        mciSendString(_T("play domusic wait"), NULL, 0, NULL);
                        
                        int win;
                        if ((win = winner()) != 0) {//�ж��Ƿ��ʤ
                            return win;
                        }

                        oldi = 0;
                        oldj = 0;
                        continue;

                    }
                    // ���½ڵ�
                    map[oldi][oldj].isnew = false;
                    drawNode(&map[oldi][oldj]);
                    map[i][j].isnew = true;
                    drawNode(&map[i][j]);
                    oldi = i;
                    oldj = j;
                }

            }
        }
        else {

            mciSendString(_T("close domusic"), NULL, 0, NULL);
            
            int board[15][15];
            mapToBoard(map, board);
            //AI����
            analyse(board, 4, -INT_MAX, INT_MAX);

            map[decision.best.x][decision.best.y].value = C_WHITE;
            map[decision.best.x][decision.best.y].isnew = true;
            
            whoplay = 0;
            drawBoard();
            mciSendString(_T("open D:\\�ز�\\down.mp3 alias domusic"), NULL, 0, NULL);
            mciSendString(_T("play domusic wait"), NULL, 0, NULL);
            
            int win;
            if ((win = winner()) != 0) {
                return win;
            }

            oldi = 0;
            oldj = 0;
        }
    }


}

int game2() {
    Sleep(500);
    
    setbkcolor(COLOR);
    cleardevice();
    
    initNode();
    drawBoard();
    
    settextstyle(20, 10, 0, 0, 0, 1000, false, false, false);
    settextcolor(BLACK);
    settextstyle(25, 0, NULL);
    outtextxy(90, 530, _T("��ҶԿ�������ִ��"));

    int whoplay = 0;
    int oldi = 0;
    int oldj = 0;


    while (1) {

        if (whoplay == 0)
        {
            mciSendString(_T("close domusic"), NULL, 0, NULL);
            MOUSEMSG mouse = GetMouseMsg();

            if (mouse.x >= 75 && mouse.y >= 75 && mouse.x <= 525 && mouse.y <= 525) {
          
                int j = (mouse.x - 75) / 30;
                int i = (mouse.y - 75) / 30;
            
                if (map[i][j].value == 0)
                {
                 
                    if (mouse.mkLButton)
                    {
                        map[i][j].value = C_BLACK; 
                        map[i][j].isnew = true;   
             
                        whoplay = 1;
                        drawBoard();
                        mciSendString(_T("open D:\\�ز�\\down.mp3 alias domusic"), NULL, 0, NULL);
                        mciSendString(_T("play domusic wait"), NULL, 0, NULL);
                        
                        int win;
                        if ((win = winner()) != 0) {
                            return win;
                        }

                        oldi = 0;
                        oldj = 0;
                        continue;

                    }
                    
                    map[oldi][oldj].isnew = false;
                    drawNode(&map[oldi][oldj]);
                    map[i][j].isnew = true;
                    drawNode(&map[i][j]);
                    oldi = i;
                    oldj = j;
                }

            }
        }
        else {
            mciSendString(_T("close domusic"), NULL, 0, NULL);

            MOUSEMSG mouse = GetMouseMsg();

            if (mouse.x >= 75 && mouse.y >= 75 && mouse.x <= 525 && mouse.y <= 525) {
                
                int j = (mouse.x - 75) / 30;
                int i = (mouse.y - 75) / 30;
            
                if (map[i][j].value == 0)
                {
                 
                    if (mouse.mkLButton)
                    {
                        map[i][j].value = C_WHITE; 
                        map[i][j].isnew = true;       
                     
                        whoplay = 0;
                        drawBoard();
                        mciSendString(_T("open D:\\�ز�\\down.mp3 alias domusic"), NULL, 0, NULL);
                        mciSendString(_T("play domusic wait"), NULL, 0, NULL);
                        
                        int win;
                        if ((win = winner()) != 0) {
                            return win;
                        }

                        oldi = 0;
                        oldj = 0;
                        continue;

                    }
          
                    map[oldi][oldj].isnew = false;
                    drawNode(&map[oldi][oldj]);
                    map[i][j].isnew = true;
                    drawNode(&map[i][j]);
                    oldi = i;
                    oldj = j;
                }

            }
        }
    }


}

int startGame() {
    initgraph(600, 600);
    
    IMAGE im_start;
    loadimage(&im_start, _T("D:\\�ز�\\start.jpg"));
    putimage(0, 0, &im_start);

    setlinecolor(BLACK);
    setfillcolor(RGB(254, 220, 130));
    fillrectangle(50, 490, 170, 545);
    fillrectangle(240, 490, 360, 545);
    fillrectangle(430, 490, 550, 545);

    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    LOGFONT nowstyle;
    gettextstyle(&nowstyle);
    settextstyle(25, 0, _T("����"));
    outtextxy(60, 510, _T("�˻���ս"));
    outtextxy(250, 510, _T("˫����Ϸ"));
    outtextxy(440, 510, _T("�˳���Ϸ"));
    settextstyle(&nowstyle);
    
    mciSendString(_T("close stmusic"), NULL, 0, NULL);
    mciSendString(_T("open D:\\�ز�\\background.mp3 alias bgmusic"), NULL, 0, NULL);
    mciSendString(_T("play bgmusic repeat"), NULL, 0, NULL);
    int gamemode = 0;
    init_tuple6type();//���ó�ʼ�����κ���

    while (1) {
        MOUSEMSG mouse = GetMouseMsg();

        if (mouse.x >= 50 && mouse.x <= 170 && mouse.y >= 490 && mouse.y <= 545 && mouse.mkLButton) {
            gamemode = 1;
            mciSendString(_T("open D:\\�ز�\\start.mp3 alias stmusic"), NULL, 0, NULL);
            mciSendString(_T("play stmusic"), NULL, 0, NULL);
            break;
        }
        if (mouse.x >= 240 && mouse.x <= 360 && mouse.y >= 490 && mouse.y <= 545 && mouse.mkLButton) {
            gamemode = 2;
            mciSendString(_T("open D:\\�ز�\\start.mp3 alias stmusic"), NULL, 0, NULL);
            mciSendString(_T("play stmusic"), NULL, 0, NULL);
            break;
        }
        if (mouse.x >= 430 && mouse.x <= 550 && mouse.y >= 490 && mouse.y <= 545 && mouse.mkLButton) {
            mciSendString(_T("open D:\\�ز�\\start.mp3 alias stmusic"), NULL, 0, NULL);
            mciSendString(_T("play stmusic wait"), NULL, 0, NULL);
            exit(0);
        }


    }
    mciSendString(_T("close bgmusic"), NULL, 0, NULL);
    return gamemode;
}