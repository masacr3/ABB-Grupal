#gratis
#leo

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
