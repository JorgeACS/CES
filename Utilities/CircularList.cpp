//
// Created by Jorge on 6/6/2017.
//

#include "CircularList.h"

class NoHayMemoria: public Excepcion{
public:
    NoHayMemoria():Excepcion("La cadena no es valida."){}
};
class ListaCircularVacia: public Excepcion{
public:
    ListaCircularVacia():Excepcion("Lista vacia."){}
};

///////////////////////Destructor
template<class T>
ListaCircular<T>::~ListaCircular()
{
    vaciar();
}
//////////////////////Constructor de copias
template<class T>
ListaCircular<T>::ListaCircular(const ListaCircular &P)
{
    cabecera = NULL;
    tam = 0;
    *this = P;
}
/////////////////////////Operador =
template<class T>
ListaCircular<T>& ListaCircular<T>::operator=(const ListaCircular<T> &P)
{
    if (!(this==&P))
    {
        vaciar();
        cabecera = new Elemento<T>(P.cabecera->info);
        Elemento<T>*aux = cabecera;
        Elemento<T>*actual = P.cabecera;
        for(int i = 0; i < P.tam; i++){
            actual=actual->sig;
            Elemento<T>*nuevo = new (std::nothrow) Elemento<T>(actual->info);
            if(nuevo == NULL)throw NoHayMemoria();
            aux->sig = nuevo;
            aux=aux->sig;
            tam++;
        }
        aux->sig=cabecera;
    }
    return *this;
}
////////////////////////Insercion de elemento en ListaCircular
template<class T>
void ListaCircular<T>::insertar(T info)
{
    if(cabecera == NULL) {
        cabecera = new (std::nothrow) Elemento<T>(info);
        if(cabecera==NULL)throw NoHayMemoria();
        cabecera->sig = cabecera;
    }
    else{
        Elemento<T> *nuevo;
        nuevo = new Elemento<T>(info, cabecera->sig);
        if (nuevo == NULL) throw NoHayMemoria();
        cabecera->sig=nuevo;
    }
    tam++;
}
//////////////////////////Quitar elemento de la ListaCircular
template<class T>
bool ListaCircular<T>::remover(T info)
{
    for(int i = 0; i < tam;i++){
        if(!(cabecera->sig->info == info)) cabecera = cabecera->sig;
        else{
            Elemento<T> * aux = cabecera->sig;
            T borrar = aux->info;
            cabecera->sig = aux->sig;
            delete aux;
            tam--;
            if(tam == 0)cabecera = NULL;
            return true;
        }
    }
    return false;
}
//////////////////////////Remover elemento (Para destructor)
template<class T>
void ListaCircular<T>::destroy()
{
    if(cabecera != NULL)
    {
        Elemento<T> * aux = cabecera;
        cabecera = cabecera->sig;
        delete aux;
        tam--;
        if(tam==0)cabecera=NULL;
    }
}
/////////////////////////////////////////Busqueda publica
template<class T>
bool ListaCircular<T>::buscarElemento(T info)
{
    for(int i = 0; i < tam;i++){
        if(cabecera->sig->info != info) cabecera = cabecera->sig;
        else{
            return true;
        }
    }
    return false;
}
/////////////////////////////////Sobrecarga de impresion
template<class T>
std::ostream & operator << (std::ostream &out, const ListaCircular<T> &P)
{
    if (! ( P.estaVacia() ) )
    {
        Elemento<T> * actual = P.cabecera;
        out << std::endl;
        for (int i = 0; i < P.tam; i++)
        {
            out <<  actual->info <<",";
            actual = actual->sig;
        }
        out<<"\b ";
    }
    else out << "No hay elementos..";
    return out;
}
