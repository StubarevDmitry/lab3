#include "Comands.h"
//#include <thread>
#include <iostream>

void OnlineComands::ComandParametrs() {
	while (true) {
		std::string comand;
		std::string obj;
		std::cin >> comand;
		if (comand == "exit") {
			exit = true;
		}
		if (comand == "tick") {
			std::cin >> obj;
			tick = stoi(obj);
			isTick = true;
		}
		if (comand == "dump") {
			std::cin >> obj;
			fileNameForRecord = obj;
			isSave = true;
		}
		if (comand == "help") {
			isHelp = true;
		}
	}
}

OfflineComands::OfflineComands(char* allComnds[]) {
	for (int i = 1; i < 7; i++) {
		if (std::string(allComnds[i]) == "-o") {
			fileNameForRead = std::string(allComnds[i + 1]);
			std::cout << "-o: " << fileNameForRead << std::endl;
		}
		if (std::string(allComnds[i]) == "-in") {
			fileNameForRecord = std::string(allComnds[i + 1]);
			std::cout << "-in: " << fileNameForRecord << std::endl;
		}
		if (std::string(allComnds[i]) == "-i") {
			tick = std::stoi(std::string(allComnds[i + 1]));
			std::cout << "-i: " << tick << std::endl;
		}
	}
}

void OfflineComands::ExecutionOfCommands() {
	setlocale(LC_ALL, "Russian");
	std::ifstream in(fileNameForRead);
	if (in.is_open()) {
		in.close();
		Life life(fileNameForRead);
		for (int i = 0; i < tick; i++) {
			life.CheckRuleAndStep();
		}
		life.SaveLifeInFile(fileNameForRecord);
	}
	else {
		std::cout << "‘айл не был найден";
	}
	in.close();
}


OnlineComands::OnlineComands() : fileExists(false), fileNameForRead("") {}

OnlineComands::OnlineComands(bool fileExists, std::string fileNameForRead) : fileExists(fileExists), fileNameForRead(fileNameForRead) {}

void OnlineComands::ExecutionOfCommands() {
	Life* life;
	if (fileExists) {
		life = new Life(fileNameForRead);
		life->Print();
	}
	else {
		life = new Life();
		life->Print();
	}
	while (true) {
		if (isTick) {
			life->FewStepsAndPrint(tick);
			isTick = false;
			tick = 1;
		}
		if (isSave) {
			life->SaveLifeInFile(fileNameForRecord);
			isSave = false;
		}
		if (isHelp) {
			life->Help();
			isHelp = false;
		}
	}
	delete life;
}

//void Launch(int argc, char* argv[]) {
//	if (argc == 7) {
//		OfflineComands offline(argv);
//		offline.ExecutionOfCommands();
//	}
//	else {
//		std::string yesOrNo;
//		setlocale(LC_ALL, "Russian");
//	tryAgain:
//		std::cout << "’отите открыть файл YES/NO:";
//		std::cin >> yesOrNo;
//		if (yesOrNo == "YES") {
//			std::cout << "\n";
//			std::cout << "¬ведите название файла:";
//			std::string fileName;
//			std::cin >> fileName;
//			std::ifstream in(fileName);
//			if (in.is_open()) {
//				in.close();
//				Play(true, fileName);
//			}
//			else {
//				in.close();
//				Play(false, "");
//			}
//		}
//		else if (yesOrNo == "NO") {
//			Play(false, "");
//		}
//		else {
//			std::cout << "\n";
//			goto tryAgain;
//		}
//	}
//}
//
//void Play(bool fileExists, std::string file) {
//	OnlineComands* mainComand;
//	if (fileExists) {
//		mainComand = new OnlineComands(fileExists, file);
//	}
//	else {
//		mainComand = new OnlineComands();
//	}
//	std::thread thr1(&OnlineComands::ExecutionOfCommands, mainComand);
//	std::thread thr2(&OnlineComands::ComandParametrs, mainComand);
//	thr1.join();
//	thr2.join();
//	delete mainComand;
//}
