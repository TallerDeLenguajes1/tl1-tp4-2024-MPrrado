#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


struct
{
    int tareaID; //autoincremental comenzando en 1000
    char *descripcion; //
    int duracion; //entre 10-100
}typedef Tarea;



typedef struct Nodo
{
    Tarea contenedorTarea;
    Nodo *siguiente;
}Nodo;

typedef Nodo* Cabecera; //defino el tipo de dato de la cabeza de la lista

//definicion funciones
Cabecera crearListaVacia();
void mostrarListas(Cabecera lista);
Cabecera cargarTareas(Cabecera TareasPendientes, int* id);
Cabecera crearNodo(Cabecera lista, char* descripcion, int* id);
Nodo* sacarNodoDeTareasPendientes(Cabecera lista, int id);
Cabecera insertarTarea(Cabecera lista, Nodo* tarea);
int main()
{
    Cabecera TareasPendientes, TareasRealizadas;
    int sigueIngresandoTareas=1, id=1000, idIngresada;
    int* idTarea;
    idTarea=&id;
    

    TareasPendientes = crearListaVacia();
    TareasRealizadas = crearListaVacia();

    srand(time(NULL));
    printf("--------- MODULO TO-DO ---------\n");
    while (sigueIngresandoTareas == 1)
    {
        TareasPendientes = cargarTareas(TareasPendientes, idTarea);
        *idTarea= *idTarea +1;
        printf("Desea cargar mas tareas? [0 = NO 1=SI]");
        scanf("%d", &sigueIngresandoTareas);
    }
    mostrarListas(TareasPendientes);

    // printf("\n--------Seleccione tareas realizadas para transferir---------\n");
    // printf("Ingrese el ID de la tarea (>= 1000):");
    // scanf("%d", &idIngresada);
    Nodo *nodoQuitado = sacarNodoDeTareasPendientes(TareasPendientes, 1001);
    TareasRealizadas = insertarTarea(TareasRealizadas, nodoQuitado);
    mostrarListas(TareasRealizadas);
    nodoQuitado = sacarNodoDeTareasPendientes(TareasPendientes, 1003);
    TareasRealizadas = insertarTarea(TareasRealizadas, nodoQuitado);
    printf("\n\n---------------------------\n\n");
    mostrarListas(TareasRealizadas);
    // if (nodoQuitado)
    // {
    //     printf("\nDescripcion tarea Nodo quitado: %s\n", nodoQuitado->contenedorTarea.descripcion); 
    //     printf("Duracion de las tarea Nodo Quitado: %d\n",nodoQuitado->contenedorTarea.duracion);
    //     printf("Id Tarea Nodo Quitado: %d",nodoQuitado->contenedorTarea.tareaID); 
    // }else{
    //     printf("Error la id de la tarea no coincide con ninguna");
    // }
    

    return 0;
}

Cabecera crearListaVacia()
{
    return NULL;
}

Cabecera cargarTareas(Cabecera TareasPendientes, int* id)
{
    char buff[100];
    printf("Ingresar descripcion de la tarea: \n");
    // fgets(buff,100,stdin);
    scanf(" %s",buff); //puedo hacer asi teniendo en cuenta el espacio anterior del %s para poder ignorar el espacio de la anterior cadenas
    TareasPendientes = crearNodo(TareasPendientes, buff, id);
    return TareasPendientes;
}
Cabecera crearNodo(Cabecera lista, char* descripcion, int* id)
{
    Nodo *nuevoNodo; // por que habia que hacerlo puntero ? será porque sino se perdera lo creado por estar dentro de una funcion
    nuevoNodo = (Nodo *) malloc(sizeof (Nodo));
    nuevoNodo->contenedorTarea.descripcion = (char*) malloc(sizeof(char) * strlen(descripcion+1));
    strcpy(nuevoNodo->contenedorTarea.descripcion, descripcion);
    nuevoNodo->contenedorTarea.duracion = rand()%11 +100;
    nuevoNodo->contenedorTarea.tareaID= *id;

    if (lista == NULL)
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }else
    {
        Cabecera aux = lista, anterior;
        
        while (aux)
        {
            anterior = aux;
            aux = aux->siguiente;
        }
        nuevoNodo->siguiente = NULL;
        anterior->siguiente= nuevoNodo;
    }
    return lista;
}
Nodo* sacarNodoDeTareasPendientes(Cabecera lista, int id)
{
    Cabecera nodoQuitado, aux = lista, anterior;
    
    while (aux && aux->contenedorTarea.tareaID != id )
    {
        anterior = aux;
        aux = aux->siguiente;
    }
    nodoQuitado = aux;
    anterior->siguiente = aux->siguiente;
    nodoQuitado->siguiente = NULL;

    return nodoQuitado;
    
    
}
void mostrarListas(Cabecera lista)
{
    int i=1;
    while(lista != NULL)
    {
        printf("\nDescripcion tarea [%d]: %s\n",i, lista->contenedorTarea.descripcion);
        printf("Duracion de las tarea [%d]: %d\n", i,lista->contenedorTarea.duracion);
        printf("Id Tarea [%d]: %d", i , lista->contenedorTarea.tareaID);
        lista=lista->siguiente;
        i++;
        printf("\n\n");
    }
}

Cabecera insertarTarea(Cabecera lista, Nodo* tarea) //inserta la tarea que se realizo al utlimo, pudiendo leer asi de arriba haci abajo la ultima tarea que se agrego es la ultimo que se temrino
{
    Cabecera aux = lista, anterior;
    if (lista)
    {
        while (aux)
        {
            anterior = aux;
            aux = aux->siguiente;
        }
        tarea->siguiente = NULL;
        anterior->siguiente=tarea;
    }else
    {
        tarea->siguiente = lista;
        lista = tarea;
    }
    return lista;
}