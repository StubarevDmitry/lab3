#pragma once
#include "GameOfLife.h"


class OfflineComands {
public:
	OfflineComands(char* allComnds[]);
	//���������� ������
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
	//�������� ����� ��������� ������ �������
	void ComandParametrs();
	//���������� ������
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

////���������� ��� � � ����� ������ ����� �������� ����
//void Launch(int argc, char* argv[]);
////��������� ����
//void Play(bool isFile, std::string file);