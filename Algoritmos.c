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

/* Selection sort */
void ordSeleccion(int elementos[], int nelementos, Informa f, TEstado* estado)
{
  boolean fin=falso;

  int i, j;
  int min, temp;

  for (i = 0; i < nelementos-1 && !fin; i++)
  {
    min = i;
    for (j = i+1; j < nelementos && !fin; j++)
    {
      if (elementos[j] < elementos[min])
        min = j;
      estado->nOperaciones++;
    }
    estado->deElemento=i;
    estado->aElemento=min;
    fin=f(estado);
    temp = elementos[i];
    elementos[i] = elementos[min];
    elementos[min] = temp;
    estado->nOperaciones++;
  }
}

/* Insertion sort */
void ordInsercion(int elementos[], int nElementos, Informa f, TEstado* estado)
{
  int i, j;
  boolean fin=falso;

  for (i=1; i < nElementos && !fin; i++)
  {
    elementos[nElementos] = elementos[i];
    j = i;
    while ((j > 0) && (elementos[j-1] > elementos[nElementos]) && !fin)
    {
      estado->deElemento=j-1;
      estado->aElemento=j;
      fin=f(estado);
      elementos[j] = elementos[j-1];
      estado->nOperaciones++;
      j = j - 1;
    }
    estado->deElemento=nElementos;
    estado->aElemento=j;
    estado->nOperaciones++;
    f(estado);
    elementos[j] = elementos[nElementos];
  }
}