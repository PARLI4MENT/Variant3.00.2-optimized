#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include "Lib.h"

using namespace std;

Lib::Lib()
{
}
Lib::~Lib()
{
}
void Lib::FileRead(FILE* fin){
	fgets(dest, l_dest, fin);
	fgets(fio, l_fio, fin);
	fgets(date, l_date, fin);
	fscanf(fin, "%i\n", &number);
}
void Lib::Print(){
	printf("%s%s%s%20i\n", dest, fio, date, number);
}
void Lib::FileWrite(FILE* fout) {
	fprintf(fout, "%s%s%s%15i\n", dest, fio, date, number);
}
void Lib::FormDest() {
	for (int i = strlen(dest); i < l_dest; i++) dest[i] = ' ';
	dest[l_dest - 1] = '\0';
}
void Lib::FormFio(){
	for (int i = strlen(fio); i < l_fio; i++) fio[i] = ' ';
	fio[l_fio - 1] = '\0';
}
void Lib::FormDate(){
	for (int i = strlen(date); i < l_date; i++) date[i] = ' ';
	date[l_date - 1] = '\0';
}