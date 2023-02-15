#include<stdio.h>
#include<math.h>
#include<graphics.h>
#include"chess.h"
#include"menu.h"
unsigned int Round;//���ûغϱ�־,��ʼ�췽����
bool is_win,over,ret;//is_win(Ӯ�˾��˳�),over��������� ret�ǻ������
IMAGE img,img2;//��Ƭ����
enum PIECES//ö������
{
    SPACE=-1,
	JU,MA,XI,SI,JI,PA,BI,//�ڷ�
	ju,ma,xi,si,ji,pa,bi,//�췽
	BEGIN,END
};
enum PIECES blackChess[] = { JU,MA,XI,SI,JI,PA,BI};//�ڷ�
enum PIECES redChess[] = {ju,ma,xi,si,ji,pa,bi};//�췽
const char *chessName[] = { "܇", "�R", "��", "ʿ", "��", "�h", "��", "�e", "��", "��", "��", "��", "��", "��" };//������д��
enum PIECES state;//��־����¼���ʼ�����
POINT begin,end;//����¼���ʼ�������ʼ����function:��¼���ε��λ�ã�
struct Chess//��������
{
	int x;
	int y;
	enum PIECES id;//��������
    int type;//����һ�������� ��or��
	bool river;//�ж�С���Ƿ���˺�
};
struct Chess red_chess[2],black_chess[2];//��¼���ӵĽṹ��(���ڻ���)
struct Chess  map[ROW][COL];//�ṹ�����飬��������ÿһ�������Ϣ
struct Chess cp_chess;//���Ե���
int main_chess(void)//mistake
{
	GameInit();//��Ϸ��ʼ��
    BeginBatchDraw();
    while(is_win)//��Ϸδ�����������ѭ��
    {
        if(Round==RED)
        {
            printf("�췽�غ�\n");
            while(Round==RED&&is_win)//����is_win��Ϊ����Ϸ����ֱ���˳�
            {
                MouseControl();
                ChessMove();
                GameDraw();//ÿ�����ݸ��º󣬽��л�ͼ
                FlushBatchDraw();//��Ҫ
                GameOver();
            }
        }
        else
        {
            printf("�ڷ��غ�\n");
            while(Round==BLACK&&is_win)//����is_win��Ϊ����Ϸ����ֱ���˳�
           {
                MouseControl();
                ChessMove();
                GameDraw();//ÿ�����ݸ��º󣬽��л�ͼ
                FlushBatchDraw();
                GameOver();
           }
        }
        FlushBatchDraw();
        Sleep(1000);
        //����ҳ��
        begin={-1,-1};
    }
    EndBatchDraw();
    Sleep(1000);
    printf("��Ϸ������\n");
    Sleep(1000);
    closegraph();//�رջ�ͼ����
	return 0;
}
void GameInit(void)
{
    Round =RED;//���ֺ췽�غ�
    is_win=true;//����ѭ��
    begin ={-1,-1},end={-1,-1};
    state=BEGIN;
    cp_chess={-1,-1,SPACE,SPACE,false};
    red_chess[1]={-1,-1,SPACE,SPACE,false};
    red_chess[0]={-1,-1,SPACE,SPACE,false};
    black_chess[0]={-1,-1,SPACE,SPACE,false};
    black_chess[1]={-1,-1,SPACE,SPACE,false};

    loadimage(&img,"./res/Chess.PNG");//�ϴ�ͼƬ
    loadimage(&img2,"./res/back.PNG",200,804);

	//��������

	initgraph(img.getwidth()+200,img.getheight(),1);
    //�������Ը�ֵ

	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
            enum PIECES chessID=SPACE;//�Ȱ�����������ΪSPACE�����壩
            int chessType=SPACE;//���������Ӫ��SPAce��ʾ�����ӵĵط�
            //���ú���
            if(i<=4)
            {
                chessType=BLACK;//�ж��Ǻڷ���Ӫ
                //���õ�һ������
                if(i==0)
                {
                    if(k<=4)
                    {
                        chessID=blackChess[k];
                    }
                    else
                    {
                        chessID=blackChess[8-k];
                    }
                }//������
                if(i==2&&(k==1||k==7))
                {
                    chessID=blackChess[5];
                }//���ñ�
                if(i==3&&k%2==0)
                {
                    chessID=blackChess[6];
                }
            }
            //���ú���
            else
            {
                chessType=RED;//�췽
                if(i==9)
                {
                    if(k<=4)
                    {
                        chessID=redChess[k];
                    }
                    else
                    {
                        chessID=redChess[8-k];
                    }
                }//������
                if(i==7&&(k==1||k==7))
                {

                    chessID=redChess[5];
                }//���ñ�
                if(i==6&&k%2==0)
                {
                    chessID=redChess[6];
                }
            }
			map[i][k].id =chessID;//��������
			if(map[i][k].id!=SPACE)//�����������BLACK or RED
                map[i][k].type=chessType;
            else//��������ΪSPACE
                map[i][k].type=SPACE;
			map[i][k].river = false;//��ʼ��С��δ����
			map[i][k].x = k*CHESS_SIZE + INTERVAL;//��¼���еط�������λ��
			map[i][k].y = i*CHESS_SIZE + INTERVAL;
		}
	}

}
void MouseControl(void)//�ɹ����������ƶ����꣬Ϊ�ƶ�����׼��//��һ��ֵ��Զ��Round���ڶ���ֵ��Զ�ǿո��!Round
{
    if(MouseHit())
    {
         MOUSEMSG msg=GetMouseMsg();
         if(msg.uMsg==WM_LBUTTONDOWN)
         {
             int row=(msg.y-INTERVAL)/CHESS_SIZE;//ת�����ص�λ��Ϊ����λ��
             int col=(msg.x-INTERVAL)/CHESS_SIZE;
             if(msg.x>map[row][col].x+30 && msg.y<map[row][col].y+30){col++;}
             if(msg.x<map[row][col].x+30 && msg.y>map[row][col].y+30){row++;}
             if(msg.x>map[row][col].x+30 && msg.y>map[row][col].y+30){row++;col++;}//΢������

             if(Round==RED)//�췽�غ�
             {
                 //begin.�������ű�Ļ������ɶ�غ�
                 if(state==BEGIN&&col<9)//���뿪ʼֵ//��ֹ����
                 {
                     if(map[row][col].type==BLACK)//������屨��
                     {
                         printf("���Ǻ췽�غ�!\n");
                     }
                     if(map[row][col].type==RED)//����������룬���ǵ���ո����������
                     {
                        begin.x=row;
                        begin.y=col;
                        state=END;
                        end={-1,-1};//���֮ǰ����ֵ
                     }
                 }
                else if(state==END&&col<9)//�������ֵ
                {
                    end.x=row;
                    end.y=col;
                    if(map[end.x][end.y].type==RED)//����ֵֻ���ǿմ�or���壬���������������ֵ��������id
                    {
                        begin.x=end.x;
                        begin.y=end.y;
                        end={-1,-1};//���֮ǰ����ֵ
                    }
                    else//����Ҫ�������
                        state=BEGIN;

                }
             }
             if(Round==BLACK)//�ڷ��غ�
             {
                if(state==BEGIN&&col<9)
                {
                    if(map[row][col].type==RED)
                      printf("���Ǻڷ��غ�!\n");
                    if(map[row][col].type==BLACK)
                    {
                        begin.x=row;
                        begin.y=col;
                        state=END;
                        end={-1,-1};
                    }
                }
                else if(state==END&&col<9)
                {
                    end.x=row;
                    end.y=col;
                    if(map[end.x][end.y].type==BLACK)
                    {
                        begin.x=end.x;
                        begin.y=end.y;
                        end={-1,-1};
                    }
                    else
                        state=BEGIN;
                }
             }
             if(msg.x>730&&msg.x<910&&msg.y>400&&msg.y<500)//�ж��Ƿ������佨
            {
                over=true;
                is_win=false;//��־��Ϸ����
            }
            if(msg.x>730&&msg.x<910&&msg.y>230&&msg.y<330)//�ж��Ƿ��»����,�������ת��
                ret=true;
         }
    }
}
void ChessMove(void)
{
    extern bool Guideline(enum PIECES chess);//ͬ�ϣ�move������
    bool canMove=false;//��Ϊ���ܶ�
    cp_chess={-1,-1,SPACE,SPACE,false};//������Ӳ����ƶ���Ҫ���ϴε��������ȻֻҪ�߷��Ƿ���ֵ���䣬һֱ��ʾ��
    //ʲô��������ƶ�����
    if(begin.x!=-1&&end.x!=-1)
    {
        switch(map[begin.x][begin.y].id)//�ȿ������������ӵ������
        {
            //��ĸ��дΪ�ڷ���СдΪ�췽
            case PIECES::JU://܇
                if((begin.x==end.x||begin.y==end.y)//ֻ�ܺ�����
                   &&Guideline(JU))//���ж���������
                        canMove=true;
                    break;
            case PIECES::ju:
                if((begin.x==end.x||begin.y==end.y)
                    &&Guideline(ju))
                        canMove=true;
                    break;
            case PIECES::MA://��
                if(((abs(end.x-begin.x)==1&&abs(end.y-begin.y)==2)||//����
                   (abs(end.y-begin.y)==1&&abs(end.x-begin.x)==2))
                      &&Guideline(MA))
                            canMove=true;
                break;
            case PIECES::ma:
                    if(((abs(end.x-begin.x)==1&&abs(end.y-begin.y)==2)||
                       (abs(end.y-begin.y)==1&&abs(end.x-begin.x)==2))&&
                        Guideline(ma))//
                            canMove=true;
                break;
            case PIECES::XI://��
                    if(abs(end.x-begin.x)==2&&
                       abs(end.y-begin.y)==2
                        &&Guideline(XI))
                        canMove=true;
                    break;
            case PIECES::xi:
                    if(abs(end.x-begin.x)==2&&
                       abs(end.y-begin.y)==2&&
                       Guideline(xi))
                        canMove=true;
                    break;
            case PIECES::SI://ʿ
                    if((abs(end.x-begin.x)==1&&
                       abs(end.y-begin.y)==1)&&
                       Guideline(SI))
                        canMove=true;
                    break;
            case PIECES::si:
                    if((abs(end.x-begin.x)==1&&
                       abs(end.y-begin.y)==1)&&
                      Guideline(si))
                        canMove=true;
                    break;
            case PIECES::JI://��
                    if(((abs(end.x-begin.x)==1&&end.y==begin.y)||//����һ��
                        (abs(end.y-begin.y)==1&&end.x==begin.x))&&//����һ��
                        Guideline(JI))
                            canMove=true;
                    break;
            case PIECES::ji://˧
                    if(((abs(end.x-begin.x)==1&&end.y==begin.y)||//����һ��
                        (abs(end.y-begin.y)==1&&end.x==begin.x))&&//����һ��
                        Guideline(ji))
                            canMove=true;
                    break;
            case PIECES::PA://��
                    if((begin.x==end.x||begin.y==end.y)&&//܇�����߷�
                       Guideline(PA))
                         canMove=true;
                    break;
            case PIECES::pa:
                     if((begin.x==end.x||begin.y==end.y)&&
                        Guideline(pa))
                         canMove=true;
                    break;
                break;
            case PIECES::BI://��
                    if(((abs(end.x-begin.x)==1&&end.y==begin.y)//�������߷�����
                        ||(abs(end.y-begin.y)==1&&end.x==begin.x))&&
                        Guideline(BI))
                            canMove=true;
                    break;
            case PIECES::bi:
                    if(((abs(end.x-begin.x)==1&&end.y==begin.y)
                        ||(abs(end.y-begin.y)==1&&end.x==begin.x))&&
                       Guideline(bi))
                            canMove=true;
                    break;
                break;
            default:
                    break;
        }
        if(canMove)
        {
            //�ƶ�֮ǰ
            //���汻�Ե�����
                cp_chess=map[end.x][end.y];
            //�洢�ƶ��켣,���ڻ���
                if(Round==RED)//�ڵײ����ݽ���֮ǰ����¼�췽�ƶ��켣
                {
                    red_chess[1]=map[end.x][end.y];
                    red_chess[0]=map[begin.x][begin.y];
                }
                else
                {
                    black_chess[1]=map[end.x][end.y];
                    black_chess[0]=map[begin.x][begin.y];
                }
            //�жϳԵ����� �����ֺñ�Ļ
                if(map[end.x][end.y].id!=SPACE&&map[end.x][end.y].type==RED)//���Ե������Ǻ췽ʱ
                {
                    printf("�췽����%s���ڷ�%s��\n",chessName[map[end.x][end.y].id],chessName[map[begin.x][begin.y].id]);
                }
                if(map[end.x][end.y].id!=SPACE&&map[end.x][end.y].type==BLACK)
                {
                    printf("�ڷ�����%s���췽%s��\n",chessName[map[end.x][end.y].id],chessName[map[begin.x][begin.y].id]);
                }
                //�ж��Ƿ�˧����
                if(map[end.x][end.y].id==JI||map[end.x][end.y].id==ji)
                    is_win=false;//�����ԣ�������Ϸ
            //��ʼ�ƶ�
                //����
                if((Round==RED&&end.x<=4)||(Round==BLACK&&end.x>4))
                    map[begin.x][begin.y].river=true;
                //��ID
                map[end.x][end.y].id=map[begin.x][begin.y].id;
                map[begin.x][begin.y].id=SPACE;
                //�����ӱ�ʾ
                map[end.x][end.y].river=map[begin.x][begin.y].river;
                map[begin.x][begin.y].river=false;
                //��type
                map[end.x][end.y].type=map[begin.x][begin.y].type;
                map[begin.x][begin.y].type=SPACE;
                Round=Round==RED?BLACK:RED;//��ɹ����꣬���غϽ�����
        }
    }
    if(ret)//�����㷨
    {
                if(Round==RED)//�췽�����
                {
                    int row=(black_chess[1].y-INTERVAL)/CHESS_SIZE;
                    int col=(black_chess[1].x-INTERVAL)/CHESS_SIZE;
                    map[row][col]=black_chess[1];

                    row=(black_chess[0].y-INTERVAL)/CHESS_SIZE;
                    col=(black_chess[0].x-INTERVAL)/CHESS_SIZE;
                    map[row][col]=black_chess[0];

                    row=(red_chess[1].y-INTERVAL)/CHESS_SIZE;
                    col=(red_chess[1].x-INTERVAL)/CHESS_SIZE;
                    map[row][col]=red_chess[1];

                    row=(red_chess[0].y-INTERVAL)/CHESS_SIZE;
                    col=(red_chess[0].x-INTERVAL)/CHESS_SIZE;
                    map[row][col]=red_chess[0];
                    ret=false;
                }
                else//�ڷ������
                {
                    int row=(red_chess[1].y-INTERVAL)/CHESS_SIZE;
                    int col=(red_chess[1].x-INTERVAL)/CHESS_SIZE;
                    map[row][col]=red_chess[1];

                    row=(red_chess[0].y-INTERVAL)/CHESS_SIZE;
                    col=(red_chess[0].x-INTERVAL)/CHESS_SIZE;
                    map[row][col]=red_chess[0];

                    row=(black_chess[1].y-INTERVAL)/CHESS_SIZE;
                    col=(black_chess[1].x-INTERVAL)/CHESS_SIZE;
                    map[row][col]=black_chess[1];

                    row=(black_chess[0].y-INTERVAL)/CHESS_SIZE;
                    col=(black_chess[0].x-INTERVAL)/CHESS_SIZE;
                    map[row][col]=black_chess[0];

                    ret=false;
                }
    }
}
void GameDraw(void)
{
    putimage(0,0,&img);//���벻�ϵ���ͼ��������֮ǰ�����
	putimage(725,0,&img2);
	//����ť
	struct button *pButton1=createButton(730,230,910,330,(char*)"����");//��ť��С�Լ�����
    struct button *pButton2=createButton(730,400,910,500,(char*)"����");
    drawButton(pButton1,60,40,LIGHTCYAN);//�������ݵ���ʽ�Լ������ɫ
    drawButton(pButton2,60,40,LIGHTCYAN);
    //������
	settextstyle(30,0,"����");
	setbkmode(0);
	for (int i=0;i<ROW;i++)
    {
        for(int k=0;k<COL;k++)
        {
            if(map[i][k].id!=SPACE)
            {
                //���ó�ʼ��
                setfillcolor(RGB(253,216,161));  //  253 216 161 *��ɫ ��ԭɫ��ֵ
                setlinecolor(map[i][k].type);
                setlinestyle(PS_SOLID,3);
                settextcolor(map[i][k].type);
                //��ͬ��Բ
                fillcircle(map[i][k].x,map[i][k].y,30);
                fillcircle(map[i][k].x,map[i][k].y,25);
                //����ı�
                outtextxy(map[i][k].x-13,map[i][k].y-15,chessName[map[i][k].id]);
            }
        }
	}
	//��������¼�
    if(begin.x!=-1&&end.x==-1)
    {
        setlinecolor(RGB(0,47,167) );
        setlinestyle(PS_SOLID,6);
        circle(map[begin.x][begin.y].x,map[begin.x][begin.y].y,35);
    }
	//�Ե�Ч��
    if(end.x!=-1&&begin.x!=-1&&cp_chess.id!=SPACE&&
       cp_chess.id!=JI&&cp_chess.id!=ji)//���Ժ󣬵�������ǡ����塯��ֵ��
    {
        setlinestyle(PS_SOLID,5);
        setlinecolor(cp_chess.type);
        settextcolor(cp_chess.type);
        circle(364,400,120);
        circle(364,400,100);
        settextstyle(120,90,"����");
        outtextxy(270,330,chessName[cp_chess.id]);
        if(Round==RED)
            settextcolor(BLACK);
        else
            settextcolor(RED);
        outtextxy(270,330,"��");
    }
    if(over||!is_win)//����
    {
         setlinestyle(PS_SOLID,5);
         settextstyle(120,90,"����");
         if(Round==BLACK)
        {
             setlinecolor(RED);
             settextcolor(RED);
             circle(364,400,120);
             circle(364,400,100);
             outtextxy(270,330,"ʤ");
             is_win=false;
        }
        else
        {
            setlinecolor(BLACK);
            settextcolor(BLACK);
            circle(364,400,120);
            circle(364,400,100);
            outtextxy(270,330,"ʤ");
            is_win=false;
        }
    }
    //�ͷţ������ò���
    freetem(pButton1);
    freetem(pButton2);
}

bool Guideline(enum PIECES chess)//��������ֵһ���������ӵ�����£�������
{
    int n=0;//���ܲ��ܳ�
    switch(chess)
    {
        case PIECES::JU:
        case PIECES::ju:
        if(end.x!=begin.x)//����
        {
            if(end.x<begin.x)//�����ƶ�
            {
                for(int i=end.x+1;i<begin.x;i++)//��Ҫ�жϲ��ܿ�����
                {
                    if(map[i][end.y].id!=SPACE)//�м������ӵ���
                    {
                        printf("�߷�������Ҫ��\n");
                        end={-1,-1};
                        return false;
                    }

                }
                return true;
            }
            else
            {
                for(int i=end.x-1;i>begin.x;i--)
                {
                    if(map[i][end.y].id!=SPACE)
                    {
                        printf("�߷�������Ҫ��\n");
                        end={-1,-1};
                        return false;
                    }
                }
                return true;
            }
        }
        else //�᷽��
        {
            if(end.y<begin.y)//�����ƶ�
            {
                for(int i=end.y+1;i<begin.y;i++)
                {
                    if(map[end.x][i].id!=SPACE)
                    {
                        printf("�߷�������Ҫ��\n");
                        end={-1,-1};
                        return false;
                    }

                }
                 return true;
            }
            else
            {
                for(int i=end.y-1;i>begin.y;i--)
                {
                    if(map[end.x][i].id!=SPACE)
                    {
                        printf("�߷�������Ҫ��\n");
                        end={-1,-1};
                        return false;
                    }
                }
                return true;
            }
        }
            break;
        case PIECES ::MA:
        case PIECES::ma:
            if(end.x<begin.x)//����
            {
                if(begin.x-end.x==2)
                {
                    if(map[begin.x-1][begin.y].id!=SPACE)
                    {
                         printf("�߷�������Ҫ��\n");
                        //��ʼ������
                        end ={-1,-1};
                        return false;
                    }
                }
                else
                {
                    if(begin.y-end.y==2)//��
                    {
                         if(map[begin.x][begin.y-1].id!=SPACE)
                         {
                              printf("�߷�������Ҫ��\n");
                            //��ʼ������
                            end ={-1,-1};
                            return false;
                         }
                    }
                    else//��
                    {
                        if(map[begin.x][begin.y+1].id!=SPACE)
                        {
                             printf("�߷�������Ҫ��\n");
                            //��ʼ������
                            end ={-1,-1};
                            return false;
                        }
                    }
                }
            }
            else
            {
                if(end.x-begin.x==2)
                {
                    if(map[begin.x+1][begin.y].id!=SPACE)
                    {
                         printf("�߷�������Ҫ��\n");
                        end ={-1,-1};
                        return false;
                    }
                }
                else
                {
                    if(end.y-begin.y==2)//��
                    {
                        if(map[begin.x][begin.y+1].id!=SPACE)
                        {
                             printf("�߷�������Ҫ��\n");
                        //��ʼ������
                        end ={-1,-1};
                        return false;
                        }
                    }
                    else//��
                    {
                        if(map[begin.x][begin.y-1].id!=SPACE)
                        {
                        printf("�߷�������Ҫ��\n");
                        //��ʼ������
                        end ={-1,-1};
                        return false;
                        }
                    }
                }
            }
            return true;
            break;
        case PIECES::XI:
        case PIECES::xi:
            //���ܹ���
                if(end.x<=4&&map[begin.x][begin.y].type==RED)
                {
                     printf("�߷�������Ҫ��\n");
                    //��ʼ������
                    end ={-1,-1};
                    return false;
                }
                else if(end.x>=5&&map[begin.x][begin.y].type==BLACK)
                {
                     printf("�߷�������Ҫ��\n");
                    //��ʼ������
                    end ={-1,-1};
                    return false;
                }
                if(end.x<begin.x)//��
                {
                    if(end.y<begin.y)//����
                    {
                        if(map[begin.x-1][begin.y-1].id!=SPACE)
                        {
                             printf("�߷�������Ҫ��\n");
                            //��ʼ������
                            end ={-1,-1};
                            return false;
                        }
                    }
                    else//����
                    {
                        if(map[begin.x-1][begin.y+1].id!=SPACE)
                        {
                             printf("�߷�������Ҫ��\n");
                        //��ʼ������
                        end ={-1,-1};
                        return false;
                        }
                    }
                }
                else//��
                {
                     if(end.y<begin.y)//����
                    {
                        if(map[begin.x+1][begin.y-1].id!=SPACE)
                        {
                             printf("�߷�������Ҫ��\n");
                            //��ʼ������
                            end ={-1,-1};
                            return false;
                        }
                    }
                    else//����
                    {
                        if(map[begin.x+1][begin.y+1].id!=SPACE)
                        {
                             printf("�߷�������Ҫ��\n");
                        //��ʼ������
                        end ={-1,-1};
                        return false;
                        }
                    }
                }
                return true;
            break;
        case PIECES::JI:
        case PIECES::ji:
        case PIECES::SI:
        case PIECES::si:
                //���ܳ��Ź���(�ų����д�㣬���µľ�����ȷ��)
                if((end.y<3||end.y>5)||(end.x>2&&end.x<7))
                {
                            printf("�߷�������Ҫ��\n");
                            //��ʼ������
                            end ={-1,-1};
                            return false;
                }
                return true;
            break;
        case PIECES::PA:
        case PIECES::pa:
                if(end.x!=begin.x)//����
                {
                    if(end.x<begin.x)//����
                    {
                        for(int i=begin.x-1;i>end.x;i--)//˳��������ܷ�
                        {
                           if(map[i][begin.y].id!=SPACE) n++;
                        }
                        if(n==1||(n==0&&map[end.x][end.y].id==SPACE))
                            return true;
                        else
                        {
                             printf("�߷�������Ҫ��\n");
                                    //��ʼ������
                                    end={-1,-1};
                                    return false;
                        }
                    }
                    else//����
                    {
                        for(int i=begin.x+1;i<end.x;i++)
                        {
                           if(map[i][begin.y].id!=SPACE)n++;
                        }
                        if(n==1||(n==0&&map[end.x][end.y].id==SPACE))
                            return true;
                        else
                        {
                             printf("�߷�������Ҫ��\n");
                                    //��ʼ������
                                    end={-1,-1};
                                    return false;
                        }
                    }
                }
                else//����
                {
                    if(end.y<begin.y)//���ƶ�
                    {
                        for(int i=begin.y-1;i>end.y;i--)
                        {
                            if(map[begin.x][i].id!=SPACE)n++;
                        }
                        if(n==1||(n==0&&map[end.x][end.y].id==SPACE))
                            return true;
                        else
                         {
                              printf("�߷�������Ҫ��\n");
                                    //��ʼ������
                                    end={-1,-1};
                                    return false;
                         }
                    }
                    else//���ƶ�
                    {
                        for(int i=begin.y+1;i<end.y;i++)
                        {
                            if(map[begin.x][i].id!=SPACE)n++;
                        }
                        if(n==1||(n==0&&map[end.x][end.y].id==SPACE))
                            return true;
                        else
                        {
                             printf("�߷�������Ҫ��\n");
                                    //��ʼ������
                                    end={-1,-1};
                                    return false;
                        }
                    }
                }
            break;
        case PIECES::BI:
        case PIECES::bi://��
            if(Round==RED)//�췽�غ�
            {
                //���ܺ���
                if(map[begin.x][begin.y].river)//�췽����
                {
                    if(end.x>begin.x)
                    {
                        printf("�߷�����Ҫ��\n");
                        end={-1,-1};
                        return false;
                    }
                    else
                        return true;
                }
                else//δ����
                {
                    if(end.x<begin.x)
                        return true;
                    else
                    {
                         printf("�߷�������Ҫ��\n");
                        //��ʼ������
                        end ={-1,-1};
                        return false;
                    }
                    return false;
                }
            }
            else               //�䡣���ڷ��غ�
            {
                if(map[begin.x][begin.y].river)//�����������ߣ�Ҳ��ǰ��
                {
                    if(end.x<begin.x)
                    {
                         printf("�߷�����Ҫ��\n");
                        end={-1,-1};
                        return false;
                    }
                    else
                        return true;
                }
                else//δ����
                {
                    if(end.x>begin.x)
                        return true;
                    else
                    {
                         printf("�߷�������Ҫ��\n");
                        //��ʼ������
                        end ={-1,-1};
                        return false;
                    }
                }

            }
            break;
        default ://�����Թ淶���
            break;
    }
    return false;
}

void  GameOver(void)
{
    if(!is_win)
    {
        Sleep(1000);
        if(Round==BLACK)
        {
            printf("�췽ʤ��\n");
        }
        else
        {
            printf("�ڷ�ʤ��\n");
        }
    }
    if(Round==BLACK)//����
    {
        for(int i=0;i<3;i++)
            for(int j=3;j<6;j++)
            if(map[i][j].id==blackChess[4])//�ҵ���λ��
            {
                    for(int k=i+1;k<10;k++)
                    {
                        if(map[k][j].id!=SPACE)
                        {
                            if(map[k][j].id==redChess[4])
                            {
                                printf("�ڷ�ʤ��\n");
                                is_win=false;
                                break;
                            }
                            else
                                break;
                        }
                    }
            }
    }
    if(Round==RED)
    {
        for(int i=7;i<10;i++)
            for(int j=3;j<6;j++)
            {
                if(map[i][j].id==redChess[4])
                {
                    for(int k=i-1;k>=0;k--)
                        if(map[k][j].id!=SPACE)
                        {
                            if(map[k][j].id==blackChess[4])
                            {
                                printf("�췽ʤ!\n");
                                is_win=false;
                                break;
                            }
                            else
                                break;
                        }
                }
            }
    }
}
