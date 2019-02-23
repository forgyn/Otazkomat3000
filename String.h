#pragma once
#include <iostream>
#include <math.h>
#include "DynamicArray.h"
using namespace std;
class String {
#define ERROR(text) std::cout << text << std::endl;
#define LOOP(n) for(int i = 0;i<n;i++)
#define RLOOP(n) for(int i = n-1;i>=0;i--)
#define INPUT int input = _getwch() 
#define DEBUG
public:
	///enums
	enum remove_enum_delete_order { ALL, FIRST, LAST };
	enum remove_use_remove_wtsp { REMOVE,USE };
	enum find_way {LEFT,RIGHT};
	///konstruktory
	String() {};
	String(const char* text);
	String(const String &text2);
	String(char *);
	///destruktor
	~String() {
		clear();
	}
	//uvolní data
	void clear() {
		if (_text != nullptr && velikost !=0) {
			delete[] _text;
			_text = nullptr;
			velikost = 0;
		}
	}

	///operatorové funkce
	//pøiøazení hodnoty
	void operator=(const char *);
	void operator=(char *);
	void operator=(String &);
	void operator=(const char &);
	//slouèení dvou øetìzcù/znakù
	String& operator+(String &);
	String& operator+(const char*);
	//String& operator[](unsigned);
	char operator[](unsigned)const;
	bool operator==(const char*)const;
	bool operator==(const String&)const;
	///ovládací funkce
	void del(unsigned);
	void delEdgWts();
	void add(const char &);
	///pomocné funkce
	//vra text
	char* get() const {
		if (_text != nullptr)
			return _text;
	}
	char* getPart(unsigned start,unsigned end)const;
	//vypíše obsah na obrazovku
	void see() {
		LOOP(velikost-1)cout << _text[i];
		cout << endl;
	}
	//vrátí velikost
	unsigned size() const { return velikost; }
	//odstraní znak dle parametrù První/Poslední/Všechny a Odstranit mezery/nechat mezery
	bool remove(const char &, remove_enum_delete_order DELETE = FIRST, remove_use_remove_wtsp WTSP = REMOVE);
	//najde první znak zleva a vrátí jeho index
	unsigned find(const char&, find_way WAY = RIGHT);
	//spocita vybrane prvky
	unsigned count(const char&)const;
	bool checkNumber();
	//vypiš text
	friend ostream& operator<<(ostream &str, const String &text);
	void operator=(const String &);
	//converzni funkce
	double convToDouble();
	char* convertToChar();
	//zkombinuje n-poèet Stringu
	void combine(DynamicArray<String> &);
	//øídící hodnoty
	bool _temp = false;
private:
	char *_text = nullptr;
	size_t velikost = 0;
	int16_t _selectedNumber = -1;
};