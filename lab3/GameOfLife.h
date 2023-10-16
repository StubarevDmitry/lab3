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
	//проверяет нужноли создать или уничтожить жизнь в этой клетке, и делает это
	void CheckRule();
	//вывод изображения в терминал
	void Print();
	//количество клеток для рожения новой
	int Birth();
	//количество клеток для выживания
	std::string Survival();
private:
	//количество клеток для рожения новой
	int birth = 2;
	//количество клеток для выживания
	string survival = "23";
	char board[sizeY][sizeX];
};

//Запускает игру
void Play();
//интерфейс и выполнение команд
void LifeOrganization();
//Выбирает какие комоманды сейчас введены
void Comand();
//Берёт число x, по модулю mod
int Modul(int x, int mod);