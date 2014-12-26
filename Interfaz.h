/**
   @file interfaz.h
   @version 1.0
   @author Francisco Charte Ojeda
   @brief Prototipos de las funciones que implementan la interfaz de la aplicación

    Este programa implementa por defecto una interfaz basada en texto,
    mediante ncurses, lo que facilita su ejecución en distintas plataformas
    sin ningún problema. No obstante, los algoritmos de ordenación y el
    núcleo del programa son independientes de la interfaz, lo cual hace
    posible su sustitución por cualquier otra siempre que se implementen las
    funciones definidas en este archivo de cabecera.
*/
#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "Definiciones.h"
#include <string.h>

/**@brief Escribe un texto centrado

  Macro para escribir centrado un texto en la zona que ocupe la mayor
  parte de la interfaz. Por defecto esa zona es la ventana @a wProceso,
  que ocupa la parte superior de la pantalla
*/
#define EscribeCentrado(lin,texto) \
  wmove(wProceso,lin,(COLS-strlen(texto))/2); \
  wprintw(wProceso,texto);

/**@brief Calcula el rango de los valores la matriz

  Los valores del vector a ordenar estarán comprendidos entre 1 y un valor
  que le interese a la interfaz, ya que es ésta la que va a representarlos
  gráficamente. Esta función devolverá un entero indicando ese valor límite.

  @return El máximo valor de los números alojados en el vector a ordenar
  @post El valor devuelto no deberá superar los valores que puede devolver la función rand()
*/
int CalculaRango();

/**@brief Prepara la interfaz de usuario del programa

  Esta función es la responsable de preparar la interfaz de usuario que va
  a ofrecer el programa. Por defecto, la aplicación inicializa ncurses y
  define las ventanas que van a utilizarse, una para mostrar el proceso y otra
  que actúa como consola.

  @return El máximo número de elementos que puede representar en pantalla
  @post La función debe evaluar, según la representación que vaya a efectuar,
  cuántos elementos puede representar y devolver ese número como resultado. El
  núcleo del programa creará el vector a ordenar con ese número exacto de elementos.
*/
int InicializaPantalla();

/**@brief Efectúa la presentación del programa

  El núcleo del programa llama a esta función facilitándole la lista de
  algoritmos que hay disponibles y un entero con el número de elementos en
  dicha lista. Lo que se espera es que la función efectúe una presentación
  al usuario de la finalidad del programa, espere un tiempo o una pulsación
  de tecla y devuelva el control al programa principal sin hacer nada más.

  @param algoritmos Vector con los algoritmos de ordenación registrados
  @param nAlgoritmos Entero indicando el número de algoritmos existentes en el vector
  @return No hay valor de retorno
  @pre El programa llamará a esta función una única vez, al inicio de la ejecución,
  por lo que es el lugar adecuado para mostrar instrucciones generales de uso.
  @post La función debe dar oportunidad al usuario a leer la presentación, si
  devuelve el control de inmediato al programa principal éste avanzará al paso
  siguiente y las instrucciones no podrán ser leídas.
*/
void Presentacion(TAlgoritmo* algoritmos, int nAlgoritmos);

/**@brief Permite elegir los algoritmos a probar

  Esta función es invocada al inicio de cada ciclo de prueba de algoritmos,
  siendo la encargada de mostrar al usuario los que hay disponibles y darle
  a elegir aquellos que quiere probar. También debe dar la posibilidad de
  terminar el programa y salir. La interfaz por defecto utiliza ncurses
  para que el usuario se desplace con las teclas de cursor y vaya marcando
  y desmarcando algoritmos. Hecha la selección, la función debe devolver el
  control al programa principal.

  @param algoritmos Vector con los algoritmos disponibles
  @param nAlgoritmos Entero indicando el número de elementos del vector
  @return Un valor @a boolean indicando si la aplicación debe terminar o no
  @pre La función debe ser cada de mostrar los @a nAlgoritmos y dar a elegir al usuario,
  ya sea mediante teclado o ratón
  @pre La función tiene que ofrecer una opción para terminar
  @post Si se elige la opción de finalización la función debe devolver @a verdad,
  retornando @a falso en caso contrario
  @post La función debe dar el valor @a verdad al campo @a elegido de cada
  algoritmo elegido por el usuario, ya que éste es el mecanismo que permitirá
  al programa principal saber qué algoritmos debe ejecutar
*/
boolean EnumeraAlgoritmos(TAlgoritmo* algoritmos, int nAlgoritmos);

/**@brief Representa gráficamente el vector

   Esta función debe mostrar en la interfaz el contenido del vector de
   elementos que se están ordenando. El núcleo del programa invoca a esta
   función cuando va a iniciarse la prueba de un algoritmo de ordenación.
   Internamente, el código que gestiona la interfaz también lo llamada cada
   vez que se notifica un cambio.

  @param vector Vector con los números que están ordenándos
  @param nElementos Número de elementos que contiene el vector
  @return No hay valor de retorno
*/
void MuestraVector(int* vector, int nElementos);

/**@brief Destaca los vectores que van a ser intercambiados

  Esta función destaca la representación gráfica de los vectores que acaban
  de ser intercambiados por el algoritmo de ordenación.

  @param i1 Índice del primer elemento a intercambiar
  @param i2 Índice del segundo elemento a intercambiar
  @param v1 Valor del primer elemento a intercambiar
  @param v2 Valor del segundo elemento a intercambiar
  @return No hay valor de retorno
  @post La interfaz por defecto muestra destacadas en otro color las líneas que
  representan a los elementos a intercambiar.
*/
void MuestraVectoresaIntercambiar(int i1, int i2, int v1, int v2);

/**@brief Notificación de cambios en el vector

  Cada vez que el algoritmo de ordenación que está ejecutándose intercambia dos
  elementos del vector, llama a una función de notificación en el programa
  principal. Esa función invocará a ésta entregándole como argumentos la
  estructura TEstado y el número de elementos del vector. La interfaz puede
  proceder según convenga, por defecto se vuelve a mostrar el vector de elementos
  mediante la función MuestraVector. Lo más importante es que esta función debe
  detectar si el usuario quiere cancelar la ejecución, devolviendo @a verdad en
  caso de que así sea.

  @param estado Puntero a la estructura TEstado del proceso de ordenación que
  está ejecutándose
  @param nElementos Número de elementos que contiene el vector
  @return Un valor de tipo @a boolean indicando si debe interrumpirse el proceso
  @post El núcleo del programa no introduce retardo alguno en el proceso de
  ordenación, siendo ésta tarea de la interfaz. Esta función puede ser el lugar
  más adecuado para establecer ese retardo de manera adecuada.
*/
boolean MuestraNotificacion(TEstado* estado, int nElementos);

/**@brief Notifica del inicio de un algoritmo de ordenación

  Cada vez que va a iniciarse la ordenación del vector mediante un algoritmo de
  los elegidos, el programa principal invoca a esta función facilitándole el
  nombre del algoritmo. La interfaz puede utilizar ese dato como convenga. Por
  defecto se usa para mostrarlo en la consola, la ventana de la parte inferior
  de la pantalla.

  @param nombre Nombre descriptivo del algoritmo de ordenación
  @return No hay valor de retorno
*/
void MuestraInicioAlgoritmo(char* nombre);

/**@brief Notifica del fin de un algoritmo de ordenación

  Cada vez que se termina la ejecución de un algoritmo de ordenación, el
  programa principal invoca a esta función indicándole si el orden final de
  los elementos ha sido correcto o no.

  @param ordenado Indica si el vector ha quedado bien ordenado
  @return No hay valor de retorno
  @pre Que el valor recibido por esta función sea @a falso puede indicar dos
  circunstancias diferentes: que el algoritmo probado no funcione adecuadamente,
  y el vector no haya quedado bien ordenado, o bien que el proceso haya sido
  interrumpido al devolver @a verdad la función @a MuestraNotificacion de la
  propiedad interfaz, en cuyo caso no puede saber si el algoritmo funciona o no
*/
void MuestraFinAlgoritmo(boolean ordenado);

/**@brief Resumen los resultados de los algoritmos probados

  Cuando se termina la prueba de la lista de algoritmos seleccionados, se
  invoca a esta función para que muestre los resultados al usuario.

  @param algoritmos Vector con los algoritmos existentes
  @param estado Vector con las estructuras TEstado que contienen los resultados
  @param nAlgoritmos Número de algoritmos registrados
  @return No hay valor de retorno
  @pre Al invocar a esta función, la estructura TAlgoritmo que representa a cada
  algoritmo tendrá el campo @a elegido a @a verdad o a @a falso, dato que debe
  utilizarse para saber qué algoritmos se han ejecutado.
  @post La función es responsable de poner a @a falso el campo @a elegido de
  cada algoritmo una vez que ya no le sea útil y, en cualquier caso, antes de
  de devolver el control al programa principal.
*/
void MuestraResumen(TAlgoritmo* algoritmos, TEstado* estado, int nAlgoritmos);

/**@brief Pone fin a la interfaz de usuario

  El programa principal invoca a esta función para dar oportunidad a que la
  interfaz se cierre apropiadamente.

  @return No hay valor de retorno
*/
void FinInterfaz();

#endif /* __INTERFAZ_H__ */

