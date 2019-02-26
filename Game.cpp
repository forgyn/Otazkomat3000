#include "Game.h"
#include "MainSystem.h"


Game::Game(MainSystem &ms){
	MS = &ms;
	loadProfiles();
}

void Game::start(){
	//výbìr profilu
	if (pocet_profilu == 0) {
		//vytvoøeni profilu
		cout << "Pred spustenim hry si prosim vytvor profil." << endl;
		PAUSE;
		createProfile();
	}

	//profilove menu
	DynamicArray<String> menu_profily;
	menu_profily("Vyber profilu");
	menu_profily("Vytvoreni noveho profilu");
	menu_profily("Zpet");
	switch (MainSystem::answerSelect("Vyber nekterou z moznosti", menu_profily)) {
	case 0:
		while(selectProfile());
		break;
	case 1:
		createProfile();
		break;
	case 2:return;
	}

	//hlavni menu
	DynamicArray<String> menu_moznosti;



}


Game::~Game(){
	delete[] profily;
}

void Game:: loadProfiles(){
	pocet_profilu = 0;
	ifstream load(PROFILE_FILE_PATH, std::ifstream::binary | std::ifstream::in);
	if(!load.fail()){
	load.read((char*)(profily), sizeof(Player)*NUM_OF_PROFILES);
	load.close();
	}else{
	cout << "Error: chybi soubor - "<< PROFILE_FILE_PATH << endl;
	PAUSE;
	}
	//zjisti poèet naètených otázek
	LOOP(NUM_OF_PROFILES)if (profily[i].INIT)pocet_profilu++;
}

void Game::saveProfiles(){

	ofstream save(PROFILE_FILE_PATH, std::ofstream::binary);
	if (!save.fail()){
	save.write((char*)(profily), sizeof(Player)*NUM_OF_PROFILES);
	}else{
	cout << "Error: chybi soubor - "<< PROFILE_FILE_PATH << endl;
	PAUSE;
	}

	save.close();
}

void Game::createProfile(){
	if (pocet_profilu < NUM_OF_PROFILES) {
		///TVORBA PROFILU
		//výbìr jmena profilu
		CLS;
		cout << "Prosim napiste sve jmeno/prezdivku(max. " << SIZE_OF_NAME << " znaku): ";
		char temp_n[SIZE_OF_NAME];
		cin.getline(temp_n, SIZE_OF_NAME);
		//výbìr hesla k profilu
		CLS;
		cout << "Prosim zvolte sve heslo(max. " << SIZE_OF_PASSWORD << " znaku): ";
		char temp_psw[SIZE_OF_PASSWORD];
		cin.getline(temp_psw, SIZE_OF_PASSWORD);
		//zvoleni vìku
		uint16_t temp_age = MainSystem::answerNum("Zvolte prosim svuj vek: ", 3, 99, 1);
		//vytvoøení nového profilu
		profily[pocet_profilu++] = Player(temp_n, temp_psw, temp_age);
		saveProfiles();
	}
	else {
		cout << "Maximalni mnozstvi profilu dosazeno!" << endl;
		PAUSE;
	}
}

bool Game::selectProfile(){
	//výbìr profilu
	DynamicArray<String> nazvy_profilu;
	LOOP(pocet_profilu)nazvy_profilu(profily[i].name);
	nazvy_profilu("Zpet<-");
	uint16_t selected_profile = MainSystem::answerSelect("Vyber profil ke kteremu se chce prihlasit: ", nazvy_profilu, true);
	if (selected_profile == nazvy_profilu.size() - 1)return false;

	//napsani a porovnani hesla
	cout << "Prosim zadej heslo k profilu: " << profily[selected_profile].name << endl;
	cout << ">>";
	char temp_psw[SIZE_OF_PASSWORD];
	cin.getline(temp_psw, SIZE_OF_PASSWORD);
	if (!(SELECTED_PROFILE.passwordCheck(temp_psw))) {
		cout << "Spatne heslo!" << endl;
		PAUSE;
		return false;
	}

	while(mainMenu(selected_profile));

}

short Game::editProfile(unsigned short selected_profile){
	//výbìr akce
	DynamicArray<String> menu_editace_profilu;
	menu_editace_profilu("Zmenit jmeno");
	menu_editace_profilu("Zmenit heslo");
	menu_editace_profilu("Zmenit vek");
	menu_editace_profilu("!Smazat profil!");
	menu_editace_profilu("Zpet");
	uint16_t ans = MainSystem::answerSelect("Vyber co chces zmenit: ", menu_editace_profilu);
	if (ans == 0) {
		CLS;
		cout << "Puvodni jmeno    : " << SELECTED_PROFILE.name << endl;
		cout << "Zadej nove jmeno : ";
		char temp_name[SIZE_OF_NAME];
		cin.getline(temp_name, SIZE_OF_NAME);
		LOOP(SIZE_OF_NAME)SELECTED_PROFILE.name[i] = temp_name[i];
		saveProfiles();
		cout << "Jmeno uspesne zmeneno" << endl;
		PAUSE;
	}
	if (ans == 1) {
		CLS;
		cout << "Zadej nove heslo : ";
		char temp_psw[SIZE_OF_PASSWORD];
		cin.getline(temp_psw, SIZE_OF_PASSWORD);
		SELECTED_PROFILE.setPassword(temp_psw);
		saveProfiles();
		cout << "Heslo uspesne zmeneno" << endl;
		PAUSE;
	}
	if (ans == 2) {
		CLS;
		SELECTED_PROFILE.age = MainSystem::answerNum("Prosim vyber novy vek: ", 3, 99, 1);
		saveProfiles();
	}
	if (ans == 3) {
		if (!MainSystem::answerBool("Opravdu si prejes smazat tento profil ?"))return true;
		for (int x = selected_profile; x < NUM_OF_PROFILES - 1; x++) {
			LOOP(NUM_OF_PROFILES)profily[x] = profily[x+1];
		}
		pocet_profilu--;
		profily[NUM_OF_PROFILES - 1] = Player();
		saveProfiles();
		return 2;
	}
	if (ans == 4)return 0;
	return 1;
}

bool Game::mainGame(unsigned short selected_profile){
	CLS;
	cout << "VITEJ VE HRE" << endl;
	DynamicArray<String> nazvy_okruhu;
	LOOP(MS->pocet_okruhu)nazvy_okruhu(MS->okruhy[i].nazev);
	nazvy_okruhu("Zpet<-");
	uint16_t vybrany_okruh = MainSystem::answerSelect("Vyber okruh ktery by jsi chtel zkusit", nazvy_okruhu, true);
	if (vybrany_okruh == nazvy_okruhu.size() - 1)return false;
	playChapter(vybrany_okruh, selected_profile);
	return true;
}

bool Game::mainMenu(unsigned short selected_profile){
	//vyber co chceš dìlat
	DynamicArray<String> menu;
	menu("Hrat hru");
	menu("Zobrazit profil");
	menu("Nastavit profil");
	menu("Zpet");
	switch (MainSystem::answerSelect("Vyber co chces delat: ", menu)) {
	case 0:
		while (mainGame(selected_profile));
		break;
	case 1:
		CLS;
		cout << SELECTED_PROFILE;
		PAUSE;
		break;
	case 2:
		while (true) {
			short stav = editProfile(selected_profile);
			if (stav == 0)break;
			if (stav == 1)continue;
			if (stav == 2)return false;
		}
		break;
	case 3:
		return false;
	}

	return true;
}



void Game::playChapter(unsigned short vybrany_okruh, unsigned short selected_profile){
	std::uniform_int_distribution<unsigned short> randomNumber(5, 10);
	std::uniform_int_distribution<unsigned short> randomNumber2(0, VYBRANY_OKRUH.pocet_otazek_okruhu-1);
	uint16_t num_of_quastions = randomNumber(randomGenerator);
	if (num_of_quastions > VYBRANY_OKRUH.pocet_otazek_okruhu)num_of_quastions = VYBRANY_OKRUH.pocet_otazek_okruhu;

	//zamichani otazek
	unsigned short *arreyOfQuastions = new unsigned short[num_of_quastions];
	LOOP(num_of_quastions)arreyOfQuastions[i] = -1;
	unsigned short temp_num = 0;
	unsigned short num_of_dup = 0;
	bool incorrect = false;
	LOOP(num_of_quastions) {
		while (true) {
			incorrect = false;
			temp_num = randomNumber2(randomGenerator);
			for (int y = 0; y < num_of_quastions; y++) {
				if (arreyOfQuastions[y] == temp_num)incorrect = true;
			}
			if (!incorrect) {
				arreyOfQuastions[i] = temp_num;
				break;
			}
		}
	}
	//loop otazek
	short body = 0;
	for (int y = 0; y < num_of_quastions;y++) {
		unsigned short vybrana_otazka = arreyOfQuastions[y];
		DynamicArray<String> odpovedi;
		LOOP(VYBRANA_OTAZKA.mnozsti_odpovedi)odpovedi(VYBRANA_OTAZKA.odpovedi[i]);
		if (MainSystem::answerSelect(VYBRANA_OTAZKA.text_otazky, odpovedi, true) == VYBRANA_OTAZKA.spravna_odpoved) {
			cout << "Spravna odpoved!" << endl;
			body += VYBRANA_OTAZKA.body_za_otazku;
			cout << "+ " << VYBRANA_OTAZKA.body_za_otazku << " body (celkem. " << body << " b)" << endl;
			PAUSE;
		}
		else {
			cout << "Spatna odpoved!" << endl;
			if(body>0)body--;
			cout << "- 1 bod (celkem. " << body << " b)" << endl;
			PAUSE;
		}
		SELECTED_PROFILE.pocet_odpovezenych_otazek++;
	}

	//vysledky
	CLS;
	short ziskatelne_body = 0;
	short body_na_profil = 0;
	float modifier_obtiznosti;
	switch (MS->okruhy[vybrany_okruh].obtiznost) {
	case 0:
		modifier_obtiznosti = 1.0f;
		break;
	case 1:
		modifier_obtiznosti = 1.3f;
		break;
	case 2:
		modifier_obtiznosti = 1.8f;
		break;
	case 3:
		modifier_obtiznosti = 2.0f;
		break;
	case 4:
		modifier_obtiznosti = 2.5f;
		break;
	case 5:
		modifier_obtiznosti = 3.0f;
		break;
	}
	body_na_profil = body * modifier_obtiznosti;

	LOOP(num_of_quastions)ziskatelne_body += MS->okruhy[vybrany_okruh].otazky[arreyOfQuastions[i]].body_za_otazku;
	cout << "------VYSLEDKY------" << endl;
	cout << "Ziskane body: " << body << "/"<< ziskatelne_body << endl;
	cout << "Procentualni vyjadreni :" << ((float)body/(float)ziskatelne_body)*100<<" %" <<endl;
	cout << "Body prictene na profil: "<< body_na_profil << endl;
	cout << "--------------------" << endl;
	PAUSE;
	SELECTED_PROFILE.celkove_mnozstvi_bodu += body_na_profil;
	SELECTED_PROFILE.pocet_hotovych_okruhu++;
	saveProfiles();
}

