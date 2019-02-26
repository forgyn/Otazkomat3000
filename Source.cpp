#define VERSION 1.10
#define PAUSE _getwch()
#define START_OF_PROJECT "27.01.2019"
#define LAST_UPDATE		 "20.02.2019"
#define END_OF_PROJECT   "26.02.2019"
#define LOOP(n) for(int i = 0;i<n;i++)

#include "String.h"

#include "DynamicArray.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include "MainSystem.h"



using namespace std;

int main() {
	//Uvitani
	cout << "Vitej ve hre/programu Otazkomat 3000, vytvorený Forgoncorpem S.R.O za ucelem zlepseni samo uceni." << endl
		<< "Verze: " << VERSION << endl
		<< "Posledni aktualizace: " << LAST_UPDATE << endl;
	PAUSE;
	//vytvoøeni instance hlavniho systemu
	MainSystem mainSystem;
	///zobrazí hlavní menu, hlavní smyèka
	while(mainSystem.mainMenu());

	return 0;
}
