#include<stdio.h>//����ʡ��
#include<graphics.h>//����ʡ��
//ҳ�水ť����
struct button//ȫ�ֽṹ��
{
    int x;//��ťλ��
    int y;
    int width;//��ť���
    int height;//��ť�߶�
    char *pstr;//��ť����
};
struct button *createButton(int x,int y,int width,int height,char *pstr)//������ť
{
     struct button* pButton=(struct button *)malloc(sizeof(struct button));
     pButton->x=x;
     pButton->y=y;
     pButton->width=width;
     pButton->height=height;
     pButton->pstr=(char*)malloc(strlen(pstr)+1);
     strcpy(pButton->pstr,pstr);
     return  pButton;
};
void drawButton(struct button * pButton,int height,int width,unsigned int color)//����ť
{
    setbkmode(0);//��������������õ�ǰ�豸ͼ�������������ʱ�ı���ģʽ��
    setfillcolor(color);//��ť�����ɫ
    settextstyle(height,width,"����");//�������������ʽ
    settextcolor(RED);
    setlinecolor(BLUE);
    setlinestyle(PS_SOLID,4);
    fillrectangle(pButton->x, pButton->y,pButton->width, pButton->height);
    outtextxy(pButton->x+20,pButton->y+17,pButton->pstr);
};
void freetem(struct button *pButton)//�ͷ��ڴ�
{
    free(pButton->pstr);
    free(pButton);
}
