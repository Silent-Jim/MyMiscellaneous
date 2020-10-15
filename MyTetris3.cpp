/*
环境 vs2019
思路 每一层 都由一个 unsigned short  二进制表示
block 将每种方块的每种形态按层用一个unsigned short  二进制表示
  #      01000000
###    11100000
碰撞检测 将每层做与运算不为0则碰撞
*/
//#include "pch.h"
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
#define F(i,m,n) for( int i=m;i<n;i++)
typedef unsigned short  us;
const int N = 20;	//N层数 最上面四层生成方块  //map 已落下固定方块 blk正在下落的方块 blocks 各种方块的各层形态用数值表示
us *blk, map[N] = { 65535 }, fall[N] = {}, blocks[7][4][4] = { {{3,3},{3,3},{3,3},{3,3}},{{0,7,2},{2,3,2},{2,6,2},{2,7}},{{0,7,1},{3,2,2},{4,7},{2,2,6}},
{{0,7,4},{2,2,3},{1,7},{6,2,2}},{{6,3},{1,3,2},{0,6,3},{2,6,4}},{{3,6},{2,3,1},{0,3,6},{4,6,2}},{{15},{2,2,2,2},{15},{4,4,4,4}} };
int xx = 1, yy = N - 4, typ = 0, stat = 0, interval = 500;// xx下落方块的横坐标 yy 下落方块的纵坐标 typ 方块类型 stat 方块姿态
int check(int nx, int ny) { //检查是否碰撞
	if (nx < 0 || ny < 0)return 0;
	F(i, 0, 4)if ((blk[i] << nx) & map[ny + i])return 0;
	return 1;
}
void display() { 显示
	system("cls");//清屏输出
	F(i, 0, N) {
		int nr = N - 1 - i; 
		us temp = yy <= nr && nr < yy + 4 ? map[nr] | (blk[nr - yy] << xx) : map[nr]; //temp 某一层的显示 下落方块与固定方块取并集
		F(j, 0, 16) (temp >> j) & 1 ? putchar('#') : putchar(' '); putchar('\n');
	}
}
int main() {
	srand(time(0));
	F(i, 0, N)map[i] = i == 0 ? 65535 : 32769; //三边进行填充
	while (1) {
		if (yy == N - 4) xx = rand() % 10 + 1, yy = N - 4, typ = rand() % 7, stat = rand() % 4, blk = blocks[typ][stat]; //生成方块
		display();
		int start = clock(), flg = 1; //flg 通过中断输入进入下次循环进行下落加速的标记
		do {
			if (_kbhit()) {
				switch (_getch()) {
				case 75: if (check(xx - 1, yy))xx--; break; //左移
				case 77: if (check(xx + 1, yy))xx++; break; 
				case 72: stat = (stat + 1) % 4; blk = blocks[typ][stat]; break; //改变形态
				case 80:  flg = 0; break; //中断输入下落加速
				}
				display();
			}
		} while (clock() - start < interval&&flg); //操作时间
		if (check(xx, yy - 1))yy--; //下落
		else {
			F(i, 0, 4) map[yy + i] = (blk[i] << xx) | map[yy + i]; //触底方块进行固定到map
			int nr = 1, ecnt = 0; 
			while (nr < N) { //消除
				map[nr - ecnt] = map[nr];
				if (map[nr] == 65535)ecnt++;
				nr++;
			}
			yy = N - 4; //重置yy
		}
		display();
		if (map[N - 5] != 32769) exit(0); //若最顶层被非下落方块占据游戏结束
	}
}
