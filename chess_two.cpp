//�� ��·�� ->����Է�*******
//����A������B*****
//������λ//�������е�bug*****�ܶ�Σ��ұ�����ʱҲ����λ
//���㻹ʣ��������*******
#include<stdio.h>
#include<math.h>
#include<graphics.h>
#include"chess_two.h"
#include"menu.h"
bool is_win_chess_two;//�ж���Ϸ�Ƿ����
bool is_trans;//�Ƿ���Խ���������λ
bool over_two;//��������ʾ������ʾʤ��
unsigned int Round_chess_two=WHITE;
struct judge//���ڳԹ�·������������
{
    int prx;
    int pry;
    bool is;
};
struct judge dead;
POINT begin_two={-1,-1},end_two={-1,-1};
IMAGE back_ground,bai_img,hei_img,biAh_img,biBh_img,chAh_img,chBh_img,waAh_img,
      waBh_img,maAh_img,maBh_img,xiAh_img,xiBh_img,
      hoAh_img,hoBh_img,biAb_img,biBb_img,chAb_img,chBb_img,
      waAb_img,waBb_img,maAb_img,maBb_img,xiAb_img,
      xiBb_img,hoAb_img,hoBb_img;
enum state_two
{   //����ż�� ��������
    hei,bai,
    biAh,biAb,chAh,chAb,maAh,maAb,xiAh,xiAb,hoAh,hoAb,waAh,waAb,//A�ǰ׷����ӣ�2-13��
    biBh,biBb,chBh,chBb,maBh,maBb,xiBh,xiBb,hoBh,hoBb,waBh,waBb,//B�Ǻڷ����ӣ�14-25��
    BEGIN,END
};
enum state_two be=BEGIN;
enum state_two  map_two[ROW_TWO][COL_TWO]={//��ֵ
    {chBb,maBh,xiBb,hoBh,waBb,xiBh,maBb,chBh},//0
    {biBh,biBb,biBh,biBb,biBh,biBb,biBh,biBb},//1
    {bai,hei,bai,hei,bai,hei,bai,hei},//2
    {hei,bai,hei,bai,hei,bai,hei,bai},//3
    {bai,hei,bai,hei,bai,hei,bai,hei},//4
    {hei,bai,hei,bai,hei,bai,hei,bai},//5
    {biAb,biAh,biAb,biAh,biAb,biAh,biAb,biAh},//6
    {chAh,maAb,xiAh,hoAb,waAh,xiAb,maAh,chAb},//7
};

int main_chess_two(void)
{
    initGame3();
    drawGame();
    BeginBatchDraw();
    while(is_win_chess_two)
    {
        if(Round_chess_two==WHITE&& is_win_chess_two)
        {
            printf("�׷�\n");
            while(Round_chess_two==WHITE&& is_win_chess_two)//����
            {
                playGame();
                move();
                drawGame();
                gameOver3();
                FlushBatchDraw();
            }
        }
        else
       {
           printf("�ڷ�\n");
           while(Round_chess_two==BLACK&& is_win_chess_two)//����
            {
                playGame();
                move();
                drawGame();
                gameOver3();
                FlushBatchDraw();
            }
       }
    }
    EndBatchDraw();
    Sleep(1000);
    closegraph();
    return 0;
}


void initGame3(void)
{
    is_win_chess_two=true;//��Ϸ��ʼ
    loadimage(&back_ground,"./res/back.PNG",200,800);
    initgraph(COL_TWO*SPACE+200,ROW_TWO*SPACE,1);
    loadimage(&bai_img,"./res/��.PNG",SPACE,SPACE,true);
    loadimage(&hei_img,"./res/��.PNG",SPACE,SPACE,true);
    loadimage(&biAh_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&biBh_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&chAh_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&chBh_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&waAh_img,"./res/����A��.PNG",SPACE,SPACE,true);
    loadimage(&waBh_img,"./res/����B��.PNG",SPACE,SPACE,true);
    loadimage(&maAh_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&maBh_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&xiAh_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&xiBh_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&hoAh_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&hoBh_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&biAb_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&biBb_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&chAb_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&chBb_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&waAb_img,"./res/����A��.PNG",SPACE,SPACE,true);
    loadimage(&waBb_img,"./res/����B��.PNG",SPACE,SPACE,true);
    loadimage(&maAb_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&maBb_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&xiAb_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&xiBb_img,"./res/��B��.PNG",SPACE,SPACE,true);
    loadimage(&hoAb_img,"./res/��A��.PNG",SPACE,SPACE,true);
    loadimage(&hoBb_img,"./res/��B��.PNG",SPACE,SPACE,true);
}
void drawGame(void)//��ͼ
{
    int white_sum=0;
    int black_sum=0;//330
    putimage(800,0,&back_ground);
    //��װ��ť
    struct button *pButton=createButton(820,350,980,430,(char*)"����");
    drawButton(pButton,50,30,YELLOW);
    for(int i=0;i<ROW_TWO;i++)
        for(int j=0;j<COL_TWO;j++)
        {
            switch(map_two[i][j])
            {
            case bai:
                putimage(j*SPACE,i*SPACE,&bai_img);
                break;
            case hei:
                putimage(j*SPACE,i*SPACE,&hei_img);
                break;
            case biAh:
                white_sum+=10;
                 putimage(j*SPACE,i*SPACE,&biAh_img);
                break;
            case biBh:
                black_sum+=10;
                 putimage(j*SPACE,i*SPACE,&biBh_img);
                break;
            case chAh:
                white_sum+=40;
                 putimage(j*SPACE,i*SPACE,&chAh_img);
                break;
            case chBh:
                black_sum+=40;
                 putimage(j*SPACE,i*SPACE,&chBh_img);
                break;
            case waAh:
                white_sum+=10;
                 putimage(j*SPACE,i*SPACE,&waAh_img);
                break;
            case waBh:
                black_sum+=10;
                 putimage(j*SPACE,i*SPACE,&waBh_img);
                break;
            case maAh:
                white_sum+=20;
                 putimage(j*SPACE,i*SPACE,&maAh_img);
                break;
            case maBh:
                black_sum+=20;
                 putimage(j*SPACE,i*SPACE,&maBh_img);
                break;
            case xiAh:
                white_sum+=20;
                 putimage(j*SPACE,i*SPACE,&xiAh_img);
                break;
            case xiBh:
                black_sum+=20;
                 putimage(j*SPACE,i*SPACE,&xiBh_img);
                break;
            case hoAh:
                white_sum+=80;
                 putimage(j*SPACE,i*SPACE,&hoAh_img);
                break;
            case hoBh:
                black_sum+=80;
                 putimage(j*SPACE,i*SPACE,&hoBh_img);
                break;
            case biAb:
                white_sum+=10;
                 putimage(j*SPACE,i*SPACE,&biAb_img);
                break;
            case biBb:
                black_sum+=10;
                 putimage(j*SPACE,i*SPACE,&biBb_img);
                break;
            case chAb:
                white_sum+=40;
                 putimage(j*SPACE,i*SPACE,&chAb_img);
                break;
            case chBb:
                black_sum+=40;
                 putimage(j*SPACE,i*SPACE,&chBb_img);
                break;
            case waAb:
                white_sum+=10;
                 putimage(j*SPACE,i*SPACE,&waAb_img);
                break;
            case waBb:
                black_sum+=10;
                 putimage(j*SPACE,i*SPACE,&waBb_img);
                break;
            case maAb:
                white_sum+=20;
                 putimage(j*SPACE,i*SPACE,&maAb_img);
                break;
            case maBb:
                black_sum+=20;
                 putimage(j*SPACE,i*SPACE,&maBb_img);
                break;
            case xiAb:
                white_sum+=20;
                 putimage(j*SPACE,i*SPACE,&xiAb_img);
                break;
            case xiBb:
                black_sum+=20;
                 putimage(j*SPACE,i*SPACE,&xiBb_img);
                break;
            case hoAb:
                white_sum+=80;
                 putimage(j*SPACE,i*SPACE,&hoAb_img);
                break;
            case hoBb:
                black_sum+=80;
                 putimage(j*SPACE,i*SPACE,&hoBb_img);
                break;
            default:
                break;
            }
        }
    if(end_two.x==-1&&begin_two.x!=-1)//�������
    {
        setlinecolor(LIGHTCYAN);
        setlinestyle(PS_SOLID,4);
        rectangle(begin_two.y*SPACE,begin_two.x*SPACE,(begin_two.y+1)*SPACE,(begin_two.x+1)*SPACE);
    }
    //Ѫ��ֵ
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID,6);
    //���
    rectangle(820,10,980,340);
    rectangle(820,440,980,770);
    //�ڷ�
    if(black_sum<=150)
        setfillcolor(RED);
    else if(black_sum<=250&&black_sum>150)
        setfillcolor(LIGHTGREEN);
    else
        setfillcolor(LIGHTCYAN);
    //��Ѫ��
    if(is_win_chess_two)//����ֱ������
        solidrectangle(820,10,980,10+black_sum);
    else
    {
        if(Round_chess_two==BLACK)
       {
            solidrectangle(820,10,980,10);
            black_sum=0;
       }
        else
        solidrectangle(820,10,980,10+black_sum);

    }
    //��ʾ����
    char *number=getNum(black_sum);
    settextcolor(BLACK);
    outtextxy(820,280,number);
    outtextxy(930,280,"%");
    //�׷�
    if(white_sum<=150)
        setfillcolor(RED);
    else if(white_sum<=250&&white_sum>150)
        setfillcolor(LIGHTGREEN);
    else
        setfillcolor(LIGHTCYAN);
    //��Ѫ��
    if(is_win_chess_two)
        solidrectangle(820,440+(330-white_sum),980,770);
    else
    {
        if(Round_chess_two==WHITE)
        {
            solidrectangle(820,770,980,770);
            white_sum=0;
        }
        else//��Ȼ����
        solidrectangle(820,440+(330-white_sum),980,770);

    }
    //��ʾ����
    char *number2=getNum(white_sum);
    settextcolor(BLACK);
    outtextxy(820,460,number2);
    outtextxy(930,460,"%");
     if(!is_win_chess_two||over_two)//���˱���
    {
         setlinestyle(PS_SOLID,5);
         settextstyle(120,90,"����");
         if(Round_chess_two==WHITE)
        {
             setlinecolor(BLACK);
             settextcolor(BLACK);
             circle(364,400,120);
             circle(364,400,100);
             outtextxy(270,330,"ʤ");
        }
        else
        {
            setlinecolor(WHITE);
            settextcolor(WHITE);
            circle(364,400,120);
            circle(364,400,100);
            outtextxy(270,330,"ʤ");
        }
        if(over_two)//����
        is_win_chess_two=false;
    }


    //�ͷ��ڴ�
    free(number2);
    free(number);
    freetem(pButton);
}
void playGame(void)//����¼�
{
    if(MouseHit())
    {
        MOUSEMSG msg=GetMouseMsg();
        if(msg.uMsg==WM_LBUTTONDOWN)
        {
            int row =msg.y/SPACE;
            int col =msg.x/SPACE;
            //�׸��Ӷ���ż�����ڸ��Ӷ�������
           if(Round_chess_two==WHITE)//����غ�
           {

               if(be==BEGIN&&map_two[row][col]>=2&&map_two[row][col]<=13)//��ʼ���붯����
                {
                    begin_two.x=row;
                    begin_two.y=col;
                    end_two={-1,-1};
                    be=END;
                }
                else if(be==END)//ֻ���ǿ�or����
                {
                    end_two.x=row;
                    end_two.y=col;
                    //�Թ�·��(�жϰ׷���·���Ƿ񱻳�)
                    if(map_two[begin_two.x][begin_two.y]==biAb||map_two[begin_two.x][begin_two.y]==biAh)
                    {
                           if((end_two.x==4)&&begin_two.x==6&&
                              ((map_two[end_two.x][end_two.y-1]==biBb||map_two[end_two.x][end_two.y-1]==biBh)
                                ||(map_two[end_two.x][end_two.y+1]==biBh||map_two[end_two.x][end_two.y+1]==biBb)))//�Ա�Ҫ�б�
                           {
                                dead.prx=end_two.x;
                                dead.pry=end_two.y;
                           }
                           else
                           {
                               if(end_two.x==dead.prx-1&&end_two.y==dead.pry)
                                    dead.is=true;
                           }
                    }
                    //������λ
                    if(map_two[ begin_two.x][begin_two.y]==waAh&&begin_two.x==7&&end_two.x==7&&
                       ((map_two[end_two.x][end_two.y]==chAh&&end_two.y==0)||
                        (map_two[end_two.x][end_two.y]==chAb&&end_two.y==7)))
                    {
                        //������һ���ж�
                        if(end_two.y==0)
                        {
                            int i;
                            for( i=1;i<4;i++)
                            {
                                if(map_two[7][i]>=2)
                                    break;
                            }
                            if(i==4)//û�����ӵ���
                            {
                                is_trans=true;
                            }
                        }
                        if(end_two.y==7)
                        {
                             int i;
                             for( i=6;i>4;i--)
                            {
                                if(map_two[7][i]>=2)
                                    break;
                            }
                            if(i==4)
                            {
                                is_trans=true;
                            }
                        }
                    }
                    if(map_two[row][col]!=bai&&map_two[row][col]!=hei&&map_two[row][col]<=13&&//�԰׷�����ʱ�ж�
                       !is_trans)//������λʧ�ܲſ�ʼɾ������
                    {
                        begin_two.x=end_two.x;
                        begin_two.y=end_two.y;
                        end_two={-1,-1};
                    }
                    else//�ɹ�����
                    be=BEGIN;
                }

           }
           else//����غ�
            {
                 if(be==BEGIN&&map_two[row][col]!=bai&&map_two[row][col]!=hei&&map_two[row][col]>13)//���붯����
                {
                        begin_two.x=row;
                        begin_two.y=col;
                        end_two={-1,-1};
                        be=END;
                }
                else if(be==END)
                {
                        end_two.x=row;
                        end_two.y=col;
                        //�Թ�·��
                        if(map_two[begin_two.x][begin_two.y]==biBb||map_two[begin_two.x][begin_two.y]==biBh)
                       {
                            if((end_two.x==3)&&begin_two.x==1&&
                               ((map_two[end_two.x][end_two.y-1]==biAb||map_two[end_two.x][end_two.y-1]==biAh)
                            ||(map_two[end_two.x][end_two.y+1]==biAh||map_two[end_two.x][end_two.y+1]==biAb)))//�Ա�Ҫ�б�
                            {
                                dead.prx=end_two.x;
                                dead.pry=end_two.y;
                            }
                            else//�԰���
                            {
                                if(end_two.x==dead.prx+1&&end_two.y==dead.pry)
                                    dead.is=true;
                            }
                       }
                       else
                       {
                           dead={-1,-1,false};
                       }
                        //������λ
                        if(map_two[ begin_two.x][begin_two.y]==waBb&&begin_two.x==0&&end_two.x==0&&
                       ((map_two[end_two.x][end_two.y]==chBh&&end_two.y==7)||
                        (map_two[end_two.x][end_two.y]==chBb&&end_two.y==0)))
                        {
                            if(end_two.y==0)
                            {int i;
                            for( i=1;i<4;i++)
                            {
                                if(map_two[0][i]>=2)
                                    break;
                            }
                            if(i==4)//û�����ӵ���
                            {
                                is_trans=true;
                            }
                            }
                            if(end_two.y==7)
                            {
                                int i;
                             for( i=6;i>4;i--)
                            {
                                if(map_two[0][i]>=2)
                                    break;
                            }
                            if(i==4)
                            {
                                is_trans=true;
                            }
                            }
                        }
                        //��ֵ
                        if(map_two[row][col]!=bai&&map_two[row][col]!=hei&&map_two[row][col]>13&&
                           !is_trans)
                        {
                            begin_two.x=end_two.x;
                            begin_two.y=end_two.y;
                            end_two={-1,-1};
                        }
                        else
                            be=BEGIN;
                }
            }
            //�ж��Ƿ������佨
            if(msg.x>820&&msg.y>360&&msg.x<980&&msg.y<460)
            {
                over_two=true;
                is_win_chess_two=false;
            }
        }
    }
}
void move(void)//����������������µ��ƶ�
{
    extern bool guidance(enum state_two pieces);
    bool canmove=false;
    bool cantran=false;//����
    if(begin_two.x!=-1&&end_two.y!=-1)
    {
        switch (map_two[begin_two.x][begin_two.y])
        {
            case biAh://��
            case biAb:
                 if(((begin_two.x-end_two.x==1||(begin_two.x-end_two.x==2&&begin_two.x==6))
                     &&begin_two.y==end_two.y&&guidance(biAb))||//������
                    (begin_two.x-end_two.x==1&&abs(begin_two.y-end_two.y)==1
                     &&map_two[end_two.x][end_two.y]>1))//��������//��������
                   {
                        canmove=true;
                        if(end_two.x==0)
                             cantran=true;
                    }
                break;
            case biBh:
            case biBb:
                  if(((end_two.x-begin_two.x==1||(end_two.x-begin_two.x==2&&begin_two.x==1))
                      &&begin_two.y==end_two.y&&guidance(biBb))||//������
                    (end_two.x-begin_two.x==1&&abs(begin_two.y-end_two.y)==1
                     &&map_two[end_two.x][end_two.y]>1))//��������//��������
                    {
                        canmove=true;
                        if(end_two.x==7)
                             cantran=true;
                    }
                break;
            case chAh://��
            case chAb:
            case chBh:
            case chBb:
                if((begin_two.x==end_two.x||begin_two.y==end_two.y)&&guidance(chBb))
                        canmove=true;
                break;
            case maAh:
            case maAb:
            case maBh:
            case maBb:
                 if(((abs(end_two.x-begin_two.x)==1&&abs(end_two.y-begin_two.y)==2)||
                   (abs(end_two.y-begin_two.y)==1&&abs(end_two.x-begin_two.x)==2)))
                            canmove=true;
                break;
            case xiAb:
            case xiAh:
            case xiBh:
            case xiBb:
                  if(abs(begin_two.x-end_two.x)==abs(begin_two.y-end_two.y)&&guidance(xiBb))
                            canmove=true;
                break;
            case hoAb:
            case hoAh:
            case hoBb:
            case hoBh:
                if(((begin_two.x==end_two.x||begin_two.y==end_two.y)&&guidance(chBb))||
                   (abs(begin_two.x-end_two.x)==abs(begin_two.y-end_two.y)&&guidance(xiBb)))
                        canmove=true;
                break;
            case waAb:
            case waAh:
            case waBh:
            case waBb:
                if((abs(begin_two.x-end_two.x)==1||abs(begin_two.y-end_two.y)==1)&&guidance(xiBb)&&guidance(chBb))
                    canmove=true;
                break;
            default:
                break;
        }
            if(canmove&&!is_trans)//������λ�ڼ䣬�������
            {
                if(map_two[end_two.x][end_two.y]==waAb||map_two[end_two.x][end_two.y]==waAh||
                   map_two[end_two.x][end_two.y]==waBb||map_two[end_two.x][end_two.y]==waBh)
                    is_win_chess_two=false;//��������Ϸ����
            //�׸�ʼ��
                if(map_two[begin_two.x][begin_two.y]%2==1)
                {
                    if(map_two[end_two.x][end_two.y]%2==0)//�ߵ���
                    {
                        map_two[end_two.x][end_two.y]=(enum state_two)(map_two[begin_two.x][begin_two.y]-1);
                        map_two[begin_two.x][begin_two.y]=bai;
                    }
                    else//�ߵ���
                    {
                        map_two[end_two.x][end_two.y]=map_two[begin_two.x][begin_two.y];
                        map_two[begin_two.x][begin_two.y]=bai;
                    }
                }
            //�ڸ�ʼ��
                else if(map_two[begin_two.x][begin_two.y]%2==0)
                {
                    if(map_two[end_two.x][end_two.y]%2==1)//�ߵ���
                    {
                        map_two[end_two.x][end_two.y]=(enum state_two)(map_two[begin_two.x][begin_two.y]+1);
                        map_two[begin_two.x][begin_two.y]=hei;
                    }
                    else//�ߵ���
                    {
                        map_two[end_two.x][end_two.y]=map_two[begin_two.x][begin_two.y];
                        map_two[begin_two.x][begin_two.y]=hei;
                    }
                }

                //����
                Round_chess_two=Round_chess_two==WHITE? BLACK:WHITE;
            }
            if(is_trans)//������λ
            {
               if(end_two.y==0)//����߻�
               {
                   if(end_two.x==0)//����
                   {
                       //����
                       map_two[0][2]=map_two[begin_two.x][begin_two.y];
                       map_two[begin_two.x][begin_two.y]=bai;
                       //����
                       map_two[0][3]=(enum state_two)(map_two[end_two.x][end_two.y]-1);
                       map_two[end_two.x][end_two.y]=bai;
                   }
                   else//����
                   {
                       map_two[7][2]=map_two[begin_two.x][begin_two.y];
                       map_two[begin_two.x][begin_two.y]=hei;

                       map_two[7][3]=(enum state_two)(map_two[end_two.x][end_two.y]+1);
                       map_two[end_two.x][end_two.y]=hei;
                   }
               }
               else//���ұ߻�
               {
                   if(end_two.x==0)//����
                   {
                       map_two[0][6]=map_two[begin_two.x][begin_two.y];
                       map_two[begin_two.x][begin_two.y]=bai;

                       map_two[0][5]=map_two[end_two.x][end_two.y];
                       map_two[end_two.x][end_two.y]=hei;
                   }
                   else//����
                   {
                       map_two[7][6]=map_two[begin_two.x][begin_two.y];
                       map_two[begin_two.x][begin_two.y]=hei;

                       map_two[7][5]=map_two[end_two.x][end_two.y];
                       map_two[end_two.x][end_two.y]=bai;
                   }
               }
                //����
                Round_chess_two=Round_chess_two==WHITE? BLACK:WHITE;
            }
            is_trans=false;//����������λ
            if(cantran)//����
            {
                if(map_two[end_two.x][end_two.y]%2==0)//�ڸ���
                {
                    if(end_two.x==0)
                    {
                        map_two[end_two.x][end_two.y]=hoAh;
                    }
                    else
                    {
                        map_two[end_two.x][end_two.y]=hoBh;
                    }
                }
                else//�׸���
                {
                    if(end_two.x==0)
                    {
                        map_two[end_two.x][end_two.y]=hoAb;
                    }
                    else
                    {
                        map_two[end_two.x][end_two.y]=hoBb;
                    }
                }
            }
            //�Թ�·��
            if(dead.is)
            {
                //�׸�ʼ��
                if(map_two[begin_two.x][begin_two.y]%2==1)
                {
                    if(map_two[end_two.x][end_two.y]%2==0)//�ߵ���
                    {
                        map_two[end_two.x][end_two.y]=(enum state_two)(map_two[begin_two.x][begin_two.y]-1);
                        map_two[begin_two.x][begin_two.y]=bai;
                    }
                    else//�ߵ���
                    {
                        map_two[end_two.x][end_two.y]=map_two[begin_two.x][begin_two.y];
                        map_two[begin_two.x][begin_two.y]=bai;
                    }
                }
            //�ڸ�ʼ��
                else if(map_two[begin_two.x][begin_two.y]%2==0)
                {
                    if(map_two[end_two.x][end_two.y]%2==1)//�ߵ���
                    {
                        map_two[end_two.x][end_two.y]=(enum state_two)(map_two[begin_two.x][begin_two.y]+1);
                        map_two[begin_two.x][begin_two.y]=hei;
                    }
                    else//�ߵ���
                    {
                        map_two[end_two.x][end_two.y]=map_two[begin_two.x][begin_two.y];
                        map_two[begin_two.x][begin_two.y]=hei;
                    }
                }
                //
                if(map_two[dead.prx][dead.pry]==biAb||map_two[dead.prx][dead.pry]==biBb)
                    map_two[dead.prx][dead.pry]=bai;
                else if(map_two[dead.prx][dead.pry]==biAh||map_two[dead.prx][dead.pry]==biBh)
                    map_two[dead.prx][dead.pry]=hei;
                //����
                Round_chess_two=Round_chess_two==WHITE? BLACK:WHITE;
                //����
                dead={-1,-1,false};
            }
   }
}
bool guidance(enum state_two pieces)//�ƶ�����
{
    switch(pieces)
    {
    case biAb:
    case biAh:
    case biBh:
    case biBb:
        if(map_two[end_two.x][end_two.y]==bai||map_two[end_two.x][end_two.y]==hei)//ֱ�����
            return true;
        return false;
        break;
    case chAb:
    case chAh:
    case chBh:
    case chBb:
        if(end_two.x!=begin_two.x)//����
        {
            if(end_two.x<begin_two.x)//����
            {
                for(int i=end_two.x+1;i<begin_two.x;i++)
                {
                    if(map_two[i][end_two.y]>1)
                    {
                         printf("�߷�������Ҫ��\n");
                         end_two={-1,-1};
                         return false;
                    }
                }
                return true;
            }
            else//����
            {
                for(int i=end_two.x-1;i>begin_two.x;i--)
                {
                    if(map_two[i][end_two.y]>1)
                    {
                        printf("�߷�������Ҫ��\n");
                        end_two={-1,-1};
                        return false;
                    }
                }
                return true;
            }
        }
        else //�᷽��
        {
            if(end_two.y<begin_two.y)//����
            {
                for(int i=end_two.y+1;i<begin_two.y;i++)
                {
                    if(map_two[end_two.x][i]>1)
                    {
                        printf("�߷�������Ҫ��\n");
                        end_two={-1,-1};
                        return false;
                    }
                }
                 return true;
            }
            else//����
            {
                for(int i=end_two.y-1;i>begin_two.y;i--)
                {
                   if(map_two[end_two.x][i]>1)
                    {
                        printf("�߷�������Ҫ��\n");
                        end_two={-1,-1};
                        return false;
                    }
                }
                return true;
            }
        }
        break;
    case xiAb:
    case xiAh:
    case xiBh:
    case xiBb:
        //���谭���
        if(end_two.x<begin_two.x)//�Ϸ�
        {
            if(end_two.y<begin_two.y)//����
            {
                for(int i=1;i<abs(begin_two.x-end_two.x);i++)
                {
                    if(map_two[end_two.x+i][end_two.y+i]>1)
                    {
                        printf("�߷�������Ҫ��\n");
                         end_two={-1,-1};
                         return false;
                    }
                }
                return true;
            }
            else//����
            {
                for(int i=1;i<abs(begin_two.x-end_two.x);i++)
                {
                    if(map_two[end_two.x+i][end_two.y-i]>1)
                    {
                        printf("�߷�������Ҫ��\n");
                         end_two={-1,-1};
                         return false;
                    }
                }
                 return true;
            }
        }
        else//�·�
        {
            if(end_two.y<begin_two.y)//����
            {
                for(int i=1;i<abs(begin_two.x-end_two.x);i++)
                {
                    if(map_two[end_two.x-i][end_two.y+i]>1)
                    {
                        printf("�߷�������Ҫ��\n");
                         end_two={-1,-1};
                         return false;
                    }
                }
                 return true;
            }
            else//����
            {
                for(int i=1;i<abs(begin_two.x-end_two.x);i++)
                {
                    if(map_two[end_two.x-i][end_two.y-i]>1)
                    {
                         printf("�߷�������Ҫ��\n");
                         end_two={-1,-1};
                         return false;
                    }
                }
                 return true;
            }
        }
        break;
    default :
        break;
    }
}
void  gameOver3(void)
{
   if(!is_win_chess_two)
   {
       if(Round_chess_two==WHITE)
        printf("����ʤ");
       else
        printf("����ʤ");
   }
}
char *getNum(int sum)
{
    char num[5];
    char*p=(char*)malloc(5*sizeof(char));
    char *pn=&num[3];
    char *pc=p;
    num[4]='\0';
    if(sum==0)
    {
        *pn=sum%10+48;
        pn--;
    }
    while(sum!=0)
    {
        *pn=sum%10+48;
        sum/=10;
        pn--;
    }
    pn++;
    while(*pn)
    {
        *pc++=*pn++;
    }
    *pc='\0';
    return p;

}
