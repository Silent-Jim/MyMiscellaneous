//#include "pch.h"
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
#define F(i,m,n) for( int i=m;i<n;i++)
typedef unsigned short  us;
const int N = 20;	//N-4 层数 最上面四层生成方块  //map 已落下固定方块 fall 正在下落方块 blocks 各种方块的各层形态用数值表示
us *blk, map[N] = { 65535 }, fall[N] = {}, blocks[7][4][4] = { {{3,3},{3,3},{3,3},{3,3}},{{0,7,2},{2,3,2},{2,6,2},{2,7}},{{0,7,1},{3,2,2},{4,7},{2,2,6}},
{{0,7,4},{2,2,3},{1,7},{6,2,2}},{{6,3},{1,3,2},{0,6,3},{2,6,4}},{{3,6},{2,3,1},{0,3,6},{4,6,2}},{{15},{2,2,2,2},{15},{4,4,4,4}} };
int xx = 1, yy = N - 4, typ = 0, stat = 0, interval = 500;
int check(int nx, int ny) {
	if (nx < 0 || ny < 0)return 0;
	F(i, 0, 4)if ((blk[i] << nx) & map[ny + i])return 0;
	return 1;
}
void display() {
	system("cls");//清屏输出
	F(i, 0, N) {
		int nr = N - 1 - i;
		us temp = yy <= nr && nr < yy + 4 ? map[nr] | (blk[nr - yy] << xx) : map[nr];
		F(j, 0, 16) (temp >> j) & 1 ? putchar('#') : putchar(' '); putchar('\n');
	}
}
int main() {
	srand(time(0));
	F(i, 0, N)map[i] = i == 0 ? 65535 : 32769;
	while (1) {
		if (yy == N - 4) xx = rand() % 10 + 1, yy = N - 4, typ = rand() % 7, stat = rand() % 4, blk = blocks[typ][stat]; //produce blocks
		display();
		int start = clock(), flg = 1;
		do {
			if (_kbhit()) {
				switch (_getch()) {
				case 75: if (check(xx - 1, yy))xx--; break;
				case 77: if (check(xx + 1, yy))xx++; break;
				case 72: stat = (stat + 1) % 4; blk = blocks[typ][stat]; break; //change state
				case 80:  flg = 0; break;
				}
				display();
			}
		} while (clock() - start < interval&&flg);
		if (check(xx, yy - 1))yy--; //下落
		else {
			F(i, 0, 4) map[yy + i] = (blk[i] << xx) | map[yy + i]; //union blocks
			int nr = 1, ecnt = 0;
			while (nr < N) { //eliminate
				map[nr - ecnt] = map[nr];
				if (map[nr] == 65535)ecnt++;
				nr++;
			}
			yy = N - 4; //reset yy
		}
		display();
		if (map[N - 5] != 32769) exit(0); //若最顶层被非下落方块占据游戏结束
	}
}
