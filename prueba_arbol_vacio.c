/*
  Leo: hola marto vamos a hacer las pruebas en bloque unas vez constatado el OK 
  lo mandamos directamente pruebas_alumno.c

*/

void p1(){
	abb_t* abb = abb_crear(strcmp, NULL);
  	char* clave = "leo";
  
  	print_test("cantidad es 0", abb_cantidad(abb) == 0);
  	print_test("obtener false", !abb_obtener(abb,clave));
 	print_test("borrar false", !abb_borrar(abb,clave));
  	print_test("pertenece false", !abb_pertenece(abb,clave));
  
  	abb_destruir(abb);
}
