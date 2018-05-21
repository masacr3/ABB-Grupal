#implementacion nodos

/*
	La idea es subir contenido despues fusionamos todo el contenido en un solo archivo
	(leo)
*/

typedef struct nodo nodo_t;

struct nodo {
    char *clave; // recien estube leyendo arboles B, B+, B*
    void *dato;
    nodo_t *izq;
    nodo_t *der;
};

nodo_t* nodo_crear(const char* clave, void* dato ){
  nodo_t* nodo = malloc( sizeof(nodo_t) );

  if(!nodo) return NULL;

  char* clave_copia = malloc ( sizeof(char) * (strlen(clave) + 1) );

  if(!clave_copia){
    free(nodo);
    return NULL;
  } 

  //copio la clave
  strcopy(clave_copia,clave);
  
  nodo->dato = dato;
  nodo->clave = clave_copia;
  nodo->izq = NULL;
  nodo->der = NULL;

  return nodo;
}
