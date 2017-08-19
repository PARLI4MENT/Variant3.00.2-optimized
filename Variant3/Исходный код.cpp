//Составить программу, которая содержит текущую информацию о заявках на авиабилеты. Каждая заявка включает:
// пункт назначения; номер рейса;
// фамилию и инициалы пассажира; желаемую дату вылета.
//Программа должна обеспечивать:
// хранение всех заявок в виде списка;
// добавление заявок в список;
// удаление заявок;
// вывод заявок по заданному номеру рейса и дате вылета;
// вывод всех заявок 

// ФУНКЦИЯ СОЗДАНИЯ ФАЙЛА ЕСЛИ ЕГО НЕТ
// ПОДТВЕРЖДЕНИЕ УДАЛЕНИЯ 
// ПОДКОРРЕКТИРОВАТЬ ПУНКТЫ МЕНЮ

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include "Lib.h"

using namespace std;

int menu();
Lib* read_dbase(char* filename);
void get_dest(char* dest);
void get_fio(char* fio);
void get_date(char* date);
Lib* add(Lib *beg, const Lib &lib);
Lib read_Lib();
void print_dbase(Lib* beg);
int write_dbase(char *filename, Lib *pv);
void find_Lib(Lib* beg);
Lib* find_date(Lib* pv, char* date, Lib *& prev);
Lib* find_fio(Lib* pv, char* dest, Lib *& prev);
void find(Lib* pv, int number);
Lib* remove(Lib* beg);
void BlueWhite();
void Table();

int main() { // ------------------------------------------------- Главная функция
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Lib *beg = read_dbase( "dbase.txt" );
	if (!beg) return 1;
	while (true) {
		switch (menu()) {
		case 1: add(beg, read_Lib()); break;
		case 2: beg = remove( beg ); break;
		case 3: find_Lib( beg ); break;
		case 4: print_dbase(beg); break;
		case 5: write_dbase( "dbase.txt", beg ); break;
		case 6: return 0;
		default: puts(" Надо вводить число от 1 до 6"); break;
		}
	}
}
int menu() { // ------------------------------------------------------- Вывод меню
	BlueWhite();
	puts("Для продолжения нажмите любую клавишу...");
	_getch();
	char buf[10];
	int option;
	do {
		system("cls");
		BlueWhite();
		puts("1 - Добавление заявки\t 3 - Поиск заявки");
		puts("2 - Удалеие заявки\t 4 - Вывод всех заявок");
		puts("5 - Сохранение в файл\t 6 - Выход");
		BlueWhite();
		gets( buf );
		option = atoi( buf );
	} while (!option);
	return option;
}
Lib* read_dbase(char* filename) { // -------------------------------- Чтение из файла
	FILE* fin;
	Lib Lib, *beg = 0;
	if ((fin = fopen(filename, "r")) == 0) {
		printf("Нет файла dbase.txt %s\n", filename); exit(1);
	}
	while (!feof(fin)) {
		Lib.FileRead(fin);
		beg = add(beg, Lib);
	}
	fclose(fin);
	return beg;
}
void get_dest(char* dest) { // --------------------------- Запрос Пункта назначения
	puts("Введите пункт назначения: "); gets(dest);
}
void get_fio(char* fio) { // --------------------------------------- Запрос фамилии
	puts("Введите фамилию И.О."); gets(fio);
}
void get_date(char* date) { // ---------------------------------------- Запрос даты
	puts("Введите дату: "); gets(date);
}
Lib* add(Lib *beg, const Lib &lib) { // ------------------------- Добавление заявки
	Lib* pv = new Lib;
	*pv = lib;
	pv->next = 0;
	if (beg) { // Список не пуст
		Lib* temp = beg;
		while (temp->next) temp = temp->next;
		temp->next = pv;
	}
	else beg = pv;
	return beg;
}
Lib read_Lib() { // ---------------------------------------------- Ввод данных заявки
	system("cls");
	Lib Lib; char buf[80];
	get_dest(Lib.dest);
		Lib.FormDest();
	do { puts("Введите номер рейса: "); gets(buf); } while (!(Lib.number = atoi(buf)));
	get_fio(Lib.fio);
		Lib.FormFio();
	get_date(Lib.date);
		Lib.FormDate();
	return Lib;
}
void print_dbase(Lib* beg) { // ----------------------------------- Вывод базы на экран
	system("cls");
	Table();
	Lib* pv = beg;
	while (pv) {
		pv->Print();
		pv = pv->next;
	}
}
int write_dbase(char *filename, Lib *pv) { // ------------------- Сохранение базы в файл
	FILE *fout;
	if ((fout = fopen(filename, "w")) == NULL) {
		puts("Ошибка открытия файла"); return 1;
	}
	while (pv) {
		pv->FileWrite(fout);
		pv = pv->next;
	}
	fclose(fout);
	return 0;
}
void find_Lib(Lib* beg) { // --------------------------------------------------- Поиск
	system("cls");
	char buf[l_date];
	int number, option;
	Lib *prev = 0, *pv = 0;
	do {
		puts("1 - Поиск по дате вылета, 2 - По номеру рейса, 3 - По фамилии И.О., 4 - Отмена\n ");
		gets(buf);
	} while (!(option = atoi(buf)));
	switch (option) {
	case 1: get_date(buf);
		pv = find_date(beg, buf, prev); break;
	case 2: do { puts("Введите номер рейса: \n"); gets(buf); } while (!(number = atoi(buf)));
		find(beg, number); break;
	case 3: get_fio(buf);
		pv = find_fio(beg, buf, prev); break;
	case 4: return;
	default: puts("неверный режим\n");
	}
}
Lib* find_date(Lib* pv, char* date, Lib *& prev) { // ---------------------- Поиск по дате
	Table();
	prev = 0;
	while (pv) {
		if (strstr(date, pv->date)) {
			pv->Print();
			return pv;
		}
		prev = pv;
		pv = pv->next;
	}
	puts("Такой заявки нет\n");
	return 0;
}
Lib* find_fio(Lib* pv, char* fio, Lib *& prev) { // ---------------------- Поиск по ФИО
	Table();
	prev = 0;
	while (pv) {
		if (strstr(pv->fio, fio))
		if (pv->fio[strlen(fio)] == ' ') {
			pv->Print();
			return pv;
		}
		prev = pv;
		pv = pv->next;
	}
	puts("Такой заявки нет\n");
	return 0;
}
void find(Lib* pv, int number) { // ------------------------------ Поиск по номеру рейса
	Table();
	while (pv) {
		if (pv->number == number)
			pv->Print();
		pv = pv->next;
	}
}
Lib* remove(Lib* beg) { // ---------------------------------- Удаление заявки
	char fio[l_fio];
	get_fio(fio); // Кого удаляем?
	Lib* prev;
	Lib* pv = find_fio(beg, fio, prev);
	if (pv) { // Если нашли
		if (pv == beg) beg = beg->next; // Удаление из начала списка
		else // Удаление из середины или конца списка
			prev->next = pv->next;
		delete pv; // Освобождение памяти из-под элемента
	}
	return beg;
}
void BlueWhite() { // ------------------------------- Цветные разделительные линии
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Цвет интерфейса
	SetConsoleTextAttribute(hConsole, (WORD)((1 << 4) | 15)); // Синий фон белые буквы
	for (int i = 1; i < 120; i++) cout << "="; cout << endl; // Вывод ===============
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); // Черный фон белые буквы
}
void Table() {
	puts("Пункт назначение: \t      Фамилия И.О. пасажира:\t    Дата вылета:      Номер рейса:");
	BlueWhite();
}