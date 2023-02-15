#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include<math.h>
#include<string.h>
#include"chess.h"
#include"gomoku.h"
#include"chess_two.h"
#include"menu.h"
int button_xy[][4]={{250,50,650,150},{350,140,550,230},{350,260,550,350},{350,380,550,470},{350,500,550,590}};//�ĸ���ť��λ��
int button_judge(int x,int y)//��������ź��Ƿ��ڰ�ť��
{
    if(x>button_xy[1][0]&&y>button_xy[1][1]&&x<button_xy[1][2]&&y<button_xy[1][3])return 1;//�����һ����ť
    if(x>button_xy[2][0]&&y>button_xy[2][1]&&x<button_xy[2][2]&&y<button_xy[2][3])return 2;//����ڶ�����ť
    if(x>button_xy[3][0]&&y>button_xy[3][1]&&x<button_xy[3][2]&&y<button_xy[3][3])return 3;//�����������ť
    if(x>button_xy[4][0]&&y>button_xy[4][1]&&x<button_xy[4][2]&&y<button_xy[4][3])return 4;//������ĸ���ť
    return 0;//δ�����ť
}
int main(void)
{
    //��Ϸ��ʼ
    int width=900,height=600,flag;//������ʾ���ڵĴ�С
    IMAGE img;//ͼƬ����
    while(true)//���ظ���Ϸ
    {
        bool quit=true;
        initgraph(width,height);//��������
        //��ͼ
        BeginBatchDraw();//����������ڿ�ʼ������ͼ��ִ�к��κλ�ͼ����������ʱ���������ͼ������
        loadimage(&img,"./res/����.PNG",900,600);//����ͼƬ��������������ڴ��ļ��ж�ȡͼ��
        putimage(0,0,&img);//��������ļ������������ڵ�ǰ�豸�ϻ���ָ��ͼ��
        //���ð�ť����
        //��ť��С�Լ�����
        struct button *pTitel  =createButton(button_xy[0][0],button_xy[0][1],button_xy[0][2],button_xy[0][3],(char*)"ͨѶ¼");
        struct button *pButton1=createButton(button_xy[1][0],button_xy[1][1],button_xy[1][2],button_xy[1][3],(char*)"����");
        struct button *pButton2=createButton(button_xy[2][0],button_xy[2][1],button_xy[2][2],button_xy[2][3],(char*)"������");
        struct button *pButton3=createButton(button_xy[3][0],button_xy[3][1],button_xy[3][2],button_xy[3][3],(char*)"��������");
        struct button *pButton4=createButton(button_xy[4][0],button_xy[4][1],button_xy[4][2],button_xy[4][3],(char*)"�˳�");
        //����ť
        drawButton(pTitel,60,40,YELLOW);//�������ݵ���ʽ�Լ���ť�����ɫ
        drawButton(pButton1,60,40,LIGHTCYAN);
        drawButton(pButton2,50,28,LIGHTCYAN);
        drawButton(pButton3,50,20,LIGHTCYAN);
        drawButton(pButton4,60,40,LIGHTCYAN);
        //��ʼ���
        while(quit)
        {
            MOUSEMSG msg=GetMouseMsg();//��ȡ�����Ϣ
            switch(msg.uMsg)
            {
                case WM_MOUSEMOVE://����ƶ��¼�
                    if(button_judge(msg.x,msg.y))
                    {
                        if(button_judge(msg.x,msg.y)==1)
                            drawButton(pButton1,60,40,LIGHTGRAY);//�ı���ɫ
                        if(button_judge(msg.x,msg.y)==2)
                            drawButton(pButton2,50,28,LIGHTGRAY);
                        if(button_judge(msg.x,msg.y)==3)
                            drawButton(pButton3,50,20,LIGHTGRAY);
                        if(button_judge(msg.x,msg.y)==4)
                            drawButton(pButton4,60,40,LIGHTGRAY);
                        flag=button_judge(msg.x,msg.y);//��¼���ı���ɫ�İ�ť
                    }
                    else//��ԭ��ťԭ��ģ��
                    {
                        if(flag==1)
                        {
                            drawButton(pButton1,60,40,LIGHTCYAN);
                            flag=0;
                        }
                        if(flag==2)
                        {
                            drawButton(pButton2,50,28,LIGHTCYAN);
                            flag=0;
                        }
                        if(flag==3)
                        {
                            drawButton(pButton3,50,20,LIGHTCYAN);
                            flag=0;
                        }
                        if(flag==4)
                        {
                            drawButton(pButton4,60,40,LIGHTCYAN);
                            flag=0;
                        }
                    }
                    break;
                case WM_LBUTTONDOWN://�������
                    switch(button_judge(msg.x,msg.y))//�ж��Ƿ����˰�ť
                    {
                        case 1:main_chess();FlushMouseMsgBuffer();quit=false;break;
                        case 2:main_gomoku();FlushMouseMsgBuffer();quit=false;break;
                        case 3:main_chess_two();FlushMouseMsgBuffer();quit=false;break;
                        case 4:closegraph();//�رջ�ͼ����
                                exit(0);//�����˳�
                        default:
                            FlushMouseMsgBuffer();//�����¼�����������Ϣ
                            //��ӡ������꣬�������ʱȷ������
                            break;
                    }
                    break;
                default :
                    break;
            }
            FlushBatchDraw();
        }
        EndBatchDraw();
        freetem(pButton1);//�ͷ��ڴ�
        freetem(pTitel);
        freetem(pButton2);
        freetem(pButton3);
        freetem(pButton4);
        closegraph();
}

}






