#include <iostream>
#include <string>

#define PRIME_SIZE 29

using namespace std;

class Note {
public:
	Note* next;
	string last_name;
	string name;
	string telephone;
	int day;
	int month;
	int year;

	Note() {
		this->next = NULL;
	}

	Note(string last_name, string name, string telephone, int day = 0, int month = 0, int year = 0) {
		this->last_name = last_name;
		this->name = name;
		this->telephone = telephone;
		this->day = day;
		this->month = month;
		this->year = year;
		this->next = NULL;
	}

	~Note() {
		if (this->next != NULL)
		{
			delete this->next;
		}
	}
};

class HashTable {
	Note* table[PRIME_SIZE];

	static int hash(string str) {
		int asciisum = 0;
		for (int i = 0; i < str.length(); i++) {
			asciisum += str[i];
		}
		return asciisum % PRIME_SIZE;
	}

public:

	HashTable() {
		for (int i = 0; i < PRIME_SIZE; i++) {
			table[i] = NULL;
		}
	}

	~HashTable() {
		//cout << "Delete table\n";
		for (int i = 0; i < PRIME_SIZE; i++) {
			delete table[i];
		}
	}

	void push(string last_name, string name, string telephone, int day, int month, int year) {
		int hashNumber = hash(telephone);
		Note* note = new Note(last_name, name, telephone, day, month, year);
		Note* place = table[hashNumber];
		if (place == NULL) {
			table[hashNumber] = note;
			return;
		}

		while (place->next != NULL) {
			place = place->next;
		}
		place->next = note;
	}

	Note* find(string telephone) {
		int hashNumber = hash(telephone);
		Note* result = table[hashNumber];
		if (!result) {
			cout << "Friend not found" << endl;
			return NULL;
		}
		while (result->telephone != telephone) {
			if (!result->next) {
				cout << "Friend not found" << endl;
				break;
			}
			result = result->next;
		}
		return result;
	}
};

int main() {
	HashTable newTable;

	string wlast_name;
	string wname;
	string wtelephone;
	int wday;
	int wmonth;
	int wyear;
	int i = 0;

	do {
		cout << "Last Name: "; cin.sync();
		cin >> wlast_name;
		cout << "Name: "; cin.sync();
		cin >> wname;
		cout << "Telephone: ";
		cin >> wtelephone;
		cout << "Birthday Day: ";
		cin >> wday;
		cout << "Birthday Month: ";
		cin >> wmonth;
		cout << "Birthday Year: ";
		cin >> wyear;
		cout << endl;
		newTable.push(wlast_name, wname, wtelephone, wday, wmonth, wyear);
		i++;
	} while (i <= 5);

	//newTable.push("Katzroy", "Sazh", "+123456789012", 15, 8, 1967);
	//newTable.push("Oerba Dia", "Vanille", "+278391745145", 2, 7, 2002);
	//newTable.push("Villiers", "Snow", "+264895037014", 14, 4, 1979);
	//newTable.push("Farron", "Lightning", "+028574637822", 8, 8, 1985);
	//newTable.push("Estheim", "Hope", "+380972577206", 7, 4, 2006);

	string tel;
	cout << "Enter Telephone: " ; cin >> tel;

	Note* search = newTable.find(tel);
	if (search) {
		cout << "Found Friend With Telephone (" << search->telephone << ") :" << endl;
		cout << endl;
		cout << "Last Name: " << search->last_name << endl;
		cout << "Name: " << search->name << endl;
		cout << "Telephone: " << search->telephone << endl;
		cout << "Birthday Day: " << search->day << endl;
		cout << "Birthday Month: " << search->month << endl;
		cout << "Birthday Year: " << search->year << endl;
	}

	return 0;
}