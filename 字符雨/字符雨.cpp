#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")//静态库
#define STR_NUM 128//字符串个数
#define STR_SIZE 20//字符串大小
#define STR_WIDTH 15//间距
#define WIDTH 1024
#define HEIGHT 640

struct Star
{
	int x;int y;
	int width;
	int vx;
	int vy;
}star[5];

struct Rain
{
	int x;
	int y;
	int speed;
	char str[STR_SIZE];
}rain[STR_NUM];

char Create()
{
	char temp = 0;
	int flag = rand() % 3;
	if (flag == 0)
		temp = rand() % 26 + 65;
	if (flag == 1)
		temp = rand() % 26 + 97;
	if (flag == 2)
		temp = rand() % 10 + 48;
	return temp;
}


void GameInit()
{
	initgraph(WIDTH, HEIGHT);
	mciSendString("open ./music.mp3 alias haha" ,0,0,0);
	mciSendString("play haha repeat", 0, 0, 0);
	

	srand((unsigned int)time(NULL));
	int i,k;
	for (i = 0;i < STR_NUM;i++)
	{
		for (k = 0;k < STR_SIZE;k++)
		{
			rain[i].str[k] = Create();
		}
	}
	//初始化坐标和速度

	for (i = 0;i < STR_NUM;i++)
	{
		rain[i].x = i * STR_WIDTH;
		rain[i].y = rand() % HEIGHT;
		rain[i].speed = rand() % 6+5;
	}

	//五角星
	for (i = 0;i < 5;i++)
	{
		star[i].x = rand() % WIDTH;
		star[i].y = rand() % HEIGHT;
		star[i].width = rand() % 11 + 20;
		star[i].vx = rand() % rand() % 4 + 1;
		star[i].vy = rand() % rand() % 4 + 1;
	}
}

void FiveStar(Star temp)
{
	POINT star[5] = { {temp.x,temp.y + temp.width / 3},
		{temp.x + temp.width / 3,temp.y},
		{temp.x + temp.width,temp.y + temp.width / 3},
		{temp.x + temp.width,temp.y + temp.width},
		{temp.x,temp.y + temp.width} };

	line(star[0].x, star[0].y, star[2].x, star[2].y);
	line(star[2].x, star[2].y, star[4].x, star[4].y);
	line(star[4].x, star[4].y, star[1].x, star[1].y);
	line(star[1].x, star[1].y, star[3].x, star[3].y);
	line(star[3].x, star[3].y, star[0].x, star[0].y);
}

//绘制五角星
void StarDraw()
{
	int i;
	setlinecolor(GREEN);
	for (i = 0;i < 5;i++)
	{
		FiveStar(star[i]);
		star[i].x += star[i].vx;
		star[i].y += star[i].vy;
		if(star[i].x+star[i].width>=WIDTH|| star[i].x <= 0)
		{ 
			star[i].vx = -star[i].vx;
		}
		 if (star[i].y+star[i].width>=HEIGHT||star[i].y<=0)
		{
			 star[i].vy = -star[i].vy;
		}
	}
}



void GameDraw()
{
	int i,k;
	setbkmode(0);
	for (i = 0;i < STR_NUM;i++)
	{
		for (k = 0;k < STR_SIZE;k++)
		{
			settextcolor(RGB(0, 255 - 10 * k, 0));
			outtextxy(rain[i].x, rain[i].y - STR_WIDTH * k, rain[i].str[k]);
		}
	}
	
}

void ChangeCh()
{
	int i ;
	for ( i = 0; i < STR_NUM; i++)
	{
		rain[i].str[rand() % 20] = Create();
	}
}

void Move()
{
	int i;
	for (i = 0;i < STR_NUM;i++)
	{
		rain[i].y += rain[i].speed;
		if (rain[i].y >= 840)
		{
			rain[i].y = 0;
		}
	}
}

int main()
{
	GameInit();
	BeginBatchDraw();
	system("color 70");
	while (1)
	{
		cleardevice();
		GameDraw();
		StarDraw();
		Move();
		ChangeCh();
		FlushBatchDraw();
		/*int i;
		for (i = 0;i < 20;i++)
		{
			
			puts(rain[i].str);
		}*/

	}
	EndBatchDraw();
	mciSendString("close haha", 0, 0, 0);
	getchar();
	return 0;
}