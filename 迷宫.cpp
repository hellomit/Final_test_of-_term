//�Թ����ͼ�ν���
//ջ���Ĵ���
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <dos.h>
#include <conio.h>//ʹ�á���getch
#define MAX_SIZE 1000
#define INCREAT  1000
#define STACK_MAX_SIZE 1000

#define LENTH 17
#define WIDTH 18
int d[18][17];
//������̺߳�����Ϊcreatthread��������ں���
DWORD _stdcall ThrProc(LPVOID lpParameter);
void initmaze();
void gdb();
void esc();
int hour=0, min=0, sec=50;//ʱ��ȫ�ֱ���
int re,k;
int rex=23;
int X,Y;
char name[30];//�ļ�·��
typedef struct PORT{
	int heng;
	int shu;
}port;
typedef struct MAZE{
	struct PORT in;//���
	struct PORT out;//����
}MAZE;
struct MAZE xx={{2,1},{17,9}};
//int  maze[WIDTH][LENTH]
//���岢��ʼ��ȫ���Թ�����....���ڿ����Ƿ�Ҫ�����ɸ߶ȺͿ��
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
	//������Ԫ��
}elem;
enum direction{//����
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
    COORD pos; //coord��һ��������windows.h������Ľṹ��
    pos.X = x - 1; //������Ϊ�ƶ�����
	
    pos.Y = y - 1;//������
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos); //��λ���λ��Api�ӿں���
}
//���ع�꺯��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//��ɫ����ʹ���ڻ�������
void SetColor(){
	int color;
	puts("����ѡһ������0-15֮�������");
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
	printf("��");
	while(x!=1)
	{
	  int m=y,n=(x+1)/2;
	  if(n==xx.out.heng&&m==xx.out.shu){
	     gotoxy(50,26);
		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		 puts("<(������)/��Ȼ����Ӯ��");
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
		   printf("��");
		   gotoxy(rx,ry);
		   printf(" ");
		   ++++rx;
		}
		break;
		case 'a':
		if(!maze[m-1][n-2]&&k!=-1){
		   ----x;
		   gotoxy(x,y);
		   printf("��");
		   gotoxy(rx,ry);
		   printf(" ");				
	    	----rx;
		}
	     break;
		 case 's':
		 if(!maze[m][n-1]&&k!=-1){
		 	++y;
			gotoxy(x,y);
			printf("��");
			gotoxy(rx,ry);
			printf(" ");
			++ry;
		}
		break;
		case 'w':
		if(!maze[m-2][n-1]&&k!=-1){
			--y;
			gotoxy(x,y);
			printf("��");
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
//�浵����
void storage(){
	
	puts("������·����,��ʽΪ�̷�:\\�ļ�����\\�ļ���");
	scanf("%s",name);
	FILE *fp=fopen(name,"w");
	if(fp){
		for(int i=0;i<WIDTH;i++){
			for(int j=0;j<LENTH;j++){
				if(maze[i][j]==1)
					fprintf(fp,"��");
				else fprintf(fp,"  ");
			}
			fprintf(fp,"\n");
		}	
	}
	else
		printf("�浵ʧ��");
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
					printf("��");
				else printf("  ");
			}
			printf("\n");
		}	
}
//�����յ�i���������ģʽ�������ǽ
//b����ǽ
int rebuild(){
	case1();
	int y=1,x=3;
	gotoxy(3,1);
	printf("��");
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
		   printf("��");
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
		   printf("��");
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
			printf("��");
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
			printf("��");
			maze[y-1][((x+1)/2)-1]=0;
			gotoxy(rx,ry);
			printf(" ");
			--ry;
			}
		break;
		case 'i':
			--(--x);
			gotoxy(x,y);
			printf("��");
			maze[y-1][((x+1)/2)-1]=1;
			gotoxy(rx,ry);
			printf("��");
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
	puts("    ������������������������������");
  printf("��  ������������������������������\n");
	puts("��  ��  ����                  ����");
	puts("��  ��  ����  ��������������  ����");
	puts("��  ��  ����  ��������������  ����");
	puts("��  ��  ����  ��������������  ����");
	puts("��  ��  ����  ����        ��  ����");
	puts("��  ��  ����        ����  ��  ����");
	puts("��  ��  ����������������  ��    ��");
	puts("��  ��  ����������������  ��������");
	puts("��  ��  ����������������  ��������");
	puts("��                ������  ��������");
	puts("��  ��  ��������  ������  ��������");
	puts("��  ��  ��������  ����    ��������");
	puts("��  ��  ��������  ����  ����������");
	puts("��  ��  ��������        ����������");
	puts("��  ��      ����������������������");
	puts("����������������������������������");

}
void Homepage(){
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
	//HideCursor();//���ع��
	case1();
	gotoxy(5,19);
	puts("");
	printf("�������ʼ��Ϸ!��W.A.S.D���Ʒ���");
	_getch();//������conioͷ�ļ��У��ӿ���̨��ȡ�ַ�������ʾ����Ļ��
	//�ڴ˵Ĺ���Ϊ��ͣ���ú������½��У�������wasd�ĸ���ֵ����������һ��ѡ��֮�󣬺������½���ִ��initsnack������
	gotoxy(5,19);
	puts("                                  ");
	puts("                                  ");
	gotoxy(6,19);
}
//����6
void helpme(){
	gotoxy(1,1);
	puts("���Թ������ǽ��༭���������ע��");
	puts("���й��ܾ���'n'���������˵�");
	puts("�Թ������ﵱ��ʱ������ʱ,����ʧȥ�ж�����");
	puts("���ڶ��̵߳Ĳ��׿���,������ʼ����ЪϢ1s");
	puts("�ȴ����롮n�������˳�");

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
//��������
void Interface(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gotoxy(50,1);	printf("____________________________");
	gotoxy(50,2);   printf("|    button   ||  function |");
	gotoxy(50,3);	printf("|-------------++-----------|");
	gotoxy(50,4);	printf("|      1      ||  �Թ����� |");
	gotoxy(50,5);	printf("|-------------+------------|");
	gotoxy(50,6);	printf("|      2      ||  ǽ��༭ |");
	gotoxy(50,7);	printf("|-------------+------------|");
	gotoxy(50,8);	printf("|      3      ||  �Թ��浵 |");
	gotoxy(50,9);	printf("|-------------+------------|");
	gotoxy(50,10);	printf("|      4      ||   ��·��  |");
	gotoxy(50,11);	printf("|-------------+------------|");
	gotoxy(50,12);	printf("|      5      ||    ����   |");
	gotoxy(50,13);	printf("|-------------+------------|");
	gotoxy(50,14);	printf("|      6      ||  readme   |");
	gotoxy(50,15);	printf("|-------------+------------|");
	gotoxy(50,16);	printf("|      7      ||   ��ɫ    |");
	gotoxy(50,17);	printf("|-------------+------------|");
	gotoxy(50,18);	printf("|      8      ||    exit   |");
	gotoxy(50,19);	printf("+--------------------------+");
	}

void mazeinterface(){
	 Homepage();
	 CreateThread(NULL,0,ThrProc,NULL,0,NULL);
	 move();
	 
	 Sleep(1000);//���̺߳����㹻��ʱ����Ϣ����
	 gotoxy(1,30);
	 puts("                                      ");
	 printf("                                    ");
	 gotoxy(1,30);
}

int main(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	HideCursor();//���ع��
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
				   printf("���·��\n");
				   esc();
				   break;
	        case 5:readfile();break;
	        case 6:help();break;
			case 7:SetColor();break;
	        case 8:BOOL=0;break;
	   	}
		re=0;//ʱ������
	}
	 return 0;
}
//��ʱ������
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
				printf("����ʱ:%2d:%2d:%2d", i, j, k);
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
	//d������
		Push(T,x+1,y);
		d[y-1][x]=1;
		a=1;
	}
	if(d[y-1][x-2]!=1&&maze[y-1][x-2]==0){//A������==0	
		Push(T,x-1,y);
		d[y-1][x-2]=1;
		a=1;
	}
	if(d[y-2][x-1]!=1&&y!=1&&maze[y-2][x-1]==0){//W������	
		Push(T,x,y-1);
		d[y-2][x-1]=1;
		a=1;
	}
	if(d[y][x-1]!=1&&maze[y][x-1]==0){//S������	
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
		while(!(T->top->h==xx.out.heng)||!(T->top->s==xx.out.shu)){//ǰ��
			Gettop(T,&x,&y);
			while(direct(x,y)){
 				Gettop(T,&x,&y);
   				PushSt(St,x,y);		
			}		
			while((T->top->h!=xx.out.heng||T->top->s!=xx.out.shu)&&T->top->tag){//����
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