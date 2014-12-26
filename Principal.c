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

/**@brief Genera un vector con el número adecuado de elementos aleatorio */
void VectorAleatorio(int* elementos, int nElementos, int rango)
{
   int i;

   for(i=0;i<nElementos;i++)
     // los números estarán en el rango adecuado
     elementos[i] = rand()%rango+1;
}

/**@brief Esta función comprueba si el vector está bien ordenado */
boolean VerificaOrden(int* elementos, int nElementos)
{
   boolean ordenado=verdad;
   int i;

   for(i=0;i<nElementos-1 && ordenado; i++)
     ordenado=elementos[i]<=elementos[i+1];

   return ordenado;
}

/* Punto de entrada a la aplicación */
int main(int argc, char *argv[])
{
   int i, rango;
   boolean fin=falso;

   int *elementos, *vector;
   TEstado *estado;

   /* Inicializamos la interfaz y obtenemos el número de elementos
     que pueden representarse */
   nElementos=InicializaPantalla();

   // Obtenemos el rango de los valores
   rango=CalculaRango();

   /* y creamos los vectores. Se usan dos, uno que mantiene los elementos
    aleatorios obtenidos inicialmente y otro que va entregándose a los
    algoritmos, para que todos ellos operen sobre el mismo conjunto de
    elementos y puedan ser comparados de manera homogénea. */
   elementos=malloc(sizeof(int)*(nElementos+1));
   assert(elementos!=NULL);
   vector=malloc(sizeof(int)*(nElementos+1));
   assert(vector!=NULL);
   estado=malloc(sizeof(TEstado)*nAlgoritmos);
   assert(estado!=NULL);

   // Presentación del programa
   Presentacion(algoritmos,nAlgoritmos);

   while(!fin) { // Hasta que se pulse ESC en la selección de algoritmos
    // Obtenemos un nuevo vector aleatorio
    VectorAleatorio(vector,nElementos,rango);
    // y permitimos la selección de algoritmos a aplicarle
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
