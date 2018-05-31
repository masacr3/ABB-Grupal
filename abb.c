#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#include <stdio.h>

#include "abb.h"
#include "pila.h"

#define RAMA_DERECHA 1
#define RAMA_IZQUIERDA -1

typedef struct nodo abb_nodo_t;

struct nodo {
    char* clave;
    void* dato;
    abb_nodo_t* izquierda;
    abb_nodo_t* derecha;
};

abb_nodo_t* nodo_crear(const char* clave, void* dato ){
  abb_nodo_t* nodo = malloc( sizeof(abb_nodo_t) );

  if (!nodo) return NULL;

  char* clave_copia = malloc(sizeof(char) * (strlen(clave) + 1) );

  if (!clave_copia){
    free(nodo);
    return NULL;
  }

  strcpy(clave_copia,clave);

  nodo->dato = dato;
  nodo->clave = clave_copia;
  nodo->izquierda = NULL;
  nodo->derecha = NULL;

  return nodo;
}

void nodo_destruir(abb_nodo_t* nodo,abb_destruir_dato_t destruir_dato){
  if (destruir_dato) destruir_dato(nodo->dato);
  free(nodo->clave);
  free(nodo);
}

struct abb {
    abb_comparar_clave_t comparar_clave;
    abb_destruir_dato_t destruir_dato;

    abb_nodo_t* raiz;
    size_t cantidad;
};

struct abb_iter{
  pila_t* pila;
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t* abb = malloc (sizeof(abb_t));

  if (!abb) return NULL;

  abb->comparar_clave = cmp;
  abb->destruir_dato = destruir_dato;

  abb->cantidad = 0;
  abb->raiz = NULL;

  return abb;
}

//buscar

abb_nodo_t* abb_nodo_buscar(const abb_t *arbol, abb_nodo_t* raiz ,const char *clave){

  if (!raiz) return false;

  int rama = arbol->comparar_clave(clave, raiz->clave);

  if(rama == 0) return raiz;

  if(rama > 0) return abb_nodo_buscar(arbol, raiz->derecha,clave);

  return abb_nodo_buscar(arbol, raiz->izquierda,clave);
}

abb_nodo_t* abb_padre_buscar(const abb_t* arbol,abb_nodo_t* padre,const char* clave){
  if (!padre) return NULL;

  int rama = arbol->comparar_clave(clave,padre->clave);

  if( rama > 0 && padre->derecha){
      int es_el_padre = arbol->comparar_clave(clave, padre->derecha->clave) == 0;

      return es_el_padre ? padre : abb_padre_buscar(arbol, padre->derecha, clave);
  }

  if( rama < 0 && padre->izquierda){
      int es_el_padre = arbol->comparar_clave(clave, padre->izquierda->clave) == 0;

      return es_el_padre ? padre : abb_padre_buscar(arbol, padre->izquierda,clave);
  }

  return NULL;

}

void* buscar_padre(abb_t* arbol, const char* clave){
  abb_nodo_t* nodo = abb_padre_buscar(arbol, arbol->raiz, clave);

  printf("padre es %d", !nodo ? 101009 : *(int*)nodo->dato);

  return !nodo ? NULL : nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  abb_nodo_t* nodo = abb_nodo_buscar(arbol, arbol->raiz,clave);

  return !nodo ? false : true;
}

void* abb_obtener(const abb_t* arbol,const char* clave){
  abb_nodo_t* nodo = abb_nodo_buscar(arbol, arbol->raiz,clave);

  return !nodo ? NULL : nodo->dato;
}

size_t abb_cantidad(abb_t* arbol){
  return arbol->cantidad;
}


bool insertar_nodo (abb_t* arbol,abb_nodo_t* raiz, const char* clave, void* dato){
  int rama = arbol->comparar_clave(clave,raiz->clave);

  if(rama == 0){

    if (arbol->destruir_dato) arbol->destruir_dato(raiz->dato);

    //actualizo
    raiz->dato = dato;
    arbol->cantidad++;
  }

  if(rama < 0 ){

    if(raiz->izquierda) return insertar_nodo(arbol,raiz->izquierda,clave,dato);

    abb_nodo_t* nodo = nodo_crear(clave,dato);

    if(!nodo) return false;

    raiz->izquierda = nodo;
    arbol->cantidad++;
  }

  if (rama > 0 ){

    if(raiz->derecha) return insertar_nodo(arbol,raiz->derecha,clave,dato);

    abb_nodo_t* nodo = nodo_crear(clave,dato);

    if(!nodo) return false;

    raiz->derecha = nodo;
    arbol->cantidad++;
  }
  return true;
  //sigue buscando
  //return insertar_nodo(arbol, rama == RAMA_DERECHA ? raiz->derecha : raiz->izquierda, clave, dato);
}


bool abb_guardar(abb_t* arbol, const char* clave, void* dato){

  if (!arbol->raiz){
    abb_nodo_t* nodo=nodo_crear(clave,dato);

    if (!nodo) return false;

    arbol->cantidad++;
    arbol->raiz=nodo;
    return true;
  }

  return insertar_nodo(arbol, arbol->raiz, clave, dato);
}



void* abb_borrar_nodo_hoja(abb_t* arbol,abb_nodo_t* nodo,abb_nodo_t* padre,const char* clave){
  arbol->cantidad--;
  void* dato=nodo->dato;

  if ( padre ){
    if (padre->izquierda && arbol->comparar_clave(clave,padre->izquierda->clave)==0) padre->izquierda=NULL;
    else padre->derecha=NULL;

  }
  //la hoja es la raiz
  else arbol->raiz = NULL;

  nodo_destruir(nodo,NULL);
  return dato;
}

void* abb_borrar_nodo_un_hijo(abb_t* arbol,abb_nodo_t* nodo,abb_nodo_t* padre,const char* clave){
  arbol->cantidad--;
  void* dato=nodo->dato;

  /*
  if (padre->izquierda && arbol->comparar_clave(clave,padre->izquierda->clave)==0){
    if (nodo->izquierda) padre->izquierda=nodo->izquierda;
    else padre->izquierda=nodo->derecha;
  }
  else{
    if (nodo->izquierda) padre->derecha=nodo->izquierda;
    else padre->derecha=nodo->derecha;
  }
  */

  if ( padre ){

    if ( padre->derecha && padre->derecha == nodo ) padre->derecha = nodo->derecha ? nodo->derecha : nodo->izquierda;
    else padre->izquierda = nodo->izquierda ? nodo->izquierda : nodo->derecha;

  }
  // quieren borrar la raiz
  else arbol->raiz = nodo->derecha ? nodo->derecha : nodo->izquierda;


  nodo_destruir(nodo,NULL);
  return dato;
}

abb_nodo_t* abb_nodo_profundo_buscar(abb_nodo_t* nodo){
  if (!nodo) return NULL;
  if (!nodo->izquierda) return nodo;
  return abb_nodo_profundo_buscar(nodo->izquierda);
}

void* abb_borrar_nodo_dos_hijos(abb_t* arbol,abb_nodo_t* nodo, abb_nodo_t* padre){
  /*abb_nodo_t* hijo_derecho=nodo->derecha;
  abb_nodo_t* nodo_profundo=abb_nodo_profundo_buscar(hijo_derecho->izquierda);
  char* clave_reemplazante;
  const char* clave_constante;
  void* dato_reemplazante;
  if (!nodo_profundo){
    clave_reemplazante=hijo_derecho->clave;
    clave_constante=clave_reemplazante;
    dato_reemplazante=abb_borrar(arbol,clave_constante);
  }
  else{
    clave_reemplazante=nodo_profundo->clave;
    clave_constante=clave_reemplazante;
    dato_reemplazante=abb_borrar(arbol,clave_constante);
  }
  void* dato=nodo->dato;
  nodo->clave=clave_reemplazante;
  nodo->dato=dato_reemplazante;
  return dato;
  */

  void* dato;

  if ( !nodo->derecha->izquierda ){
    dato = nodo->dato;

    if (padre){
      if ( padre->derecha && arbol->comparar_clave(nodo->clave, padre->deracha->clave) == 0) padre->derecha = nodo->derecha;
      else padre->izquierda = nodo->derecha;
    }
    else{
      nodo->derecha->izquierda = nodo->izquierda;
      abb->raiz = nodo->derecha->izquierda;
    }

    //fijate que explota ahora no explota
    nodo_destruir(nodo, null); // esto explota
  }
  else{

    abb_nodo_t* susesor = abb_nodo_profundo_buscar(nodo->derecha->izquierda);

    abb_nodo_t* padre_susesor = abb_padre_buscar(abb, nodo->derecha->izquierda, susesor->clave );

    if ( susesor->derecha) padre_susesor->izquierda = susesor->derecha;
    else padre_susesor->izquierda = NULL;

    //swap nodo

    susessor->derecha = nodo->derecha;
    susessor->izquierda = nodo->izquierda;

    //if borras la raiz .. arbol->raiz = susessor;

    if (padre){
      if ( padre->derecha && arbol->comparar_clave(nodo->clave, padre->deracha->clave) == 0) padre->derecha = susessor;
      else padre->izquierda = susessor;
    }
  }

}

void* abb_borrar(abb_t* arbol, const char* clave){

  if (arbol->cantidad==0) return NULL;

  abb_nodo_t* nodo=abb_nodo_buscar(arbol,arbol->raiz,clave);

  if (!nodo) return NULL;

  abb_nodo_t* padre=abb_padre_buscar(arbol,arbol->raiz,clave);

  if (!nodo->izquierda && !nodo->derecha) return abb_borrar_nodo_hoja(arbol,nodo,padre,clave);

  if (!nodo->izquierda || !nodo->derecha) return abb_borrar_nodo_un_hijo(arbol,nodo,padre,clave);

  return abb_borrar_nodo_dos_hijos(arbol,nodo);
}

void abb_destruir_nodos(abb_nodo_t* nodo,abb_destruir_dato_t destruir_dato){
  if (!nodo) return;
  abb_destruir_nodos(nodo->izquierda,destruir_dato);
  abb_destruir_nodos(nodo->derecha,destruir_dato);
  nodo_destruir(nodo,destruir_dato);
}

void abb_destruir(abb_t* arbol){
  abb_destruir_nodos(arbol->raiz,arbol->destruir_dato);
  free(arbol);
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

/*******************************************************************************
 *                         ITERADOR EXTERNO
 ******************************************************************************/
void apilar_hijos_izquierdos(pila_t* pila,abb_nodo_t* nodo){
  if (!nodo) return;
  pila_apilar(pila,nodo);
  return apilar_hijos_izquierdos(pila,nodo->izquierda);
}

abb_iter_t* abb_iter_in_crear(const abb_t* arbol){
  abb_iter_t* iter=malloc(sizeof(abb_iter_t));
  if (!iter) return NULL;
  iter->pila=pila_crear();
  apilar_hijos_izquierdos(iter->pila,arbol->raiz);
  return iter;
}

bool abb_iter_in_avanzar(abb_iter_t* iter){
  if (pila_esta_vacia(iter->pila)) return false;
  abb_nodo_t* nodo=pila_desapilar(iter->pila);
  apilar_hijos_izquierdos(iter->pila,nodo->derecha);
  return true;
}

const char* abb_iter_in_ver_actual(const abb_iter_t* iter){
  if (pila_esta_vacia(iter->pila)) return NULL;
  abb_nodo_t* nodo_actual=pila_ver_tope(iter->pila);
  return nodo_actual->clave;
  //return pila_esta_vacia(iter->pila)? NULL:pila_ver_tope(iter->pila)->clave;
}

bool abb_iter_in_al_final(const abb_iter_t* iter){
  return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
  pila_destruir(iter->pila);
  free(iter);
}
