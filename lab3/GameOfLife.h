#pragma once
//#include <string.h>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;

struct ComandParametrs {
	std::string dump;
	bool isDump;
	int tick;
	bool isTick;
	bool exit;
};

class Life
{
public:
	//записывает в массив начачальные показатели из файла .life
	//записывает в массив начачальные показатели
	Life();
	//запускает код
	void Run();
	void OneStep();
	//провер€ет нужноли создать или уничтожить жизнь в этой клетке, и делает это
	void CheckRule();
	void Print();

private:
	//количество клеток дл€ рожени€ новой
	int birth = 2;
	//количество клеток дл€ выживани€
	int survival = 3;
	char board[sizeY][sizeX];
};

//«апускает игру
void Play();

//¬ыбирает какие комоманды сейчас введены
void Comand();

//ЅерЄт число x, по модулю mod
int Modul(int x, int mod);