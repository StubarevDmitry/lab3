#pragma once
#include "GameOfLife.h"


class OfflineComands {
public:
	OfflineComands(char* allComnds[]);
	//Выполнение команд
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
	//Выбирает какие комоманды сейчас введены
	void ComandParametrs();
	//Выполнение команд
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

////определяет как и в каком режиме будет запущена игра
//void Launch(int argc, char* argv[]);
////Запускает игру
//void Play(bool isFile, std::string file);