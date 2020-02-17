//疯狂缩行版（还是压不进限制1000个字符）

//#include"pch.h"
#include<windows.h>
#include<conio.h>
#include<ctime>
#include<cstdio>
#define F(i,m,n) for(int i=m;i<n;i++)
typedef unsigned short us;
const int N=20;
us mp[N]={65535},fal[N]={},blk[7][4][4]= { {{3,3},{3,3},{3,3},{3,3}},{{0,7,2},{2,3,2},{2,6,2},{2,7}},{{0,7,1},{3,2,2},{4,7},{2,2,6}},
{{0,7,4},{2,2,3},{1,7},{6,2,2}},{{6,3},{1,3,2},{0,6,3},{2,6,4}},{{3,6},{2,3,1},{0,3,6},{4,6,2}},{{15},{2,2,2,2},{15},{4,4,4,4}} };
int a=0,b=0,c=12,d=0,ch,st,T=500;
void dw(int x){F(i,0,N-x){fal[i]=fal[i+x];fal[i+x]=0;}}void lf(int x){F(i,0,N)fal[i]>>=x;}void rg(int x){F(i,0,N)fal[i]<<=x;}void ubk(){F(i,0,N){mp[i]|=fal[i];fal[i]=0;}}
us chk(){F(i,0,N-1){if(mp[i]&fal[i+1])return 1;}return 0;}
void nbk(int f){if(!f)a=rand()%7,b=rand()%4,c=rand()%12,d=N-4;else b=(b+1)%4;F(i,0,N)fal[i]=0;  F(i,0,4)fal[i+d]=(blk[a][b][i]<<c);}
void elm(int x){F(i,1,N)if(mp[i]==65535&&i--){F(j,i+1,N-1)mp[j]=mp[j+1];mp[N-1]=0;}}
void rf(){if(chk()){ubk();elm(0);nbk(0);}system("cls");F(i,0,N){F(j,0,16)((mp[N-1-i]>>j)|(fal[N-1-i]>>j))&1?putchar('#'):putchar(' ');putchar('\n');}}
void(*fs[5])(int)={nbk,lf,rg,NULL,dw};
int main(){srand(time(0));while(1){st=clock();if(d<=1)nbk(0);dw(1);d--;rf();do{if(_kbhit()&&(ch=_getch())&&(ch>=72&&ch<=80)){fs[ch/2-36](1);rf();}}while(clock()-st<T);if(mp[N-5])exit(0);}}


//正常
/*
//#include "pch.h"
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
#define F(i,m,n) for( int i=m;i<n;i++)  
typedef unsigned short  us;
const int N = 20;	//N-4 层数 最上面四层生成方块
us map[N] = { 65535 }, fall[N] = {}, blocks[7][4][4] = {	//map 已落下固定方块 fall 正在下落方块 blocks 各种方块的各层形态用数值表示
	{{3,3},{3,3},{3,3},{3,3}},{{0,7,2},{2,3,2},{2,6,2},{2,7}},{{0,7,1},{3,2,2},{4,7},{2,2,6}},{{0,7,4},{2,2,3},{1,7},{6,2,2}},{{6,3},{1,3,2},{0,6,3},{2,6,4}},{{3,6},{2,3,1},{0,3,6},{4,6,2}},{{15},{2,2,2,2},{15},{4,4,4,4}} };
int a = 0, b = 0, xx = 12, yy = 0, ch = 0, cnt = 0, interval = 500;	//a 方块种类 b方块形态 xx 方块偏移横坐标 yy 方块偏移纵坐标
void go_down(int x) { F(i, 0, N - x) { fall[i] = fall[i + x]; fall[i + x] = 0; } }//下落按层赋值
void go_left(int x) { F(i, 0, N)fall[i] >>= x; }	//往左  fall各层右移一位
void go_right(int x) { F(i, 0, N)fall[i] <<= x; }	//往右  fall各层左移一位
void union_block() { F(i, 0, N) { map[i] |= fall[i]; fall[i] = 0; } }	//下落方块固定
us  check() { F(i, 0, N - 1) { if (map[i] & fall[i + 1])return 1; }return 0; }	//碰撞检测
void new_block(int flag) {	//flag=1 旋转，0新生成一个
	if (!flag)a = rand()%7, b = rand() % 4, xx = rand() % 12, yy = N - 4;
	else b = (b + 1) % 4;
	F(i, 0, N)fall[i] = 0;
	F(i, 0, 4) fall[i + yy] = (blocks[a][b][i] << xx);
}//若i层 为2^16-1 连续判断消去
void eliminate(int x) { F(i, 1, N) if (map[i] == 65535 && i--) { F(j, i + 1, N - 1) map[j] = map[j + 1]; map[N - 1] = 0; } }
void refresh() {
	if (check()) { union_block(); eliminate(0); new_block(0); }
	system("cls");//清屏输出
	F(i, 0, N) { F(j, 0, 16) ((map[N - 1 - i] >> j) | (fall[N - 1 - i] >> j)) & 1 ? putchar('#') : putchar(' '); putchar('\n'); }
}
void(*func_arr[5])(int) = { new_block,go_left,go_right,NULL,go_down };//上下左右函数指针数组
int main() {	//不要问我为什么边缘会被削去这是(b)特(u)性(g)，(wo)特(shou)性(can)知(zuo)道(bi)吗(yong)
	srand(time(0));
	while (1) {
		int start = clock();
		if (yy <= 1) new_block(0);
		go_down(1); yy--; refresh();// 键值映射函数指针数组
		do {
			if (_kbhit() && (ch = _getch()) && (ch >= 72 && ch <= 80)) { func_arr[ch / 2 - 36](1); refresh(); }
		} while (clock() - start < interval);
		if (map[N - 5]) exit(0); //若最顶层被非下落方块占据游戏结束
	}
}

*/
