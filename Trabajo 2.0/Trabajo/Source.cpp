#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <string.h>
#include <vector>
#include "Arbol.h"
using namespace std;

class Columna {
	string nombre;
	string tipo;
	bool indexada;
public:
	vector<string> datos;
	Columna(string nombre, string tipo) : nombre(nombre), tipo(tipo) {}
	string getNombre() {
		return nombre;
	}
	string getTipo() {
		return tipo;
	}
	bool getIndex() {
		return indexada;
	}
	void setIndex(bool nuevo) {
		indexada = nuevo;
	}

};

//class Fila {
//	map<string, Columna*> columnas;
//public:
//	map<string, Columna*> getMap() {
//		return columnas;
//	}
//	int getInt(string nomColumna) {
//		return columnas[nomColumna]->datos[0];
//	}
//};

class Tabla {
	map<string, Columna*> columnas;
	map<string, Arbol<string, string>*> arboles;
public:
	void agregarColumna(string nombre, string tipo) {
		columnas[nombre] = new Columna(nombre, tipo);
	}
	string getNombre(string nom) {
		return columnas[nom]->getNombre();
	}
	void insertarDatos(string nom, string dato) {
		columnas[nom]->datos.push_back(dato);
	}
	void mostrarTabla() {
		for (auto i = columnas.begin(); i != columnas.end(); i++)
			cout << i->first << setw(15);
		cout << endl << endl;
		for (auto i = columnas.begin(); i != columnas.end(); i++) {
			for (int j = 0; j < columnas[i->first]->datos.size(); j++) {
				cout << left;
				for (auto k = columnas.begin(); k != columnas.end(); k++)
					cout << columnas[k->first]->datos[j] << setw(17);
				cout << endl;
			}
			break;
		}
	}
	map<string, Columna*> getMapa() {
		return columnas;
	}
	void indexar(string nombreColumna) {
		arboles[nombreColumna] = new Arbol<string, string>();

		for (auto a : columnas[nombreColumna]->datos)
			arboles[nombreColumna]->add(a);

		columnas[nombreColumna]->setIndex(true);
	}
	void ordenar(string nombreColumna) {

	}
};

void menuPrincipal() {
	cout << "***********************************************" << endl;
	cout << "*                                             *" << endl;
	cout << "*      BIENVENIDO A MINI SGBD                 *" << endl;
	cout << "*      Elija una opcion                       *" << endl;
	cout << "*   1. Crear una tabla                        *" << endl;
	cout << "*   2. Insertar datos en tabla                *" << endl;
	cout << "*   3. Mostrar tabla                          *" << endl;
	cout << "*   4. Seleccionar columnas                   *" << endl;
	cout << "*   5. Indexar columnas                       *" << endl;
	cout << "*   6. Ordenar tabla                          *" << endl;
	cout << "*   0. Salir                                  *" << endl;
	cout << "*                                             *" << endl;
	cout << "***********************************************" << endl;
}

int main() {
	int opcion;
	Tabla *obj = new Tabla();

volver:;
	do {
		system("cls");
		menuPrincipal();
		cin >> opcion;

		if (opcion == 1) {
			system("cls");
			int opcion2;
			string nombre, tipo;
			do {
				cout << "Ingrese el nombre de la columna: ";
				cin >> nombre;
				cout << "Ingrese el tipo de dato de la columna (int, float o string): ";
				cin >> tipo;

				obj->agregarColumna(nombre, tipo);

				cout << "Desea ingresar mas columnas? (1: si, 0: no): ";
				cin >> opcion2;

				if (opcion2 == 0) {
					cout << "La tabla se ha creado correctamente" << endl;
					system("pause");
				}
			} while (opcion2 != 0);
		}
		if (opcion == 2) {
			system("cls");
			int opcion3;

			if (obj->getMapa().size() == 0) {
				cout << "Debe crear una tabla primero" << endl;
				system("pause");
				goto volver;
			}

			map<string, Columna*> mapa = obj->getMapa();
			map<string, Columna*>::iterator i;
			string dato;

			do {
				for (i = mapa.begin(); i != mapa.end(); i++) {
					cout << "Ingrese el dato para la columna " << i->first << ": ";
					cin >> dato;
					obj->insertarDatos(i->first, dato);
				}

				cout << "Desea seguir insertando datos? (1: si, 0: no): ";
				cin >> opcion3;

				if (opcion3 == 0) {
					cout << "Se han ingresado correctamente" << endl;
					system("pause");
				}
			} while (opcion3 != 0);
		}
		if (opcion == 3) {
			system("cls");

			if (obj->getMapa().size() == 0) {
				cout << "Debe crear una tabla primero" << endl;
				system("pause");
				goto volver;
			}

			obj->mostrarTabla();
			cout << endl;
			system("pause");
		}
		if (opcion == 5) {
			system("cls");

			if (obj->getMapa().size() == 0) {
				cout << "Debe crear una tabla primero" << endl;
				system("pause");
				goto volver;
			}

			map<string, Columna*> mapa = obj->getMapa();
			map<string, Columna*>::iterator i;
			int sel;

			for (i = mapa.begin(); i != mapa.end(); i++) {
				cout << "Desea indexar la columna " << i->first << "? (1: si, 0: no): ";
				cin >> sel;

				if (sel == 1)
					obj->indexar(i->first);
			}
			
			system("pause");
		}
		if (opcion == 6) {
			system("cls");
			string nom;

			if (obj->getMapa().size() == 0) {
				cout << "Debe crear una tabla primero" << endl;
				system("pause");
				goto volver;
			}

			cout << "Escriba el nombre de la columna que desea ordenar: ";
			cin >> nom;

			system("pause");
		}
	} while (opcion != 0);

	cout << endl;
	system("pause");
	delete obj;
	return 0;
}