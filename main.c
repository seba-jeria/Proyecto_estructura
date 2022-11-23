#include <math.h>
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"
#include "treemap.h"
//#include "combate.h"
//#include "grafo.h"

//Declaracion Struct

typedef struct{

    char Nombre_Item[30];
    char Tipo[30];
    int Dano_Cantidad_Armadura;
    int Nivel_o;

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
    int nivel_e;

}Enemigo;

typedef struct{

    Enemigo* enemigo;
    Objeto* objeto;
    NodoGrafo* nodoizquierdo;
    NodoGrafo* nododerecha;

}NodoGrafo;

typedef struct{
    
    HashMap* Niveles;
    NodoGrafo* nodoinicial;
    NodoGrafo* nodoactual;

}Grafo;

typedef struct{

    char nombreNivel;
    int camino_der;
    int camino_izq;

}Nivel;

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
void submenu();
int lower_than_int(void* , void* );
void agregarVideojuego(TreeMap *, void* , Usuario*);
void mostrar(TreeMap *, Pair *, Pair* (avanzar)(TreeMap *mapa));

void avanzar();
void Mostrarinventario();
void Mostrarestado();
bool esnemigo(NodoGrafo*);
void combatir();
void tomarobjeto();
void mostrarinfoenemigo();
void motrarinfoobjeto();

//cargar objetos y enemigos, despues cargar los niveles
void Cargarenemigos(HashMap*);
void Cargarobjetos(HashMap*);
void CargarNiveles(Grafo*);

Grafo* grafo;


int main(){
    int num;
    bool flag = true;

    TreeMap* Marcadores = createTreeMap(lower_than_int);
    HashMap* Mapaenemigo = (Enemigo*)malloc(sizeof(Enemigo));
    Cargarenemigos(Mapaenemigo);
    HashMap* Mapaobjeto = (Objeto*)malloc(sizeof(Objeto));
    Cargarobjetos(Mapaobjeto);
    grafo = (Grafo*)malloc(sizeof(Grafo));
    CargarNiveles(grafo);

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
	        case 1:{

                char ing_nombre;
                int opcion, aux;

                printf("Ingrese nombre personaje: ");
                fflush(stdin);
                scanf("%[^\n]", ing_nombre);

                submenu();
                fflush(stdin);
                scanf("%d", &opcion);

                while(1){
                    switch (opcion){
                        case 1:{
                            avanzar();
                            break;
                        }
                        case 2:{
                            Mostrarinventario();
                            break;
                        }
                        case 3:{
                            Mostrarestado();
                            break;
                        }
                        if (num==4){
                            printf("Juego finalizado");
                            break;
                        }
                        printf("\n");
                        printf("Ingrese otro valor: ");
                        scanf("%d", &aux);
                        while(aux<1||aux>4){
                            printf("Introdusca un numero valido: ");
                            scanf("%d", &aux);
                        }
                    }
                }
            }
            case 2:{

                int opcion;

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

void submenu(){
    printf("1. Avanzar\n");
    printf("2. Mostrar inventario\n");
    printf("3. Mostrar estado\n");
    printf("4. Rendirse\n");
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

bool esenmigo(NodoGrafo* n){
    if(n->enemigo == NULL){
        return false;
    }
    return true;
}

void avanzar(){
    int opcion;
    if(grafo->nodoactual == NULL){
        grafo->nodoactual = grafo->nodoinicial;
    }
    else{
        NodoGrafo* nd = grafo->nodoactual->nododerecha;
        NodoGrafo* ni = grafo->nodoactual->nodoizquierdo;

        printf("Camino derecho: ");
        if(esnemigo(nd)){
            mostrarinfoenemigo(nd->enemigo);
        }
        else{
            motrarinfoobjeto(nd->objeto);
        }

        printf("Camino izquierdo: ");
        if(esnemigo(ni)){
            mostrarinfoenemigo(ni->enemigo);
        }
        else{
            motrarinfoobjeto(ni->objeto);
        }
        
        printf("1. Izquierda o 2. Derecha: ");
        fflush(stdin);
        scanf("%d", &opcion);
        if (opcion == 1){
            grafo->nodoactual = grafo->nodoactual->nodoizquierdo;
        }
        else{
            grafo->nodoactual = grafo->nodoactual->nododerecha;
        }
    }

    if(esnemigo(grafo->nodoactual)){
        combatir();
    }
    else{
        tomarobjeto();
    }
}


void Cargarenemigos(HashMap* Map){
    Enemigo* e = (Enemigo*)malloc(sizeof(Enemigo));
    int k=0;
    FILE *fp = fopen ("Enemigos.csv","r");
    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    fgets (linea, 1023, fp);
    while (fgets (linea, 1023, fp) != NULL){ // Se lee la linea 

        strcpy(e->Nombre_Enemigo, get_csv_field(linea, 0)); 
        e->Dano = atoi(get_csv_field(linea, 1));
        e->Vida = atoi(get_csv_field(linea, 2));
        e->nivel_e = atoi(get_csv_field(linea, 3));
                    
        insertMap(Map, e->Nombre_Enemigo, e);
                    
        e = (Enemigo*)malloc(sizeof(Enemigo));

        k++; 
        if(k==51) break;
    }
}

void Cargarobjetos(HashMap* Map){
    Objeto* o = (Objeto*)malloc(sizeof(Objeto));
    int k=0;
    FILE *fp = fopen ("Objetos.csv","r");
    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    fgets (linea, 1023, fp);
    while (fgets (linea, 1023, fp) != NULL){ // Se lee la linea 

        strcpy(o->Nombre_Item, get_csv_field(linea, 0)); 
        strcpy(o->Tipo, get_csv_field(linea, 1)); 
        o->Dano_Cantidad_Armadura = atoi(get_csv_field(linea, 2));
        o->Nivel_o = atoi(get_csv_field(linea, 3));
                    
        insertMap(Map, o->Nombre_Item, o);
                    
        o = (Objeto*)malloc(sizeof(Objeto));

        k++; 
        if(k==51) break;
    }
}

void CargarNiveles(Grafo* G){
    Nivel* n = (Nivel*)malloc(sizeof(Nivel));
    int k=0;
    FILE *fp = fopen ("Niveles.csv","r");
    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    fgets (linea, 1023, fp);
    while (fgets (linea, 1023, fp) != NULL){ // Se lee la linea 

        strcpy(n->nombreNivel, get_csv_field(linea, 0)); 
        n->camino_izq = atoi(get_csv_field(linea, 1));
        n->camino_der = atoi(get_csv_field(linea, 2));
                    
        insertMap(G->Niveles, n->nombreNivel, n);
                    
        n = (Nivel*)malloc(sizeof(Nivel));

        k++; 
        if(k==51) break;
    }
}