#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_NOMBRE 100
#define PRIORIDADES 5

// Estructura para definir los datos del paciente
typedef struct Paciente
{
    char nombre[MAX_NOMBRE];
    int prioridad;
    struct Paciente* siguiente
} Paciente;

// Definimos la cola
typedef struct Cola
{
    Paciente* frente;
    Paciente* final;
} Cola;

// Funcion para inicializar las colas de prioridades C1, C2, C3, C4, C5
void inicializar_Colas(Cola* colas){
    for(int i = 0; i < PRIORIDADES; i++){
        colas[i].frente = NULL;
        colas[i].final = NULL;
    }
}

// Ingresamos el paciente considerando su nombre y la prioridad
void ingresar_Paciente(Cola* colas, char nombre, int prioridad){
    // Variable que utilizaremos de forma auxiliar para ingresar a los pacientes
    int indice;
    //Verificamos si la prioridad ingresada es valida
    if(prioridad < 1 || prioridad > 5){
        printf("Error: La prioridad debe ser entre 1(C1) y 5(C5)\n");
        return;
    }
    //Creamos un nuevo dato para la cola y verificamos si es valido
    Paciente* nuevo = (Paciente* )malloc(sizeof(Paciente));
    if (nuevo == NULL){
        printf("Error: Memoria insuficiente\n");
        return;
    }
    //Asignamos los valores del paciente al nuevo dato de la cola
    strcpy(nuevo->nombre, nombre);
    nuevo->prioridad = prioridad;
    nuevo->siguiente = NULL;
    //Utilizamos la variable auxiliar para ingresar correctamente al paciente a su cola correspondiente
    indice = prioridad - 1;
    Cola* cola = &colas[indice];
    if (colaVacia(cola)){
        cola->frente = nuevo;
        cola->final = nuevo;
    }
    else{
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }

    printf("Paciente %s agregado a cola C%d\n", nombre, prioridad);
}

void atender_Paciente(Cola* colas){
    Paciente* paciente = NULL;
    int prioridad = -1;
    for (int i = 0; i < PRIORIDADES; i++) {
        if (!colaVacia(&colas[i])) {
            paciente = colas[i].frente;
            prioridad = i + 1;
            colas[i].frente = colas[i].frente->siguiente;

            if (colas[i].frente == NULL) {
                colas[i].final = NULL;
            }
            break;
        }
    }
    if (paciente == NULL) {
        printf("No hay pacientes en espera\n");
    } else {
        printf("Atendiendo a %s (Prioridad C%d)\n", paciente->nombre, prioridad);
        free(paciente);
    }
}

void mostrarEstado(Cola* colas){
    printf("\nEstado de las colas:\n");
    printf("--------------------\n");
    for (int i = 0; i < PRIORIDADES; i++) {
        printf("Cola C%d: ", i+1);
        if (colaVacia(&colas[i])) {
            printf("Vacía\n");
        } else {
            Paciente* actual = colas[i].frente;
            while (actual != NULL) {
                printf("%s", actual->nombre);
                if (actual->siguiente != NULL) {
                    printf(" -> ");
                }
                actual = actual->siguiente;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void procesarArchivo(){

}

bool colaVacia(Cola* cola){
    return cola->frente == NULL;
}

int main(){

}




