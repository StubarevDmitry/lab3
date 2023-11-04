#pragma once
//#include <string.h>
#include <fstream>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;

class Comands {
public:
	Comands();
	Comands(bool fileExists, std::string ReadFileName);
	//¬ыбирает какие комоманды сейчас введены
	void ComandParametrs();
	void ExecutionOfCommands();
private:
	bool fileExists;
	std::string readFileName;
	std::string recordFileName;
	bool isSave = false;
	bool isTick = false;
	bool isHelp = false;
	bool exit = false;
	int tick = 1;
};

class Life {
public:
	//записывает в массив начачальные показатели
	Life();
	//записывает в массив начачальные показатели из файла .life
	Life(std::string fileName);
	//tick = infinite 
	void Run();
	//tick = 1
	void OneStep();
	//tick = n
	void FewSteps(int n);
	//провер€ет нужноли создать или уничтожить жизнь в этой клетке, и делает это
	void CheckRule();
	//вывод изображени€ в терминал
	void Print();
	// оличество живых клеток
	int CountLife();
	//≈сть ли жизнь в клетке
	bool IsLife(int x, int y);
	void SaveLifeInFile(std::string fileName);
	void Help();
private:
	//количество клеток дл€ рожени€ новой
	int birth = 2;
	//количество клеток дл€ выживани€
	std::string survival = "23";
	char board[sizeY][sizeX];
};

void Launch();
//«апускает игру
void Play(bool isFile, std::string file);
//ЅерЄт число x, по модулю mod
int Module(int x, int mod);