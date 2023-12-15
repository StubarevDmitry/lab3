#pragma once
#include <fstream>
#include <string>

const size_t sizeY = 15;
const size_t sizeX = 25;


class BoardParameters {
public:
	//��������� ������ ������
	int PointEnvironment(size_t x, size_t y);
	void WriteToCell(size_t x, size_t y, int i);
	int StateInTheCell(size_t x, size_t y);
	int GetBirth();
	void SetBirth(int i);
	std::string GetSurvival();
	void SetSurvival(std::string str);
private:
	//���������� ������ ��� ������� �����
	int birth = 3;
	//���������� ������ ��� ���������
	std::string survival = "23";
	char board[sizeY][sizeX];
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
	bool IsLife(size_t x, size_t y);
	void SaveLifeInFile(std::string fileName);
	void Help();
private:
	BoardParameters board;
};
//���������� ��� � � ����� ������ ����� �������� ����
void Launch(int argc, char* argv[]);
//��������� ����
void Play(bool isFile, std::string file);
//���� ����� x, �� ������ mod
int Module(int x, int mod);