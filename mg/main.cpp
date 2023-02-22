#include<graphics.h>
#include<malloc.h>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<queue>
#include<iostream>
#include<vector>


//迷宫高度
#define LH 31
//迷宫长度
#define LW 31

//迷宫构建速度
#define BUILDERSLEEP 1

//菜单栏的
//#define 


using std::queue;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

//迷宫地图
int map[LH + 1][LW + 1];

//起点
int startX = 2, startY = 2;
int moveX = 2, moveY=2;
//终点
int endX = LW, endY = LH - 1;

void menu();
void dfs(int map[LH + 1][LW + 1], int darwX, int darwY);

//利用prim算法绘制地图
void primDraw() {

	
	//初始化地图数据
	for (int y = 0; y <= 30; ++y) {
		for (int x = 0; x <= 30; ++x) {
			map[y][x] = 0;
		}
	}

	//设置围墙
	setfillcolor(RGB(200, 147, 246));
	for (int y = 1; y <= LH; ++y) {
		for (int x = 1; x <= LW; ++x) {
			if (y == 1 || y == LH || x == 1 || x == LW) {
				map[y][x] = -1;
				fillrectangle(20 * (x - 1), 20 * (y - 1), 20 * x, 20 * y);
			}
		}
	}

	//Prim算法绘制地图
	//setfillcolor(WHITE);
	setfillcolor(BLACK);

	vector<int*> data;
	data.push_back(new int[2] {2,2});

	while (true) {
		if (data.size() == 0)
			break;

		int randIndex = rand() % data.size();

		int xx = data[randIndex][0];
		int yy = data[randIndex][1];

		int next[4][2]{
			{xx,yy - 2},
			{xx,yy + 2},
			{xx - 2,yy},
			{xx + 2,yy},
		};

		vector<int> res;

		for (int i = 0; i < 4; ++i) {

			if (next[i][0] <= 1 || next[i][0] >= LW || next[i][1] <= 1 || next[i][1] >= LH) {
				continue;
			}

			if (map[next[i][1]][next[i][0]] == 1)
				continue;

			res.push_back(i);

		}

		if (res.size() != 0) {
			int randNum = rand() % res.size();

			int x = next[res[randNum]][0];
			int y = next[res[randNum]][1];

			if (res[randNum] == 0) {
				fillrectangle(20 * (x - 1), 20 * (y - 1 + 1), 20 * x, 20 * (y + 1));
				data.push_back(new int[2] {x, y});
				map[y+1][x] = 1;
				map[y][x] = 1;
			}
			if (res[randNum] == 1) {
				fillrectangle(20 * (x - 1), 20 * (y - 1 - 1), 20 * x, 20 * (y - 1));
				data.push_back(new int[2] {x, y});
				map[y-1][x] = 1;
				map[y][x] = 1;
			}
			if (res[randNum] == 2) {
				fillrectangle(20 * (x - 1 + 1), 20 * (y - 1), 20 * (x + 1), 20 * y);
				data.push_back(new int[2] {x, y});
				map[y][x+1] = 1;
				map[y][x] = 1;
			}
			if (res[randNum] == 3) {
				fillrectangle(20 * (x - 1 - 1), 20 * (y - 1), 20 * (x - 1), 20 * y);
				data.push_back(new int[2] {x, y});
				map[y][x-1] = 1;
				map[y][x] = 1;
			}
			fillrectangle(20 * (x - 1), 20 * (y - 1), 20 * x, 20 * y);


		}
		else {
			data.erase(data.begin() + randIndex);
		}
		Sleep(BUILDERSLEEP);

	}


}

void dfsDraw(int map[LH+1][LW+1],int darwX,int darwY) {

	//初始化地图数据
	for (int y = 0; y <= 30; ++y) {
		for (int x = 0; x <= 30; ++x) {
			map[y][x] = 0;
		}
	}

	//设置围墙
	setfillcolor(RGB(200, 147, 246));
	for (int y = 1; y <= LH; ++y) {
		for (int x = 1; x <= LW; ++x) {
			if (y == 1 || y == LH || x == 1 || x == LW) {
				map[y][x] = -1;
				fillrectangle(20 * (x - 1), 20 * (y - 1), 20 * x, 20 * y);
			}
		}
	}

	//DFS算法绘制地图
	//setfillcolor(WHITE);
	setfillcolor(BLACK);


	dfs(map,startX,startY);
	
}

void dfs(int map[LH + 1][LW + 1], int darwX, int darwY) {
	Sleep(BUILDERSLEEP);
	
	int next[4][2] = {
		{darwX,darwY-2},
		{darwX,darwY+2},
		{darwX-2,darwY},
		{darwX+2,darwY},
	};

	vector<int> res;

	for (int i = 0; i < 4; ++i) {
		
		if (next[i][0] <= 1 || next[i][0] >= LW || next[i][1] <= 1 || next[i][1] >= LH)
			continue;

		if (map[next[i][1]][next[i][0]] == 1)
			continue;
		res.push_back(i);
	}



	
	while (res.size() != 0) {
		int randNum = rand() % res.size();

		int x = next[res[randNum]][0];
		int y = next[res[randNum]][1];

		int resValue = res[randNum];
		res.erase(res.begin()+randNum);

		if (resValue == 0) {
			if (map[y][x] == 1)
				continue;

			fillrectangle(20 * (darwX - 1), 20 * (darwY - 1), 20 * darwX, 20 * darwY);
			fillrectangle(20 * (x - 1), 20 * (y - 1 + 1), 20 * x, 20 * (y + 1));
			map[y + 1][x] = 1;
			map[y][x] = 1;
			dfs(map, x, y);
		}
		if (resValue == 1) {
			if (map[y][x] == 1)
				continue;
			fillrectangle(20 * (darwX - 1), 20 * (darwY - 1), 20 * darwX, 20 * darwY);
			fillrectangle(20 * (x - 1), 20 * (y - 1 - 1), 20 * x, 20 * (y - 1));
			
			map[y - 1][x] = 1;
			map[y][x] = 1;
			dfs(map, x, y);
		}
		if (resValue == 2) {
			if (map[y][x] == 1)
				continue;
			fillrectangle(20 * (darwX - 1), 20 * (darwY - 1), 20 * darwX, 20 * darwY);
			fillrectangle(20 * (x - 1 + 1), 20 * (y - 1), 20 * (x + 1), 20 * y);
			map[y][x + 1] = 1;
			map[y][x] = 1;
			dfs(map, x, y);
		}
		if (resValue == 3) {
			if (map[y][x] == 1)
				continue;
			fillrectangle(20 * (darwX - 1), 20 * (darwY - 1), 20 * darwX, 20 * darwY);
			fillrectangle(20 * (x - 1 - 1), 20 * (y - 1), 20 * (x - 1), 20 * y);
			map[y][x - 1] = 1;
			map[y][x] = 1;
			dfs(map, x, y);
		}


	}



}

void minWin(int step,char press) {
	settextcolor(BLACK);
	setlinecolor(BLACK);
	settextstyle(42,20,_T("隶书"));
	outtextxy((LW*20)+25,50,_T("当前步数"));
	

	
	TCHAR stepTXT[20] = TEXT("");
	wsprintf(stepTXT, _T("%d"),step);
	outtextxy((LW*20) + 90, 100, stepTXT);

	rectangle( (LW*20)+60,180, (LW * 20) + 150, 260);
	outtextxy((LW * 20) + 90, 200, TCHAR(press-32));

	settextcolor(BLACK);
	setlinecolor(BLACK);
	//outtextxy((LW * 20) + 25, 300, _T("刷新地图"));
	//rectangle((LW * 20) + 20, 300, (LW * 20) + 185, 350);

	


}


//检查是否到达终点
bool checkTerminus(int mX,int mY,int eX,int eY) {
	if (mX == eX && mY == eY) {
		return true;
	}
	return false;
}

//控制部分
void controller() {

	//初始化控制位置
	moveX = startX;
	moveY = startY;

	for (int y = 0; y < LH; ++y) {
		for (int x = 0; x < LW; ++x) {
			cout << map[y][x] << " ";
		}
		cout << endl;
	}


	char key='\0',resKey=' ';
 	int stepNum=0;

	//设置起点
	map[startX][startY] = 1;
	setfillcolor(BLACK);
	fillrectangle(20 * (startX - 1), 20 * (startY - 1), 20 * startX, 20 * startY);

	//设置终点
	map[endY][endX] = 1;
	setfillcolor(BLACK);
	fillrectangle(20 * (endX - 1), 20 * (endY - 1), 20 * endX, 20 * endY);
	map[endY][endX-1] = 1;
	setfillcolor(BLACK);
	fillrectangle(20 * (endX - 2), 20 * (endY - 1), 20 * endX-1, 20 * endY);
	map[endY][endX - 2] = 1;
	setfillcolor(BLACK);
	fillrectangle(20 * (endX - 3), 20 * (endY - 1), 20 * endX - 2, 20 * endY);

	while (true) {

		setfillcolor(RGB(87, 166, 74));
		fillrectangle(20 * (moveX - 1), 20 * (moveY - 1), 20 * moveX, 20 * moveY);


		if (_kbhit()) {
			key = _getch();
		}
		else
		{
			key = '\0';
		}

		if (key == 'w') {
			resKey = 'w';
			setfillcolor(BLACK);
			fillrectangle(20 * (moveX - 1), 20 * (moveY - 1), 20 * moveX, 20 * moveY);
			if (map[moveY - 1][moveX] == 1) {
				--moveY;
				++stepNum;
			}
		}
		if (key == 's') {
			resKey = 's';
			setfillcolor(BLACK);
			fillrectangle(20 * (moveX - 1), 20 * (moveY - 1), 20 * moveX, 20 * moveY);
			if (map[moveY + 1][moveX] == 1) {
				++moveY;
				++stepNum;
			}
			//minWin(stepNum, key);
		}
		if (key == 'a') {
			resKey = 'a';
			setfillcolor(BLACK);
			fillrectangle(20 * (moveX - 1), 20 * (moveY - 1), 20 * moveX, 20 * moveY);
			if (map[moveY][moveX - 1] == 1) {
				--moveX;
				++stepNum;
			}
			//minWin(stepNum, key);
		}
		if (key == 'd') {
			resKey = 'd';
			setfillcolor(BLACK);
			fillrectangle(20 * (moveX - 1), 20 * (moveY - 1), 20 * moveX, 20 * moveY);
			if (map[moveY][moveX + 1] == 1) {
				++moveX;
				++stepNum;
			}
			//minWin(stepNum, key);
		}

		if (checkTerminus(moveX,moveY,endX,endY)) {
			settextstyle(LH*3, LW, _T("隶书"));
			outtextxy((LW/2)*20-(LW*2), (LH / 2) * 20, _T("游戏结束！"));
			system("pause");
			return;
		}
		minWin(stepNum, resKey);


	}
	



}



void game(int mod) {

	srand((unsigned)time(NULL));

	//创建窗口
	initgraph(LW * 20+200, LH * 20, SHOWCONSOLE);
	//setbkcolor(RGB(30, 30, 30));
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	
	if (mod == 0) {
		primDraw();
	}
	else if (mod == 1) {
		dfsDraw(map, startX, startY);

	}
	controller();

	menu();
}

//菜单
void menu() {
	initgraph(500, 300);
	setbkcolor(RGB(45, 45, 48));
	cleardevice();
	setlinecolor(WHITE);
	settextcolor(WHITE);
	settextstyle(42, 20, _T("隶书"));
	outtextxy(180, 40, _T("走迷宫"));
	outtextxy(125, 100, _T("Prim算法生成"));
	outtextxy(140, 170, _T("BFS算法生成"));

	//画框
	rectangle(110, 95, 380, 145);
	rectangle(110, 160, 380, 220);


	MOUSEMSG m;
	while (true) {
		m = GetMouseMsg();
		if (m.x > 110 && m.y > 95 && m.x < 380 && m.y < 145) {
			settextcolor(RED);
			setlinecolor(RED);
			
			outtextxy(125, 100, _T("Prim算法生成"));

			//画框
			rectangle(110, 95, 380, 145);

			if (m.uMsg == WM_LBUTTONDOWN) {
				game(0);
				return;
			}

		}
		else {
			setlinecolor(WHITE);
			settextcolor(WHITE);
			outtextxy(125, 100, _T("Prim算法生成"));
			//画框
			rectangle(110, 95, 380, 145);
		}

		if (m.x > 110 && m.y > 160 && m.x < 380 && m.y < 220) {
			settextcolor(RED);
			setlinecolor(RED);
			outtextxy(140, 170, _T("BFS算法生成"));
			//画框
			rectangle(110, 160, 380, 220);

			if (m.uMsg == WM_LBUTTONDOWN) {
				game(1);
				return;
			}
		}
		else {
			setlinecolor(WHITE);
			settextcolor(WHITE);
			outtextxy(140, 170, _T("BFS算法生成"));
			//画框
			rectangle(110, 160, 380, 220);
		}
	}



}

int main() {

	menu();
	//game();
	
	return 0;
}