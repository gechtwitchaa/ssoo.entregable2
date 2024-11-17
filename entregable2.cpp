#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Definicion de la constante SIZE
#define SIZE 10

// Definicion de la estructura potencia_t
typedef struct {
    int base;
    int exp;
    int potencia;
} potencia_t;

// Definicion de un puntero a potencia_t
typedef potencia_t* potenciaP_t;

// Funcion para inicia base y exponente, y setear potencia a -1
void setBaseExp(potenciaP_t pot, int base, int exp) {
    pot->base = base;
    pot->exp = exp;
    pot->potencia = -1;
}

// Funcion para calcular base^exp
int getPotencia(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// Funcion para calcular y setear el valor de potencia en una estructura
void setPotenciaEst(potenciaP_t pot) {
    pot->potencia = getPotencia(pot->base, pot->exp);
}

// Funcion para iniciar un array de estructuras potencia_t
void initArrayEst(potencia_t arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i].base = i + 1;
        arr[i].exp = 0;
        arr[i].potencia = 1;
    }
}

// Funcion para imprimir el contenido de un array de estructuras potencia_t
void printArrayEst(potencia_t arr[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("arr[%d]: base: %d exp: %d potencia: %d\n", i, arr[i].base, arr[i].exp, arr[i].potencia);
    }
}

// Funcion para calcular la potencia en una hebra
void* calcuPotHeb(void* arg) {
    potenciaP_t pot = (potenciaP_t)arg;
    pot->potencia = getPotencia(pot->base, pot->exp);
    return NULL;
}

// Funcion main
int main() {
    potencia_t arr1[SIZE];
    potencia_t arr2[SIZE];

    // Iniciar y mostrar arr1
    initArrayEst(arr1);
    printArrayEst(arr1);

    // Actualizar arr1 con setBaseExp y mostrarlo
    for (int i = 0; i < SIZE; i++) {
        setBaseExp(&arr1[i], i, 2);
    }
    printArrayEst(arr1);

    // Crear hebras para calcular potencias en arr1
    pthread_t threads1[SIZE];
    for (int i = 0; i < SIZE; i++) {
        pthread_create(&threads1[i], NULL, calcuPotHeb, &arr1[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads1[i], NULL);
    }
    // Mostrar arr1 despues de calcular potencias
    printArrayEst(arr1);

    // Iniciar y mostrar arr2
    initArrayEst(arr2);
    printArrayEst(arr2);

    // Crear hebras para calcular potencias en arr2
    pthread_t threads2[SIZE];
    for (int i = 0; i < SIZE; i++) {
        setBaseExp(&arr2[i], i, 2);
        pthread_create(&threads2[i], NULL, calcuPotHeb, &arr2[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads2[i], NULL);
    }
    // Mostrar arr2 después de calcular potencias
    printArrayEst(arr2);

    return 0;
}