#pragma once
#include <iostream>
#include <random>
#include <ctime>
class MainSystem;
using namespace std;
#define LOOP(n) for(int i = 0;i<n;i++)
#define NUM_OF_PROFILES 20
#define SIZE_OF_NAME 30
#define SIZE_OF_PASSWORD 100
#define PROFILE_FILE_PATH "Data/Profiles.dat"
#define PAUSE _getwch()
#define VYBRANA_OTAZKA MS->okruhy[vybrany_okruh].otazky[vybrana_otazka]
#define VYBRANY_OKRUH MS->okruhy[vybrany_okruh]
#define SELECTED_PROFILE profily[selected_profile]
struct Player {
	Player() {
		LOOP(SIZE_OF_NAME) { name[i] = ' '; }
		LOOP(SIZE_OF_PASSWORD) { password[i] = ' '; }
		age = 0;
		celkove_mnozstvi_bodu = 0;
		pocet_hotovych_okruhu = 0;
		pocet_odpovezenych_otazek = 0;
		INIT = false;
	}
	
	Player(char N[SIZE_OF_NAME],char PSW[SIZE_OF_PASSWORD], unsigned short AGE) {
		LOOP(SIZE_OF_NAME) { name[i] = N[i]; }
		LOOP(SIZE_OF_PASSWORD) password[i] = PSW[i];
		celkove_mnozstvi_bodu = 0;
		pocet_hotovych_okruhu = 0;
		pocet_odpovezenych_otazek = 0;
		age = AGE;
		INIT = true;
	}

	Player(const Player &pl) {
		LOOP(SIZE_OF_NAME) { name[i] = pl.name[i]; }
		LOOP(SIZE_OF_PASSWORD) password[i] = pl.password[i];
		celkove_mnozstvi_bodu = pl.celkove_mnozstvi_bodu;
		pocet_hotovych_okruhu = pl.pocet_hotovych_okruhu;
		pocet_odpovezenych_otazek = pl.pocet_odpovezenych_otazek;
		age = pl.age;
		INIT = true;
	}

	friend ostream& operator<<(ostream &stream,const Player player) {
		stream << "Jmeno: ";
		for (int i = 0; player.name[i] != '\0'; i++)stream << player.name[i];
		stream << endl;
		stream << "BODY: " << player.celkove_mnozstvi_bodu << endl;
		stream << "Pocet zodpovezenych otazek: " << player.pocet_odpovezenych_otazek << endl;
		stream << "Pocet hotovych okruhu: " << player.pocet_hotovych_okruhu << endl;
		stream << "Vek: " << player.age << endl;
		return stream;
	}

	void setPassword(char temp_psw[SIZE_OF_PASSWORD]) { LOOP(SIZE_OF_PASSWORD)password[i] = temp_psw[i]; }

	char name[SIZE_OF_NAME];
	unsigned short age;
	bool INIT = false;
	short celkove_mnozstvi_bodu;
	short pocet_odpovezenych_otazek;
	short pocet_hotovych_okruhu;
	bool passwordCheck(char temp_psw[SIZE_OF_PASSWORD]) { 
		//zjištìní velikosti puvodniho hesla
		uint16_t velikost_password = 0;
		while (password[velikost_password++] != '\0');
		//zjištìní velikosti porovnávaneho hesla
		uint16_t velikost_temp_psw = 0;
		while (temp_psw[velikost_temp_psw++] != '\0');

		if (velikost_password != velikost_temp_psw)return false;

		LOOP(velikost_password) if (password[i] != temp_psw[i])return false;
		return true;
	}
private:
	char password[SIZE_OF_PASSWORD];
};

static default_random_engine randomGenerator(time(NULL));

class Game
{
public:
	Game(MainSystem &);
	void start();
	~Game();

private:
	MainSystem *MS = nullptr;
	unsigned short pocet_profilu = 0;
	Player *profily = new Player[NUM_OF_PROFILES];
	void loadProfiles();
	void saveProfiles();
	void createProfile();
	bool selectProfile();
	short editProfile(unsigned short);
	bool mainGame(unsigned short);
	bool mainMenu(unsigned short);
	void playChapter(unsigned short, unsigned short );
};

