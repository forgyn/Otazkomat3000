#include "MainSystem.h"
#include "Editor.h"
#define VYBRANA_OTAZKA MS->okruhy[vybrany_okruh].otazky[vybrana_otazka]
#define VYBRANY_OKRUH MS->okruhy[vybrany_okruh]
Editor::Editor(MainSystem &ms) {
	MS = &ms;
}

Editor::~Editor()
{
}

void Editor::start(){
	Quast moznosti;
	moznosti("Vytvorit novy okruh otazek");
	moznosti("Vytvorit nove otazky");
	moznosti("Editovet okruh otazek");
	moznosti("Zobrazit okruhy");
	moznosti("Zpet");
	while (true) {
		switch (MainSystem::answerSelect("EDITOR", moznosti)) {
		case 0:
			while(novyOkruh());
			break;
		case 1:
			while (novaOtazka());
			break;
		case 2:
			while (editChapter());
			break;
		case 3:
			MS->showChapters();
			break;
		case 4:
			return;
		}
	}
}

bool Editor::novyOkruh(){
	//deklarace
	char *temp_name = new char[SIZE_OF_NAME];
	char *temp_popis = new char[SIZE_OF_DESCRIPTION];

	//výbìr názvu okruhu
	system("cls");
	cout << "Prosim vyberte nazev okruhu(max. " << SIZE_OF_NAME << " znaku): ";
	cin.getline(temp_name, SIZE_OF_NAME);
	
	//Nastaveni popisu okruhu
	system("cls");
	cout << "Prosim napis popis okruhu(max. " << SIZE_OF_DESCRIPTION << " znaku): ";
	cin.getline(temp_popis, SIZE_OF_DESCRIPTION);

	//Obtiznost
	Quast moznosti2;
	moznosti2("Primitivni obtiznost"); moznosti2("Lehka obtiznost"); moznosti2("Stredni obtiznost");
	moznosti2("Tezka obtiznost"); moznosti2("Velmi tezka obtiznost"); moznosti2("Extremni obtiznost");
	uint16_t obtiznost = MainSystem::answerSelect("Vyberte relativni obtiznost okruhu", moznosti2);

	//Iniciace okruhu a jeji ulozeni
	Okruh okruh(obtiznost, temp_name,temp_popis);
	MS->pridat_okruh(okruh);
	delete[] temp_name,temp_popis;

	return false;
}

bool Editor::novaOtazka(){
	if (MS->pocet_okruhu == 0) {
		cout << "Nebyly doposud pridany zadne okruhy!" << endl;
		PAUSE;
		return false;
	}

	//výbìr okruhu do kterého chce uživatel pøidat otázku
	DynamicArray<String> nazvy_okruhu;
	LOOP(MS->pocet_okruhu)nazvy_okruhu((MS->okruhy[i].nazev));
	nazvy_okruhu("Zpet");
	uint16_t vybrany_okruh = MainSystem::answerSelect("Vyber okruh ke kteremu chces pridat otazku: ", nazvy_okruhu,1);
	if (vybrany_okruh == nazvy_okruhu.size() - 1)return false;

	///vytvoøení otázky
	//deklarace
	char temp_quastion[SIZE_OF_QUASTION];
	char temp_answers[NUM_OF_ANSWERS][SIZE_OF_ANSWER];
	uint16_t pocet_odpovedi = 0;
	uint16_t spravna_odpoved = 0;
	//zadani otazky
	system("cls");
	cout << "Zadejte otazku : " <<endl <<">>";
	cin.getline(temp_quastion, SIZE_OF_QUASTION);

	//zadani poctu odpovedi za otazku
	uint16_t body = MainSystem::answerNum("Zvolne pocet bodu za otazku: ", 1, 10, 1);

	///zapsani odpovedi (TO DO)
	//zapsani minimalnì dvou odpovedi
	while (pocet_odpovedi<2) {
		system("cls");
		cout << "Odpovedi : " << pocet_odpovedi << "/" << NUM_OF_ANSWERS << endl;
		cout << "Zadani otazky  : " << temp_quastion << endl;
		cout << "Napiste odpoved (otazka musi mit minimalne 2.odpovedi)" << endl << ">>";
		cin.getline(temp_answers[pocet_odpovedi++], SIZE_OF_ANSWER);
	}

	Quast odpovedi;
	LOOP(pocet_odpovedi)odpovedi(temp_answers[i]);

	while (true) {
		//výbìr správne odpovedi
		if (pocet_odpovedi < 10)odpovedi("PRIDAT DALSI OTAZKU");
		spravna_odpoved = MainSystem::answerSelect("Vyberte spravnou odpoved: ", odpovedi, true);
		if (pocet_odpovedi < 10 && spravna_odpoved == odpovedi.size() - 1) {
				system("cls");
				cout << "Odpovedi : " << pocet_odpovedi << "/" << NUM_OF_ANSWERS << endl;
				cout << "Zadani otazky  : " << temp_quastion << endl;
				cout << "Napiste odpoved :" << endl << ">>";
				cin.getline(temp_answers[pocet_odpovedi], SIZE_OF_ANSWER);
				odpovedi[spravna_odpoved]=temp_answers[pocet_odpovedi];
				pocet_odpovedi++;
		}
		else break;
	}

	MS->okruhy[vybrany_okruh].pridatOtazku(Otazka(temp_quastion, temp_answers, pocet_odpovedi, body, spravna_odpoved));
	MS->saveChapters();
	return false;
}

bool Editor::editChapter(){
	if (MS->pocet_okruhu == 0) {
		cout << "Nebyly doposud pridany zadne okruhy!" << endl;
		PAUSE;
		return false;
	}

	//výbìr okruhu který chceš upravit
	DynamicArray<String> nazvy_okruhu;
	LOOP(MS->pocet_okruhu)nazvy_okruhu((MS->okruhy[i].nazev));
	nazvy_okruhu("Zpet");
	uint16_t vybrany_okruh = MainSystem::answerSelect("Vyber okruh ktery chces editovat: ", nazvy_okruhu, 1);
	if (vybrany_okruh == nazvy_okruhu.size() - 1)return false;

	//vyber co chceš editovat
	DynamicArray<String> moznosti_editovani;
	moznosti_editovani("Nazev"); 
	moznosti_editovani("Popis");
	moznosti_editovani("Obtiznost"); 
	moznosti_editovani("Otazky"); 
	moznosti_editovani("!Smazat okruh!");
	moznosti_editovani("Zpet");
	while (true) {
		uint16_t selected_answer = MainSystem::answerSelect("Vyber co chces na okruhu editovat: ", moznosti_editovani);
		if (selected_answer == 0) {
			//výbìr nového názvu okruhu
			system("cls");
			cout << "Puvodni nazev okruhu: " << VYBRANY_OKRUH.nazev << endl;
			cout << "Prosim vyberte nazev okruhu(max. " << SIZE_OF_NAME << " znaku): ";
			char temp_name[SIZE_OF_NAME];
			cin.getline(temp_name, SIZE_OF_NAME);
			//zmeneni nazvu
			MS->okruhy[vybrany_okruh].setName(temp_name);
			//uložení 
			MS->saveChapters();
			//informace o operaci
			cout << "Nazev uspesne zmenen!" << endl;
			PAUSE;
		}
		if (selected_answer == 1) {
			//výbìr nového popisu okruhu
			system("cls");
			cout << "Puvodni popis okruhu: " << VYBRANY_OKRUH.popis << endl;
			cout << "Prosim vyberte popis okruhu(max. " << SIZE_OF_DESCRIPTION << " znaku): ";
			char temp_popis[SIZE_OF_DESCRIPTION];
			cin.getline(temp_popis, SIZE_OF_DESCRIPTION);
			//zmeneni popisu
			MS->okruhy[vybrany_okruh].setDescription(temp_popis);
			//uložení 
			MS->saveChapters();
			//informace o operaci
			cout << "Popis uspesne zmenen!" << endl;
			PAUSE;
		}
		if (selected_answer == 2) {
			//výbìr nové obtížnosti
			system("cls");
			Quast moznosti2;
			moznosti2("Primitivni obtiznost"); moznosti2("Lehka obtiznost"); moznosti2("Stredni obtiznost");
			moznosti2("Tezka obtiznost"); moznosti2("Velmi tezka obtiznost"); moznosti2("Extremni obtiznost");
			uint16_t obtiznost = MainSystem::answerSelect("Vyberte novou obtiznost okruhu", moznosti2);
			//nastaveni nové obtížnosti
			MS->okruhy[vybrany_okruh].obtiznost = obtiznost;
			//uložení 
			MS->saveChapters();
			//informace o operaci
			cout << "Popis uspesne zmenen!" << endl;
			PAUSE;
		}
		if (selected_answer == 3) {
			while (editQuastions(vybrany_okruh));
		}
		if (selected_answer == 4) {
			if (MainSystem::answerBool("Opravdu si prejes smazat tento okruh ?? Toto je nevratny proces.")) {
				//pøesune všechny odpovedi od indexu vybrane odpovedi o jeden stupeò dolu
				for (int x = vybrany_okruh; x < NUM_OF_CHAPTERS - 1; x++) {
					MS->okruhy[x] = MS->okruhy[x + 1];
				}
				MS->pocet_okruhu--;
				MS->okruhy[NUM_OF_CHAPTERS - 1] = Okruh();
				MS->saveChapters();
				cout << "Okruh uspesne smazana!" << endl;
				PAUSE;
				return true;
			}
		}
		if (selected_answer == moznosti_editovani.size()-1)break;
	}
	return true;
}

bool Editor::editQuastions(unsigned short vybrany_okruh){
	if (VYBRANY_OKRUH.pocet_otazek_okruhu == 0) {
		cout << "Nebyly doposud pridany zadne otazky!" << endl;
		PAUSE;
		return false;
	}

	//výbìr otazky kterou chce uživatel upravit
	DynamicArray<String> otazky;
	LOOP(VYBRANY_OKRUH.pocet_otazek_okruhu)otazky((VYBRANY_OKRUH.otazky[i].text_otazky));
	otazky("Zpet");
	uint16_t vybrana_otazka = MainSystem::answerSelect("Vyber otazku kterou chces upravit ", otazky, 1);
	if (vybrana_otazka == otazky.size() - 1)return false;

	//výbìr toho co chceš upravit
	//vyber co chceš editovat
	DynamicArray<String> moznosti_editovani;
	moznosti_editovani("Text otazky"); 
	moznosti_editovani("Body za otazku"); 
	moznosti_editovani("Zmenit odpoved"); 
	moznosti_editovani("!Smazat odpoved!"); 
	moznosti_editovani("Zmenit spravnou odpoved");
	moznosti_editovani("Pridat novou odpoved");
	moznosti_editovani("!Smazat otazku!");
	moznosti_editovani("Zpet");
	while (true) {
		uint16_t ans = MainSystem::answerSelect("Vyber co si prejec upravit: ", moznosti_editovani);
		if (ans == 0) {
			//zadani nove otazky
			system("cls");
			cout << "Puvodni otazka: " << VYBRANA_OTAZKA.text_otazky << endl;
			cout << "Zadejte novou otazku : ";
			char temp_text[SIZE_OF_DESCRIPTION];
			cin.getline(temp_text, SIZE_OF_DESCRIPTION);
			//nastaveni nove otazky
			VYBRANA_OTAZKA.setText(temp_text);
			//ulozeni nove otazky
			MS->saveChapters();
			cout << "Otazka byla uspesne zmenena !" << endl;
			PAUSE;
		}
		if (ans == 1) {
			//zmeneni poctu bodu za otazku
			uint16_t body = MainSystem::answerNum("Zvolne novy pocet bodu za otazku: ", 1, 10, 1);
			VYBRANA_OTAZKA.body_za_otazku = body;
		}
		//vìtší sraèka
		if (ans == 2) {
			//výbìr odpovìdí kterou chceme zmìnit
			if (VYBRANA_OTAZKA.mnozsti_odpovedi == 0) {
				cout << "Nebyly doposud pridany zadne odpovedi!" << endl;
				PAUSE;
				return false;
			}

			//výbìr otazky kterou chce uživatel upravit
			DynamicArray<String> odpovedi;
			LOOP(VYBRANA_OTAZKA.mnozsti_odpovedi)odpovedi((VYBRANA_OTAZKA.odpovedi[i]));
			odpovedi("Zpet");
			uint16_t vybrana_odpoved = MainSystem::answerSelect("Vyber odpoved jejiz text chces zmenit: ", odpovedi, 1);
			if (vybrana_odpoved != odpovedi.size() - 1) {

			//zadani noveho textu odpovedi
			system("cls");
			cout << "Zadani otazky  : " << VYBRANA_OTAZKA.text_otazky << endl;
			cout << "Puvodni odpoved: " << VYBRANA_OTAZKA.odpovedi[vybrana_odpoved] << endl;
			cout << "Napiste novou odpoved (max. " << SIZE_OF_ANSWER << " znaku)" << endl << ">>";
			cin.getline(VYBRANA_OTAZKA.odpovedi[vybrana_odpoved], SIZE_OF_ANSWER);
			MS->saveChapters();
			cout << "Text otezky byl uspesne zmenen! " << endl;
			PAUSE;
		}
		}
		if (ans == 3) {
			//výbìr otazky kterou chce uživatel upravit
			DynamicArray<String> odpovedi;
			LOOP(VYBRANA_OTAZKA.mnozsti_odpovedi)odpovedi((VYBRANA_OTAZKA.odpovedi[i]));
			odpovedi("Zpet");
			uint16_t vybrana_odpoved = MainSystem::answerSelect("Vyber odpoved kterou chcete smazat: ", odpovedi, 1);
			if (vybrana_odpoved != odpovedi.size() - 1) {
				//pøesune všechny odpovedi od indexu vybrane odpovedi o jeden stupeò dolu
				for (int x = vybrana_odpoved; x < NUM_OF_ANSWERS - 1; x++) {
					LOOP(SIZE_OF_ANSWER)VYBRANA_OTAZKA.odpovedi[x][i] = VYBRANA_OTAZKA.odpovedi[x + 1][i];
				}
				VYBRANA_OTAZKA.mnozsti_odpovedi--;
				if (VYBRANA_OTAZKA.spravna_odpoved == vybrana_odpoved)VYBRANA_OTAZKA.spravna_odpoved = 1010101010;
				if (VYBRANA_OTAZKA.spravna_odpoved > vybrana_odpoved)VYBRANA_OTAZKA.spravna_odpoved--;
				LOOP(SIZE_OF_ANSWER)VYBRANA_OTAZKA.odpovedi[NUM_OF_ANSWERS-1][i] = '.';
				cout << "Odpoved uspesne smazana !" << endl;
				PAUSE;
				MS->saveChapters();
			}
		}
		if (ans == 4) {
			//výbìr nové správne odpovìdi
			DynamicArray<String> odpovedi;
			LOOP(VYBRANA_OTAZKA.mnozsti_odpovedi)odpovedi((VYBRANA_OTAZKA.odpovedi[i]));
			odpovedi("Zpet");
			uint16_t vybrana_odpoved = MainSystem::answerSelect("Vyber novou spravnou odpoved: ", odpovedi, 1);
			if (vybrana_odpoved != odpovedi.size() - 1) {
				VYBRANA_OTAZKA.spravna_odpoved = vybrana_odpoved;
				MS->saveChapters();
			}
		}
		if (ans == 5) {
			//zajistí aby bylo množství odpovìdí menší než povolené maximum
			if (VYBRANA_OTAZKA.mnozsti_odpovedi < NUM_OF_ANSWERS) {
				system("cls");
				cout << "Odpovedi        : " << VYBRANA_OTAZKA.mnozsti_odpovedi << "/" << NUM_OF_ANSWERS << endl;
				cout << "Zadani otazky   : " << VYBRANA_OTAZKA.text_otazky << endl;
				cout << "Napiste odpoved : " << endl << ">>";
				cin.getline(VYBRANA_OTAZKA.odpovedi[VYBRANA_OTAZKA.mnozsti_odpovedi++], SIZE_OF_ANSWER);
				MS->saveChapters();
			}
			else {
				cout << "Maximalni mnozstvi odpovedi dosazeno !" << endl;
				PAUSE;
			}
		}
		if (ans == 6) {
			if (MainSystem::answerBool("Opravdu si prejes smazat tuto otazku ?? Toto je nevratny proces.")) {
				//pøesune všechny odpovedi od indexu vybrane odpovedi o jeden stupeò dolu
				for (int x = vybrana_otazka; x < NUM_OF_QUASTIONS - 1; x++) {
					VYBRANY_OKRUH.otazky[x] = VYBRANY_OKRUH.otazky[x + 1];
				}
				VYBRANY_OKRUH.pocet_otazek_okruhu--;
				VYBRANY_OKRUH.otazky[NUM_OF_ANSWERS - 1] = Otazka();
				MS->saveChapters();
				cout << "Otazka uspesne smazana!" << endl;
				PAUSE;
				return false;
			}
		}
		if (ans == 7)break;
	}
	return true;
}

