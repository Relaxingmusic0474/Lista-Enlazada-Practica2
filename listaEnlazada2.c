/* 

ACTIVIDAD

Objetivo: Comprender y dominar mejor la implementación de las listas enlazadas simples y algunas de sus funciones básicas

Ejercicio:

Aplicando una lista enlazada simple, crear un programa en C que permita imprimir una lista de tamaño 10, de tipos variables.   El tipo de cada nodo de la lista,
dependerá del número generado aleatoriamente.

0: Número entero entre -10 y 30
1: Número flotante entre -20.0 y 20.0
2: Caracter alfabético ('A' - 'Z')
3: Cadena de 4 caracteres (cada uno generado aleatoriamente)

Adicionalmente:

Lograr deducir la lógica de implementación de las funciones agregarNodoInicio y buscarElemento, e implementarlas de forma libre en alguna parte del código

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM 10

typedef union dato Dato;
typedef struct nodo Nodo;
typedef struct lista Lista;

union dato
{
    int entero;
    float decimal;
    char ch;
    char str[5];
};

struct nodo
{
    unsigned int type;
    Dato dato;
    Nodo* sig;
};

struct lista
{
    Nodo* cabeza;
};

Dato generarDato(unsigned int);
Nodo* crearNodo(unsigned int, Dato);
void agregarNodo(unsigned int, Dato, Lista*);
void agregarNodoInicio(unsigned int, Dato, Lista*);
Nodo* buscarElemento(unsigned int, Dato, Lista);
void imprimirLista(Lista);
void liberarLista(Lista*);

int main(void)
{
    Lista list;
    unsigned int tipo;
    Dato data;
    int opcion;
    int nodos;
    Nodo* resultadoBusqueda = NULL;

    list.cabeza = NULL;

    srand(time(NULL));

    // Resto del codigo
    for (int i=0; i<TAM; i++)
    {
        tipo = rand() % 4;
        data = generarDato(tipo);
        agregarNodo(tipo, data, &list);
    }

    imprimirLista(list);

    printf("\nDesea agregar nodos al inicio??\n");
    printf("\n1) Si\n2) No\n\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    while (opcion != 1 && opcion != 2)
    {
        printf("\nOpcion no valida... Seleccione una opcion valida del menu:  ");
        scanf("%d", &opcion);
    }

    if (opcion == 1)
    {
        printf("\n");

        do
        {
            printf("Cuantos nodos desea agregar??\n\n");
            scanf("%d", &nodos);
        }

        while(nodos < 0);

        for (int i=0; i<nodos; i++)
        {
            tipo = rand() % 4;
            data = generarDato(tipo);
            agregarNodoInicio(tipo, data, &list);
        }

        printf("\n");

        imprimirLista(list);
    }

    printf("\nDesea buscar algun elemento dentro de la lista?? \n");
    printf("\n1) Si\n2) No\n\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    while (opcion != 1 && opcion != 2)
    {
        printf("\nOpcion no valida... Seleccione una opcion valida del menu:  ");
        scanf("%d", &opcion);
    }


    if (opcion == 1)
    {
        printf("\nTipo de dato deseado: \n\n");
        printf("0) Entero\n1) Decimal\n2) Caracter\n3) Cadena\n\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        while (opcion < 0 || opcion > 3)
        {
            printf("\nOpcion no valida... Seleccione una opcion valida del menu: ");
            scanf("%d", &opcion);
        }
        
        switch (opcion)
        {
            case 0:
                    printf("\nIngrese el entero que desea buscar: ");
                    scanf("%d", &data.entero);
                    break;
            
            case 1:
                    printf("\nIngrese el decimal que desea buscar: ");
                    scanf("%f", &data.decimal);
                    break;

            case 2:
                    printf("\nIngrese el caracter que desea buscar: ");
                    scanf(" %c", &data.ch);
                    break;

            case 3:
                    printf("\nIngrese la cadena que desea buscar: ");
                    scanf("%4s", &data.str);
                    break;
        }
        
        resultadoBusqueda = buscarElemento(opcion, data, list);

        (resultadoBusqueda) ? printf("\nElemento encontrado.\n\n") : printf("\nElemento no encontrado.\n\n");
    }

    liberarLista(&list);

    return 0;
}

Dato generarDato(unsigned int tipo)
{
    Dato data;
    int i;

    switch (tipo)
    {
        case 0: 
                data.entero = rand() % 41 - 10;
                break;
        
        case 1:
                data.decimal = rand() % 4001 - 2000;
                data.decimal /= 100;
                break;

        case 2:
                data.ch = rand() % 26 + 'A';
                break;
        
        case 3:
                for (i=0; i<4; i++)
                {
                    data.str[i] = rand() % 26 + 'A';
                }

                data.str[i] = '\0';

                break;               
    }

    return data;
}

Nodo* crearNodo(unsigned int tipo, Dato dato)
{
    Nodo* nuevoNodo = (Nodo *) malloc(sizeof(Nodo));

    if (!nuevoNodo)
    {
        printf("Error de memoria\n");
        return NULL;
    }

    nuevoNodo->type = tipo;
    nuevoNodo->dato = dato;
    nuevoNodo->sig = NULL;

    return nuevoNodo;
}

void agregarNodo(unsigned int tipo, Dato dato, Lista* L)
{
    Nodo* temp = NULL;
    Nodo* nuevoNodo = crearNodo(tipo, dato);

    if (!nuevoNodo)
    {
        return;
    }

    if (!L->cabeza)
    {
        L->cabeza = nuevoNodo;
    }

    else
    {
        temp = L->cabeza;

        while (temp->sig)
        {
            temp = temp->sig;
        }

        temp->sig = nuevoNodo;
    }

    return;
}

void agregarNodoInicio(unsigned int tipo, Dato dato, Lista* L)
{
    Nodo* nuevoNodo = (Nodo *) malloc(sizeof(Nodo));

    if (!nuevoNodo)
    {
        printf("Error de memoria.\n");
        return;
    }

    nuevoNodo->type = tipo;
    nuevoNodo->dato = dato;
    nuevoNodo->sig = L->cabeza;
    L->cabeza = nuevoNodo;

    return;
}

Nodo* buscarElemento(unsigned int tipo, Dato dato, Lista L)
{
    Nodo* temp = L.cabeza;

    while (temp)
    {
        if (temp->type == tipo)
        {
            switch (tipo)
            {
                case 0:
                        if (temp->dato.entero == dato.entero)
                        {
                            return temp;
                        }

                        break;

                case 1:
                        if (temp->dato.decimal == dato.decimal)
                        {
                            return temp;
                        }

                        break;
                
                case 2:
                        if (temp->dato.ch == dato.ch)
                        {
                            return temp;
                        }

                        break;

                case 3:
                        if (!strcmp(temp->dato.str, dato.str))
                        {
                            return temp;
                        }

                        break;
            }
        }

        temp = temp->sig;
    }

    return NULL;
}

void imprimirLista(Lista L)
{
    Nodo* temp = L.cabeza;

    while (temp)
    {
        switch (temp->type)
        {
            case 0: 
                printf("%d -> ", temp->dato.entero);
                break;
            
            case 1:
                printf("%.2f -> ", temp->dato.decimal);
                break;

            case 2:
                printf("%c -> ", temp->dato.ch);
                break;

            default:
                printf("%s -> ", temp->dato.str);
                break;
        }

        temp = temp->sig;
    }

    printf("NULL\n");

    return;
}

void liberarLista(Lista* L)
{
    Nodo* temp = L->cabeza;
    Nodo* next = NULL;

    while (temp)
    {
        next = temp->sig;
        free(temp);
        temp = next;
    }

    L->cabeza = NULL;

    return;
}