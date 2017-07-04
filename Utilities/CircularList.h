//
// Created by Jorge on 6/6/2017.
//

#ifndef UNTITLED_CIRCULARLIST_H
#define UNTITLED_CIRCULARLIST_H

#include <iostream>
#include <new>
#include <stdio.h>
#include <string.h>
//////////////////////////Declaracion anticipada de clases y funciones amigas
template <class T = int> class Elemento;
template <class T = int> class ListaCircular;
template <class T> std::ostream & operator <<(std::ostream &, const ListaCircular<T> &);

template <class T>
class ListaCircular
{
public:
    friend std::ostream & operator << <>(std::ostream &, const ListaCircular<T> &);
    ListaCircular():cabecera(NULL),tam(0) {}
    ListaCircular(const ListaCircular &);
    ~ListaCircular();
    ListaCircular<T> & operator=(const ListaCircular<T> &);
    void insertar(T);
    void vaciar(){while(!estaVacia()) destroy();}
    bool buscarElemento(T);
    bool remover(T);
    int numeroElementos() {return tam;}
    bool estaVacia() const{return (cabecera == NULL);}
private:
    void destroy();
    Elemento<T> *cabecera;
    int tam;
};

///////////////////////////////Plantilla de clase Elemento
template <class T> class Elemento
{
    friend class ListaCircular<T>;
    friend std::ostream & operator << <> (std::ostream &, const  ListaCircular <T> &);
public:
    Elemento(T _info, Elemento * _sig = NULL): info(_info),sig(_sig) {}
private:
    T info;
    Elemento *sig;
};

class Excepcion{
public:
    Excepcion(const char *m){strcpy(mensaje, m);}
    char *getMensaje(){return mensaje;}

private:
    char mensaje[100];
};



#endif //UNTITLED_CIRCULARLIST_H
