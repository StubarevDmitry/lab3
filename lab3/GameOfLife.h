#pragma once
#include <fstream>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;


class OfflineComands {
public:
	OfflineComands(char* allComnds[]);
	//¬ыполнение команд
	void ExecutionOfCommands();
private:
	std::string fileNameForRead;
	std::string fileNameForRecord;
	int tick;
};

class OnlineComands {
public:
	OnlineComands();
	OnlineComands(bool fileExists, std::string FileName);
	//¬ыбирает какие комоманды сейчас введены
	void ComandParametrs();
	//¬ыполнение команд
	void ExecutionOfCommands();
private:
	bool fileExists;
	std::string fileNameForRead;
	std::string fileNameForRecord;
	bool isSave = false;
	bool isTick = false;
	bool isHelp = false;
	bool exit = false;
	int tick = 1;
};

class BoardParameters {
public:
	//соста€ние вокруг клетки
	int PointEnvvironment(size_t x, size_t y);
	void WriteToCell(size_t x, size_t y, int i);
	int StateInTheCell(size_t x, size_t y);
	int GetBirth();
	void SetBirth(int i);
	std::string GetSurvival();
	void SetSurvival(std::string str);
private:
	//количество клеток дл€ рожени€ новой
	int birth = 3;
	//количество клеток дл€ выживани€
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
	//провер€ет нужноли создать или уничтожить жизнь в этой клетке, и делает это
	void CheckRuleAndStep();
	//вывод изображени€ в терминал
	void Print();
	// оличество живых клеток
	int CountLife();
	//≈сть ли жизнь в клетке
	bool IsLife(size_t x, size_t y);
	void SaveLifeInFile(std::string fileName);
	void Help();
private:
	BoardParameters board;
};
//определ€ет как и в каком режиме будет запущена игра
void Launch(int argc, char* argv[]);
//«апускает игру
void Play(bool isFile, std::string file);
//ЅерЄт число x, по модулю mod
int Module(int x, int mod);