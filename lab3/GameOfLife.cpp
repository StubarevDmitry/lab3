#include "GameOfLife.h"
#include <iostream>
#include "windows.h"
#include <thread>

void Play() {
	Life life;
	std::thread thr1(Life::Run, life);
	std::thread thr2();
}

int Modul(int x, int mod) {
	if (x < 0) {
		return x + mod;
	}
	if (x > (mod - 1)) {
		return x - mod;
	}
	return x;
}

Life::Life(){
	for (size_t i = 0; i < sizeY; i++)
	{
		for (size_t j = 0; j < sizeX; j++)
		{
			board[i][j] = 0;
		}
	}
	board[10][10] = 1;
	board[11][10] = 1;
	board[9][10] = 1;
	board[9][9] = 1;
	board[10][8] = 1;
	Print();
}

void Life::CheckRule() {
	char check[sizeY][sizeX];
	for (size_t y = 0; y < sizeY; y++) {
		for (size_t x = 0; x < sizeX; x++) {
			int lifeCount = 0;
			check[y][x] = 0;
			if (y == 0 && x == 10) {
				int a = 3;
			}
			for (int i = (int)x - 1; i < (int)x + 2; i++) {
				for (int j = (int)y - 1; j < (int)y + 2; j++) {
					lifeCount += board[Modul(j, sizeY)][Modul(i, sizeX)];
				}
			}
			lifeCount -= board[y][x];
			if (lifeCount == 3 && board[y][x] == 0) {
				check[y][x] = 1;
			}
			if ((lifeCount < 2 || lifeCount > 3) && board[y][x] == 1) {
				check[y][x] = -1;
			}
		}
	}
	for (size_t y = 0; y < sizeY; y++) {
		for (size_t x = 0; x < sizeX; x++) {
			board[y][x] += check[y][x];
		}
	}
}

void Life::OneStep() {
	CheckRule();
	system("cls");
	Print();
}

void Life::Run() {
	//Print();
	//Sleep(1000);
	while (true) {
		//CheckRule();
		Sleep(200);
		OneStep();
		//system("cls");
		//Print();
	}
}

void Life::Print(){
	for (size_t i = 0; i < sizeY; i++)
	{
		for (size_t j = 0; j < sizeX; j++)
		{
			if (board[i][j] == 1) {
				std::cout << "1";
			}
			else{
				std::cout << ".";
			}
		}
		std::cout << "\n";
	}
}