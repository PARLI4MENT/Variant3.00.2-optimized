#pragma once
const int l_dest = 31, l_fio = 31, l_date = 11;
class Lib {
public:
	Lib();
	~Lib();
	void FileRead(FILE*);
	void Print();
	void FileWrite(FILE*);
	void FormDest();
	void FormFio();
	void FormDate();

	char dest[l_dest]; // Пункт назначения
	char fio[l_fio]; // ФИО пасажира
	char date[l_date]; // Дата вылета
	int number; // Номер рейса
	Lib *next;
};