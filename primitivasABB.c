#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "abb.h"

#define RAMA_DERECHA 1
#define RAMA_IZQUIERDA -1

//---------- struct iterador
struct abb_iter{
	const abb_t* abb;
	pila_t* pila;
};



abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t* abb = malloc (sizeof(abb_t));

  if (!abb) return NULL;

  //vinculo funciones
  abb->comparar_clave = cmp;
  abb->destruir_dato = destruir_dato;

  //incializo miembros
  abb->cantidad = 0;
  abb->raiz = NULL;

  return abb;
}

abb_nodo_t* abb_nodo_buscar(abb_t* arbol,abb_nodo_t* nodo,const char* clave){
  if (!nodo) return NULL;
  if (arbol->comparar_clave(clave,nodo->clave)==0) return nodo;
  if (arbol->comparar_clave(clave,nodo->clave)<0) return abb_nodo_buscar(arbol,nodo->izquierda,clave);
  return abb_nodo_buscar(arbol,nodo->derecha,clave);
}

abb_nodo_t* abb_padre_buscar(abb_t* arbol,abb_nodo_t* padre,const char* clave){
  //if (!padre) return NULL;
  if (arbol->comparar_clave(clave,padre->clave)==0) return padre;
  if (arbol->comparar_clave(clave,padre->clave)<0){
    if (!padre->izquierda) return padre;
    return abb_nodo_buscar(arbol,padre->izquierda,clave);
  }
  if (!padre->derecha) return padre;
  return abb_nodo_buscar(arbol,padre->derecha,clave);
}

void* abb_obtener(const abb_t* arbol,const char* clave){
  abb_nodo_t* nodo=abb_nodo_buscar(arbol,arbol->raiz,clave);
  if (!nodo) return NULL;
  return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  abb_nodo_t* nodo=abb_nodo_buscar(arbol,arbol->raiz,clave);
  if (!nodo) return false;
  return true;
}

size_t abb_cantidad(abb_t* arbol){
  return arbol->cantidad;
}

bool abb_guardar(abb_t* arbol, const char* clave, void* dato){

  if (!arbol->raiz){
    abb_nodo_t* nodo=nodo_crear(clave,dato);

    if (!nodo) return false;

    arbol->cantidad++;
    arbol->raiz=nodo;
    return true;
  }

  abb_nodo_t* nodo=abb_nodo_buscar(arbol,arbol->raiz,clave);

  if (nodo){

    if (arbol->destruir_dato) arbol->destruir_dato(nodo->dato);

    nodo->dato=dato;
    return true;
  }

  arbol->cantidad++;
  abb_nodo_t* hijo=nodo_crear(clave,dato);
  abb_nodo_t* padre=abb_padre_buscar(arbol,arbol->raiz,clave);

  if (arbol->comparar_clave(clave,padre->clave)<0) padre->izquierda=hijo;

  else padre->derecha=hijo;

  return true;/*
  int rama = arbol->comparar(clave , arbol->clave);

  if ( rama == RAMA_DERECHA ){

    if( arbol->der ){
    }
    else{
      abb_nodo_t* nodo = nodo_crear(clave, dato);

      if(!nodo) return false;

      arbol->der = nodo;
      arbol->cantidad++;
      return true;
    }
  }

  if ( rama == RAMA_IZQUIERDA ){
    if( arbol->der ){
    }
    else{
      abb_nodo_t* nodo = nodo_crear(clave, dato);

      if(!nodo) return false;

      arbol->der = nodo;
      arbol->cantidad++;
      return true;
    }
  }

  /* si caigo aca es por las claves son identicas

      ... hacer esto

 */
}

/*******************************************************************************
 *                           ITERADOR INTERNO
 ******************************************************************************/
void abb_iter_in_order(abb_nodo_t* nodo,bool visitar(const char* clave, void* dato, void* extra),void* extra){
  if (!nodo) return;
  abb_iter_in_order(nodo->izquierda,visitar,extra);
  bool seguir=visitar(nodo->clave,nodo->dato,extra);
  if (!seguir) return;
  abb_iter_in_order(nodo->derecha,visitar,extra);
}

void abb_in_order(abb_t* arbol, bool visitar(const char* clave, void* dato, void* extra), void* extra){
  abb_iter_in_order(arbol->raiz,visitar,extra);
}
