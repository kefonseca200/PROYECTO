#include <iostream>
#include <string>
using namespace std;


struct Contacto {
    string nombre;
    string telefono;
    string correo;
};


class ArrayList {
private:
    Contacto* datos;
    int capacidad;
    int cantidad;

    void expandir() {
        capacidad *= 2;
        Contacto* nuevo = new Contacto[capacidad];
        for (int i = 0; i < cantidad; i++) { // Copiar los contactos existentes al nuevo arreglo
            nuevo[i] = datos[i];
        }
        delete[] datos; //Libera el arreglo anterior
        datos = nuevo; // Se remplaza por el nuevo
    }

public:
    ArrayList(int cap = 10) {
        capacidad = cap;
        cantidad = 0;
        datos = new Contacto[capacidad];
    }

    //Agregar contacto al final del arreglo
    void agregarContacto(Contacto c) {
        if (cantidad == capacidad)
            expandir();
        datos[cantidad++] = c;
    }

    Contacto obtener(int i) {
        return datos[i];
    }

    int size() { return cantidad; }

    void set(int i, Contacto c) {
        datos[i] = c;
    }

    // Enlista los contactos por  su nombre
    void ListaPorNombre() {
        for (int i = 0; i < cantidad - 1; i++) {
            for (int j = 0; j < cantidad - i - 1; j++) {
                if (datos[j].nombre > datos[j + 1].nombre) {
                    Contacto temp = datos[j];
                    datos[j] = datos[j + 1];
                    datos[j + 1] = temp;
                }
            }
        }
    }

    // Enlista los contactos por su numero de telefono
    void ListaPorTelefono() {
        for (int i = 0; i < cantidad; i++) {
            int minIdx = i;
            for (int j = i + 1; j < cantidad; j++) {
                if (datos[j].telefono < datos[minIdx].telefono)
                    minIdx = j;
            }
            Contacto temp = datos[i];
            datos[i] = datos[minIdx];
            datos[minIdx] = temp;
        }
    }
};


int buscarLineal(ArrayList& lista, string nombre) {
    for (int i = 0; i < lista.size(); i++) {
        if (lista.obtener(i).nombre == nombre)
            return i;
    }
    return -1;
}

int busquedaBinaria(ArrayList& lista, string nombre) {
    int inicio = 0, fin = lista.size() - 1;
    while (inicio <= fin) {
        int mid = (inicio + fin) / 2;
        string actual = lista.obtener(mid).nombre;

        if (actual == nombre) return mid;
        if (actual < nombre) inicio = mid + 1;
        else fin = mid - 1;
    }
    return -1;
}
