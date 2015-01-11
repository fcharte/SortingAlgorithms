/**
   @file definiciones.h
   @version 1.0
   @author Francisco Charte Ojeda
   @brief Definici�n de tipos de datos necesarios para la aplicaci�n

   Este archivo de cabecera debe ser incluido en cualquier m�dulo que desee
   a�adirse al programa, por ejemplo conteniendo algoritmos adicionales de
   ordenaci�n, ya que contiene los tipos fundamentales que facilitan la
   comunicaci�n entre los algoritmos de ordenaci�n y la aplicaci�n principal.
*/
#ifndef __DEFINICIONES_H__
#define __DEFINICIONES_H__

/**@brief Tipo usado para indicadores y centinelas */
typedef enum {
   falso=0,
   verdad
} boolean; 

/**@brief Informaci�n que cada algoritmo devolver� al programa principal

   Cuando se invoca a un m�todo de ordenaci�n hay que entregarle un puntero
   a una estructura de este tipo debidamente inicializada, con los primeros
   cuatro campos puestos a 0 y el puntero @a vector apuntando al vector a
   ordenar. La funci�n de ordenaci�n ir� actualizando ciertos elementos de
   esta estructur� y la facilitar� como par�metro cada vez que invoque a la
   funci�n de notificaci�n.
*/
typedef struct {
   int deElemento; /** Elemento que va a cambiarse */
   int aElemento;  /** destino del elemento a intercambiar */
   int nOperaciones; /** N�mero de ciclos ejecutados por el algoritmo */
   int nIntercambios; /** N�mero de intercambios de elementos efectuados */
   int *vector; /** Puntero al vector que est� orden�ndose */
} TEstado;

/**@brief Firma de la funci�n de notificaci�n

   La funci�n de notificaci�n es una funci�n a la que los algoritmos de
   ordenaci�n invocar�n cada vez que se produzca un intercambio. Dicha
   funci�n recibe como par�metro un puntero a TEstado, con el estado del
   proceso, y devuelve un valor @a boolean que, de ser @a verdad, indicar�
   al algoritmo que debe interrumpirse.

   Es la aplicaci�n principal la que aporta esta funci�n de notificaci�n,
   si bien puede ser sustituida por otra que efect�e la tarea de otra forma
   pero mantenga la firma.
*/
typedef boolean (*Informa)(TEstado*);

/**@brief Firma de las funciones de ordenaci�n

   Todas las funciones de ordenaci�n deben ajustarse a esta firma, tomando
   como argumentos el vector de enteros a ordenar, un entero que indica el
   n�mero de elementos en el vector, un puntero a la funci�n de notificaci�n
   y un puntero a una estructura TEstado.

   Cualquier funci�n de ordenaci�n que se agregue al programa, para probar
   algoritmos adicionales, tiene que ajustarse a esta norma.
*/
typedef void (*Ordena)(int [], int, Informa, TEstado*);

/**@brief Informaci�n que registro de los algoritmos

   Datos que la aplicaci�n necesita saber por cada algoritmo que se agregue.
*/
typedef struct {
   char* nombre; /** Nombre descriptivo del algoritmo */
   Ordena f;   /** Puntero a la funci�n que lo implementa */
   boolean elegido; /** Usado por la interfaz del programa para saber si se ha elegido probar este algoritmo */
} TAlgoritmo;

#endif /* __DEFINICIONES_H__ */

