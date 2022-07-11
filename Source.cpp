#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include "CC212SGL.h"
#include <Windows.h>
#include <conio.h>
#pragma comment(lib,"CC212SGL.lib")
// This function is to reset the game//
void reset(char board[3][4]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '-';
		}
	}

}
//-----------Check if coloum is empty---------//
int checkcoloum(char board[3][4], int x) {
	if (board[0][x] == '-' || board[1][x] == '-' || board[2][x] == '-')
		return 1;
	else
		return 0;
}
/* ---- - Generating a random number-------- - */
int random() {
	int i;
	srand(time(NULL));
	i = rand() % 3;
	return i;
}
//----------New experimental functions--------------//
//----new win------//
int check_h(int arr[]) {
	if (arr[0] == arr[3] && arr[3] == arr[6] && arr[0] != 0)
		return 1;
	if (arr[1] == arr[4] && arr[4] == arr[7] && arr[1] != 0)
		return 2;
	if (arr[2] == arr[5] && arr[5] == arr[8] && arr[2] != 0)
		return 3;
	return 0;
}
int check_v(int arr[]) {
	if (arr[0] == arr[1] && arr[1] == arr[2] && arr[0] != 0)
		return 1;
	if (arr[3] == arr[4] && arr[4] == arr[5] && arr[3] != 0)
		return 2;
	if (arr[6] == arr[7] && arr[7] == arr[8] && arr[6] != 0)
		return 3;
	return 0;
}
int check_d(int arr[]) {
	if (arr[0] == arr[4] && arr[4] == arr[8] && arr[0] != 0)
		return 1;
	if (arr[6] == arr[4] && arr[4] == arr[2] && arr[6] != 0)
		return 2;
	return 0;
}

void main() {
	int x[9] = { 0 }, o[9] = { 0 }, turn = 0, ox = 150, oy = 150, mx, my, p1 = 0, p2 = 0, won = 3, x1/*0=x won and 1= o won*/;
	int input[2];
	char board[3][4] = { {'-','-','-'},{'-','-','-'},{'-','-','-'} };
	char turn1;
	int boardpc[3][3] = { {1,4,7},{2,5,8},{3,6,9} };
	POINT cursorPostition;
	CC212SGL g;
	g.setup(true);
	DWORD width = GetSystemMetrics(SM_CXSCREEN);
	DWORD height = GetSystemMetrics(SM_CYSCREEN);
	DEVMODE screenres;

	screenres.dmPelsWidth = 1024;
	screenres.dmPelsHeight = 768;
	screenres.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	screenres.dmSize = sizeof(DEVMODE);
	long result = ChangeDisplaySettings(&screenres, 0);
	g.setFullScreenMode();
	while (true) {
		g.beginDraw();
		g.setDrawingColor(RGB(255, 255, 255));
		g.setFontSizeAndBoldness(60, 100);
		g.drawText(150, 200, "Hello , This is Tic Tac Toe game ");
		g.setFontSizeAndBoldness(50, 500);
		g.drawText(230, 350, "Press any key to start the game");

		if (kbhit())
			break;
		g.endDraw();
	}
	while (true) {
		g.beginDraw();
		g.setDrawingColor(RGB(255, 255, 255));
		g.setFontSizeAndBoldness(50, 10);
		g.drawText(235, 200, "Choose The Number of Players");
		g.setDrawingColor(RGB(255, 0, 0));
		g.setFontSizeAndBoldness(50, 200);
		g.drawText(427, 354, "1P");
		g.drawText(547, 354, "2P");
		g.setDrawingColor(RGB(0, 0, 255));
		g.setDrawingThickness(15);
		g.drawRectangle(382, 314, 260, 140);
		g.setDrawingColor(RGB(0, 255, 0));
		g.setDrawingThickness(10);
		g.drawRectangle(402, 334, 100, 100);
		g.drawRectangle(522, 334, 100, 100);

		if (kbhit()) {
			if (GetAsyncKeyState(VK_LBUTTON)) {
				GetCursorPos(&cursorPostition);

				mx = cursorPostition.x;
				my = cursorPostition.y;
				if (mx < 502 && mx>402 && my > 334 && my < 434) {
					p1 = 1;
					break;
				}
				if (mx < 622 && mx>522 && my > 334 && my < 434) {
					p2 = 1;
					break;
				}
			}
		}

		g.endDraw();
	}

	while (p1 == 1) {

		g.beginDraw();
		g.setDrawingColor(RGB(255, 0, 0));
		g.drawSolidRectangle(821, 263, 100, 50);
		g.setDrawingColor(RGB(255, 255, 255));
		g.setFontSizeAndBoldness(40, 500);
		g.drawText(825, 270, "Reset");
		g.setDrawingColor(RGB(255, 0, 0));
		g.drawSolidRectangle(821, 333, 100, 50);
		g.setDrawingColor(RGB(255, 255, 255));
		g.setFontSizeAndBoldness(40, 500);
		g.drawText(840, 340, "Exit");

		if (turn % 2 == 0 && turn < 10) {

			//Checking if O won or not;
			if (check_h(o) || check_v(o) || check_d(o)) {
				won = 1;
				g.setDrawingColor(RGB(255, 255, 255));
				g.setFontSizeAndBoldness(35, 50);
				g.drawText(730, 100, "O won The Game");
				for (int d = 1, dy = 200, dx = 200; d < 4; d++) {
					if (check_h(o) == d) {
						g.setDrawingColor(RGB(255, 255, 255));
						g.setDrawingThickness(15);
						g.drawLine(120, dy, 680, dy);
					}
					else {
						dy += 200;
					}
					if (check_v(o) == d) {
						g.setDrawingColor(RGB(255, 255, 255));
						g.setDrawingThickness(15);
						g.drawLine(dx, 200, dx, 650);
					}
					else {
						dx += 200;
					}


				}
				if (check_d(o) == 1) {
					g.setDrawingColor(RGB(255, 255, 255));
					g.setDrawingThickness(15);
					g.drawLine(100, 100, 700, 700);
				}
				else if (check_d(o) == 2) {
					g.setDrawingColor(RGB(255, 255, 255));
					g.setDrawingThickness(15);
					g.drawLine(700, 100, 100, 700);
				}

			}
			else {
				g.setDrawingColor(RGB(255, 255, 255));
				g.setFontSizeAndBoldness(50, 50);
				g.drawText(800, 100, "X-Turn");
				turn1 = 'X';
			}

		}
		else if (turn % 2 != 0 && turn < 10) {

			//Checking if x won or not;
			if (check_h(x) || check_v(x) || check_d(x)) {
				won = 1;
				g.setDrawingColor(RGB(255, 255, 255));
				g.setFontSizeAndBoldness(35, 50);
				g.drawText(730, 100, "X won The Game");
				turn = 9;
				for (int d = 1, dy = 200, dx = 200; d < 4; d++) {
					if (check_h(x) == d) {
						g.setDrawingColor(RGB(255, 255, 255));
						g.setDrawingThickness(15);
						g.drawLine(120, dy, 680, dy);
					}
					else {
						dy += 200;
					}
					if (check_v(x) == d) {
						g.setDrawingColor(RGB(255, 255, 255));
						g.setDrawingThickness(15);
						g.drawLine(dx, 150, dx, 650);
					}
					else {
						dx += 200;
					}


				}
				if (check_d(x) == 1) {
					g.setDrawingColor(RGB(255, 255, 255));
					g.setDrawingThickness(15);
					g.drawLine(100, 100, 700, 700);
				}
				else if (check_d(x) == 2) {
					g.setDrawingColor(RGB(255, 255, 255));
					g.setDrawingThickness(15);
					g.drawLine(700, 100, 100, 700);
				}

			}
			else if (turn < 9) {
				g.setDrawingColor(RGB(255, 255, 255));
				g.setFontSizeAndBoldness(50, 50);
				g.drawText(800, 100, "O-Turn");
				turn1 = 'O';


			}

		}
		if (turn % 2 != 0 && turn < 9) {
			x1 = random();
			int ocheck = 0;
			if (checkcoloum(board, x1) == 1) {
				if (x1 == 2) {
					ocheck = 6;
				}
				else if (x1 == 1) {
					ocheck = 3;
				}
				for (int p = 0; p < 3; p++) {
					if (o[ocheck] != 1 && x[ocheck] != 1) {
						board[p][x1] = turn1;
						o[ocheck] = 1;
						turn++;
						break;
					}
					ocheck++;
				}

			}
			else if (x1 > 1) {
				ocheck = 6;
				for (int n = 0; n < 2; n++) {
					x1--;
					ocheck -= 3;
					if (checkcoloum(board, x1) == 1) {
						for (int p = 0; p < 3; p++) {
							if (o[ocheck] != 1 && x[ocheck] != 1) {
								board[p][x1] = turn1;
								o[ocheck] = 1;
								turn++;
								break;
							}
							ocheck++;
						}
						break;
					}
				}

			}
			else if (x1 > 0) {
				x1--;
				ocheck = 0;
				if (checkcoloum(board, x1) == 1) {
					for (int p = 0; p < 3; p++) {
						if (o[ocheck] != 1 && x[ocheck] != 1) {
							board[p][x1] = turn1;
							o[ocheck] = 1;
							turn++;
							break;
						}
						ocheck++;
					}
				}
				else {
					ocheck = 6;
					x1 += 2;
					if (checkcoloum(board, x1) == 1) {
						for (int p = 0; p < 3; p++) {
							if (o[ocheck] != 1 && x[ocheck] != 1) {
								o[ocheck] = 1;
								board[p][x1] = turn1;
								turn++;
								break;
							}
							ocheck++;
						}
					}
				}
			}
			else {
				ocheck = 0;
				for (int n = 0; n < 2; n++) {
					x1++;
					ocheck += 3;
					if (checkcoloum(board, x1) == 1) {
						for (int p = 0; p < 3; p++) {
							if (o[ocheck] != 1 && x[ocheck] != 1) {
								o[ocheck] = 1;
								board[p][x1] = turn1;
								turn++;
								break;
							}
							ocheck++;
						}
						break;
					}
				}

			}



		}
		if (turn == 9 && won != 1) {
			g.setDrawingColor(RGB(255, 255, 255));
			g.setFontSizeAndBoldness(70, 50);
			g.drawText(800, 100, "DRAW");
		}


		g.hideCursor();

		g.setDrawingColor(RGB(0, 0, 255));
		g.setDrawingThickness(20);
		g.drawRectangle(100, 100, 600, 600);
		g.setDrawingColor(RGB(0, 255, 0));
		g.setDrawingThickness(10);
		g.drawLine(300, 115, 300, 685);
		g.drawLine(500, 115, 500, 685);
		g.drawLine(115, 300, 685, 300);
		g.drawLine(115, 500, 685, 500);


		g.setDrawingColor(RGB(255, 0, 0));
		g.setDrawingThickness(15);
		for (int z = 0; z < 9; z++) {

			if (z < 3) {
				if (x[z] == 1) {
					g.drawLine(ox, oy, ox + 100, oy + 100);
					g.drawLine(ox + 100, oy, ox, oy + 100);
				}
				if (o[z] == 1) {
					g.drawCircle(ox, oy, 100);
				}
				if (z == 2) {
					ox = 350;
					oy = 150;
				}
				else {
					oy += 200;
				}
			}
			if (z > 2 && z < 6) {
				if (x[z] == 1) {
					g.drawLine(ox, oy, ox + 100, oy + 100);
					g.drawLine(ox + 100, oy, ox, oy + 100);
				}
				if (o[z] == 1) {
					g.drawCircle(ox, oy, 100);
				}
				if (z == 5) {
					ox = 550;
					oy = 150;
				}
				else {
					oy += 200;
				}
			}
			if (z > 5) {
				if (x[z] == 1) {
					g.drawLine(ox, oy, ox + 100, oy + 100);
					g.drawLine(ox + 100, oy, ox, oy + 100);
				}
				if (o[z] == 1) {
					g.drawCircle(ox, oy, 100);
				}
				if (z == 8) {
					ox = 150;
					oy = 150;
				}
				else {
					oy += 200;
				}
			}
		}

		if (kbhit()) {

			GetCursorPos(&cursorPostition);

			mx = cursorPostition.x;
			my = cursorPostition.y;
			if (GetAsyncKeyState(VK_LBUTTON)) {
				if (mx > 820 && mx < 922 && my>262 && my < 314) {
					reset(board);
					for (int u = 0; u < 9; u++) {
						x[u] = 0;
						o[u] = 0;
					}
					turn = 0;
					won = 3;
				}
				if (mx > 820 && mx < 922 && my>334 && my < 384) {

					screenres.dmPelsWidth = width;
					screenres.dmPelsHeight = height;
					long result = ChangeDisplaySettings(&screenres, 0);
					g.showCursor();
					g.setWindowScreenMode();
					exit(0);
				}
				if (won > 1) {
					if (mx > 100 && mx < 300) {
						if (my > 100 && my < 300) {
							if (turn % 2 == 0) {
								if (o[0] != 1 && x[0] != 1) {
									x[0] = 1;
									input[0] = 0;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}

						if (my > 300 && my < 500) {
							if (turn % 2 == 0) {
								if (o[1] != 1 && x[1] != 1) {
									x[1] = 1;
									input[0] = 1;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}

						if (my > 500 && my < 700) {
							if (turn % 2 == 0) {
								if (o[2] != 1 && x[2] != 1) {
									x[2] = 1;
									input[0] = 2;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}
					}
					if (mx > 300 && mx < 500) {
						if (my > 100 && my < 300) {
							if (turn % 2 == 0) {
								if (o[3] != 1 && x[3] != 1) {
									x[3] = 1;
									input[0] = 0;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}
						if (my > 300 && my < 500) {
							if (turn % 2 == 0) {
								if (o[4] != 1 && x[4] != 1) {
									x[4] = 1;
									input[0] = 1;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}
						if (my > 500 && my < 700) {
							if (turn % 2 == 0) {
								if (o[5] != 1 && x[5] != 1) {
									x[5] = 1;
									input[0] = 2;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}
					}
					if (mx > 500 && mx < 700) {
						if (my > 100 && my < 300) {
							if (turn % 2 == 0) {
								if (o[6] != 1 && x[6] != 1) {
									x[6] = 1;
									input[0] = 0;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}
						if (my > 300 && my < 500) {
							if (turn % 2 == 0) {
								if (o[7] != 1 && x[7] != 1) {
									x[7] = 1;
									input[0] = 1;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}
						if (my > 500 && my < 700) {
							if (turn % 2 == 0) {
								if (o[8] != 1 && x[8] != 1) {
									x[8] = 1;
									input[0] = 2;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}

						}
					}

				}


			}
		}

		g.endDraw();


	}

	while (p2 == 1) {
		g.beginDraw();
		g.setDrawingColor(RGB(255, 0, 0));
		g.drawSolidRectangle(821, 263, 100, 50);
		g.setDrawingColor(RGB(255, 255, 255));
		g.setFontSizeAndBoldness(40, 500);
		g.drawText(825, 270, "Reset");
		g.setDrawingColor(RGB(255, 0, 0));
		g.drawSolidRectangle(821, 333, 100, 50);
		g.setDrawingColor(RGB(255, 255, 255));
		g.setFontSizeAndBoldness(40, 500);
		g.drawText(840, 340, "Exit");

		if (turn % 2 == 0 && turn < 9) {

			//Checking if O won or not;
			if (check_h(o) || check_v(o) || check_d(o)) {
				won = 1;
				g.setDrawingColor(RGB(255, 255, 255));
				g.setFontSizeAndBoldness(35, 50);
				g.drawText(730, 100, "O won The Game");
				for (int d = 1, dy = 200, dx = 200; d < 4; d++) {
					if (check_h(o) == d) {
						g.setDrawingColor(RGB(255, 255, 255));
						g.setDrawingThickness(15);
						g.drawLine(120, dy, 680, dy);
					}
					else {
						dy += 200;
					}
					if (check_v(o) == d) {
						g.setDrawingColor(RGB(255, 255, 255));
						g.setDrawingThickness(15);
						g.drawLine(dx, 200, dx, 650);
					}
					else {
						dx += 200;
					}


				}
				if (check_d(o) == 1) {
					g.setDrawingColor(RGB(255, 255, 255));
					g.setDrawingThickness(15);
					g.drawLine(100, 100, 700, 700);
				}
				else if (check_d(o) == 2) {
					g.setDrawingColor(RGB(255, 255, 255));
					g.setDrawingThickness(15);
					g.drawLine(700, 100, 100, 700);
				}

			}
			else {
				g.setDrawingColor(RGB(255, 255, 255));
				g.setFontSizeAndBoldness(50, 50);
				g.drawText(800, 100, "X-Turn");
				turn1 = 'X';
			}

		}
		else if (turn % 2 != 0 && turn < 10) {

			//Checking if x won or not;
			if (check_h(x) || check_v(x) || check_d(x)) {
				won = 0;
				g.setDrawingColor(RGB(255, 255, 255));
				g.setFontSizeAndBoldness(35, 50);
				g.drawText(730, 100, "X won The Game");
				for (int d = 1, dy = 200, dx = 200; d < 4; d++) {
					if (check_h(x) == d) {
						g.setDrawingColor(RGB(255, 255, 255));
						g.setDrawingThickness(15);
						g.drawLine(120, dy, 680, dy);
					}
					else {
						dy += 200;
					}
					if (check_v(x) == d) {
						g.setDrawingColor(RGB(255, 255, 255));
						g.setDrawingThickness(15);
						g.drawLine(dx, 150, dx, 650);
					}
					else {
						dx += 200;
					}


				}
				if (check_d(x) == 1) {
					g.setDrawingColor(RGB(255, 255, 255));
					g.setDrawingThickness(15);
					g.drawLine(100, 100, 700, 700);
				}
				else if (check_d(x) == 2) {
					g.setDrawingColor(RGB(255, 255, 255));
					g.setDrawingThickness(15);
					g.drawLine(700, 100, 100, 700);
				}

			}
			else if (turn < 9) {
				g.setDrawingColor(RGB(255, 255, 255));
				g.setFontSizeAndBoldness(50, 50);
				g.drawText(800, 100, "O-Turn");
				turn1 = 'O';
			}
		}
		if (turn == 9 && won != 0) {
			g.setDrawingColor(RGB(255, 255, 255));
			g.setFontSizeAndBoldness(70, 50);
			g.drawText(800, 100, "DRAW");
		}


		g.hideCursor();

		g.setDrawingColor(RGB(0, 0, 255));
		g.setDrawingThickness(20);
		g.drawRectangle(100, 100, 600, 600);
		g.setDrawingColor(RGB(0, 255, 0));
		g.setDrawingThickness(10);
		g.drawLine(300, 115, 300, 685);
		g.drawLine(500, 115, 500, 685);
		g.drawLine(115, 300, 685, 300);
		g.drawLine(115, 500, 685, 500);


		g.setDrawingColor(RGB(255, 0, 0));
		g.setDrawingThickness(15);
		for (int z = 0; z < 9; z++) {

			if (z < 3) {
				if (x[z] == 1) {
					g.drawLine(ox, oy, ox + 100, oy + 100);
					g.drawLine(ox + 100, oy, ox, oy + 100);
				}
				if (o[z] == 1) {
					g.drawCircle(ox, oy, 100);
				}
				if (z == 2) {
					ox = 350;
					oy = 150;
				}
				else {
					oy += 200;
				}
			}
			if (z > 2 && z < 6) {
				if (x[z] == 1) {
					g.drawLine(ox, oy, ox + 100, oy + 100);
					g.drawLine(ox + 100, oy, ox, oy + 100);
				}
				if (o[z] == 1) {
					g.drawCircle(ox, oy, 100);
				}
				if (z == 5) {
					ox = 550;
					oy = 150;
				}
				else {
					oy += 200;
				}
			}
			if (z > 5) {
				if (x[z] == 1) {
					g.drawLine(ox, oy, ox + 100, oy + 100);
					g.drawLine(ox + 100, oy, ox, oy + 100);
				}
				if (o[z] == 1) {
					g.drawCircle(ox, oy, 100);
				}
				if (z == 8) {
					ox = 150;
					oy = 150;
				}
				else {
					oy += 200;
				}
			}
		}

		if (kbhit()) {
			GetCursorPos(&cursorPostition);

			mx = cursorPostition.x;
			my = cursorPostition.y;
			if (GetAsyncKeyState(VK_LBUTTON)) {
				if (mx > 820 && mx < 922 && my>262 && my < 314) {
					reset(board);
					for (int u = 0; u < 9; u++) {
						x[u] = 0;
						o[u] = 0;
					}
					turn = 0;
					won = 3;
				}

				if (mx > 820 && mx < 922 && my>334 && my < 384) {

					screenres.dmPelsWidth = width;
					screenres.dmPelsHeight = height;
					long result = ChangeDisplaySettings(&screenres, 0);
					g.showCursor();
					g.setWindowScreenMode();
					exit(0);

				}
				if (won > 1) {
					if (mx > 100 && mx < 300) {
						if (my > 100 && my < 300) {
							if (turn % 2 == 0) {
								if (o[0] != 1 && x[0] != 1) {
									x[0] = 1;
									input[0] = 0;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (x[0] != 1 && o[0] != 1) {
									o[0] = 1;
									input[0] = 0;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
						}

						if (my > 300 && my < 500) {
							if (turn % 2 == 0) {
								if (o[1] != 1 && x[1] != 1) {
									x[1] = 1;
									input[0] = 1;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (o[1] != 1 && x[1] != 1) {
									o[1] = 1;
									input[0] = 1;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
						}

						if (my > 500 && my < 700) {
							if (turn % 2 == 0) {
								if (o[2] != 1 && x[2] != 1) {
									x[2] = 1;
									input[0] = 2;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (o[2] != 1 && x[2] != 1) {
									o[2] = 1;
									input[0] = 2;
									input[1] = 0;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
						}
					}
					if (mx > 300 && mx < 500) {
						if (my > 100 && my < 300) {
							if (turn % 2 == 0) {
								if (o[3] != 1 && x[3] != 1) {
									x[3] = 1;
									input[0] = 0;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (o[3] != 1 && x[3] != 1) {
									o[3] = 1;
									input[0] = 0;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
						}
						if (my > 300 && my < 500) {
							if (turn % 2 == 0) {
								if (o[4] != 1 && x[4] != 1) {
									x[4] = 1;
									input[0] = 1;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (o[4] != 1 && x[4] != 1) {
									o[4] = 1;
									input[0] = 1;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
						}
						if (my > 500 && my < 700) {
							if (turn % 2 == 0) {
								if (o[5] != 1 && x[5] != 1) {
									x[5] = 1;
									input[0] = 2;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (o[5] != 1 && x[5] != 1) {
									o[5] = 1;
									input[0] = 2;
									input[1] = 1;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
						}
					}
					if (mx > 500 && mx < 700) {
						if (my > 100 && my < 300) {
							if (turn % 2 == 0) {
								if (o[6] != 1 && x[6] != 1) {
									x[6] = 1;
									input[0] = 0;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (o[6] != 1 && x[6] != 1) {
									o[6] = 1;
									input[0] = 0;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
						}
						if (my > 300 && my < 500) {
							if (turn % 2 == 0) {
								if (o[7] != 1 && x[7] != 1) {
									x[7] = 1;
									input[0] = 1;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (o[7] != 1 && x[7] != 1) {
									o[7] = 1;
									turn++;
									input[0] = 1;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;
								}
							}
						}
						if (my > 500 && my < 700) {
							if (turn % 2 == 0) {
								if (o[8] != 1 && x[8] != 1) {
									x[8] = 1;
									input[0] = 2;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;
									turn++;
								}
							}
							else {
								if (o[8] != 1 && x[8] != 1) {
									o[8] = 1;
									input[0] = 2;
									input[1] = 2;
									board[input[0]][input[1]] = turn1;

									turn++;
								}
							}
						}
					}

				}


			}
		}
		g.endDraw();

	}



}
