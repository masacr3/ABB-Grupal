/*
  Leo: hola marto vamos a hacer las pruebas en bloque unas vez constatado el OK
  lo mandamos directamente pruebas_alumno.c

*/
#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p1(){
		abb_t* abb = abb_crear(strcmp, NULL);
  	char* clave = "leo";

  	print_test("cantidad es 0", abb_cantidad(abb) == 0);
  	print_test("obtener false", !abb_obtener(abb,clave));
 		print_test("borrar false", !abb_borrar(abb,clave));
  	print_test("pertenece false", !abb_pertenece(abb,clave));

  	abb_destruir(abb);
}


/*
	idea del arbol

					b
			  /	  \
			a			 c
*/
void p2(){
	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "a";
	char* clave2 = "b";
	char* clave3 = "c";
	char* clave4 = "d";

	int dato1 = 1;
	int dato2 = 2;
	int dato3 = 3;

	print_test("Arbol vacio", abb_cantidad(abb) == 0);
	print_test("guardo dato", abb_guardar(abb,clave2,&dato2));
	print_test("guardo dato2", abb_guardar(abb,clave1,&dato1));
	print_test("guardo dato3", abb_guardar(abb,clave3,&dato3));

	print_test("(a) pertenece ", abb_pertenece(abb,clave1));
	print_test("(b) pertenece ", abb_pertenece(abb,clave2));
	print_test("(c) pertenece ", abb_pertenece(abb,clave3));
	print_test("(d) no pertenece ", !abb_pertenece(abb,clave4));

	abb_destruir(abb);
}


void pruebas_abb_alumno()
{
    p1();
		p2();
}
