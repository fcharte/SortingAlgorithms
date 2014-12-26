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
  boolean fin=falso;

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
  boolean fin=falso, hayCambio=verdad;

  while(i<nelementos && hayCambio && !fin) {
    hayCambio=falso;
    for (j = 0; j <= nelementos-i && !fin; j++) {
      if (elementos[j] > elementos[j+1]) {
        temp = elementos[j];
        elementos[j] = elementos[j+1];
        elementos[j+1] = temp;
        estado->deElemento=j;
        estado->aElemento=j+1;
        fin=f(estado);
        hayCambio=verdad;
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

/* Shaker sort (also known as cocktail sort) */
void ordSacudida(int elementos[], int nelementos, Informa f, TEstado* estado)
{
  int i, izq=0, der=nelementos-1, ultimo=0, temp;
  boolean fin=falso;

  while(izq<der && !fin) {
    for (i = der; i > izq && !fin; i--) {
      if (elementos[i-1] > elementos[i]) {
          estado->deElemento=i-1;
          estado->aElemento=i;
          fin=f(estado);
          temp = elementos[i-1];
          elementos[i-1] = elementos[i];
          elementos[i] = temp;
          ultimo=i;
      }
      estado->nOperaciones++;
    }

    izq=ultimo;

    for (i = izq; i < der && !fin; i++) {
      if (elementos[i] > elementos[i+1]) {
          estado->deElemento=i;
          estado->aElemento=i+1;
          fin=f(estado);
          temp = elementos[i];
          elementos[i] = elementos[i+1];
          elementos[i+1] = temp;
          ultimo=i;
      }
      estado->nOperaciones++;
    }
    der=ultimo;
   };
}


/* Shell sort */
void ordShell(int elementos[], int nelementos, Informa f, TEstado* estado)
{
  int i, j, k, intervalo=nelementos, temp;
  boolean fin=falso, terminado;

  while(intervalo>0 && !fin) {
    intervalo/=2;
    do {
     terminado=verdad;
     for(i=0; i<nelementos-intervalo && !fin; i++) {
        j = i+intervalo;
        if (elementos[i] > elementos[j]) {
          estado->deElemento=i;
          estado->aElemento=j;
          fin=f(estado);
          temp = elementos[i];
          elementos[i] = elementos[j];
          elementos[j] = temp;
          terminado=falso;
         }
     estado->nOperaciones++;
    }
   } while(!terminado);
  }
}

/* Internal recursive function for quick sort */
boolean quickSort(int elementos[], int izq, int der, Informa f, TEstado* estado)
{
  int pivote, i, j;

  boolean fin=falso;

  i = izq;
  j = der;
  pivote = elementos[izq];
  while (izq < der && !fin)
  {
    while ((elementos[der] >= pivote) && (izq < der) && !fin)
      der--;
    if (izq != der)
    {
      estado->deElemento=der;
      estado->aElemento=izq;
      estado->nOperaciones++;
      fin|=f(estado);
      elementos[izq] = elementos[der];
      izq++;
    }
    while ((elementos[izq] <= pivote) && (izq < der) && !fin)
      izq++;
    if (izq != der)
    {
      estado->deElemento=izq;
      estado->aElemento=der;
      estado->nOperaciones++;
      fin|=f(estado);
      elementos[der] = elementos[izq];
      der--;
    }
  }
  elementos[izq] = pivote;
  pivote = izq;
  izq = i;
  der = j;
  if (izq < pivote && !fin)
    fin|=quickSort(elementos, izq, pivote-1,f,estado);
  if (der > pivote && !fin)
    fin|=quickSort(elementos, pivote+1, der, f, estado);

  return fin;
}

/* Quick sort */
void ordQuick(int elementos[], int nelementos, Informa f, TEstado* estado)
{
  quickSort(elementos, 0, nelementos - 1, f, estado);
}
