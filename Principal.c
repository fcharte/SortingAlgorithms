/** @mainpage Aplicación de prueba de algoritmos de ordenación
    @e Escrita por Francisco Charte Ojeda

    Esta aplicación está escrita en lenguaje C y basada en los algoritmos de
    ordenación más documentados en la literatura. Su finalidad es didáctica,
    permitiendo obtener una visualización gráfica del proceso de ordenación.
    El programa puede ampliarse agregando nuevos algoritmos de ordenación y
    registrándolos con el núcleo de la aplicación, para lo cual es necesario
    seguir las instrucciones agregadas al código.

    Este programa puede compilarse en cualquier sistema que cuente con un
    compilador ANSI de C y la biblioteca ncurses, que se utiliza para crear
    la interfaz de usuario. Dicha biblioteca está incluida en todas las
    distribuciones de Linux y también forma parte de otros sistemas operativos,
    como Mac OS X, pero en el caso de DOS/Windows es necesario añadirla al
    compilador que esté utilizándose. La página oficial del compilador MingW,
    que es el que incluye Dev-C++, ofrece ncurses y muchas otras bibliotecas
    útiles para desarrollar aplicaciones.

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
   @brief Núcleo del programa de algoritmos de ordenación
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Interfaz.h"
#include "Definiciones.h"
#include "Algoritmos.h"

/**@brief Matriz con los algoritmos registrados

   Si quieren agregarse otros algoritmos, aparte de añadir el prototipo de la
   función a Algoritmos.h y la implementación a Algoritmos.c, es necesario
   agregar una línea a este vector indicando su nombre descriptivo, el nombre
   de la función que lo implementa y dejando el tercer componente a falso.
*/
TAlgoritmo algoritmos[] = {
  {"Selección", ordSeleccion, falso},
  {"Inserción", ordInsercion, falso},
  {"Burbuja", ordBurbuja, falso},
  {"Burbuja mejorado", ordBurbujaMejorado, falso},
  {"Sacudida", ordSacudida, falso },
  {"Shell", ordShell, falso },
  {"Quick", ordQuick, falso }

};

int nElementos; // Número de elementos a ordenar

/* Número de algoritmos registrados. nAlgoritmos se actualiza automáticamente
  en caso de que se agreguen m s elementos a la matriz algoritmos anterior */
int nAlgoritmos=sizeof(algoritmos)/sizeof(algoritmos[0]);

/**@brief Función que recibe las notificaciones del algoritmo
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
