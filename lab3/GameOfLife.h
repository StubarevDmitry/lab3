#pragma once
#include <fstream>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;


class OfflineComands {
public:
	OfflineComands(std::string allComnds[]);
	void ExecutionOfCommands();
private:
	//bool fileExists;
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

class Life {
public:
	//���������� � ������ ����������� ����������
	Life();
	//���������� � ������ ����������� ���������� �� ����� .life
	Life(std::string fileName);
	//tick = infinite 
	void Run();
	//tick = 1
	void OneStepAndPrint();
	//tick = n
	void FewStepsAndPrint(int n);
	//��������� ������� ������� ��� ���������� ����� � ���� ������, � ������ ���
	void CheckRuleAndStep();
	//����� ����������� � ��������
	void Print();
	//���������� ����� ������
	int CountLife();
	//���� �� ����� � ������
	bool IsLife(int x, int y);
	void SaveLifeInFile(std::string fileName);
	void Help();
private:
	//���������� ������ ��� ������� �����
	int birth = 2;
	//���������� ������ ��� ���������
	std::string survival = "23";
	char board[sizeY][sizeX];
};
//���������� ��� � � ����� ������ ����� �������� ����
void Launch(int argc, std::string argv[]);
//��������� ����
void Play(bool isFile, std::string file);
//���� ����� x, �� ������ mod
int Module(int x, int mod);