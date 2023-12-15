#pragma once
#include <fstream>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;


class BoardParameters {
public:
	//состаяние вокруг клетки
	int PointEnvironment(size_t x, size_t y);
	void WriteToCell(size_t x, size_t y, int i);
	int StateInTheCell(size_t x, size_t y);
	int GetBirth();
	void SetBirth(int i);
	std::string GetSurvival();
	void SetSurvival(std::string str);
private:
	//количество клеток для рожения новой
	int birth = 3;
	//количество клеток для выживания
	std::string survival = "23";
	char board[sizeY][sizeX];
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
	void OneStepAndPrint();
	//tick = n
	void FewStepsAndPrint(int n);
	//проверяет нужноли создать или уничтожить жизнь в этой клетке, и делает это
	void CheckRuleAndStep();
	//вывод изображения в терминал
	void Print();
	//Количество живых клеток
	int CountLife();
	//Есть ли жизнь в клетке
	bool IsLife(size_t x, size_t y);
	void SaveLifeInFile(std::string fileName);
	void Help();
private:
	BoardParameters board;
};
//определяет как и в каком режиме будет запущена игра
void Launch(int argc, char* argv[]);
//Запускает игру
void Play(bool isFile, std::string file);
//Берёт число x, по модулю mod
int Module(int x, int mod);