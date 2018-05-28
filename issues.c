#la raiz es sin const.
abb_nodo_t* abb_buscar_nodo(const abb_t *arbol, abb_nodo_t* raiz ,const char *clave){

  if (!raiz) return false;

  int rama = arbol->comparar_clave(clave, raiz->clave);

  if(rama == 0) return nodo;

  if(rama > 0) return abb_buscar_nodo(arbol, raiz->derecha,clave);

  return abb_buscar_nodo(arbol, raiz->izquierda,clave);
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  abb_nodo_t* nodo = abb_buscar_nodo(arbol, arbol->raiz,clave);
  
  return !nodo ? false : true;
}

void* abb_obtener(const abb_t* arbol,const char* clave){
  abb_nodo_t* nodo = abb_buscar_nodo(arbol, arbol->raiz,clave);
  
  return !nodo ? NULL : nodo->dato;
}


