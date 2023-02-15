//�ظ�ռ������****
//�������״̬
#include<stdio.h>
#include<graphics.h>
#include"gomoku.h"
unsigned int Round_gomoku;
bool is_win_gomoku;
bool is_move;
IMAGE img_wuzi;
struct chess
{
    int x;
    int y;
    unsigned int  type;
};
struct chess un_gomoku;//��Ӱû���ӵĵط�ֵ��¼
struct chess gomoku[15][15];//�������ӣ���¼��Ϣ;
int  main_gomoku(void)
{
    initGame2();
    BeginBatchDraw();
    while(is_win_gomoku)
    {
        if(Round_gomoku==BLACK)
        {
            while(Round_gomoku==BLACK)
            {
                playChess();
                drawGame2();
                FlushBatchDraw();
                gameOver2();
            }
        }
        else
        {
            while(Round_gomoku==WHITE)
            {
                playChess();
                drawGame2();
                FlushBatchDraw();
                gameOver2();
            }
        }
        FlushBatchDraw();
        //ˢ����ɫ��ʾ��
        setlinecolor(BLACK);
        setfillcolor(BLACK);
        fillrectangle(620,240,780,310);
        Sleep(1000);
    }
     EndBatchDraw();
    //ʤ����ʾ
    setfillcolor(RED);
    fillrectangle(620,240,780,310);
    if(Round_gomoku==WHITE)
            outtextxy(660,250,"��ʤ");
    else
            outtextxy(660,250,"��ʤ");
    Sleep(1000);
    closegraph();
    return 0;
}
void initGame2(void)
{
    Round_gomoku=BLACK;//�غϳ���
    is_win_gomoku=true;//��ʼ����
    loadimage(&img_wuzi,"./res/wuzi.PNG",600,600);
    initgraph(800,600);
    //�غ���ʾ�� ��ͼ
    fillrectangle(620,70,780,140);
    //��ͼ
    setfillcolor(BLACK);
    setlinecolor(WHITE);
    fillrectangle(620,380,780,450);
    //��ʼ���ײ�����
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++)
        {
            gomoku[i][j].type=1;
            gomoku[i][j].x=-1;
            gomoku[i][j].y=-1;
        }
}
void drawGame2(void)
{
    //��ͼ
    putimage(0,0,&img_wuzi);
    //����
    settextstyle(40,0,"����");
    setbkmode(0);
    setlinecolor(WHITE);
    //��ʾ�غϱ�
    if(Round_gomoku==BLACK)//�ڷ�
    {
         settextcolor(WHITE);
         outtextxy(620,400,"�ڷ��غ�");
         setfillcolor(WHITE);
         fillrectangle(620,70,780,140);
    }
    else//�׷�
    {
        settextcolor(BLACK);
        outtextxy(620,90,"�׷��غ�");
        setfillcolor(BLACK);
        fillrectangle(620,380,780,450);
    }
    //�غ� ������
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++)
        {
            if(gomoku[i][j].type!=1)//ֻ�����ӵĵط���ʾ
            {
                if(gomoku[i][j].type==BLACK)
                {
                 setlinecolor(BLACK);
                 setfillcolor(BLACK);
                 fillcircle(gomoku[i][j].x,gomoku[i][j].y,10);
                }
                else if(gomoku[i][j].type==WHITE)
                {
                setfillcolor(WHITE);
                solidcircle(gomoku[i][j].x,gomoku[i][j].y,10);//����
                }
            }
        }
        //Ԥ����״̬
    if(Round_gomoku==BLACK&&
       un_gomoku.x!=-1)//���㴦��
    {
        setlinecolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(un_gomoku.x,un_gomoku.y,10);
    }
    else if(Round_gomoku==WHITE&&
            un_gomoku.x!=-1)
    {
        setfillcolor(WHITE);
        solidcircle(un_gomoku.x,un_gomoku.y,10);
    }
}
void playChess(void)
{
    is_move=false;//��δ����
    //����¼�
    if(MouseHit())
   {
        //���
        MOUSEMSG msg=GetMouseMsg();
        int chess_x=(msg.x-INTER_X)/SIZE*SIZE+INTER_X;//�������룬�պ������
        int chess_y=(msg.y-INTER_Y)/SIZE*SIZE+INTER_Y;
        //����
        if(msg.x>chess_x+19&&msg.y>chess_y+19){chess_x=chess_x+SIZE;chess_y=chess_y+SIZE;};//���´�
        if(msg.x>chess_x+19&&msg.y<chess_y+19){chess_x=chess_x+SIZE;};//�Ҵ�
        if(msg.x<chess_x+19&&msg.y>chess_y+19){chess_y=chess_y+SIZE;};//�´�
        //ĿǰΪֹ��chess_x��Ȼ�����ؼ�
        //�ƶ��¼�
        if(msg.uMsg==WM_MOUSEMOVE)
        {
            //���������ƶ�
            if(msg.x>=INTER_X-15&&msg.y>=INTER_Y-15
               &&msg.x<=14*SIZE+INTER_X+15
               &&msg.y<=14*SIZE+INTER_Y+15)
            {
                if(gomoku[(chess_y-INTER_Y)/SIZE][(chess_x-INTER_X)/SIZE].type==1)
                {
                    un_gomoku.x=chess_x;
                    un_gomoku.y=chess_y;
                }
                else//��ָ�������ӵĵط�ʱ������
                {
                    un_gomoku.x=-1;
                    un_gomoku.y=-1;
                }
            }
            //�������ƶ�������
            else
            {
                un_gomoku.x=-1;
                un_gomoku.y=-1;
            }
        }
        //����¼�
        if(msg.uMsg==WM_LBUTTONDOWN&&msg.x>=INTER_X-15//����¼�
          &&msg.y>=INTER_Y-15&&msg.x<=14*SIZE+INTER_X+15
          &&msg.y<=14*SIZE+INTER_Y+15)//�߽�����
        {
           if(gomoku[(chess_y-INTER_Y)/SIZE][(chess_x-INTER_X)/SIZE].type==1)//�����ڿյĵط�
           {
                 gomoku[(chess_y-INTER_Y)/SIZE][(chess_x-INTER_X)/SIZE].type=Round_gomoku;//����
                 gomoku[(chess_y-INTER_Y)/SIZE][(chess_x-INTER_X)/SIZE].x=chess_x;
                 gomoku[(chess_y-INTER_Y)/SIZE][(chess_x-INTER_X)/SIZE].y=chess_y;
                 is_move=true;//������
           }
           else
           {
                setfillcolor(RED);
                fillrectangle(620,240,780,310);
                outtextxy(630,250,"��������");
           }
       }
   }
}
void gameOver2(void)
{
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++)
        {
            if(gomoku[i][j].type==Round_gomoku)
            {
                int k=0,l=0,m=0,n=0;//����
                for( k=0;k<5;k++)//���ű���
                {
                    if(gomoku[i][j+k].type!=Round_gomoku)
                        break;
                }
                if(k==5)
                {
                    is_win_gomoku=false;
                    break;
                }
                for(l=0;l<5;l++)//���ű���
                {
                    if(gomoku[i+l][j].type!=Round_gomoku)
                        break;
                }
                if(l==5)
                {
                       is_win_gomoku=false;
                    break;
                }
                for(m=0;m<5;m++)//����
                {
                    if(gomoku[i+m][j+m].type!=Round_gomoku)
                        break;
                }
                if(m==5)
                {
                    is_win_gomoku=false;
                    break;
                }
                for(n=0;n<5;n++)
                {
                    if(gomoku[i+n][j-n].type!=Round_gomoku)
                    break;
                }
                if(n==5)
                {
                    is_win_gomoku=false;
                    break;
                }
            }
        }
//        �ж�ʤ�����پ���
        if(is_move)
           Round_gomoku=Round_gomoku==BLACK?WHITE:BLACK;
}
