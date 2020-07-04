#include <iostream>
#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include "Arbol.h"
using namespace std;

class Columna {
	string nombre;
	string tipo;
	bool indexada;
public:
	vector<string> datos;
	Columna(string nombre, string tipo) : nombre(nombre), tipo(tipo), indexada(false) {}
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
	string getDato(int pos) {
		return datos[pos];
	}
	void add(string elem) {
		datos.push_back(elem);
	}

};

class Fila {
	int numero;
public:
	Fila(int num) : numero(num) {}
	int getNum() {
		return numero;
	}
	string getDato(map<string, Columna*> columnas, string nombreColumna) {
		return columnas[nombreColumna]->getDato(numero);
	}
	void imprimirFila(map<string, Columna*> columnas) {
		cout << setw(0);
		for (auto i = columnas.begin(); i != columnas.end(); i++)
			cout << columnas[i->first]->getDato(numero) << setw(15);
		cout << endl;
	}
};

class Tabla {
	string nomAux;
public:
	map<string, Columna*> columnas;
	vector<Fila*> filas;
	map<string, Arbol<Fila*, string, nullptr>*> arboles;
	void addColumna(string nombre, string tipo) {
		columnas[nombre] = new Columna(nombre, tipo);
	}
	void addDatos(string nombreColumna, string dato) {
		columnas[nombreColumna]->datos.push_back(dato);
	}
	vector<string> getDatos(string nombreColumna) {
		return columnas[nombreColumna]->datos;
	}
	void addFila(Fila* fila) {
		filas.push_back(fila);
	}
	string getNomColumna(Columna* columna) {
		return columna->getNombre();
	}
	void mostrarTabla(map<string, Columna*> columnas, vector<Fila*> filas) {
		for (auto i = columnas.begin(); i != columnas.end(); i++)
			cout << i->first << setw(15);
		cout << endl << endl;
		for (int i = 0; i < filas.size(); i++)
			filas[i]->imprimirFila(columnas);
	}
	void indexar(string nombreColumna) {
		auto k = [=](Fila* fila) {return fila->getDato(columnas, nombreColumna); };
		arboles[nombreColumna] = new Arbol<Fila*, string, nullptr>(k);

		for (auto fila : filas)
			arboles[nombreColumna]->add(fila);

		nomAux = nombreColumna;
	}
	void ordenar(string nombreColumna) {
		indexar(nombreColumna);
		arboles[nombreColumna]->inorder([=](Fila* fila) { fila->imprimirFila(columnas); });
	}
	void seleccionar(map<string, Columna*> mapa) {
		mostrarTabla(mapa, filas);
	}
	void filtrarIgual(string dato) {
		vector<Fila*> f;

		for (auto i = columnas.begin(); i != columnas.end(); i++) {
			auto j = find(columnas[i->first]->datos.begin(), columnas[i->first]->datos.end(), dato);
			if (j != columnas[i->first]->datos.end())
				arboles[i->first]->find(dato, f);
		}
		mostrarTabla(columnas, f);
	}
	void filtrarMayor(string dato) {
		vector<Fila*> f;

		for (auto i = columnas.begin(); i != columnas.end(); i++) {
			auto j = find(columnas[i->first]->datos.begin(), columnas[i->first]->datos.end(), dato);
			if (j != columnas[i->first]->datos.end())
				arboles[i->first]->findMa(dato, f);
		}
		mostrarTabla(columnas, f);
	}
	void filtrarMenor(string dato) {
		vector<Fila*> f;

		for (auto i = columnas.begin(); i != columnas.end(); i++) {
			auto j = find(columnas[i->first]->datos.begin(), columnas[i->first]->datos.end(), dato);
			if (j != columnas[i->first]->datos.end())
				arboles[i->first]->findMi(dato, f);
		}
		mostrarTabla(columnas, f);
	}
	void filtrarInicio(string dato, string nombreColumna) {
		vector<Fila*> f;

		arboles[nombreColumna]->findX(dato, f);
		mostrarTabla(columnas, f);
	}
	void exportarArchivo() {
		string nombre;

		cout << "Ingrese el nombre del archivo: ";
		cin >> nombre;

		ofstream archivo(nombre);

		for (auto i = columnas.begin(); i != columnas.end(); i++)
			archivo << i->first << " ";
		archivo << endl << endl;
		archivo << setw(0);
		for (int i = 0; i < filas.size(); i++) {
			for (auto j = columnas.begin(); j != columnas.end(); j++) {
				archivo << columnas[j->first]->getDato(filas[i]->getNum()) << " ";
			}
			archivo << endl;
		}

		archivo.close();
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
	cout << "    7. Filtrar                                *" << endl;
	cout << "*   8. Exportar                               *" << endl;
	cout << "*   0. Salir                                  *" << endl;
	cout << "*                                             *" << endl;
	cout << "***********************************************" << endl;
}

int main() {
	Tabla* tabla = new Tabla();
	int opcion;

volver:;
	do {
		system("cls");
		menuPrincipal();
		cin >> opcion;

		if (opcion == 1) {
			system("cls");
			int num;

			cout << "Ingrese cuantas columnas desea: ";
			cin >> num;

			string nombre, tipo;

			for (int i = 0; i < num; i++) {
				cout << "Ingrese el nombre de la columna " << i + 1 << ": ";
				cin >> nombre;
				cout << "Ingrese el tipo de la columna: ";
				cin >> tipo;
				tabla->addColumna(nombre, tipo);
			}

			cout << "La tabla se ha creado correctamente" << endl;
			system("pause");
		}
		if (opcion == 2) {
			system("cls");
			string dato;

			if (tabla->columnas.size() == 0) {
				cout << "Debe crear una tabla primero" << endl;
				system("pause");
				goto volver;
			}
			
			string nom;

			for (auto i = tabla->columnas.begin(); i != tabla->columnas.end(); i++) {
				cout << "Ingrese el dato de la columna " << i->first << ": ";
				cin >> dato;
				tabla->addDatos(i->first, dato);

				if (i == tabla->columnas.begin())
					nom = i->first;
			}
			
			tabla->addFila(new Fila(tabla->columnas[nom]->datos.size() - 1));
			system("pause");
		}
		if (opcion == 3) {
			system("cls");

			if (tabla->columnas.size() == 0) {
				cout << "Debe crear una tabla primero" << endl;
				system("pause");
				goto volver;
			}

			tabla->mostrarTabla(tabla->columnas, tabla->filas);
			cout << endl;
			system("pause");
		}
		if (opcion == 4) {
			system("cls");
			int op;

			if (tabla->columnas.size() == 0) {
				cout << "Debe crear una tabla primero" << endl;
				system("pause");
				goto volver;
			}

			map<string, Columna*> selec = tabla->columnas;

			for (auto i = selec.begin(); i != selec.end();) {
				cout << "Desea seleccionar la columna " << i->first << "? (1: si, 0: no): ";
				cin >> op;

				if (op == 0)
					i = selec.erase(i);
				else
					i++;
			}
			
			cout << endl;
			tabla->seleccionar(selec);

			cout << endl << endl;
			cout << "Desea exportar la tabla? (1: si, 0: no): ";
			cin >> op;

			if (op == 1)
				tabla->exportarArchivo();

			system("pause");
		}
		if (opcion == 5) {
			system("cls");
			int rep;

			map<string, Columna*> aux = tabla->columnas;

			for (auto i = aux.begin(); i != aux.end(); i++) {
				cout << "Desea indexar la columna " << i->first << "? (1: si, 0: no): ";
				cin >> rep;

				if (rep == 1)
					tabla->indexar(i->first);
			}

			system("pause");
		}
		if (opcion == 6) {
			system("cls");
			string columna;

			cout << "Ingrese el nombre de la columna que desea ordenar: ";
			cin >> columna;

			tabla->ordenar(columna);

			int op;
			cout << endl << endl;
			cout << "Desea exportar la tabla? (1: si, 0: no): ";
			cin >> op;

			if (op == 1)
				tabla->exportarArchivo();

			system("pause");
		}
		if (opcion == 7) {
			system("cls");
			int op2;
			
			cout << "*   1. Igual a                                *" << endl;
			cout << "*   2. Mayor que                              *" << endl;
			cout << "*   3. Menor que                              *" << endl;
			cout << "*   4. Inicia con                             *" << endl;
			cout << "*   5. Finaliza con                           *" << endl;
			cout << "*   6. Esta contenido en                      *" << endl;
			cout << "*   7. No esta contenido en                   *" << endl;
			cout << "    Ingrese el filtro que desea: ";
			cin >> op2;

			string dato;

			if (op2 == 1) {
				system("cls");

				cout << "Ingrese el dato a buscar: ";
				cin >> dato;

				tabla->filtrarIgual(dato);
				system("pause");
			}
			if (op2 == 2) {
				system("cls");

				cout << "Ingrese el dato de referencia: ";
				cin >> dato;

				tabla->filtrarMayor(dato);
				system("pause");
			}
			if (op2 == 3) {
				system("cls");

				cout << "Ingrese el dato de referencia: ";
				cin >> dato;

				tabla->filtrarMenor(dato);
				system("pause");
			}
			if (op2 == 4) {
				system("cls");
				string nom;

				cout << "Ingrese el nombre de la columna donde quiere buscar: ";
				cin >> nom;
				cout << "Ingrese la letra con la que empieza: ";
				cin >> dato;

				tabla->filtrarInicio(dato, nom);
				system("pause");
			}
			
			cout << "Desea exportar la tabla? (1: si, 0: no): ";
			cin >> op2;

			if (op2 == 1) {
				tabla->exportarArchivo();
				cout << "Se ha exportado satisfactoriamente" << endl;
			}
			system("pause");
		}
		if (opcion == 8) {
			system("cls");
			tabla->exportarArchivo();
			cout << "Se ha exportado satisfactoriamente" << endl;
			system("pause");
		}
	} while (opcion != 0);

	cout << endl;
	system("pause");
	delete tabla;
	return 0;
}