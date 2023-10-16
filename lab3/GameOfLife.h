#pragma once
//#include <string.h>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;

class Comands {
public:
	//�������� ����� ��������� ������ �������
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
	//���������� � ������ ����������� ���������� �� ����� .life
	//���������� � ������ ����������� ����������
	Life();
	//��������� ���
	void Run();
	void OneStep();
	void FewSteps(int n);
	//��������� ������� ������� ��� ���������� ����� � ���� ������, � ������ ���
	void CheckRule();
	//����� ����������� � ��������
	void Print();
	//���������� ����� ������
	int CountLife();
	bool IsLife(int x, int y);
	void SaveLifeInFile(std::string fileName);
private:
	//���������� ������ ��� ������� �����
	int birth = 2;
	//���������� ������ ��� ���������
	std::string survival = "23";
	char board[sizeY][sizeX];
};

//��������� ����
void Play();
//���� ����� x, �� ������ mod
int Modul(int x, int mod);