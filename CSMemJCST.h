// ---------------------------------------------------------------------------

#ifndef CSMemJCSTH
#define CSMemJCSTH
// ---------------------------------------------------------------------------

#include <iostream>
#include <string>

using namespace std;

const int MAX = 20;
const int NULO = -1;

struct NodoMem {
	int dato;
	string id;
	int link;
};

class CSMemoria {
private:
	NodoMem* mem; // NodoMem mem[MAX];
	int libre;

	int numero_ids(string id);
	string* vector_ids(string cad);

public:
	CSMemoria();
	int new_espacio(string cadena);
	int new_espacio2(string cadena);
	void delete_espacio(int dir);
	void poner_dato(int dir, string cadena_id, int valor);
	int obtener_dato(int dir, string cadena_id);
	int espacios_disponibles();
	int espacios_ocupados();
	bool dir_libre(int dir);
	void mostrar_Julio();
};

int cantidad_ids(string id) {
	int ce = 0;
	int le = id.length();
	for (int i = 0; i < le; i++) {
		char c = id[i];
		if (c == ',')
			ce++;
	}
	if (id[le - 1] != ',')
		ce++;
	return ce;
}

string *vector_ids(string ids) {
	int cantidad = cantidad_ids(ids);
	string *vect = new string[cantidad];
	int c = 0;
	string copia = ids;
	while (copia.length() > 0) {
		int pos = copia.find_first_of(",");
		pos = pos == - 1 ? copia.length() : pos;
		string id = copia.substr(0, pos);
		if (c + 1 < cantidad)
			copia = copia.substr(pos-1, copia.length() - pos - 1);
		else
			copia = "";
		vect[c] = id;
		c++;
	}
	return vect;
}

// ---------complementos para mostrar_Julio
string repetir(unsigned int cantidad, char c) {
	return std::string(cantidad, c);
}

string rellenar(string s, int espacios) {
	if (espacios <= s.length()) {
		return s;
	}
	int relleno = espacios - s.length();
	return s + repetir(relleno, ' ');
}

string to_string(int value) {
	if (value == 0)
		return "0";
	bool es_negativo = value < 0;
	string r = "";
	if (es_negativo)
	value *= -1;
	while (value != 0) {
		char c = value % 10 + 0x30;
		r = c + r;
		value = value / 10;
	}
	return es_negativo ? "-" + r : r;
}
#endif
