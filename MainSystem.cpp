#include "Editor.h"
#include "MainSystem.h"
#include "Game.h"

///v planovani
void MainSystem::game(){}

bool MainSystem::initSystem(){
    //inicializuje soubory
    ofstream create;
    create.open(CHAPTER_FILE_PATH,std::ofstream::binary);
    create.close();
    create.open(PROFILE_FILE_PATH,std::ofstream::binary);
    create.close();
	loadChapters();
	return true;
}

MainSystem::MainSystem(){
	//inicializuje system
	if (!initSystem()) {
		cout << "Error" << endl;
		PAUSE;
		return;
	}
}

MainSystem::~MainSystem(){
	delete[] okruhy;
}

bool MainSystem::answerBool(String quastion) {
	uint16_t selectedAnswer = 0;
	while (true) {
		//vyèisti vystup na konzoli
		CLS;
		//položí otázku
		cout << quastion << endl;
		//zobrazí ANO/NE s vyznaèenim vybrane odpovedi
		if (selectedAnswer == 0)cout << "-> ";
		else cout << "  ";
		cout << "ANO" << endl;

		if (selectedAnswer == 1)cout << "-> ";
		else cout << "  ";
		cout << "NE" << endl;

		//èekání na vstup uživatele x pro vyber, w pro posun nahoru, s pro posun dolu
		char move = _getch();

		//vyber moznosti podle zmacknute klavesy
		switch (move) {
		case 's':
			if (selectedAnswer == 0)selectedAnswer++;
			break;
		case 'w':
			if (selectedAnswer == 1)selectedAnswer--;
			break;
		case 'x':
			return !selectedAnswer;
			break;
		}
	}
}

uint16_t MainSystem::answerSelect(String quastion, Quast &choices, bool showNum) {
	uint16_t numberOfChoices = choices.size();
	uint16_t selectedAnswer = 0;
	while (true) {
		//vyèisti vystup na konzoli
		CLS;
		//položí otázku
		cout << quastion << endl;
		//zobrazí odpovìdí s vyznaèenim vybrane odpovedi
		LOOP(choices.size()) {
			if (selectedAnswer == i)cout << "-> ";
			else cout << "  ";
			if (showNum)cout << i + 1 << ".) ";
			cout << choices[i] << endl;
		}
		//èekání na vstup uživatele x pro vyber, w pro posun nahoru, s pro posun dolu
		char move = _getch();
		//vyber moznosti podle zmacknute klavesy
		switch (move) {
		case 's':
			if (selectedAnswer < choices.size() - 1)selectedAnswer++;
			break;
		case 'w':
			if (selectedAnswer > 0)selectedAnswer--;
			break;
		case 'x':
			return selectedAnswer;
			break;
		}

	}
}

uint16_t MainSystem::answerNum(String quastion, uint16_t min, uint16_t max, uint16_t krok){
	uint16_t selectedAnswer = min;
	while (true) {
		//vyèisti vystup na konzoli
		CLS;
		//položí otázku
		cout << quastion << endl;
		//zobrazí vybrane mnozstvi
		cout <<"-- ["<< selectedAnswer<<"] ++" << endl;
		//èekání na vstup uživatele x pro vyber, w pro posun nahoru, s pro posun dolu
		char move = _getch();
		//vyber moznosti podle zmacknute klavesy
		switch (move) {
		case 'a':
			if (selectedAnswer-krok >= min)selectedAnswer-=krok;
			break;
		case 'd':
			if (selectedAnswer+krok <= max)selectedAnswer+=krok;
			break;
		case 'x':
			return selectedAnswer;
			break;
		}
	}
}

bool MainSystem::pridat_okruh(Okruh okruh){
	if (pocet_okruhu == NUM_OF_CHAPTERS) {
		return false;
	}
	okruhy[pocet_okruhu++] = okruh;
	saveChapters();
	return true;
}

bool MainSystem::mainMenu(){
	//Výbìr mezi editorem otázek nebo hrou
	while (true) {
		DynamicArray<String> moznosti; moznosti("Spustit hru"); moznosti("Editor"); moznosti("Debug"); moznosti("Konec");
		Editor editor(*this);
		Game game(*this);
		switch (answerSelect("Prosim vyber jesli si prejes hrat hru nebo vytvaret/editovat otazky:", moznosti)) {
		case 0:
			game.start();
			return true;
		case 1:
			editor.start();
			return true;
		case 2:
			debug();
			break;
		case 3:
			return false;
		}
	}
}

void MainSystem::saveChapters(){
	ofstream save;
	save.open(CHAPTER_FILE_PATH,std::ofstream::binary);
	if(!save.fail()){
	save.write((char*)(okruhy), sizeof(Okruh)*NUM_OF_CHAPTERS);
	}else{
	cout << "Error: chybi soubor - "<< CHAPTER_FILE_PATH << endl;
	PAUSE;
	}
	save.close();
}


void MainSystem::showDebugInfo(){
	CLS;
	cout << "Velikost jednoho okruhu : " << sizeof(Okruh)  << " B" << endl;
	cout << "Velikost jedne otazky   : " << sizeof(Otazka) << " B" << endl;
	cout << "Velikost jednoho profilu: " << sizeof(Player) << " B" << endl;
	PAUSE;
}

void MainSystem::loadChapters(){
	pocet_okruhu = 0;
	ifstream load(CHAPTER_FILE_PATH, std::ifstream::binary| std::ifstream::in);
	if(!load.fail()){
	load.read((char*)(okruhy), sizeof(Okruh)*NUM_OF_CHAPTERS);
	}else{
		cout << "Error: chybi soubor - "<< CHAPTER_FILE_PATH << endl;
	PAUSE;
	}
	load.close();
	//zjisti poèet naètených otázek
	LOOP(NUM_OF_CHAPTERS)if (okruhy[i].isLoaded)pocet_okruhu++;
}

void MainSystem::debug(){
	CLS;
	Quast moznosti;
	moznosti("Znovu nacist data ze souboru chapters.dat"); moznosti("Zobrazit info");
	switch (answerSelect("DEBUG:", moznosti)) {
	case 0:
		//pøeèti datový blok ze souboru "okruhy.txt"
		loadChapters();
		break;
	case 1:
	    //zobrazi velikosti nekterych objektu
		showDebugInfo();
		break;
	}

}

void MainSystem::showChapters(){
	CLS;
	cout << "Pocet okruhu: " << pocet_okruhu<<"/"<<NUM_OF_CHAPTERS << endl;
	LOOP(pocet_okruhu) {
		cout << i + 1 << ".)" << endl;
		cout << okruhy[i] <<endl;
	}
	PAUSE;
}
