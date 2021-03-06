/**
   @file algoritmos.h
   @version 1.0
   @author Francisco Charte Ojeda
   @brief Prototipos de las funciones de ordenación disponibles
*/
#ifndef __ALGORITMOS_H__
#define __ALGORITMOS_H__

/* Sorting function prototypes */

/**
   @brief Ordena un vector de enteros mediante el algoritmo de la burbuja
   @param elementos Vector con los elementos a ordenar
   @param nelementos Número de elementos que contiene el vector
   @param f Puntero a la función de notificación de cambios
   @param estado Puntero a una estructura TEstado con la información del proceso
   @pre El vector de elementos debe contener al menos 2 elementos
   @pre La estructura TEstado a la que apunta @a estado debe estar inicializada
   @post El proceso de ordenación finaliza cuando el vector esté ordenado o bien cuando la función de notificación devuelva @a verdad
*/
void ordBurbuja(int elementos[], int nelementos, Informa f, TEstado* estado); /* Bubble sort */

/**
   @brief Ordena un vector de enteros mediante el algoritmo de la burbuja mejorado
   @param elementos Vector con los elementos a ordenar
   @param nelementos Número de elementos que contiene el vector
   @param f Puntero a la función de notificación de cambios
   @param estado Puntero a una estructura TEstado con la información del proceso
   @pre El vector de elementos debe contener al menos 2 elementos
   @pre La estructura TEstado a la que apunta @a estado debe estar inicializada
   @post El proceso de ordenación finaliza cuando el vector esté ordenado o bien cuando la función de notificación devuelva @a verdad
*/
void ordBurbujaMejorado(int elementos[], int nelementos, Informa f, TEstado* estado); /* Improved bubble sort */

/**
   @brief Ordena un vector de enteros mediante el algoritmo de selección
   @param elementos Vector con los elementos a ordenar
   @param nelementos Número de elementos que contiene el vector
   @param f Puntero a la función de notificación de cambios
   @param estado Puntero a una estructura TEstado con la información del proceso
   @pre El vector de elementos debe contener al menos 2 elementos
   @pre La estructura TEstado a la que apunta @a estado debe estar inicializada
   @post El proceso de ordenación finaliza cuando el vector esté ordenado o bien cuando la función de notificación devuelva @a verdad
*/
void ordSeleccion(int elementos[], int nelementos, Informa f, TEstado* estado); /* Selection sort */

/**
   @brief Ordena un vector de enteros mediante el algoritmo de inserción
   @param elementos Vector con los elementos a ordenar
   @param nelementos Número de elementos que contiene el vector
   @param f Puntero a la función de notificación de cambios
   @param estado Puntero a una estructura TEstado con la información del proceso
   @pre El vector de elementos debe contener al menos 2 elementos
   @pre La estructura TEstado a la que apunta @a estado debe estar inicializada
   @post El proceso de ordenación finaliza cuando el vector esté ordenado o bien cuando la función de notificación devuelva @a verdad
*/
void ordInsercion(int elementos[], int nelementos, Informa f, TEstado* estado); /* Insertion sort */

/**
   @brief Ordena un vector de enteros mediante el algoritmo de la sacudida
   @param elementos Vector con los elementos a ordenar
   @param nelementos Número de elementos que contiene el vector
   @param f Puntero a la función de notificación de cambios
   @param estado Puntero a una estructura TEstado con la información del proceso
   @pre El vector de elementos debe contener al menos 2 elementos
   @pre La estructura TEstado a la que apunta @a estado debe estar inicializada
   @post El proceso de ordenación finaliza cuando el vector esté ordenado o bien cuando la función de notificación devuelva @a verdad
*/
void ordSacudida(int elementos[], int nelementos, Informa f, TEstado* estado); /* Shaker sort (also known as cocktail sort) */

/**
   @brief Ordena un vector de enteros mediante el algoritmo Shell
   @param elementos Vector con los elementos a ordenar
   @param nelementos Número de elementos que contiene el vector
   @param f Puntero a la función de notificación de cambios
   @param estado Puntero a una estructura TEstado con la información del proceso
   @pre El vector de elementos debe contener al menos 2 elementos
   @pre La estructura TEstado a la que apunta @a estado debe estar inicializada
   @post El proceso de ordenación finaliza cuando el vector esté ordenado o bien cuando la función de notificación devuelva @a verdad
*/
void ordShell(int elementos[], int nelementos, Informa f, TEstado* estado); /* Shell sort */

/**
   @brief Ordena un vector de enteros mediante el algoritmo de QuickSort
   @param elementos Vector con los elementos a ordenar
   @param nelementos Número de elementos que contiene el vector
   @param f Puntero a la función de notificación de cambios
   @param estado Puntero a una estructura TEstado con la información del proceso
   @pre El vector de elementos debe contener al menos 2 elementos
   @pre La estructura TEstado a la que apunta @a estado debe estar inicializada
   @post El proceso de ordenación finaliza cuando el vector esté ordenado o bien cuando la función de notificación devuelva @a verdad
*/
void ordQuick(int elementos[], int nelementos, Informa f, TEstado* estado); /* Quick sort */

#endif /* __ALGORITMOS_H__ */
