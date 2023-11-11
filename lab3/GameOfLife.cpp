#include "GameOfLife.h"
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
			board[i][j] = 0;
		}
	}
	while (in >> x >> y) {
		board[y][x] = 1;
	}
	//Print();
}

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

OfflineComands::OfflineComands(std::string allComnds[]) {
	setlocale(LC_ALL, "Russian");
	for (int i = 1; i < 7; i++) {
		if (allComnds[i] == "-o") {
			fileNameForRead = allComnds[i + 1];
		}
		if (allComnds[i] == "-in") {
			fileNameForRecord = allComnds[i + 1];
		}
		if (allComnds[i] == "-i") {
			tick = stoi(allComnds[i + 1]);
		}
	}
}

void OfflineComands::ExecutionOfCommands() {
	fileNameForRead = "sec.life";
	fileNameForRecord = "second.life";
	tick = 30;
	std::ifstream in(fileNameForRead);
	if (in.is_open()) {
		in.close();
		Life life(fileNameForRead);
		for (int i = 0; i < tick; i++) {
			life.CheckRuleAndStep();
		}
		life.SaveLifeInFile(fileNameForRecord);
	}
	else {
		std::cout << "‘айл не был найден";
	}
	in.close();
}

OnlineComands::OnlineComands() : fileExists(false), fileNameForRead("") {}

OnlineComands::OnlineComands(bool fileExists, std::string fileNameForRead): fileExists(fileExists), fileNameForRead(fileNameForRead){}

void Launch(int argc, std::string argv[]) {
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

void OnlineComands::ExecutionOfCommands() {
	Life* life;
	if (fileExists) {
		life = new Life(fileNameForRead);
		life->Print();
	}
	else {
		life = new Life();
		life->Print();
	}
	while (true) {
		if (isTick) {
			life->FewStepsAndPrint(tick);
			isTick = false;
			tick = 1;
		}
		if (isSave) {
			life->SaveLifeInFile(fileNameForRecord);
			isSave = false;
		}
		if (isHelp) {
			life->Help();
			isHelp = false;
		}
	}
	delete life;
}

void Life::SaveLifeInFile(std::string fileName) {
	std::ofstream out;
	out.open(fileName);
	if (out.is_open())
	{
		out.clear();
		out << "#Life 1.06" << std::endl;
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

void Life::Help() {
	std::cout << "dump filename - сохранить вселенную в файл" << "\n";
	std::cout << "tick 1- рассчитать n (по умолчанию 1) итераций и напечатать результат." << "\n";
	std::cout << "exit Ц завершить игру" << "\n";
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

void OnlineComands::ComandParametrs() {
	while (true) {
		std::string comand;
		std::string obj;
		std::cin >> comand;
		if (comand == "exit") {
			exit = true;
		}
		if (comand == "tick") {
			std::cin >> obj;
			tick = stoi(obj);
			isTick = true;
		}
		if (comand == "dump") {
			std::cin >> obj;
			fileNameForRecord = obj;
			isSave = true;
		}
		if (comand == "help") {
			isHelp = true;
		}
	}
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
			int lifeCount = 0;
			check[y][x] = 0;
			if (y == 0 && x == 10) {
				int a = 3;
			}
			for (int i = (int)x - 1; i < (int)x + 2; i++) {
				for (int j = (int)y - 1; j < (int)y + 2; j++) {
					lifeCount += board[Module(j, sizeY)][Module(i, sizeX)];
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
	//Print();
	//Sleep(1000);
	while (true) {
		//CheckRule();
		Sleep(200);
		OneStepAndPrint();
		//system("cls");
		//Print();
	}
}

void Life::Print(){
	system("cls");
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