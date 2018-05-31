#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p1(){

	printf("~~prueba arbol vacio\n\n");
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

	printf("~~guardar en el arbol\n\n");
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

	printf("~~arbol\n\n");
	printf(".....b\n");
	printf(".../...\\ \n");
	printf("..a.....c\n\n");

	print_test("arbol cantidad 3", abb_cantidad(abb) == 3);
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

	printf("~~ Llenar arbol un poco mas complejo\n\n");
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

	printf("\narbol~~\n\n");
	printf(".........d\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....b.......g\n");
	printf("..../.\\...../.\\ \n");
	printf("...a...c...f...h \n");
	printf("........../\n");
	printf(".........e\n\n");

	print_test("arbol cantidad 8", abb_cantidad(abb) == 8);
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

void p4(){

	printf("~~Borrar datos del arbol binario--\n\n");
	abb_t* abb = abb_crear(strcmp, NULL);

	char* clave1 = "a";
	char* clave2 = "b";
	char* clave3 = "c";
	char* clave4 = "d";
	char* clave5 = "e";
	char* clave6 = "f";
	char* clave7 = "g";
	char* clave8 = "h";

	int dato1 = 1;
	int dato2 = 2;
	int dato3 = 3;
	int dato4 = 4;
	int dato5 = 5;
	int dato6 = 6;
	int dato7 = 7;
	int dato8 = 8;


	printf("~~~ caso hoja raiz ~~~~\n");
	print_test("Arbol vacio", abb_cantidad(abb) == 0);
	print_test("guardo dato1", abb_guardar(abb,clave1,&dato1));
  print_test("arbol cantidad 1 ", abb_cantidad(abb) == 1);
	print_test("(a) pertenece ", abb_pertenece(abb,clave1));
	print_test("(a) borrar ", *(int*)abb_borrar(abb,clave1) == 1);
	print_test("(a) no pertenece ", !abb_pertenece(abb,clave1));
	print_test("arbol vacio" ,abb_cantidad(abb) == 0);

	printf("~~~caso hoja no raiz~~~\n");

	print_test("guardo dato4", abb_guardar(abb,clave4,&dato4));
	print_test("guardo dato2", abb_guardar(abb,clave2,&dato2));
	print_test("guardo dato3", abb_guardar(abb,clave3,&dato3));
	print_test("guardo dato7", abb_guardar(abb,clave7,&dato7));
	print_test("guardo dato1", abb_guardar(abb,clave1,&dato1));
	print_test("guardo dato6", abb_guardar(abb,clave6,&dato6));
	print_test("guardo dato8", abb_guardar(abb,clave8,&dato8));
	print_test("guardo dato5", abb_guardar(abb,clave5,&dato5));

	printf("\narbol~~\n\n");
	printf(".........d\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....b.......g\n");
	printf("..../.\\...../.\\ \n");
	printf("...a...c...f...h \n");
	printf("........../\n");
	printf(".........e\n\n");

	print_test("cantidad 8", abb_cantidad(abb) == 8);
	print_test("(d) borrar ", *(int*)abb_borrar(abb,clave4) == 4);
	print_test("(f) borrar ", *(int*)abb_borrar(abb,clave6) == 6);
	print_test("(e) borrar ", *(int*)abb_borrar(abb,clave5) == 5);
	print_test("cantidad 5", abb_cantidad(abb) == 5);
	print_test("(b) borrar ", *(int*)abb_borrar(abb,clave2) == 2);
	/*
	print_test("cantidad 8", abb_cantidad(abb) == 8);
	print_test("(a) borrar ", *(int*)abb_borrar(abb,clave1) == 1);
	print_test("(c) borrar ", *(int*)abb_borrar(abb,clave3) == 3);
	print_test("(e) borrar ", *(int*)abb_borrar(abb,clave5) == 5);
	print_test("(h) borrar ", *(int*)abb_borrar(abb,clave8) == 8);
	print_test("cantidad 4", abb_cantidad(abb) == 4);
	print_test("(a) no pertenece ", !abb_pertenece(abb,clave1));
	print_test("(c) no pertenece ", !abb_pertenece(abb,clave3));
	print_test("(e) no pertenece ", !abb_pertenece(abb,clave5));
	print_test("(d) no pertenece ", !abb_pertenece(abb,clave8));

	printf("\narbol~~\n\n");
	printf(".........d\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....b.......g\n");
	printf("..../.\\...../.\\ \n");
	printf("...x...x...f...x \n");
	printf("........../\n");
	printf(".........x\n\n");

	print_test("(d) pertenece ", abb_pertenece(abb,clave4));
	print_test("(b) pertenece ", abb_pertenece(abb,clave2));
	print_test("(g) pertenece ", abb_pertenece(abb,clave6));
	print_test("(f) pertenece ", abb_pertenece(abb,clave7));

	printf("\n~~prueba con 1 hijos~~\n");
	print_test("guardo dato3", abb_guardar(abb,clave3,&dato3));

	printf("\narbol~~\n\n");
	printf(".........d\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....b.......g\n");
	printf("......\\...../. \n");
	printf(".......c...f. \n\n");


	print_test("cantidad 5", abb_cantidad(abb) == 5);
	print_test("(b) borrar ", *(int*)abb_borrar(abb,clave2) == 2);
	print_test("(g) borrar ", *(int*)abb_borrar(abb,clave6) == 6);

	printf("\narbol~~\n\n");
	printf(".........d\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....x.......x\n");
	printf("......\\...../. \n");
	printf(".......c...f. \n\n");

	printf("\narbol~~\n\n");
	printf(".........d\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....c.......f\n\n");


	print_test("cantidad 3", abb_cantidad(abb) == 3);
	print_test("(c) pertenece ", abb_pertenece(abb,clave3));
	print_test("(d) pertenece ", abb_pertenece(abb,clave4));
	print_test("(f) pertenece ", abb_pertenece(abb,clave7));
	print_test("(b) no pertenece", !abb_pertenece(abb,clave2));
	print_test("(g) no pertenece", !abb_pertenece(abb,clave6));

	print_test("(d) borrar", *(int*)abb_borrar(abb,clave4) == 4);

	printf("\narbol~~\n\n");
	printf(".........x\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....c.......f\n\n");

	print_test("cantidad 2", abb_cantidad(abb) == 2);
	print_test("(d) no pertenece", !abb_pertenece(abb,clave4));
	print_test("(c) pertenece", abb_pertenece(abb,clave3));
	print_test("(f) pertenece", abb_pertenece(abb,clave7));
	print_test("(f) borrar", *(int*)abb_borrar(abb,clave7) == 7);

	printf("\narbol~~\n\n");
	printf(".........x\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....c.......x\n\n");

	printf("\narbol~~\n\n");
	printf(".........c\n\n");

	print_test("cantidad 1", abb_cantidad(abb) == 1);
	print_test("(d) no pertenece", !abb_pertenece(abb,clave4));
	print_test("(c) pertenece", abb_pertenece(abb,clave3));

	print_test("(f) borrar", abb_borrar(abb,clave7));

	printf("\narbol~~\n\n");
	printf(".........d\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....c.......x\n\n");

	print_test("cantidad 2", abb_cantidad(abb) == 2);
	print_test("(f) no pertenece", !abb_pertenece(abb,clave7));
	print_test("(c) pertenece", abb_pertenece(abb,clave3));
	print_test("(d) pertenece", abb_pertenece(abb,clave4));
	print_test("(d) borrar", *(int*)abb_borrar(abb,clave4) == 4);

	printf("\narbol~~\n\n");
	printf(".........d\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....c.......x\n\n");

	printf("\narbol~~\n\n");
	printf(".........x\n");
	printf("......./...\\..\n");
	printf("....../.....\\ \n");
	printf(".....c.......x\n\n");

	printf("\narbol~~\n\n");
	printf(".........c\n\n");

	print_test("cantidad 1", abb_cantidad(abb) == 1);
	print_test("(d) no pertenece", !abb_pertenece(abb,clave4));
	print_test("(c) pertenece", abb_pertenece(abb,clave3));
	print_test("guardo dato 4", abb_guardar(abb,clave4,&dato4));

	printf("\narbol~~\n\n");
	printf(".........c\n");
	printf("..........\\..\n");
	printf("...........d \n");

	print_test("(c) borrar", *(int*)abb_borrar(abb,clave3) == 3);
	printf("\narbol~~\n\n");
	printf(".........x\n");
	printf("..........\\..\n");
	printf("...........d \n");

	printf("\narbol~~\n\n");
	printf(".........d\n\n");

	print_test("cantidad 1", abb_cantidad(abb) == 1);
	print_test("(c) no pertenece", !abb_pertenece(abb,clave3));
	print_test("(d) pertenece", abb_pertenece(abb,clave4));*/

	abb_destruir(abb);
}



void pruebas_abb_alumno()
{
	p1();
	p2();
	p3();
	p4();
}
