#include "GameOfLife.h"
#include <fstream>
#include <iostream>
#include "windows.h"
#include <iostream>
#include <thread>

Life::Life() {
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
	board[10][15] = 1;
	board[10][16] = 1;
	board[11][15] = 1;
	board[11][16] = 1;
	Print();
}

void Play() {
	Comands mainComand;
	std::thread thr1(&Comands::ExecutionOfCommands, &mainComand);
	std::thread thr2(&Comands::ComandParametrs, &mainComand);
	thr1.join();
	thr2.join();
}

void Comands::ExecutionOfCommands() {
	Life life;
	while (true)
	{
		if (isTick) {
			life.FewSteps(tick);
			isTick = false;
			tick = 1;
		}
		if (isDump) {
			life.SaveLifeInFile(fileName);
			isDump = false;
		}
	}
}

void Life::SaveLifeInFile(std::string fileName) {
	std::ofstream out;
	out.open(fileName);
	if (out.is_open())
	{
		out.clear();
		out << "#N " << fileName << std::endl;
		out << "#R B" << birth << "/S" << survival << std::endl;
		for (size_t i = 0; i < sizeY; i++) {
			for (size_t j = 0; j < sizeX; j++) {
				if (board[i][j] == 1) {
					out << j << " " << i << std::endl;
				}
			}
		}
	}
	out.close();
}

bool Life::IsLife(int x, int y) {
	if (board[y][x] == 1) {
		return true;
	}
	return false;
}

int Life::CountLife(){
	int count = 0;
	for (size_t i = 0; i < sizeY; i++) {
		for (size_t j = 0; j < sizeX; j++) {
			if (board[i][j] == 1) {
				count += 1;
			}
		}
	}
	return count;
}

void Comands::ComandParametrs() {
	while (true) {
		std::string comand;
		std::string obj;
		std::cin >> comand >> obj;
		if (comand == "exit") {
			exit = true;
		}
		if (comand == "tick") {
			tick = stoi(obj);
			isTick = true;
		}
		if (comand == "dump") {
			fileName = obj;
			isDump = true;
		}
		if (comand == "help") {
		
		}
	}
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

void Life::FewSteps(int n) {
	for (size_t i = 0; i < n; i++)
	{
		Sleep(200);
		OneStep();
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