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

//Aquí realizo una lista enlazada para eliminar contactos

struct Nodo {
    Contacto dato;
    Nodo* sig;
};

class ListaEnlazada {
public:
    Nodo* head;
    ListaEnlazada() { head = NULL; }

    //Insertar al inicio de la lista.
    void insertar(Contacto c) {
        Nodo* nuevo = new Nodo();
        nuevo->dato = c;
        nuevo->sig = head;
        head = nuevo;
    }

    //Eliminar contacto por nombre
    void eliminar(string nombre) {
        Nodo* actual = head;
        Nodo* anterior = NULL;

        while (actual != NULL) {
            if (actual->dato.nombre == nombre) {
                if (anterior == NULL) head = actual->sig;
                else anterior->sig = actual->sig;

                delete actual;
                cout << "El contacto se elimino de manera correcta.\n";
                return;
            }

            anterior = actual;
            actual = actual->sig;
        }
        cout << "No se ha encontrado el contacto que buscas.\n";
    }
};

//Utilizo una pila para el hsitorial de operaciones
struct NodoPila {
    string operacion;
    NodoPila* sig;
};

class Pila {
public:
    NodoPila* top;

    Pila() { top = NULL; }

    //Agrega las operaciones al historial
    void push(string op) {
        NodoPila* nuevo = new NodoPila();
        nuevo->operacion = op;
        nuevo->sig = top;
        top = nuevo;
    }

    //Muestra el historial de operaciones
    void mostrar() {
        NodoPila* aux = top;
        cout << "\n HISTORIAL DE OPERACIONES\n";
        while (aux != NULL) {
            cout << aux->operacion << endl;
            aux = aux->sig;
        }
    }
};

// En esta parte utilizo una cola para los contactos pendientes.
struct NodoCola {
    Contacto dato;
    NodoCola* sig;
};

class Cola {
public:
    NodoCola* frente;
    NodoCola* fin;

    Cola() { frente = fin = NULL; }

    //Envia el contacto al final
    void encolar(Contacto c) {
        NodoCola* nuevo = new NodoCola();
        nuevo->dato = c;
        nuevo->sig = NULL;
        if (fin == NULL) frente = fin = nuevo;
        else {
            fin->sig = nuevo;
            fin = nuevo;
        }
    }

    bool vacia() {
        return frente == NULL;
    }
    //Saca al primero de la cola.
    Contacto desencolar() {
        if (vacia()) {
            cout << "Cola vacia\n";
            return Contacto{};
        }
        NodoCola* temp = frente;
        frente = frente->sig;
        Contacto c = temp->dato;
        delete temp;
        if (frente == NULL) fin = NULL;
        return c;
    }
};

// Lista de contactos
struct NodoArbol {
    Contacto dato;
    NodoArbol* izq;
    NodoArbol* der;
};

class BST {
public:
    NodoArbol* raiz;

    BST() { raiz = NULL; }

    NodoArbol* insertarNodo(NodoArbol* r, Contacto c) {
        if (r == NULL) {
            r = new NodoArbol();
            r->dato = c;
            r->izq = r->der = NULL;
            return r;
        }
        if (c.nombre < r->dato.nombre)
            r->izq = insertarNodo(r->izq, c);
        else
            r->der = insertarNodo(r->der, c);

        return r;
    }

    void insertar(Contacto c) {
        raiz = insertarNodo(raiz, c);
    }

    // Recorre en inorden
    void inorden(NodoArbol* r) {
        if (r == NULL) return;
        inorden(r->izq);
        cout << r->dato.nombre << " | " << r->dato.telefono << " | " << r->dato.correo << endl;
        inorden(r->der);
    }
};