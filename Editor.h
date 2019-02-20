#pragma once
//#include "MainSystem.h"
class MainSystem;

class Editor
{
public:
	Editor(MainSystem &);
	~Editor();
	void start();
private:
	bool novyOkruh();
	bool novaOtazka();
	bool editChapter();
	bool editQuastions(unsigned short);
	MainSystem *MS = nullptr;
};

