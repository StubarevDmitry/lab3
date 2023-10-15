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
	//���������� � ������ ����������� ���������� �� ����� .life
	//���������� � ������ ����������� ����������
	Life();
	//��������� ���
	void Run();
	void OneStep();
	//��������� ������� ������� ��� ���������� ����� � ���� ������, � ������ ���
	void CheckRule();
	void Print();

private:
	//���������� ������ ��� ������� �����
	int birth = 2;
	//���������� ������ ��� ���������
	int survival = 3;
	char board[sizeY][sizeX];
};

//��������� ����
void Play();

//�������� ����� ��������� ������ �������
void Comand();

//���� ����� x, �� ������ mod
int Modul(int x, int mod);