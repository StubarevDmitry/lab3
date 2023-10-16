#pragma once
//#include <string.h>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;

class Comands {
public:
	//¬ыбирает какие комоманды сейчас введены
	void ComandParametrs();
	void ExecutionOfCommands();
private:
	std::string fileName;
	bool isDump = false;
	bool isTick = false;
	bool exit = false;
	int tick = 1;
};

class Life {
public:
	//записывает в массив начачальные показатели из файла .life
	//записывает в массив начачальные показатели
	Life();
	//запускает код
	void Run();
	void OneStep();
	void FewSteps(int n);
	//провер€ет нужноли создать или уничтожить жизнь в этой клетке, и делает это
	void CheckRule();
	//вывод изображени€ в терминал
	void Print();
	// оличество живых клеток
	int CountLife();
	bool IsLife(int x, int y);
	void SaveLifeInFile(std::string fileName);
private:
	//количество клеток дл€ рожени€ новой
	int birth = 2;
	//количество клеток дл€ выживани€
	std::string survival = "23";
	char board[sizeY][sizeX];
};

//«апускает игру
void Play();
//ЅерЄт число x, по модулю mod
int Modul(int x, int mod);