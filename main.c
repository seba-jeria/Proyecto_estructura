
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>


//Declaracion Struct

typedef struct{

    char Nombre_Usuario[30];
    int Vida;
    int Oro;
    Objeto Arma;
    Objeto Armadura;

}Personaje;

typedef struct{

    char Nombre_Item[30];
    char Tipo[30];
    int Daño_Cantidad_Armadura;

}Objeto;

typedef struct{

    int Vida;
    int Daño;

}Enemigo;



