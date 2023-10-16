#pragma once
//#include <string.h>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;

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
	//����� ����������� � ��������
	void Print();
	//���������� ������ ��� ������� �����
	int Birth();
	//���������� ������ ��� ���������
	std::string Survival();
private:
	//���������� ������ ��� ������� �����
	int birth = 2;
	//���������� ������ ��� ���������
	string survival = "23";
	char board[sizeY][sizeX];
};

//��������� ����
void Play();
//��������� � ���������� ������
void LifeOrganization();
//�������� ����� ��������� ������ �������
void Comand();
//���� ����� x, �� ������ mod
int Modul(int x, int mod);