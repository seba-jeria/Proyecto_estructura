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
    int Dano_vida_Armadura;
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
    int Nivel_e;

}Enemigo;

typedef struct NodoGrafo NodoGrafo;

struct NodoGrafo{

    Enemigo* enemigo;
    Objeto* objeto;
    NodoGrafo* nodoizquierdo;
    NodoGrafo* nododerecha;

};

typedef struct{
    
    TreeMap* Niveles;
    NodoGrafo* nodoinicial;
    NodoGrafo* nodoactual;

}Grafo;

typedef struct{

    char nombreNivel[30];
    char camino_der[30];
    char camino_izq[30];

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
void submenuinventario();
void submenucombate();

int lower_than_int(void* , void* );
void mostrar(TreeMap *, Pair *, Pair* (avanzar)(TreeMap *mapa));

//cargar objetos y enemigos, despues cargar los niveles
void Cargarenemigos(HashMap*);
void Cargarobjetos(HashMap*);
void CargarNiveles(Grafo*);

void avanzar();
void Mostrarinventario();
void Mostrarestado();
bool esenemigo(NodoGrafo*);
void combatir(Enemigo*);
void tomarobjeto();

Grafo* grafo;
HashMap* Mapaenemigo;
HashMap* Mapaobjeto;
HashMap* Mapainventario;
Personaje* personaje;

int main(){
    int num, opcion;

    //TreeMap* Marcadores = createTreeMap(lower_than_int);
    Mapaenemigo = createMap(55);
    Mapaobjeto = createMap(55);
    Mapainventario = createMap(55);
    grafo = (Grafo*)malloc(sizeof(Grafo));
    Cargarenemigos(Mapaenemigo);
    Cargarobjetos(Mapaobjeto);
    CargarNiveles(grafo);

    //Usuario* u = (Usuario*)malloc(sizeof(Usuario));
    personaje = (Personaje*)malloc(sizeof(Personaje));

    menu();
    scanf("%d",&num);
    while(num<1||num>3){
        printf("Introdusca un numero valido: ");
        scanf("%d", &num);
    }

    while (1){
        switch (num){
	        case 1:{

                char ing_nombre[30];
                int aux;

                Objeto* aux_objeto1 = (Objeto*)malloc(sizeof(Objeto));
                Pair_2* aux_pairO = (Pair_2*)malloc(sizeof(Pair_2));
                aux_pairO = searchMap(Mapaobjeto, "Ropa de campesino");
                aux_objeto1 = aux_pairO->value;
                personaje->Armadura = aux_objeto1;
                insertMap(Mapainventario, aux_objeto1->Nombre_Item, aux_objeto1);

                aux_pairO = searchMap(Mapaobjeto, "Punos");
                aux_objeto1 = aux_pairO->value;
                personaje->Arma = aux_objeto1;
                insertMap(Mapainventario, aux_objeto1->Nombre_Item, aux_objeto1);

                printf("Ingrese nombre personaje: ");
                fflush(stdin);
                scanf("%[^\n]", ing_nombre);
                strcpy(personaje->Nombre_Usuario, ing_nombre);
                personaje->Vida = 100;
                personaje->Oro = 0;

                printf("\n");

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
                    }
                    if (opcion == 4 || (personaje->Vida <= 0)){
                        break;
                    }
                    submenu();
                    scanf("%d", &opcion);
                    printf("\n");
                    while(opcion<1||opcion>4){
                        printf("Introdusca un numero valido: ");
                        scanf("%d", &opcion);
                    }
                }
            }
            case 2:{

                /*int opcion;

                cargarusuario();

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
                }*/
                break;
            }
        }
        if (num==3 || (personaje->Vida <= 0) || opcion == 4){
            printf("Has acabado tu aventura");
            break;
        }
        printf("\n");
        printf("Ingrese otro valor: ");
        fflush(stdin);
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

void submenucombate(){
    printf("1. Atacar\n");
    printf("2. Curar\n");
    printf("3. Huir\n");
    printf("Introdusca un numero: ");
}

void submenuinventario(){
    printf("1. Equipar arma\n");
    printf("2. Equipar rmadura\n");
    printf("3. Curar\n");
    printf("4. salir del inventario\n");
    printf("Introdusca un numero: ");
}

int lower_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
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

bool esenemigo(NodoGrafo* n){
    if(n->enemigo == NULL){
        return false;
    }
    return true;
}

void combatir(Enemigo* e){
    int opcion;
    Objeto* pocion = (Objeto*)malloc(sizeof(Objeto));
    Pair_2* pair_o = (Pair_2*)malloc(sizeof(Pair_2));
    e = grafo->nodoactual->enemigo;
    submenucombate();
    fflush(stdin);
    scanf("%d", &opcion);
    printf("Vida personaje: %d", personaje->Vida);
    printf("Armadura: %d", personaje->Armadura->Dano_vida_Armadura);
    printf("Vida enemigo: %d", e->Vida);
    while(personaje->Vida>0 && e->Vida>0){
        switch (opcion){
            case 1:{
                e->Vida -= personaje->Arma->Dano_vida_Armadura;
                if (e->Vida < 0) break;
                else personaje->Vida -= e->Dano;
                break;
            }
            case 2:{
                //??????????????????????
                pair_o = searchMap(Mapainventario, "Pocion de vida");
                if(pair_o != NULL){
                    pocion = pair_o->value;
                    personaje->Vida += pocion->Dano_vida_Armadura;
                    eraseMap(Mapaenemigo, "Pocion de vida");
                    break;
                }
                printf("No tienes pociones de vida");
                break;
            }
        }
        if (opcion == 3){
            printf("Cobarde...");
            personaje->Oro -= 100;
            break;
        }
        printf("Vida personaje: %d", personaje->Vida);
        printf("Armadura: %d", personaje->Armadura->Dano_vida_Armadura);
        printf("Vida enemigo: %d", e->Vida);

        printf("\n");
        printf("Ingrese otro valor: ");
        fflush(stdin);
        scanf("%d", &opcion);
        while(opcion<1||opcion>3){
            printf("Introdusca un numero valido: ");
            scanf("%d", &opcion);
        }
    }
}

void tomarobjeto(){
    insertMap(Mapainventario, grafo->nodoactual->objeto->Nombre_Item, grafo->nodoactual->objeto);
}

void avanzar(){
    Pair* aux = firstTreeMap(grafo->Niveles);
    Nivel* niveles = aux->value;
    while(personaje->Vida>0 || aux==NULL){
        int opcion;
        if(grafo->nodoactual == NULL){
            grafo->nodoactual = grafo->nodoinicial;
        }
        else{
            printf("1. Izquierda o 2. Derecha: ");
            fflush(stdin);
            scanf("%d", &opcion);
            if (opcion == 1){
                grafo->nodoactual = grafo->nodoactual->nodoizquierdo;
                Pair_2* aux_izq = searchMap(Mapaenemigo,niveles->camino_izq);
                if(aux_izq==NULL){
                    aux_izq = searchMap(Mapaobjeto,niveles->camino_izq);
                    Objeto* objeto_izq = aux_izq->value;
                    grafo->nodoactual->objeto = objeto_izq;
                }
                else{
                    Enemigo* enemigo_izq = aux_izq->value;
                    grafo->nodoactual->enemigo = enemigo_izq;
                }
            }
            else{
                grafo->nodoactual = grafo->nodoactual->nododerecha;
                Pair_2* aux_der = searchMap(Mapaenemigo,niveles->camino_der);
                if(aux_der==NULL){
                    aux_der = searchMap(Mapaobjeto,niveles->camino_der);
                    Objeto* objeto_der = aux_der->value;
                    grafo->nodoactual->objeto= objeto_der;
                }
                else{
                    Enemigo* enemigo_der = aux_der->value;
                    grafo->nodoactual->enemigo= enemigo_der;
                }
            }
        }
        if(esenemigo(grafo->nodoactual)){
            printf("Te has encontrado con un enemigo");
            combatir(grafo->nodoactual->enemigo);
        }
        else{
            printf("Te has encontrado con un objeto");
            tomarobjeto();
        }
        aux = nextTreeMap(grafo->Niveles);
    }
}

void Mostrarinventario(){
    printf("\n");
    Pair_2* pair_o = firstMap(Mapainventario);
    Objeto* o = pair_o->value;
    while(pair_o != NULL){
        o = pair_o->value;
        printf("%s / %s / %d / %d\n",o->Nombre_Item, o->Tipo, o->Dano_vida_Armadura, o->Nivel_o);
         pair_o = nextMap(Mapainventario);
    }

    int opcion;
    char aux_objeto[30];
    Objeto* pocion = (Objeto*)malloc(sizeof(Objeto));
    pair_o = (Pair_2*)malloc(sizeof(Pair_2));
    submenuinventario();
    fflush(stdin);
    scanf("%d", &opcion);
    printf("\n");
    while(1){
        switch (opcion){
            case 1:{
                printf("Introduzca el nombre del arma: ");
                fflush(stdin);
                scanf("%[^\n]", aux_objeto);
                pair_o = searchMap(Mapainventario, aux_objeto);
                /*if(pair_o->value == NULL){
                    printf("Objeto no encontrado");
                    break;
                }
                else{
                    personaje->Arma = pair_o->value;
                    break;
                }*/
                personaje->Arma = pair_o->value;
                break;
            }
            case 2:{
                printf("Introduzca el nombre de la armadura: ");
                fflush(stdin);
                scanf("%[^\n]", aux_objeto);
                pair_o = searchMap(Mapainventario, aux_objeto);
                /*if(pair_o->value == NULL){
                    printf("Objeto no encontrado");
                    break;
                }
                else{
                    personaje->Armadura = pair_o->value;
                    break;
                }*/
                personaje->Armadura = pair_o->value;
                break;
            }
            case 3:{
                pair_o = searchMap(Mapainventario, "Pocion de vida");
                if(pair_o != NULL){
                    pocion = pair_o->value;
                    personaje->Vida += pocion->Dano_vida_Armadura;
                    eraseMap(Mapaenemigo, "Pocion de vida");
                    break;
                }
                printf("No tienes pociones de vida");
                break;
            }
        }
        if (opcion == 4){
            printf("\n");
            break;
        }
        printf("\n");
        submenuinventario();
        fflush(stdin);
        scanf("%d", &opcion);
        while(opcion<1||opcion>4){
            printf("Introdusca un numero valido: ");
            scanf("%d", &opcion);
        }
    }
}

void Mostrarestado(){
    printf("\n");
    printf("Vida personaje: %d\n", personaje->Vida);
    printf("Armadura: %s / %d\n", personaje->Armadura->Nombre_Item, personaje->Armadura->Dano_vida_Armadura);
    printf("Arma: %s / %d\n", personaje->Arma->Nombre_Item, personaje->Arma->Dano_vida_Armadura);
    printf("Oro: %d\n", personaje->Oro);
    printf("\n");
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
        e->Nivel_e = atoi(get_csv_field(linea, 3));
                    
        insertMap(Map, e->Nombre_Enemigo, e);
                    
        e = (Enemigo*)malloc(sizeof(Enemigo));

        k++; 
        if(k==10) break;
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
        o->Dano_vida_Armadura = atoi(get_csv_field(linea, 2));
        o->Nivel_o = atoi(get_csv_field(linea, 3));
                    
        insertMap(Map, o->Nombre_Item, o);
                    
        o = (Objeto*)malloc(sizeof(Objeto));

        k++; 
        if(k==11) break;
    }
}

void CargarNiveles(Grafo* G){
    Nivel* n = (Nivel*)malloc(sizeof(Nivel));
    TreeMap* auxtree = createTreeMap(lower_than_int);
    int k=0;
    FILE *fp = fopen ("Niveles.csv","r");
    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    fgets (linea, 1023, fp);
    while (fgets (linea, 1023, fp) != NULL){ // Se lee la linea 

        strcpy(n->nombreNivel, get_csv_field(linea, 0));
        strcpy(n->camino_izq, get_csv_field(linea, 1));
        strcpy(n->camino_der, get_csv_field(linea, 2));
                    
        insertTreeMap(auxtree, n->nombreNivel, n);
        
        n = (Nivel*)malloc(sizeof(Nivel));

        k++; 
        if(k==11) break;
    }
    G->Niveles = auxtree;
}