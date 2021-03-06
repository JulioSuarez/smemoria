// ---------------------------------------------------------------------------

#pragma hdrstop

#include "CSMemJCST.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

CSMemoria::CSMemoria() {
	mem = new NodoMem[MAX];
	for (int i = 0; i < MAX; i++) {
		mem[i].link = i + 1;
	}
	mem[MAX - 1].link = NULO;
	libre = 0;
}

int CSMemoria::numero_ids(string id) {
	if (id.length() == 0)
		return 0;
	int cont = 0;
	for (int i = 0; i < id.length(); i++) {
		if (id[i] == ',')
			cont++;
	}
	return cont + 1;
}

string* CSMemoria::vector_ids(string cad) {
	int n = numero_ids(cad);
	string* vids = new string[n];
	int c = 0;
	while (cad.length() > 0) {
		int pos = cad.find_first_of(",");
		if (pos == -1)
			pos = cad.length();
		string id = cad.substr(0, pos);
		vids[c] = id;
		c++;
		cad.erase(0, pos);
	}
	return vids;
}

int CSMemoria::new_espacio2(string cadena) {
	int cant = numero_ids(cadena); // cant de terminos
	int dir = this->libre; // dir = 0
	int d = this->libre; // d = 0
	string* ids = vector_ids(cadena); // ["dia", "mes", "a?o"]
	int i = 0;
	for (i = 0; i < cant - 1; i++) { // i= 0, 1, 2
		mem[d].id = ids[i];
		d = mem[d].link;
	}
	mem[d].id = ids[i];
	this->libre = mem[d].link;
	mem[d].link = -1;
	return dir;

}

int CSMemoria::new_espacio(string cadena) {
	int num = numero_ids(cadena); /* num toma el valor de la cantidad de
	 palabras ingresadas en la CADENA */
	int dir = this->libre; /* dir toma el valor de libre
	 que en este caso es 0 */
	int d = this->libre; /* d toma el valor de libre
	 que en este caso es 0 */
	int aux;
	if (num <= espacios_disponibles()) {
		/*
		 si num es menor igual al espacio disponible
		 num = 3
		 espacio disponible = 20
		 */
		while (cadena.length() > 0) {
			/*
			 mientras que la longitud de la cadena sea mayor que 0
			 cadena = dia,mes,a?o
			 longitud = 11 caracteres
			 */
			int pos = cadena.find_first_of(",");
			/*
			 pos tomara el valor de la cadena hasta la
			 primera coma ","
			 pos tomara el valor 4
			 en el siguiente ciclo
			 pos tomara el valor 8
			 */
			if (pos == NULO) {
				/*
				 suponiendo que la cadena es de una sola palabra
				 ejemplo: dia
				 osea si no existe una coma ","
				 */
				pos = cadena.length();
				/*
				 pos tomara toda la cadena
				 tomando el ejemplo: dia entonces pos = 3
				 */
				aux = d;
				// la variable aux tomara el valor de libre
			}
			string id = cadena.substr(0, pos);
			/*
			 se pondra en id una parte de la cadena desde
			 la posicion 0 hasta pos
			 en el primer ciclo	dia
			 en el segundo ciclo	mes
			 en el tercer ciclo	a?o
			 */
			mem[d].id = id;
			/*
			 Memoria En la posicion libre que en este ciclo es 0
			 poner id en este ejemplo entraria dia
			 */
			d = mem[d].link;
			/*
			 en este primer ciclo
			 d que estaba inicialmente en 0
			 cambia el valor al de link en este caso 1
			 entonces d=1
			 */
			cadena.erase(0, pos + 1);
			/*
			 de la cadena dia,mes,a?o
			 borra lo insertado en el primer ciclo "dia"
			 quedando en la cadena mes,a?o para el siguiente ciclo
			 */
		} // repita el ciclo hasta que la cadena quede vacia
		this->libre = mem[aux].link;
		/*
		 libre tomara el valor de link en aux
		 */
		mem[aux].link = -1;
		/*
		 mem[aux].link indica la ultima posicion de link
		 el cual tomara el valor -1
		 */
		return dir;
	}
	else {
		cout << "ERROR: ESPACIOS INSUFICIENTES\n";
		return NULO;
	}
}

void CSMemoria::delete_espacio(int dir) {
	int x = dir;
	while (mem[x].link != -1)
		x = mem[x].link;
	mem[x].link = libre;
	libre = dir;
}

void CSMemoria::poner_dato(int dir, string cadena_id, int valor) {
	int z = dir;
	cadena_id = cadena_id.substr(2, cadena_id.length() - 2);
	// Elimina la flecha
	while (z != NULO) {
		if (mem[z].id == cadena_id) {
			mem[z].dato = valor;
			break;
		}
		z = mem[z].link;
	}
}

int CSMemoria::obtener_dato(int dir, string cadena_id) {
	int z = dir;
	cadena_id = cadena_id.substr(2, cadena_id.length() - 2);
	// Elimina la flecha
	while (z != NULO) {
		if (mem[z].id == cadena_id)
			return mem[z].dato;
		z = mem[z].link;
	}
}

int CSMemoria::espacios_disponibles() {
	int x = libre;
	int c = 0;
	while (x != -1) {
		c++;
		x = mem[x].link;
	}
	return c;
}

int CSMemoria::espacios_ocupados() {
	int c = MAX - espacios_disponibles();
	return c;
}

bool CSMemoria::dir_libre(int dir) {
	int x = libre;
	bool c = false;
	while (x != -1 && c == false) {
		if (x == dir)
			c = true;
		x = mem[x].link;
	}
	return c;
}

void CSMemoria::mostrar_Julio() {
	int esp = 10;
	string cab = rellenar("dir", esp) + "|" + rellenar("id", esp) + "|" +
		rellenar("dato", esp) + "|" + rellenar("link", esp);
	string linea = repetir(cab.length(), '-');
	cout << cab << endl << linea << endl;
	for (int i = 0; i < MAX; i++) {
		string datos = rellenar(to_string(i), esp) + "|" + rellenar(mem[i].id,
			esp) + "|" + rellenar(to_string(mem[i].dato), esp) + "|" +
			rellenar(to_string(mem[i].link), esp);
		cout << datos << endl;
	}
	cout << linea << endl << "libre   :   " << to_string(libre) << endl;
	cout << "Memoria Disponible   :   " << to_string(espacios_disponibles())
		<< endl;
	cout << "Memoria Ocupada  :   " << to_string(espacios_ocupados()) << endl;
}
