#pragma once
//#include <string.h>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;

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
	//вывод изображени€ в терминал
	void Print();
	//количество клеток дл€ рожени€ новой
	int Birth();
	//количество клеток дл€ выживани€
	std::string Survival();
	// оличество живых клеток
	int CountLife();
	bool IsLife(int x, int y);
private:
	//количество клеток дл€ рожени€ новой
	int birth = 2;
	//количество клеток дл€ выживани€
	std::string survival = "23";
	char board[sizeY][sizeX];
};

//«апускает игру
void Play();
//интерфейс и выполнение команд
void LifeOrganization();
//¬ыбирает какие комоманды сейчас введены
void Comand();
//ЅерЄт число x, по модулю mod
int Modul(int x, int mod);