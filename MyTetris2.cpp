//#include "pch.h"
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
#define F(i,m,n) for( int i=m;i<n;i++)
typedef unsigned short  us;
const int N = 20;	//N-4 ���� �������Ĳ����ɷ���  //map �����¹̶����� fall �������䷽�� blocks ���ַ���ĸ�����̬����ֵ��ʾ
us *blk,map[N] = { 65535 }, fall[N] = {}, blocks[7][4][4] = {
	{{3,3},{3,3},{3,3},{3,3}},
{{0,7,2},{2,3,2},{2,6,2},{2,7}},
{{0,7,1},{3,2,2},{4,7},{2,2,6}},
{{0,7,4},{2,2,3},{1,7},{6,2,2}},
{{6,3},{1,3,2},{0,6,3},{2,6,4}},
{{3,6},{2,3,1},{0,3,6},{4,6,2}},{{15},{2,2,2,2},{15},{4,4,4,4}} };
int xx=1, yy=N-4, typ=0, stat=0, interval=500;
char ch;
void init() {
	srand(time(0));
	F(i, 0, N)map[i] = 32769;
	map[0] = 65535;
}
void produce() {
	xx = rand() % 10 + 1;
	yy = N - 4;
	typ = rand() % 7;
	stat = rand() % 4;
	blk = blocks[typ][stat];
}
int check(int nx, int ny) {
	if (nx < 0 || ny < 0)return 0;
	F(i, 0, 4) {
		if ((blk[i] << nx) & map[ny + i])return 0;
	}
	return 1;
}
void union_block() {
	F(i, 0, 4) map[yy + i] = (blk[i] << xx) | map[yy + i];
}

void eliminate() {
	int nr = 1, ecnt = 0;
	while (nr < N) {
		map[nr - ecnt] = map[nr];
		if (map[nr] == 65535)ecnt++;
		nr++;
	}
}
void change_stat() {
	stat = (stat + 1) % 4;
	blk = blocks[typ][stat];
}
int move(int kv) {
	switch (kv)
	{
	case 75: if (check(xx - 1, yy))xx--; return 0;
	case 77: if (check(xx + 1, yy))xx++; return 0;
	case 72: change_stat(); return 0;
	case 80: return 1;
	}
}

void display() {
	system("cls");//�������
	F(i, 0, N) {
		int nr = N - 1 - i;
		us temp = map[nr];
		if (yy <= nr && nr < yy + 4)temp = temp | (blk[nr - yy]<<xx);
	    F(j, 0, 16) (temp >> j) & 1 ? putchar('#') : putchar(' '); putchar('\n'); 
	}
}

int main() {
	init();
	while (1) {
		if (yy == N - 4) produce(); //��ʼ����
		display();
		int start = clock();
		do{
			if (_kbhit() && (ch = _getch()) && (ch >= 72 && ch <= 80)) {
				if (move(ch) ){
					display();
					break;
				}
				display();
			}
		} while (clock() - start < interval);
		
		if (check(xx, yy - 1))yy--; //����
		else {
			union_block();
			eliminate();
			yy = N - 4;
		}
		display();
		if (map[N - 5]!=32769) exit(0); //����㱻�����䷽��ռ����Ϸ����
	}

}
