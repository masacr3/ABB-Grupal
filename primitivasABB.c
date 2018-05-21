#gratis
#leo

#define RAMA_DERECHA 1
#define RAMA_IZQUIERDA -1

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t* abb = malloc (sizeof(abb_t));

  if(!abb) return NULL;

  //vinculo funciones
  abb->comparar_clave = cmp;
  abb->destruir_dato = destruir_dato;

  //incializo miembros
  abb->cantidad = 0;
  abb->raiz = NULL; 

  return abb;
}

size_t abb_cantidad(abb_t *arbol){
  return arbol->cantidad;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
  //tenemos que comparar las claves
  // lo vi en la pagina de los algoritmos

  int rama = arbol->comparar ( clave , arbol->clave );

  if ( rama == RAMA_DERECHA ){

    if( arbol->der ){
    }
    else{
      nodo_t* nodo = nodo_crear(clave, dato);

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
      nodo_t* nodo = nodo_crear(clave, dato);

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
