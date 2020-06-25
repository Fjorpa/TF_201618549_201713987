#ifndef __TABLA_H__
#define __TABLA_H__
#include <string>
#include "Columna.h"
#include "Fila.h"

class Tabla {
public:
	void agregarColumna(Columna* col);
	void agregarFila();
	void filtrar();
	void seleccionar();
	void indexar(string nombreColumna);
	string getString(int numFila, string nombreColumna);
};

#endif