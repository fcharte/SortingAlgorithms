/**
   @file algoritmos.c
   @version 1.0
   @author Francisco Charte Ojeda
   @brief Implementación de los algoritmos de ordenación

   Este módulo contiene el código en el que se implementan las distintas
   funciones de ordenación. 
*/

#include "Definiciones.h"
#include "Algoritmos.h"

/* Sorting function implementation */

/* Bubble sort */
void ordBurbuja(int elementos[], int nelementos, Informa f, TEstado* estado)
{
  int i, j, temp;
  boolean fin=false;

  for (i = (nelementos - 1); i >= 0 && !fin; i--)
    for (j = 1; j <= i && !fin; j++) {
      if (elementos[j-1] > elementos[j]) {
        temp = elementos[j-1];
        elementos[j-1] = elementos[j];
        elementos[j] = temp;
        estado->deElemento=j;
        estado->aElemento=j-1;
        fin=f(estado);
      }
      estado->nOperaciones++;
    }
}

/* Improved bubble sort */
void ordBurbujaMejorado(int elementos[], int nelementos, Informa f, TEstado* estado)
{
  int i=1, j, temp;
  boolean fin=false, hayCambio=true;

  while(i<nelementos && hayCambio && !fin) {
    hayCambio=false;
    for (j = 0; j <= nelementos-i && !fin; j++) {
      if (elementos[j] > elementos[j+1]) {
        temp = elementos[j];
        elementos[j] = elementos[j+1];
        elementos[j+1] = temp;
        estado->deElemento=j;
        estado->aElemento=j+1;
        fin=f(estado);
        hayCambio=true;
      }
      estado->nOperaciones++;
    }
    i++;
   }
}
