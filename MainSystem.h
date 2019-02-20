#pragma once

#define LOOP(n) for(int i = 0;i<n;i++)
#define PAUSE _getwch()
#define READ(text) for(int i=0;text[i]!='\0',i++) 
#define SIZE_OF_QUASTION 200
#define SIZE_OF_DESCRIPTION 100
#define SIZE_OF_ANSWER 100
#define SIZE_OF_NAME 30
#define NUM_OF_ANSWERS 10
#define NUM_OF_QUASTIONS 100
#define NUM_OF_CHAPTERS 50
#define CHAPTER_FILE_PATH "Data/Chapters.dat"
#define CLS system("cls")

#include <conio.h>
#include <iostream>
#include "String.h"
#include "DynamicArray.h"
#include <fstream>
#include <string>
#include "Game.h"
typedef DynamicArray<String> Quast;



class Otazka {
public:
	Otazka() {
		LOOP(SIZE_OF_QUASTION)text_otazky[i] = '.';
		body_za_otazku = 0;
		mnozsti_odpovedi = 0;
		spravna_odpoved = 0;
		for (int i = 0; i < NUM_OF_ANSWERS; i++) {
			for (int y = 0; y < SIZE_OF_ANSWER; y++)odpovedi[i][y] = '.';
		}
	}
	Otazka(char TEXT[SIZE_OF_QUASTION], char ODPOVEDI[NUM_OF_ANSWERS][SIZE_OF_ANSWER],uint16_t POCET_ODPOVEDI, uint16_t BODY, uint16_t SPRAVNA_ODPOVED) {
		LOOP(SIZE_OF_QUASTION)text_otazky[i] = TEXT[i];
		body_za_otazku = BODY;
		mnozsti_odpovedi = POCET_ODPOVEDI;
		spravna_odpoved = SPRAVNA_ODPOVED;
		for (int i = 0; i < NUM_OF_ANSWERS; i++) {
			for (int y = 0; y < SIZE_OF_ANSWER; y++)odpovedi[i][y] = ODPOVEDI[i][y];
		}
	}
	Otazka(const Otazka &otazka) {
		body_za_otazku = otazka.body_za_otazku;
		mnozsti_odpovedi = otazka.mnozsti_odpovedi;
		LOOP(SIZE_OF_DESCRIPTION)text_otazky[i] = otazka.text_otazky[i];
		for (int i = 0; i < NUM_OF_ANSWERS; i++) {
			for (int y = 0; y < SIZE_OF_QUASTION; y++)odpovedi[i][y] = otazka.odpovedi[i][y];
		}
	}
	void setText(char text[SIZE_OF_DESCRIPTION]) { LOOP(SIZE_OF_DESCRIPTION)text_otazky[i] = text[i]; }
	char text_otazky[SIZE_OF_DESCRIPTION];
	uint16_t body_za_otazku;
	uint16_t mnozsti_odpovedi;
	uint16_t spravna_odpoved;
	char odpovedi[NUM_OF_ANSWERS][SIZE_OF_ANSWER];
};

class Okruh {
public:
	Okruh(DynamicArray<Otazka> seznam_otazek, uint16_t OBTIZNOST) {
		LOOP(seznam_otazek.size())otazky[i] = seznam_otazek[i];
		obtiznost = OBTIZNOST;
		pocet_otazek_okruhu = seznam_otazek.size();
	}
	Okruh(uint16_t OBTIZNOST, char NAZEV[SIZE_OF_NAME], char POPIS[SIZE_OF_DESCRIPTION]) {
		pocet_otazek_okruhu = 0;
		obtiznost = OBTIZNOST;
		LOOP(SIZE_OF_NAME)nazev[i] = NAZEV[i];
		LOOP(SIZE_OF_DESCRIPTION)popis[i] = POPIS[i];
		isLoaded = true;
	}
	Okruh() {
		//LOOP(20)otazky[i] = Otazka();
		obtiznost = 0;
		pocet_otazek_okruhu = 0;
		isLoaded = false;
	}
	Okruh(const Okruh &okruh) {
		obtiznost = okruh.obtiznost;
		pocet_otazek_okruhu = okruh.pocet_otazek_okruhu;
		LOOP(SIZE_OF_NAME)nazev[i] = okruh.nazev[i];
		LOOP(SIZE_OF_DESCRIPTION)popis[i] = okruh.popis[i];
		LOOP(NUM_OF_QUASTIONS)otazky[i] = okruh.otazky[i];
		isLoaded = okruh.isLoaded;
	}

	friend ostream& operator<<(ostream &stream,const Okruh &okruh) {
		stream << "Nazev okruhu : ";
		for(int i =0;okruh.nazev[i]!='\0';i++)stream << okruh.nazev[i];
		stream << endl;

		stream << "Popis okruhu : " << endl;
		for (int i = 0; okruh.popis[i] != '\0'; i++)stream << okruh.popis[i];
		stream << endl;
		stream << "Obtiznost : ";
		switch (okruh.obtiznost) {
		case 0:
			stream << "Primitivni obtiznost";
			break;
		case 1:
			stream << "Lehka obtiznost";
			break;
		case 2:
			stream << "Stredni obtiznost";
			break;
		case 3:
			stream << "Tezka obtiznost";
			break;
		case 4:
			stream << "Velmi tezka obtiznost";
			break;
		case 5:
			stream << "Extremni obtiznost";
			break;
		}
		stream << endl;
		if (okruh.pocet_otazek_okruhu > 0) {
			stream << "Pocet otazek okruhu : " << okruh.pocet_otazek_okruhu << endl;
			stream << "-OTAZKY-" << endl;
			LOOP(okruh.pocet_otazek_okruhu) {
				stream << "------------------------------" << endl;
				stream << i + 1 << ".)" << endl << "Zadani: ";
				for (int y = 0; okruh.otazky[i].text_otazky[y] != '\0'; y++)stream << okruh.otazky[i].text_otazky[y];
				stream << endl;
				//odpovedi
				for (int y = 0; y < okruh.otazky[i].mnozsti_odpovedi; y++) {
					stream << y + 1 << ".)";
					for (int x = 0; okruh.otazky[i].odpovedi[y][x] != '\0'; x++)stream << okruh.otazky[i].odpovedi[y][x];
					stream << endl;
				}
				//spravna odpoved
				stream << "Spravna odpoved : " << okruh.otazky[i].spravna_odpoved + 1 << endl;
				stream << "Body za spravnou odboved : " << okruh.otazky[i].body_za_otazku << " b" << endl;

			}
		}
		
		return stream;
	}
	void pridatOtazku(Otazka OTAZKA) {
		if (pocet_otazek_okruhu < NUM_OF_QUASTIONS) {
			otazky[pocet_otazek_okruhu++] = OTAZKA;
		}
		else cout << "ERROR = MAXIMALNI POCET OTAZEK DOSAZEN!" << endl;
	}
	void setName(char temp_name[SIZE_OF_NAME]) { LOOP(SIZE_OF_NAME)nazev[i] = temp_name[i]; }
	void setDescription(char temp_popis[SIZE_OF_DESCRIPTION]) { LOOP(SIZE_OF_DESCRIPTION)popis[i] = temp_popis[i]; }
	uint16_t obtiznost;
	uint16_t pocet_otazek_okruhu;
	bool isLoaded;
	char nazev[SIZE_OF_NAME];
	Otazka otazky[NUM_OF_QUASTIONS];
	char popis[SIZE_OF_DESCRIPTION];
};

class Editor; class Game;

class MainSystem
{
public:
	MainSystem();
	~MainSystem();
	static uint16_t answerSelect(String quastion, Quast &choices, bool showNum = false);
	static bool answerBool(String quastion);
	static uint16_t answerNum(String quastion, uint16_t min, uint16_t max, uint16_t krok);
	bool pridat_okruh(Okruh okruh);
	bool mainMenu();
	Okruh *okruhy = new Okruh[NUM_OF_CHAPTERS];
	void showChapters();
	uint16_t pocet_okruhu = 0;
	void saveChapters();
	void loadChapters();
private:
	void game();
	bool initSystem();
	void showDebugInfo();
	void debug();
};
