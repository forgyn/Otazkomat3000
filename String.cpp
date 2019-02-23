#include "String.h"
#include "String.h"

void String::operator=(const char *text) {
 if (velikost > 0)clear();
 unsigned i = 0;
 while (text[i++] != '\0')velikost = i + 1;
 _text = new char[velikost];
 LOOP(velikost) _text[i] = text[i];
 delete[] text;
}
void String::operator=(char *text) {
	if (velikost > 0)clear();
	unsigned i = 0;
	while (text[i++] != '\0')velikost = i + 1;
	_text = new char[velikost];
	LOOP(velikost) _text[i] = text[i];
}


String& String::operator+(String &text2) {
	String *vysledek = new String;
	char *cast1, *cast2;
	cast1 = _text;
	cast2 = text2.get();
	unsigned vyslednaVelikost = velikost + text2.size();
	char* vyslednyText = new char[vyslednaVelikost-1];
	LOOP(velikost - 1)vyslednyText[i] = _text[i];
	LOOP(text2.size())vyslednyText[i + (velikost - 1)] = text2.get()[i];
	*vysledek = vyslednyText;
	delete[] vyslednyText;
	vyslednyText = nullptr;
	vysledek->_temp = true;
	return *vysledek;
}

String& String::operator+(const char* text) {
	String *vysledek = new String;
	vysledek->_temp = true;
	int i = 0;
	unsigned velikost2 = 0;
	//zjištìní velikosti øetìzce
	while (text[i++] != '\0')velikost2 = i + 1;
	//celková velikost
	unsigned vyslednaVelikost = velikost + velikost2;
	//iniciace doèasného výsledku
	char* vyslednyText = new char[vyslednaVelikost - 1];
	//pøesunuti znaku do noveho vysledku
	LOOP(velikost - 1)vyslednyText[i] = _text[i];
	LOOP(velikost2)vyslednyText[i + (velikost - 1)] = text[i];
	//nastaveni velikosti a vysledku
	velikost = vyslednaVelikost;
	*vysledek = vyslednyText;
	//smazani docesneho vysledku
	delete[] vyslednyText;
	vyslednyText = nullptr;
	return *vysledek;
}
char String::operator[](unsigned n)const{
	if (n >= 0 && n < velikost) {
		return _text[n];
	}
}
bool String::operator==(const char *text)const{
	unsigned _velikost,i=0;
	while (text[i++] != '\0')_velikost = i + 1;
	if (_velikost != velikost)return false;
	LOOP(velikost) {
		if (_text[i] != text[i])return false;
	}
	return true;
}
bool String::operator==(const String &text)const {
	if (text.size() != velikost)return false;
	LOOP(velikost) {
		if (_text[i] != text[i])return false;
	}
	return true;
}
void String::del(unsigned n){
	if (velikost > 0 && n<velikost-1) {
		//zmenší velikost o 1
		velikost--;
		//vytvoøí doèasný pole znaku
		char *temp_text = new char[velikost];
		//vloží znaky jejichž index se nemìní
		LOOP(n)temp_text[i] = _text[i];
		//vloží znaky posunuty o -1
		for (int i = n; i < velikost;i++)temp_text[i] = _text[i+1];
		//smaže pùvodní pole znakù, a nahradí jej novým polem
		delete[] _text; _text = nullptr;
		_text = new char[velikost];
		LOOP(velikost) _text[i] = temp_text[i];
		//smaže doèasné pole znakù
		delete[] temp_text;
	}else ERROR("ERROR")
}
void String::delEdgWts(){
	//smaže mezery zleva
	while(true){
		if (_text[0] == ' ') {
			del(0);
		}
		else break;
	}
	//smaže mezery zprava
	RLOOP(velikost-1) {
		if (_text[i] == ' ') {
			del(i);
		}
		else break;
	}
		
}
void String::add(const char &c){
	char *temp_text = new char[velikost];
	LOOP(velikost)temp_text[i] = _text[i];
	delete[] _text;
	_text = new char[++velikost];
	LOOP(velikost-2)_text[i] = temp_text[i];
	_text[velikost - 2] = c;
	_text[velikost - 1] = '\0';
}
char*String::getPart(unsigned start, unsigned end)const{
	if (start <= end && end<velikost) {
		char *part = new char[100]; unsigned i = 0,y = 0;
		for (i = start; i <= end; i++) {
				part[y++] = _text[i];
		}
		part[y] = '\0';
		return part;
	}
	else { 
		
		ERROR("ERROR"); 
	
	}
}
void String::operator=(String &text2) {
	if (velikost > 0 && _text != nullptr)clear();
	_text = new char[text2.size()];
	velikost  = text2.size();
	LOOP(text2.size()) _text[i] = text2.get()[i];
	if(text2._temp)delete &text2;
}
void String::operator=(const String &text2) {
	if (velikost > 0 && _text != nullptr)clear();
	_text = new char[text2.size()];
	velikost = text2.size();
	LOOP(text2.size()) _text[i] = text2.get()[i];
	if (text2._temp)delete &text2;
}

double String::convToDouble(){
	double final_number = 0;
	//najdi tecku
	bool dot = false;
	unsigned dot_index = 0;
	dot_index = velikost-1;
	LOOP(velikost)if (_text[i] == '.') { dot = true; dot_index = i; }
	String bigger = getPart(0, dot_index-1);
	LOOP(bigger.size()) {
		switch (bigger[i]) {
		case '1':
			final_number += 1 * pow(10, bigger.size() - 2 - i);
			break;
		case '2':
			final_number += 2 * pow(10, bigger.size() - 2 - i);
			break;
		case '3':
			final_number += 3 * pow(10, bigger.size() - 2 - i);
			break;
		case '4':
			final_number += 4 * pow(10, bigger.size() - 2 - i);
			break;
		case '5':
			final_number += 5 * pow(10, bigger.size() - 2 - i);
			break;
		case '6':
			final_number += 6 * pow(10, bigger.size() - 2 - i);
			break;
		case '7':
			final_number += 7 * pow(10, bigger.size() - 2 - i);
			break;
		case '8':
			final_number += 8 * pow(10, bigger.size() - 2 - i);
			break;
		case '9':
			final_number += 9 * pow(10, bigger.size() - 2 - i);
			break;
		}
	}
	if (dot) {
		String smaller = getPart(dot_index + 1, velikost - 2);
		LOOP(smaller.size()) {
			switch (smaller[i]) {
			case '1':
				final_number += 1 * pow(10, -i-1);
				break;
			case '2':
				final_number += 2 * pow(10, -i - 1);
				break;
			case '3':
				final_number += 3 * pow(10, -i - 1);
				break;
			case '4':
				final_number += 4 * pow(10, -i - 1);
				break;
			case '5':
				final_number += 5 * pow(10, -i - 1);
				break;
			case '6':
				final_number += 6 * pow(10, -i - 1);
				break;
			case '7':
				final_number += 7 * pow(10, -i - 1);
				break;
			case '8':
				final_number += 8 * pow(10, -i - 1);
				break;
			case '9':
				final_number += 9 * pow(10, -i - 1);
				break;
			}
		}




	}
	return final_number;
}

char* String::convertToChar(){
	char new_text[200];
	LOOP(200)new_text[i] = _text[i];
	return new_text;
}

void String::combine(DynamicArray<String> &texty){
	if (_text != nullptr && velikost != 0) {
		clear();
	}

	LOOP(texty.size())velikost += texty[i].size()-1;
	velikost += 1;
	_text = new char[velikost];
	uint16_t ukazatel = 0;
	LOOP(texty.size()) {
		for (int y = 0; y < texty[i].size()-1; y++,ukazatel++) {
			_text[ukazatel] = texty[i][y];
		}
	}
	_text[velikost - 1] = '\0';
}

String::String(const char* text) {
	unsigned i = 0;
	while (text[i++] != '\0')velikost = i + 1;
	_text = new char[velikost];
	LOOP(velikost) _text[i] = text[i];
}
String::String(const String &str) {
	delete[] _text;
	_text = new char[str.size()];
	velikost = str.size();
	LOOP(str.size()) _text[i] = str.get()[i];
	if (str._temp)delete &str;
}
String::String(char *text) {
	unsigned i = 0;
	while (text[i++] != '\0')velikost = i + 1;
	_text = new char[velikost];
	LOOP(velikost) _text[i] = text[i];
}

bool String::remove(const char &c, remove_enum_delete_order DELETE, remove_use_remove_wtsp WTSP) {
	switch (DELETE) {
	case FIRST:
		switch (WTSP) {
		case USE:
			LOOP(velikost) {
				if (_text[i] == c) {
					_text[i] = ' ';
					return true;
				}	
			}
			return false;
			break;
		case REMOVE:
			LOOP(velikost) {
				if (_text[i] == c) {
					del(i);
					return true;
				}	
			}
			return false;
			break;
		}
		break;
	case LAST:
		switch (WTSP) {
		case USE:
			RLOOP(velikost) {
				if (_text[i] == c) {
					_text[i] = ' ';
					return true;
				}
			}
			return false;
			break;
		case REMOVE:
			RLOOP(velikost) {
				if (_text[i] == c) {
					del(i);
					return true;
				}
			}
			return false;
			break;
		}
		break;
	case ALL:
		switch (WTSP) {
		case USE:
			LOOP(velikost) {
				if (_text[i] == c) {
					_text[i] = ' ';
				}
			}
			return false;
			break;
		case REMOVE:
			RLOOP(velikost) {
				if (_text[i] == c) {
					del(i);
				}
			}
			return false;
			break;
		}
		break;
	}
}

/*String& String::operator[](unsigned n) {
	if (n >= 0 && n<velikost) {
		_selectedNumber = n;
		return *this;
	}
	else {
		_selectedNumber = -2;
		return *this;
	}
}*/
void String::operator=(const char &znak) {
	if (_selectedNumber >= 0) {
		_text[_selectedNumber] = znak;
		_selectedNumber = -1;
	}
	else if (_selectedNumber == -1) {
		if (velikost > 0)clear();
		velikost=2;
		_text = new char[velikost];
		_text[0] = znak;
		_text[1] = '\0';

	}
	else {
		_selectedNumber = -1;
		ERROR("ERROR")
	}
}
unsigned String::find(const char &c, find_way WAY) {
	switch (WAY) {
	case RIGHT:
		LOOP(velikost)if (_text[i] == c)return i;
		break;
	case LEFT:
		RLOOP(velikost)if (_text[i] == c)return i;
		break;
	}
}

unsigned String::count(const char &c)const{
	unsigned NUM = 0;
	LOOP(velikost)if (_text[i] == c)NUM++;
	return NUM;
}

ostream & operator<<(ostream & str, const String & text){
	str << text.get();
	return str;
}

bool String::checkNumber() {
	//zkontroluje zda nema cislo vic nez 1 tecky
	if (count('.') > 1)return false;

	//zkontroluje zda jsou obsazeny pouze cisla,tecka bez znaku
	LOOP(velikost) {
		if (_text[i] != '1'
			&& _text[i] != '2'
			&& _text[i] != '3'
			&& _text[i] != '4'
			&& _text[i] != '5'
			&& _text[i] != '6'
			&& _text[i] != '7'
			&& _text[i] != '8'
			&& _text[i] != '9'
			&& _text[i] != '0'
			&& _text[i] != '\0'
			&& _text[i] != '.')
			return false;
	}
	return true;
}