#include <iostream>
#include <string>
#include <sstream>
#include "CSMemJCST.h"
using namespace std;

void menu(CSMemoria *mem);

int main() {
	string ids;
	cout <<"Ingrese los Ids :"<<endl;
	cin.clear();
	getline(cin, ids);
	CSMemoria* mem = new CSMemoria();
	mem->new_espacio(ids);
	cout << " memoria lista" << endl;
	mem->mostrar_Julio();
	cout << "desea a?adir mas ids: "<<endl;
	cout << "	Ingrese los Ids	: " << endl;
	cin.clear();
	getline(cin, ids);
	mem->new_espacio(ids);
	cout << " LA NUEVA MEMORIA ESTA LISTA\n" << endl;
	mem->mostrar_Julio();

	system("pause");
	return 0;
}

void menu(CSMemoria *mem) {
	cout << "1. Crear Memoria, agregar IDS y mostrar Memoria\n" << endl;
	/* int opcion;
	 cin >> opcion;
	 switch (opcion) {
	 case 1: {
	 cout << "Se a Creado la Memoria\n" << endl;
	 mem->new CSMemoria();

	 string ids;
	 cout << "	Ingrese los Ids	:	\n" << endl;
	 cin.ignore();
	 getline(cin, ids);
	 mem->new_espacio(ids);
	 cout << " memoria lista\n" << endl;
	 mem->mostrar_Julio();

	 } break;
	 } */
}
