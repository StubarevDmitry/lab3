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
	//�������� ����� ��������� ������ �������
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
	//���������� � ������ ����������� ����������
	Life();
	//���������� � ������ ����������� ���������� �� ����� .life
	Life(std::string fileName);
	//tick = infinite 
	void Run();
	//tick = 1
	void OneStep();
	//tick = n
	void FewSteps(int n);
	//��������� ������� ������� ��� ���������� ����� � ���� ������, � ������ ���
	void CheckRule();
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

void Launch();
//��������� ����
void Play(bool isFile, std::string file);
//���� ����� x, �� ������ mod
int Module(int x, int mod);