#include <math.h>
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"

//Declaracion Struct

struct NodeGrafo{
    Nivel* nivel;
    List* nivelAdesbloquear;
    bool completado;
};

typedef struct{
    Enemigo* e;
    Personaje* p;
    Objeto* o;
}Nivel;

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
    int Dano_Cantidad_Armadura;

}Objeto;

typedef struct{

    char Nombre_Enemigo[30];
    int Vida;
    int Dano;

}Enemigo;

//Funcion para leer el k-esimo elemento de un string (separado por comas)
char *get_csv_field(char *linea, int indice){
    char *campo = (char *) malloc(100 * sizeof(char *)); // Guarda el string a retornar
    int i = 0; // Recorre la linea
    int k = 0; // Cuenta las comas
    int n = 0; // Recorre el campo
    bool coma = false;
    while(linea[i] != '\0'){
        if(linea[i] == '\"'){
            coma = !coma;
        }
        if(k == indice){
            if(linea[i] != '\"'){
                campo[n] = linea[i];
                n++;
            }
        }
        i++;
        if(linea[i] == ',' && !coma){
            k++;
            i++;
        }
        if(k > indice || linea[i] == '\0' || linea[i] == '\n'){
            campo[n] = '\0';
            return campo;
        }
    }
    return NULL;
}
void menu();

int main(){
    int num;
    bool flag = true;
    menu();
    scanf("%d",&num);
    while(num<1||num>3){
        printf("Introdusca un numero valido: ");
        scanf("%d", &num);
    }
    while (flag){
        switch (num){
            case 0:{
                printf("Programa finalizado");
                flag=false;
                break;
            }
	        case 1:{

            }
            case 2:{

            }
            case 3:{

            }
        }
        if (num==3){
            break;
        }
        printf("\n");
        printf("Ingrese otro valor: ");
        scanf("%d", &num);
        while(num<1||num>3){
            printf("Introdusca un numero valido: ");
            scanf("%d", &num);
        }
    }
return 0;
}

void menu(){
    printf("1. Iniciar Partida\n");
    printf("2. Ver Macadores\n");
    printf("3. Salir\n");
    printf("Introdusca un numero: ");
}


