#include "GameOfLife.h"
#include <fstream>
#include <iostream>
#include "windows.h"
#include <iostream>
#include <thread>

struct ComandParametrs {
	std::string dump;
	bool isDump = false;
	bool isTick = false;
	bool exit = false;
	int tick = 1;
}ComandParametrs;

void Play() {
	//Life life;
	std::thread thr1(LifeOrganization);
	std::thread thr2(Comand);
	thr1.join();
	thr2.join();
}

void LifeOrganization() {
	Life life;
	while (true)
	{
		if (ComandParametrs.isTick) {
			for (size_t i = 0; i < ComandParametrs.tick; i++)
			{
				Sleep(200);
				life.OneStep();
			}
			ComandParametrs.isTick = false;
			ComandParametrs.tick = 1;
		}
		if (ComandParametrs.isDump) {
			std::ofstream out;
			out.open(ComandParametrs.dump);
			if (out.is_open())
			{
				out.clear();
				out << "#N " << ComandParametrs.dump << std::endl;
				out << "#R B" << life.Birth() << "/S" << life.Survival() << std::endl;
				for (size_t i = 0; i < sizeY; i++) {
					for (size_t j = 0; j < sizeX; j++) {
						if (life.IsLife(j,i) == true) {
							out << j << " " << i << std::endl;
						}
					}
				}
			}
			out.close();
			ComandParametrs.isDump = false;
		}
	}
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

int Life::Birth() {
	return birth;
}

std::string Life::Survival() {
	return survival;
}

void Comand() {
	while (true)
	{
		std::string comand;
		std::string obj;
		std::cin >> comand >> obj;
		if (comand == "exit") {
			ComandParametrs.exit = true;
		}
		if (comand == "tick") {
			ComandParametrs.isTick = true;
			ComandParametrs.tick = stoi(obj);
		}
		if (comand == "dump") {
			ComandParametrs.isDump = true;
			ComandParametrs.dump = obj;
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