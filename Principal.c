/** @mainpage Aplicaci�n de prueba de algoritmos de ordenaci�n
    @e Escrita por Francisco Charte Ojeda

    Esta aplicaci�n est� escrita en lenguaje C y basada en los algoritmos de
    ordenaci�n m�s documentados en la literatura. Su finalidad es did�ctica,
    permitiendo obtener una visualizaci�n gr�fica del proceso de ordenaci�n.
    El programa puede ampliarse agregando nuevos algoritmos de ordenaci�n y
    registr�ndolos con el n�cleo de la aplicaci�n, para lo cual es necesario
    seguir las instrucciones agregadas al c�digo.

    Este programa puede compilarse en cualquier sistema que cuente con un
    compilador ANSI de C y la biblioteca ncurses, que se utiliza para crear
    la interfaz de usuario. Dicha biblioteca est� incluida en todas las
    distribuciones de Linux y tambi�n forma parte de otros sistemas operativos,
    como Mac OS X, pero en el caso de DOS/Windows es necesario a�adirla al
    compilador que est� utiliz�ndose. La p�gina oficial del compilador MingW,
    que es el que incluye Dev-C++, ofrece ncurses y muchas otras bibliotecas
    �tiles para desarrollar aplicaciones.

    Las tres capturas siguientes lo muestran en
    funcionamiento en DOS, Linux y Mac OS X.

    @htmlonly
    <img src="EnDos.jpg"><hr>
    <img src="EnLinux.jpg"><hr>
    <img src="EnMacOSX.jpg"><hr>
    @endhtmlonly
*/

/**
   @file principal.c
   @version 1.0
   @author Francisco Charte Ojeda
   @brief N�cleo del programa de algoritmos de ordenaci�n
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Interfaz.h"
#include "Definiciones.h"
#include "Algoritmos.h"

/**@brief Matriz con los algoritmos registrados

   Si quieren agregarse otros algoritmos, aparte de a�adir el prototipo de la
   funci�n a Algoritmos.h y la implementaci�n a Algoritmos.c, es necesario
   agregar una l�nea a este vector indicando su nombre descriptivo, el nombre
   de la funci�n que lo implementa y dejando el tercer componente a falso.
*/
TAlgoritmo algoritmos[] = {
  {"Selecci�n", ordSeleccion, falso},
  {"Inserci�n", ordInsercion, falso},
  {"Burbuja", ordBurbuja, falso},
  {"Burbuja mejorado", ordBurbujaMejorado, falso},
  {"Sacudida", ordSacudida, falso },
  {"Shell", ordShell, falso },
  {"Quick", ordQuick, falso }

};

int nElementos; // N�mero de elementos a ordenar

/* N�mero de algoritmos registrados. nAlgoritmos se actualiza autom�ticamente
  en caso de que se agreguen m�s elementos a la matriz algoritmos anterior */
int nAlgoritmos=sizeof(algoritmos)/sizeof(algoritmos[0]);

/**@brief Funci�n que recibe las notificaciones del algoritmo
*/
boolean Notifica(TEstado* estado)
{
  boolean retorno=falso;
  int i,j,tecla;

  // Se muestran los elementos a intercambiar
  MuestraVectoresaIntercambiar(
    estado->aElemento,estado->deElemento,
    estado->vector[estado->aElemento],
    estado->vector[estado->deElemento]);

  // y se notifica el cambio
  retorno=MuestraNotificacion(estado, nElementos);

  return retorno;
}
