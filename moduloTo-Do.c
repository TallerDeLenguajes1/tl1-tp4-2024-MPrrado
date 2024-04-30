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
Nodo* sacarNodoDeTareasPendientes(Cabecera *lista, int id);
Cabecera insertarTarea(Cabecera lista, Nodo* tarea);
void buscarSegunPalabra(Cabecera listaPendientes, Cabecera listaRealizadas, char* palabraBuscar);
void buscarSegunID(Cabecera listaPendientes, Cabecera listaRealizadas, int idBuscad);
int main()
{
    Cabecera TareasPendientes, TareasRealizadas;
    int sigueIngresandoTareas=1, id=1000, idIngresada, sigueTransfieriendoTareas=1, sigueBuscando =1;
    int* idTarea, IDoPalabra, idBuscada;
    char buffPalabraClave[100];
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

    while (sigueTransfieriendoTareas == 1)
    {
        printf("\n--------Seleccione tareas realizadas para transferir---------\n\n");
        printf("Ingrese el ID de la tarea (>= 1000):");
        scanf("%d", &idIngresada);
        Nodo *nodoQuitado = sacarNodoDeTareasPendientes(&TareasPendientes, idIngresada);
        if (nodoQuitado == NULL)
        {
            printf("no se encontro la id/no hay tareas para transferir");
        }else{

            TareasRealizadas = insertarTarea(TareasRealizadas, nodoQuitado);
            printf("Tarea transferida a la lista de Tareas Realizadas!!\n");
        }
        printf("\nDesea seguir transfiriendo tareas? SI:[1]  NO:[0] ");
        scanf("%d", &sigueTransfieriendoTareas);
    }
    
    printf("\n\n-------------TAREAS REALIZADAS--------------\n\n");
    mostrarListas(TareasRealizadas);
    printf("\n\n--------------TAREAS PENDIENTES-------------\n\n");
    mostrarListas(TareasPendientes);    
    
    while (sigueBuscando == 1)
    {
        printf("\n----------Buscando por ID o palabra clave----------\n");
        printf("ingrese por que metodo buscar la tarea: palabra [1] ID [2] ");
        scanf("%d", &IDoPalabra);
        fflush(stdin);
        switch (IDoPalabra)
        {
        case 1:
            printf("\n ingrese la palabra clave para buscar la tarea: ");
            fgets(buffPalabraClave,100,stdin);
            buscarSegunPalabra(TareasPendientes, TareasRealizadas, buffPalabraClave);
            break;

        case 2:
            printf("\n ingrese el ID para buscar la tarea: ");
            scanf("%d", &idBuscada);
            buscarSegunID(TareasPendientes, TareasRealizadas, idBuscada);
            break;
        }
    }
    

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
    fflush(stdin);
    fgets(buff,100,stdin);
    // scanf(" %s",buff); //puedo hacer asi teniendo en cuenta el espacio anterior del %s para poder ignorar el espacio de la anterior cadenas
    TareasPendientes = crearNodo(TareasPendientes, buff, id);
    return TareasPendientes;
}
Cabecera crearNodo(Cabecera lista, char* descripcion, int* id)
{
    Nodo *nuevoNodo; // por que habia que hacerlo puntero ? será porque sino se perdera lo creado por estar dentro de una funcion
    nuevoNodo = (Nodo *) malloc(sizeof (Nodo));
    nuevoNodo->contenedorTarea.descripcion = (char*) malloc(sizeof(char) * (strlen(descripcion)+1));
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
        
        while (aux) // bloque que me permite pasar agregar la tarea al final
        {
            anterior = aux;
            aux = aux->siguiente;
        }
        nuevoNodo->siguiente = NULL;
        anterior->siguiente= nuevoNodo;
    }
    return lista;
}
Nodo* sacarNodoDeTareasPendientes(Cabecera *lista, int id)
{
    Cabecera nodoQuitado, aux = *lista, anterior = *lista;
    if(*lista == NULL)
    {
        return NULL;
    }else
    {
        if (aux != NULL && aux->contenedorTarea.tareaID == id)
        {
            (*lista) = (*lista)->siguiente;
            aux->siguiente = NULL;
            return aux;
        }else
        {
            while (aux != NULL)
            {
                if(aux != NULL && aux->contenedorTarea.tareaID == id)
                {
                    anterior->siguiente = aux->siguiente;
                    aux->siguiente = NULL;
                    return aux;
                }
                anterior =aux;
                aux=aux->siguiente;
            }
            return aux;
        }
        
    }
    
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
Cabecera insertarTarea(Cabecera lista, Nodo* tarea) //inserta la tarea que se realizo al utlimo, pudiendo leer asi de arriba hacia abajo la ultima tarea que se agrego es la ultima que se termino
{
    Cabecera aux = lista, anterior;
    if (lista != NULL)
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
void buscarSegunPalabra(Cabecera listaPendientes, Cabecera listaRealizadas, char *palabraBuscar)
{
    Cabecera auxPend = listaPendientes, auxReal = listaRealizadas;
    int resultadoComparacion;
    while (auxPend != NULL || auxReal != NULL)
    {
        resultadoComparacion = strcmp(palabraBuscar, auxPend->contenedorTarea.descripcion);
        if(resultadoComparacion == 0)
        {
            printf("-------Tarea coincidente en PENDIENTES-------: \n\n");
            printf("\nDescripcion tarea: %s\n", auxPend->contenedorTarea.descripcion);
            printf("Duracion de las tarea: %d\n",auxPend->contenedorTarea.duracion);
            printf("Id Tarea: %d\n", auxPend->contenedorTarea.tareaID);
        }
         resultadoComparacion = strcmp(palabraBuscar, auxReal->contenedorTarea.descripcion);
        if (resultadoComparacion == 0)
        {
            printf("-------Tarea coincidente en REALIZADAS:------- \n\n");
            printf("\nDescripcion tarea: %s\n", auxPend->contenedorTarea.descripcion);
            printf("Duracion de las tarea: %d\n",auxPend->contenedorTarea.duracion);
            printf("Id Tarea: %d\n", auxPend->contenedorTarea.tareaID);
        }
        if (auxPend != NULL && auxReal != NULL)
        {
            auxPend = auxPend->siguiente; 
            auxReal = auxReal->siguiente;
        }else if (auxReal != NULL)
        {
            auxReal = auxReal->siguiente;
        }else{
            auxPend = auxPend->siguiente; 
        }
        
        
    }
    
}
void buscarSegunID(Cabecera listaPendientes, Cabecera listaRealizadas, int idBuscad)
{
    Cabecera auxPend = listaPendientes, auxReal = listaRealizadas;
    while (auxPend != NULL && auxReal != NULL)
    {
        if(auxPend->contenedorTarea.tareaID == idBuscad)
        {
            printf("-------Tarea coincidente en PENDIENTES-------: \n\n");
            printf("\nDescripcion tarea: %s\n", auxPend->contenedorTarea.descripcion);
            printf("Duracion de las tarea: %d\n",auxPend->contenedorTarea.duracion);
            printf("Id Tarea: %d\n", auxPend->contenedorTarea.tareaID);
        }
        if (auxReal->contenedorTarea.tareaID == idBuscad)
        {
            printf("-------Tarea coincidente en REALIZADAS:------- \n\n");
            printf("\nDescripcion tarea: %s\n", auxPend->contenedorTarea.descripcion);
            printf("Duracion de las tarea: %d\n",auxPend->contenedorTarea.duracion);
            printf("Id Tarea: %d\n", auxPend->contenedorTarea.tareaID);
        }
        auxPend = auxPend->siguiente;
        auxReal = auxReal->siguiente;
    }
}