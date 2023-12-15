#include "GameOfLife.h"
#include "Comands.h"
#include <fstream>
#include "windows.h"
#include <iostream>
#include <thread>

Life::Life(std::string fileName) {
	std::ifstream in(fileName);
	std::string str1Part1, str1Part2;
	in >> str1Part1 >> str1Part2;
	if ("#Life" != str1Part1 || str1Part2 != "1.06") {
		in.close();
		Life();
		return;
	}
	std::string str2Part1, str2Part2;
	in >> str2Part1 >> str2Part2;
	if ("#N" != str2Part1 || fileName != str2Part2) {
		in.close();
		Life();
		return;
	}
	std::string str3Part1, str3Part2, str3Part3;
	in >> str3Part1 >> str3Part2;
	if ("#R" != str3Part1 ) {
		in.close();
		Life();
		return;
	}
	int x, y;
	for (size_t i = 0; i < sizeY; i++)
	{
		for (size_t j = 0; j < sizeX; j++)
		{
			board.WriteToCell(j, i, 0);
		}
	}
	while (in >> x >> y) {
		board.WriteToCell(x, y, 1);
	}
}

Life::Life() {
	for (size_t i = 0; i < sizeY; i++)
	{
		for (size_t j = 0; j < sizeX; j++)
		{
			board.WriteToCell(j, i, 0);
			//board[i][j] = 0;
		}
	}
	board.WriteToCell(10, 10, 1);
	board.WriteToCell(10, 11, 1);
	board.WriteToCell(10, 9, 1);
	board.WriteToCell(9, 9, 1);
	board.WriteToCell(8, 10, 1);
	board.WriteToCell(15, 10, 1);
	board.WriteToCell(16, 10, 1);
	board.WriteToCell(15, 11, 1);
	board.WriteToCell(16, 11, 1);
	Print();
}

void Launch(int argc, char* argv[]) {
	if(argc == 7){
		OfflineComands offline(argv);
		offline.ExecutionOfCommands();
	}
	else {
		std::string yesOrNo;
		setlocale(LC_ALL, "Russian");
	tryAgain:
		std::cout << "’отите открыть файл YES/NO:";
		std::cin >> yesOrNo;
		if (yesOrNo == "YES") {
			std::cout << "\n";
			std::cout << "¬ведите название файла:";
			std::string fileName;
			std::cin >> fileName;
			std::ifstream in(fileName);
			if (in.is_open()) {
				in.close();
				Play(true, fileName);
			}
			else {
				in.close();
				Play(false, "");
			}
		}
		else if (yesOrNo == "NO") {
			Play(false, "");
		}
		else {
			std::cout << "\n";
			goto tryAgain;
		}
	}
}

void Play(bool fileExists, std::string file) {
	OnlineComands *mainComand;
	if (fileExists) {
		mainComand = new OnlineComands(fileExists ,file);
	}
	else {
		mainComand = new OnlineComands();
	}
	std::thread thr1(&OnlineComands::ExecutionOfCommands, mainComand);
	std::thread thr2(&OnlineComands::ComandParametrs, mainComand);
	thr1.join();
	thr2.join();
	delete mainComand;
}

void Life::SaveLifeInFile(std::string fileName) {
	std::ofstream out;
	out.open(fileName);
	if (out.is_open())
	{
		out.clear();
		out << "#Life 1.06" << std::endl;
		out << "#N " << fileName << std::endl;
		out << "#R B" << board.GetBirth() << "/S" << board.GetSurvival() << std::endl;
		for (size_t i = 0; i < sizeY; i++) {
			for (size_t j = 0; j < sizeX; j++) {
				if (IsLife(j, i)) {
					out << j << " " << i << std::endl;
				}
			}
		}
	}
	out.close();
}

void Life::Help() {
	std::cout << "dump filename - сохранить вселенную в файл" << "\n";
	std::cout << "tick 1- рассчитать n (по умолчанию 1) итераций и напечатать результат." << "\n";
	std::cout << "exit Ц завершить игру" << "\n";
}

bool Life::IsLife(size_t x, size_t y) {
	if (board.StateInTheCell(x, y) == 1) {
		return true;
	}
	return false;
}

int Life::CountLife(){
	int count = 0;
	for (size_t i = 0; i < sizeY; i++) {
		for (size_t j = 0; j < sizeX; j++) {
			if (board.StateInTheCell(j, i) == 1) {
				count += 1;
			}
		}
	}
	return count;
}

int Module(int x, int mod) {
	if (x < 0) {
		return x + mod;
	}
	if (x > (mod - 1)) {
		return x - mod;
	}
	return x;
}

void Life::CheckRuleAndStep() {
	char check[sizeY][sizeX];
	for (size_t y = 0; y < sizeY; y++) {
		for (size_t x = 0; x < sizeX; x++) {
			check[y][x] = 0;
			int lifeCount = board.PointEnvironment(x, y);
			if (lifeCount == board.GetBirth() && board.StateInTheCell(x, y) == 0) {
				check[y][x] = 1;
			}
			if ((lifeCount < 2 || lifeCount > 3) && board.StateInTheCell(x, y) == 1) {
				check[y][x] = -1;
			}
		}
	}
	for (size_t y = 0; y < sizeY; y++) {
		for (size_t x = 0; x < sizeX; x++) {
			board.WriteToCell(x, y, board.StateInTheCell(x, y) + check[y][x]);
		}
	}
}

void Life::FewStepsAndPrint(int n) {
	for (size_t i = 0; i < n; i++)
	{
		Sleep(200);
		OneStepAndPrint();
	}
}

void Life::OneStepAndPrint() {
	CheckRuleAndStep();
	Print();
}

void Life::Run() {
	while (true) {
		Sleep(200);
		OneStepAndPrint();
	}
}

void Life::Print(){
	system("cls");
	for (size_t i = 0; i < sizeY; i++)
	{
		for (size_t j = 0; j < sizeX; j++)
		{
			if (IsLife(j, i)) {
				std::cout << "1";
			}
			else{
				std::cout << ".";
			}
		}
		std::cout << "\n";
	}
}

int BoardParameters::PointEnvironment(size_t x, size_t y) {
	int lifeCount = 0;
	for (int i = (int)x - 1; i < (int)x + 2; i++) {
		for (int j = (int)y - 1; j < (int)y + 2; j++) {
			lifeCount += board[Module(j, sizeY)][Module(i, sizeX)];
		}
	}
	lifeCount -= board[y][x];
	return lifeCount;
}

void BoardParameters::WriteToCell(size_t x, size_t y, int i) {
	board[y][x] = i;
}

int BoardParameters::StateInTheCell(size_t x, size_t y) {
	return board[y][x];
}

int BoardParameters::GetBirth() {
	return birth;
}

void BoardParameters::SetBirth(int i) {
	birth = i;
}

std::string BoardParameters::GetSurvival() {
	return survival;
}

void BoardParameters::SetSurvival(std::string str) {
	survival = str;
}