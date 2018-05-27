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
 *	idea del arbol
 *					b
 *			  /	  \
 *			a			 c
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

/*
 *						 d
 *					/			\
 *				b				 g
 *			/  \			/	\
 *		a			c    f   h
 *							/
 *						 e
 */
void p3(){
	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "a";
	char* clave2 = "b";
	char* clave3 = "c";
	char* clave4 = "d";
	char* clave5 = "e";
	char* clave6 = "f";
	char* clave7 = "g";
	char* clave8 = "h";
	char* clave9 = "noesta";

	int dato1 = 1;
	int dato2 = 2;
	int dato3 = 3;
	int dato4 = 4;
	int dato5 = 5;
	int dato6 = 6;
	int dato7 = 7;
	int dato8 = 8;


	print_test("Arbol vacio", abb_cantidad(abb) == 0);
	print_test("guardo dato4", abb_guardar(abb,clave4,&dato4));
	print_test("guardo dato2", abb_guardar(abb,clave2,&dato2));
	print_test("guardo dato3", abb_guardar(abb,clave3,&dato3));
	print_test("guardo dato7", abb_guardar(abb,clave7,&dato7));
	print_test("guardo dato1", abb_guardar(abb,clave1,&dato1));
	print_test("guardo dato6", abb_guardar(abb,clave6,&dato6));
	print_test("guardo dato8", abb_guardar(abb,clave8,&dato8));
	print_test("guardo dato5", abb_guardar(abb,clave5,&dato5));

	print_test("(a) pertenece ", abb_pertenece(abb,clave1));
	print_test("(b) pertenece ", abb_pertenece(abb,clave2));
	print_test("(c) pertenece ", abb_pertenece(abb,clave3));
	print_test("(d) pertenece ", abb_pertenece(abb,clave4));
	print_test("(e) pertenece ", abb_pertenece(abb,clave5));
	print_test("(f) pertenece ", abb_pertenece(abb,clave6));
	print_test("(g) pertenece ", abb_pertenece(abb,clave7));
	print_test("(h) pertenece ", abb_pertenece(abb,clave8));
	print_test("(noesta) no pertenece ", !abb_pertenece(abb,clave9));

	abb_destruir(abb);

}

void pruebas_abb_alumno()
{
	p1();
	p2();
	p3();
}
