#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define CANTIDADCODIGOS 21

// Definimos la estructura de cada codigo
typedef struct Codigo {
    int cifras;
    struct Codigo * siguiente;
} Codigo;

// Definimos la estructura de cada compartimento
typedef struct Pila {
    Codigo* cabeza;
} Pila;

// Prototipo de funciones
void inicializar(Pila * compartimento);
bool estavacia(Pila * compartimento);
void push(Pila * compartimento, int codigo);
void pop(Pila * compartimento);
int top(Pila * compartimento);
void repartir(Pila *a, Pila *b, Pila *c, int codigos[]);
void reensamblar(Pila * a, Pila * b, Pila * c, int codigosnuevos[]);
void adivinar(Pila * b);
void liberar(Pila * compartimento);
void mostrar_uno(Pila * compartimento);
void mostrar(Pila * a, Pila * b, Pila * c);

// Inicializamos el compartimento correspondiente
void inicializar(Pila * compartimento) {
    compartimento -> cabeza = NULL;
}

// Verficamos si es que el compartimento esta vacio
bool estavacia(Pila * compartimento) {
    return compartimento -> cabeza == NULL;
}

// Añadimos un nuevo codigo al compartimento correspondiente
void push(Pila * compartimento, int codigo) {
    Codigo * nuevo = (Codigo *)malloc(sizeof(Codigo));
    if (nuevo == NULL) {
        printf("Error: Memoria insuficiente\n");
        return;
    }
    nuevo -> cifras = codigo;
    nuevo -> siguiente = compartimento -> cabeza;
    compartimento -> cabeza = nuevo;
}

// Eliminamos y retornamos la cabeza del compartimento correspodiente
void pop(Pila * compartimento) {
    if (estavacia(compartimento)) {
        printf("Error: Compartimento vacio\n");
        return;
    }
    Codigo * actual = compartimento -> cabeza;
    compartimento -> cabeza = actual -> siguiente;
    free(actual);
}

// Retornamos la cabeza del compartimento correspondiente
int top(Pila * compartimento) {
    if (estavacia(compartimento)) {
        printf("Error: Compartimento vacio\n");
        return 0;
    }
    return compartimento -> cabeza -> cifras;
}

// Repartimos los codigos
void repartir(Pila *a, Pila *b, Pila *c, int codigos[]) {
    for (int i = 0; i < CANTIDADCODIGOS; i++) {
        if (i % 3 == 0) {
            push(a, codigos[i]);
        } else if (i % 3 == 1) {
            push(b, codigos[i]);
        }
        else {
            push(c, codigos[i]);
        }
    }
}

// Preguntamos al usuario en que compartimento esta su codigo y reensamblamos los compartimentos en la nueva secuencia
void reensamblar(Pila * a, Pila * b, Pila * c, int codigosnuevos[]) {
    char eleccion;
    do {
        printf("¿En que compartimento esta su codigo? ('a', 'b', o 'c'): ");
        scanf(" %c", &eleccion);
        if (eleccion != 'a' && eleccion != 'b' && eleccion != 'c') {
            printf("Error: Eleccion no valida. Intente nuevamente...\n");
        }
    } while (eleccion != 'a' && eleccion != 'b' && eleccion != 'c');
    int i = 0;
    if (eleccion == 'a') {
        while (!estavacia(b)) {
            codigosnuevos[i] = top(b);
            pop(b);
            i += 1;
        }
        while (!estavacia(a)) {
            codigosnuevos[i] = top(a);
            pop(a);
            i += 1;
        }
        while (!estavacia(c)) {
            codigosnuevos[i] = top(c);
            pop(c);
            i += 1;
        }
    } else if (eleccion == 'b') {
        while (!estavacia(a)) {
            codigosnuevos[i] = top(a);
            pop(a);
            i += 1;
        }
        while (!estavacia(b)) {
            codigosnuevos[i] = top(b);
            pop(b);
            i += 1;
        }
        while (!estavacia(c)) {
            codigosnuevos[i] = top(c);
            pop(c);
            i += 1;
        }
    } else {
        while (!estavacia(a)) {
            codigosnuevos[i] = top(a);
            pop(a);
            i += 1;
        }
        while (!estavacia(c)) {
            codigosnuevos[i] = top(c);
            pop(c);
            i += 1;
        }
        while (!estavacia(b)) {
            codigosnuevos[i] = top(b);
            pop(b);
            i += 1;
        }
    }
}

// Identificamos el codigo que el usuario eligio
void adivinar(Pila * b) {
    Codigo * actual = b -> cabeza;
    int codigoresultado;
    for (int i = 0; i < 3; i++) {
        actual = actual -> siguiente;
    }
    codigoresultado = actual -> cifras;
    printf("Su codigo objetivo es: %02d\n\n", codigoresultado);
}

// Liberamos la memoria del sistema mediante la eliminacion de un compartimento
void liberar(Pila * compartimento) {
    while (!estavacia(compartimento)) {
        pop(compartimento);
    }   
}

// Mostramos el contenido del compartimento correspondiente
void mostrar_uno(Pila * compartimento) {
    if (estavacia(compartimento)) {
        printf("%-15s", "(Vacío)");
        return;
    }
    Codigo * actual = compartimento->cabeza;
    while (actual != NULL) {
        printf("%02d ", actual->cifras);
        actual = actual->siguiente;
    }
    printf("\n");
}

// Mostramos el contenido de cada compartimento
void mostrar(Pila * a, Pila * b, Pila * c) {
    printf("\n");
    printf("A: ");
    mostrar_uno(a);
    printf("B: ");
    mostrar_uno(b);
    printf("C: ");
    mostrar_uno(c);
    printf("\n");
}

int main() {
    Pila a; inicializar(&a);
    Pila b; inicializar(&b);
    Pila c; inicializar(&c);

    int codigos[CANTIDADCODIGOS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
    repartir(&a, &b, &c, codigos);

    printf("\nBienvenido señor agente!!\n");
    printf("Seleccione uno de los 21 codigos que tiene a disposicion y memorizelo: \n");
    mostrar(&a, &b, &c);

    int codigosnuevos[CANTIDADCODIGOS];
    for (int i = 0; i < 3; i++) {
        reensamblar(&a, &b, &c, codigosnuevos);
        repartir(&a, &b, &c, codigosnuevos);
        mostrar(&a, &b, &c);
    }
    adivinar(&b);

    liberar(&a);
    liberar(&b);
    liberar(&c);
    return 0;
}