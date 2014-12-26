/**
   @file definiciones.h
   @version 1.0
   @author Francisco Charte Ojeda
   @brief Definición de tipos de datos necesarios para la aplicación

   Este archivo de cabecera debe ser incluido en cualquier módulo que desee
   añadirse al programa, por ejemplo conteniendo algoritmos adicionales de
   ordenación, ya que contiene los tipos fundamentales que facilitan la
   comunicación entre los algoritmos de ordenación y la aplicación principal.
*/
#ifndef __DEFINICIONES_H__
#define __DEFINICIONES_H__

/**@brief Tipo usado para indicadores y centinelas */
typedef enum {
   falso=0,
   verdad
} boolean; 

/**@brief Información que cada algoritmo devolverá al programa principal

   Cuando se invoca a un método de ordenación hay que entregarle un puntero
   a una estructura de este tipo debidamente inicializada, con los primeros
   cuatro campos puestos a 0 y el puntero @a vector apuntando al vector a
   ordenar. La función de ordenación irá actualizando ciertos elementos de
   esta estructurá y la facilitará como parámetro cada vez que invoque a la
   función de notificación.
*/
typedef struct {
   int deElemento; /** Elemento que va a cambiarse */
   int aElemento;  /** destino del elemento a intercambiar */
   int nOperaciones; /** Número de ciclos ejecutados por el algoritmo */
   int nIntercambios; /** Número de intercambios de elementos efectuados */
   int *vector; /** Puntero al vector que está ordenándose */
} TEstado;

/**@brief Firma de la función de notificación

   La función de notificación es una función a la que los algoritmos de
   ordenación invocarán cada vez que se produzca un intercambio. Dicha
   función recibe como parámetro un puntero a TEstado, con el estado del
   proceso, y devuelve un valor @a boolean que, de ser @a verdad, indicará
   al algoritmo que debe interrumpirse.

   Es la aplicación principal la que aporta esta función de notificación,
   si bien puede ser sustituida por otra que efectúe la tarea de otra forma
   pero mantenga la firma.
*/
typedef boolean (*Informa)(TEstado*);

/**@brief Firma de las funciones de ordenación

   Todas las funciones de ordenación deben ajustarse a esta firma, tomando
   como argumentos el vector de enteros a ordenar, un entero que indica el
   número de elementos en el vector, un puntero a la función de notificación
   y un puntero a una estructura TEstado.

   Cualquier función de ordenación que se agregue al programa, para probar
   algoritmos adicionales, tiene que ajustarse a esta norma.
*/
typedef void (*Ordena)(int [], int, Informa, TEstado*);

/**@brief Información que registro de los algoritmos

   Datos que la aplicación necesita saber por cada algoritmo que se agregue.
*/
typedef struct {
   char* nombre; /** Nombre descriptivo del algoritmo */
   Ordena f;   /** Puntero a la función que lo implementa */
   boolean elegido; /** Usado por la interfaz del programa para saber si se ha elegido probar este algoritmo */
} TAlgoritmo;

#endif /* __DEFINICIONES_H__ */

