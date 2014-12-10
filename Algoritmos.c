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