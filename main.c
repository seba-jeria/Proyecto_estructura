#include <math.h>
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"
#include "treemap.h"

//Declaracion Struct

/*struct NodeGrafo{
    Nivel* Nivel;
    List* NivelaDesbloquear;
    bool Completado;
};

typedef struct{
    Enemigo* e;
    Personaje* p;
    Objeto* o;
}Nivel;*/

typedef struct{

    char Nombre_Item[30];
    char Tipo[30];
    int Dano_Cantidad_Armadura;

}Objeto;

typedef struct{

    char Nombre_Usuario[30];
    int Vida;
    int Oro;
    Objeto* Arma;
    Objeto* Armadura;

}Personaje;

typedef struct{

    char Nombre_Enemigo[30];
    int Vida;
    int Dano;

}Enemigo;

typedef struct {
    char nombre[30];
    int puntaje;
}Usuario;



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

int lower_than_int(void* , void* );
void agregarVideojuego(TreeMap *, void* , Usuario*);
void mostrar(TreeMap *, Pair *, Pair* (avanzar)(TreeMap *mapa));


int main(){
    int num;
    bool flag = true;

    TreeMap* Marcadores = createTreeMap(lower_than_int);

    Usuario* u = (Usuario*)malloc(sizeof(Usuario));
    Personaje* p = (Personaje*)malloc(sizeof(Personaje));

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

                char ing_nombre;

                printf("Ingrese nombre personaje: ");
                fflush(stdin);
                scanf("%[^\n]", ing_nombre);

                

                break;
            }
            case 2:{

                int k=0;
                int opcion;

                FILE *fp = fopen ("PuntajesM.csv","r");

                // Cadena para guardar la linea completa del archivo csv
                char linea[1024];
                fgets (linea, 1023, fp);
                while (fgets (linea, 1023, fp) != NULL){ // Se lee la linea 

                    strcpy(u->nombre, get_csv_field(linea, 0));
                    u->puntaje = atoi(get_csv_field(linea, 1)); 

                    agregarVideojuego(Marcadores, &(u->puntaje), u);
                    
                    u = (Usuario*)malloc(sizeof(Usuario));

                    k++; 
                    if(k==51) break;
                }

                mostrar(Marcadores, lastTreeMap(Marcadores), prevTreeMap);

                printf("1. Para exportar o 2. Para salir: ");
                scanf("%d", &opcion);
                while(opcion<1 || opcion>2){
                    printf("Introduzca una opcion valida: ");
                    fflush(stdin);
                    scanf("%d", &opcion);
                }
                if (opcion == 1){
                    char nombre_archivo2[30];
                    strcpy(nombre_archivo2, "Marcadores.csv");
                    FILE *fp = fopen (nombre_archivo2, "w");
                    fprintf(fp,"Nombre,Puntaje\n");
                    Pair *pair = lastTreeMap(Marcadores);
                    while(pair) {
                        List *lista = pair->value;
                        Usuario* u = firstList(lista);
                        while(u) {
                            fprintf(fp,"%s,%d\n", u->nombre, u->puntaje);
                            u = nextList(lista);
                        }
                        pair = prevTreeMap(Marcadores);
                    }
                    fclose(fp);
                    break;
                }
                else{
                    break;
                }
            }
        }
        if (num==3){
            printf("Juego finalizado");
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

int lower_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
}


void agregarVideojuego(TreeMap *mapa, void* clave, Usuario* videojuego) {
    Pair *pair = searchTreeMap(mapa, clave);
    List *listaVideojuegos = NULL;

    // No existe la clave en el mapa
    if (pair == NULL) {
        listaVideojuegos = createList();
        insertTreeMap(mapa, clave, listaVideojuegos);
    }
    // Si existe 
    else {
        listaVideojuegos = pair->value;
    }
    pushBack(listaVideojuegos, videojuego);
}

void mostrar(TreeMap *mapa, Pair *primero, Pair* (avanzar)(TreeMap *mapa)) {
    Pair *pair = primero;
    while(pair) {
        List *lista = pair->value;
        Usuario* u = firstList(lista);
        while(u) {
            printf("%s / %d\n", u->nombre, u->puntaje);
            u = nextList(lista);
        }
        pair = avanzar(mapa);
    }
}