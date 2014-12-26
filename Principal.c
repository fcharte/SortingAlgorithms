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

/**@brief Genera un vector con el n�mero adecuado de elementos aleatorio */
void VectorAleatorio(int* elementos, int nElementos, int rango)
{
   int i;

   for(i=0;i<nElementos;i++)
     // los n�meros estar�n en el rango adecuado
     elementos[i] = rand()%rango+1;
}

/**@brief Esta funci�n comprueba si el vector est� bien ordenado */
boolean VerificaOrden(int* elementos, int nElementos)
{
   boolean ordenado=verdad;
   int i;

   for(i=0;i<nElementos-1 && ordenado; i++)
     ordenado=elementos[i]<=elementos[i+1];

   return ordenado;
}

/* Punto de entrada a la aplicaci�n */
int main(int argc, char *argv[])
{
   int i, rango;
   boolean fin=falso;

   int *elementos, *vector;
   TEstado *estado;

   /* Inicializamos la interfaz y obtenemos el n�mero de elementos
     que pueden representarse */
   nElementos=InicializaPantalla();

   // Obtenemos el rango de los valores
   rango=CalculaRango();

   /* y creamos los vectores. Se usan dos, uno que mantiene los elementos
    aleatorios obtenidos inicialmente y otro que va entreg�ndose a los
    algoritmos, para que todos ellos operen sobre el mismo conjunto de
    elementos y puedan ser comparados de manera homog�nea. */
   elementos=malloc(sizeof(int)*(nElementos+1));
   assert(elementos!=NULL);
   vector=malloc(sizeof(int)*(nElementos+1));
   assert(vector!=NULL);
   estado=malloc(sizeof(TEstado)*nAlgoritmos);
   assert(estado!=NULL);

   // Presentaci�n del programa
   Presentacion(algoritmos,nAlgoritmos);

   while(!fin) { // Hasta que se pulse ESC en la selecci�n de algoritmos
    // Obtenemos un nuevo vector aleatorio
    VectorAleatorio(vector,nElementos,rango);
    // y permitimos la selecci�n de algoritmos a aplicarle
    fin=EnumeraAlgoritmos(algoritmos, nAlgoritmos);
    if(!fin) { // si no se optado por salir del programa
      for(i=0; i<nAlgoritmos; i++) {
       if(algoritmos[i].elegido) { // y los entregamos a cada algoritmo elegido
         MuestraVector(vector,nElementos); // mostramos los elementos
         memcpy(elementos,vector,nElementos*sizeof(int));
         estado[i].nOperaciones=estado[i].nIntercambios=0;
         estado[i].vector=elementos;
         MuestraInicioAlgoritmo(algoritmos[i].nombre);
         algoritmos[i].f(elementos,nElementos,Notifica,&estado[i]);
         MuestraVector(elementos,nElementos); // mostramos los elementos
         MuestraFinAlgoritmo(VerificaOrden(elementos,nElementos));
       }
     }
     MuestraResumen(algoritmos,estado,nAlgoritmos);
    }
   }
   free(estado);
   free(elementos);
   FinInterfaz();
}
