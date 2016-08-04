//迷宫求解图形界面
//栈区的创建
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <dos.h>
#include <conio.h>//使用——getch
#define MAX_SIZE 1000
#define INCREAT  1000
#define STACK_MAX_SIZE 1000

#define LENTH 17
#define WIDTH 18
int d[18][17];
//定义多线程函数作为creatthread函数的入口函数
DWORD _stdcall ThrProc(LPVOID lpParameter);
void initmaze();
void gdb();
void esc();
int hour=0, min=0, sec=50;//时间全局变量
int re,k;
int rex=23;
int X,Y;
char name[30];//文件路径
typedef struct PORT{
	int heng;
	int shu;
}port;
typedef struct MAZE{
	struct PORT in;//入口
	struct PORT out;//出口
}MAZE;
struct MAZE xx={{2,1},{17,9}};
//int  maze[WIDTH][LENTH]
//定义并初始化全局迷宫矩阵....正在考虑是否要有自由高度和宽度
int  maze[WIDTH][LENTH]={
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1},
		{1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1},
		{1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1},
		{1,0,1,0,1,1,0,1,1,0,0,0,0,1,0,1,1},
		{1,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1,1},
		{1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,0,0},
		{1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1},
		{1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1},
		{1,0,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1},
		{1,0,1,0,1,1,1,1,0,1,1,0,0,1,1,1,1},
		{1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1},
		{1,0,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1},
		{1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},	
		};
typedef struct Selemtype{
	int i;
//	int y;
	//待增加元素
}elem;
enum direction{//方向
	LEFT,
	RIGHT,
	UP,
	DOWN
};
typedef struct record{
	int h;
	int s;
	int tag;
}Elemtype;
struct record hello[1000];
typedef struct stack{
	Elemtype *base;
	Elemtype *top;
	int stack_size;
}stack;
struct stack *St=(struct stack *)malloc(sizeof(stack));
struct stack *T=(struct stack *)malloc(sizeof(stack));
void Initstack(stack *S){
	S->base=(struct record *)malloc(STACK_MAX_SIZE*sizeof(Elemtype));
	if(!S->base){
		exit(0);
		puts("stack overflow");
	}
	S->top=S->base;
	S->stack_size=1;
}
void Pop(stack *h,int *heng,int *shu){
	if(h->top<h->base){
		puts("the stack is empty");
		exit(0);
	}
	*heng=h->top->h;
	*shu=h->top->s;
	h->top--;
	h->stack_size--;
}
void Push(stack *h,int heng,int shu){
	if((h->top)-(h->base)>=STACK_MAX_SIZE){
		puts("the stack is full");
		exit(0);
	}
	h->top++;
	h->top->h=heng;
	h->top->s=shu;
	
	h->top->tag=0;
	h->stack_size++;
}
void PushSt(stack *h,int heng,int shu){
	if((h->top)-(h->base)>=STACK_MAX_SIZE){
		puts("the stack is full");
		exit(0);
	}
	
	h->top->h=heng;
	h->top->s=shu;
	h->top++;
	h->stack_size++;
}
void Gettop(stack *h,int *heng,int *shu){
	if(h->top<h->base){
		puts("the stack is empty");
		exit(0);
	}
	*heng=h->top->h;
	*shu=h->top->s;
}
int Stackempty(stack *h){
	if(h->top<h->base)
		return 0;
	else 
		return 1;
}
void initd(){
	for(int i=0;i<18;i++)
		for(int j=0;j<17;j++)
			d[i][j]=0;
}
void gotoxy(int x, int y)
{ 
    COORD pos; //coord是一个定义在windows.h函数里的结构体
    pos.X = x - 1; //根据行为移动横光标
	
    pos.Y = y - 1;//纵坐标
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos); //定位光标位置Api接口函数
}
//隐藏光标函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//变色函数使用在基础界面
void SetColor(){
	int color;
	puts("请挑选一个介于0-15之间的数字");
	scanf("%d",&color);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	gotoxy(1,30);
	 puts("                                      ");
	 puts("                                    ");
	 puts("                                    ");
	 puts("                                    ");
	 puts("                                    ");
	 gotoxy(1,30);
}
int move(){	
	int y=1,x=3;
	int rx=x,ry=y;	
	gotoxy(3,1);
	printf("●");
	while(x!=1)
	{
	  int m=y,n=(x+1)/2;
	  if(n==xx.out.heng&&m==xx.out.shu){
	     gotoxy(50,26);
		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		 puts("<(￣ˇ￣)/竟然被你赢了");
		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		 Sleep(4000);
		 gotoxy(50,26);
		 printf("                                        ");
	  }
	  fflush(stdin);
	  char ch;
      ch=getch();
	  switch(ch){
  	    case 'd':
	    if(!maze[m-1][n]&&k!=-1){
		   ++(++x);
     	   gotoxy(x,y);
		   printf("●");
		   gotoxy(rx,ry);
		   printf(" ");
		   ++++rx;
		}
		break;
		case 'a':
		if(!maze[m-1][n-2]&&k!=-1){
		   ----x;
		   gotoxy(x,y);
		   printf("◆");
		   gotoxy(rx,ry);
		   printf(" ");				
	    	----rx;
		}
	     break;
		 case 's':
		 if(!maze[m][n-1]&&k!=-1){
		 	++y;
			gotoxy(x,y);
			printf("▼");
			gotoxy(rx,ry);
			printf(" ");
			++ry;
		}
		break;
		case 'w':
		if(!maze[m-2][n-1]&&k!=-1){
			--y;
			gotoxy(x,y);
			printf("▲");
			gotoxy(rx,ry);
			printf(" ");
			--ry;

		}
		break;
		case 'n':
		gotoxy(1,1);
		puts("                                  ");
	    puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		gotoxy(1,30);
	    puts("                                      ");
	    printf("                                    ");
		re=1;
		return 0;
		break;
		default : break;
		}
	}
	return 0;
}
//存档函数
void storage(){
	
	puts("请输入路径呗,格式为盘符:\\文件夹名\\文件名");
	scanf("%s",name);
	FILE *fp=fopen(name,"w");
	if(fp){
		for(int i=0;i<WIDTH;i++){
			for(int j=0;j<LENTH;j++){
				if(maze[i][j]==1)
					fprintf(fp,"▓");
				else fprintf(fp,"  ");
			}
			fprintf(fp,"\n");
		}	
	}
	else
		printf("存档失败");
	fclose(fp);
	gotoxy(1,30);
	    puts("                                                ");
	    puts("                                                ");
		puts("                                                ");
	    puts("                                                ");
		gotoxy(1,30);
}
void readfile(){
	char str[10];
	FILE *fp=fopen(name,"r");
	while(!feof(fp)){
		fgets(str,2,fp);
		printf("%s",str);
	}	
	esc();
}
void case1(){
	gotoxy(1,1);
	for(int i=0;i<WIDTH;i++){
			for(int j=0;j<LENTH;j++){
				if(maze[i][j]==1)
					printf("▓");
				else printf("  ");
			}
			printf("\n");
		}	
}
//当接收到i键进入插入模式方向键拆墙
//b键建墙
int rebuild(){
	case1();
	int y=1,x=3;
	gotoxy(3,1);
	printf("●");
	while(x!=1)
	{
		int rx=x,ry=y;
	  int m=y,n=(x+1)/2;
	  fflush(stdin);
	  char ch;
      ch=getch();
	  switch(ch){
  	    case 'd': 
			if(n+1<19){
			x=x+2;
     	   gotoxy(x,y);
		   printf("●");
		   maze[y-1][((x+1)/2)-1]=0;
		   gotoxy(rx,ry);
		   printf(" ");
		   ++++rx;
			}
		break;
		case 'a':
			if(n-1>1){
		   x=x-2;
		   gotoxy(x,y);
		   printf("◆");
		   maze[y-1][((x+1)/2)-1]=0;
		   gotoxy(rx,ry);
		   printf(" ");				
	    	----rx;
			}
	     break;
		 case 's':
			 if(y+1<18){
		 	++y;
			gotoxy(x,y);
			printf("▼");
			maze[y-1][((x+1)/2)-1]=0;
			gotoxy(rx,ry);
			printf(" ");
			++ry;
			 }
		break;
		case 'w':
			if(y-1>1){
			--y;
			gotoxy(x,y);
			printf("▲");
			maze[y-1][((x+1)/2)-1]=0;
			gotoxy(rx,ry);
			printf(" ");
			--ry;
			}
		break;
		case 'i':
			--(--x);
			gotoxy(x,y);
			printf("▓");
			maze[y-1][((x+1)/2)-1]=1;
			gotoxy(rx,ry);
			printf("●");
			++(++x);
			break;
			case 'n':
		gotoxy(1,1);
		puts("                                  ");
	    puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		puts("                                  ");
		gotoxy(1,30);
	    puts("                                      ");
	    printf("                                    ");
		gotoxy(1,30);
		return 0;
		break;
		default : break;
		}
	}
	return 0;
}
void initmaze(){
	gotoxy(1,1);
	puts("    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓");
  printf("▓  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");
	puts("▓  ▓  ▓▓                  ▓▓");
	puts("▓  ▓  ▓▓  ▓▓▓▓▓▓▓  ▓▓");
	puts("▓  ▓  ▓▓  ▓▓▓▓▓▓▓  ▓▓");
	puts("▓  ▓  ▓▓  ▓▓▓▓▓▓▓  ▓▓");
	puts("▓  ▓  ▓▓  ▓▓        ▓  ▓▓");
	puts("▓  ▓  ▓▓        ▓▓  ▓  ▓▓");
	puts("▓  ▓  ▓▓▓▓▓▓▓▓  ▓    ★");
	puts("▓  ▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓");
	puts("▓  ▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓");
	puts("▓                ▓▓▓  ▓▓▓▓");
	puts("▓  ▓  ▓▓▓▓  ▓▓▓  ▓▓▓▓");
	puts("▓  ▓  ▓▓▓▓  ▓▓    ▓▓▓▓");
	puts("▓  ▓  ▓▓▓▓  ▓▓  ▓▓▓▓▓");
	puts("▓  ▓  ▓▓▓▓        ▓▓▓▓▓");
	puts("▓  ▓      ▓▓▓▓▓▓▓▓▓▓▓");
	puts("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓");

}
void Homepage(){
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
	//HideCursor();//隐藏光标
	case1();
	gotoxy(5,19);
	puts("");
	printf("任意键开始游戏!按W.A.S.D控制方向");
	_getch();//定义在conio头文件中，从控制台读取字符但不显示在屏幕上
	//在此的功能为暂停不让函数向下进行，当输入wasd四个键值中其中任意一个选项之后，函数向下进行执行initsnack（）；
	gotoxy(5,19);
	puts("                                  ");
	puts("                                  ");
	gotoxy(6,19);
}
//功能6
void helpme(){
	gotoxy(1,1);
	puts("在迷宫界面和墙体编辑两种情况下注意");
	puts("所有功能均按'n'键返回主菜单");
	puts("迷宫界面里当计时器归零时,老鼠失去行动能力");
	puts("鉴于多线程的不易控制,故引入始终暂歇息1s");
	puts("等待输入‘n’键以退出");

}
int help(){
	helpme();
	  char ch;
      ch=getch();
	  switch(ch){
	  case 'n' : 
		gotoxy(1,1);
		puts("                                               ");
		puts("                                               ");
		puts("                                               ");
		puts("                                               ");
		puts("                                               ");
		puts("                                               ");
		gotoxy(1,30);
	    puts("                                      ");
	    printf("                                    ");
		gotoxy(1,30);
		return 0;
		break;
	  default: break;
	  }
	return 0;

}
//交互界面
void Interface(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gotoxy(50,1);	printf("____________________________");
	gotoxy(50,2);   printf("|    button   ||  function |");
	gotoxy(50,3);	printf("|-------------++-----------|");
	gotoxy(50,4);	printf("|      1      ||  迷宫界面 |");
	gotoxy(50,5);	printf("|-------------+------------|");
	gotoxy(50,6);	printf("|      2      ||  墙体编辑 |");
	gotoxy(50,7);	printf("|-------------+------------|");
	gotoxy(50,8);	printf("|      3      ||  迷宫存档 |");
	gotoxy(50,9);	printf("|-------------+------------|");
	gotoxy(50,10);	printf("|      4      ||   求路径  |");
	gotoxy(50,11);	printf("|-------------+------------|");
	gotoxy(50,12);	printf("|      5      ||    读档   |");
	gotoxy(50,13);	printf("|-------------+------------|");
	gotoxy(50,14);	printf("|      6      ||  readme   |");
	gotoxy(50,15);	printf("|-------------+------------|");
	gotoxy(50,16);	printf("|      7      ||   变色    |");
	gotoxy(50,17);	printf("|-------------+------------|");
	gotoxy(50,18);	printf("|      8      ||    exit   |");
	gotoxy(50,19);	printf("+--------------------------+");
	}

void mazeinterface(){
	 Homepage();
	 CreateThread(NULL,0,ThrProc,NULL,0,NULL);
	 move();
	 
	 Sleep(1000);//给线程函数足够的时间休息结束
	 gotoxy(1,30);
	 puts("                                      ");
	 printf("                                    ");
	 gotoxy(1,30);
}

int main(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	HideCursor();//隐藏光标
	Initstack(T);
	Initstack(St);
	Interface();
	int mark,BOOL=1;
	gotoxy(1,30);
	while(BOOL){		
	    puts("please input the button:  ");
		  scanf("%d",&mark);
	    switch(mark){
	        case 1:mazeinterface();break;	        
	        case 2:rebuild();break;
			case 3:storage();break;
	        case 4:gdb();
				   printf("最短路径\n");
				   esc();
				   break;
	        case 5:readfile();break;
	        case 6:help();break;
			case 7:SetColor();break;
	        case 8:BOOL=0;break;
	   	}
		re=0;//时针重置
	}
	 return 0;
}
//计时器函数
DWORD _stdcall ThrProc(LPVOID lpParameter)
{		
	int i, j;
	for(i=hour; i>=0; i--) {
		for(j=min; j>=0; j--) {
			for(k=sec; k>=0; k--) {
				if(re==1){
					gotoxy(3,20);
					puts("                                          ");
				//	gotoxy(1,30);
					return 0;
				}
				gotoxy(3,20);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
				printf("倒计时:%2d:%2d:%2d", i, j, k);
				Sleep(1000);
			}
			sec = 59;
		}
		min = 59;
	}
	gotoxy(3,20);
	printf("                                      ");
return 0;
    
}
 
void printload(struct stack *pass){
//	int m,n;
//	Gettop(pass,&m,&n);
	Elemtype *t=pass->base;
	for(;pass->base<pass->top;pass->base++){
	printf("(%d,%d)\n",pass->base->h,pass->base->s);
	printf("   |   \n");
	}
	pass->base=t;
	pass->top=pass->base;
}
int direct(int x,int y){
	int a=0;
	if(d[y-1][x]!=1&&maze[y-1][x]==0){
	//d键可行
		Push(T,x+1,y);
		d[y-1][x]=1;
		a=1;
	}
	if(d[y-1][x-2]!=1&&maze[y-1][x-2]==0){//A键可行==0	
		Push(T,x-1,y);
		d[y-1][x-2]=1;
		a=1;
	}
	if(d[y-2][x-1]!=1&&y!=1&&maze[y-2][x-1]==0){//W键可行	
		Push(T,x,y-1);
		d[y-2][x-1]=1;
		a=1;
	}
	if(d[y][x-1]!=1&&maze[y][x-1]==0){//S键可行	
		Push(T,x,y+1);
		d[y][x-1]=1;
		a=1;
	}
	T->top->tag=1;
	return a;
}
void gdb(){
	initd();
	int x,y,m,n;
	T->top->h=xx.in.heng;
	T->top->s=xx.in.shu;
	T->top->tag=1;
	d[T->top->s-1][T->top->h-1]=1;
	Gettop(T,&x,&y);
	PushSt(St,x,y);
	while(Stackempty(T)){
		while(!(T->top->h==xx.out.heng)||!(T->top->s==xx.out.shu)){//前攻
			Gettop(T,&x,&y);
			while(direct(x,y)){
 				Gettop(T,&x,&y);
   				PushSt(St,x,y);		
			}		
			while((T->top->h!=xx.out.heng||T->top->s!=xx.out.shu)&&T->top->tag){//回折
					Pop(T,&x,&y);			
					Pop(St,&m,&n);
			}
			x=T->top->h;
			y=T->top->s;
			T->top->tag=1;
			
			if(St->top!=St->base)
			printload(St);
			PushSt(St,x,y);
		}
		if(Stackempty(St))
			puts("(17,9)");
		getchar();
		break;
	}
}
void esc(){
	int a=1;
	while(a){
	if(getch()=='n'){
		gotoxy(1,30);
		for(int xu=0;xu<200;xu++)
		puts("                                      ");
	 gotoxy(1,30);
	 a=0;
	
	}
	}

}