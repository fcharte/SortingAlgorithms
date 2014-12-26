/**
   @file interfaz.h
   @version 1.0
   @author Francisco Charte Ojeda
   @brief Prototipos de las funciones que implementan la interfaz de la aplicaci�n

    Este programa implementa por defecto una interfaz basada en texto,
    mediante ncurses, lo que facilita su ejecuci�n en distintas plataformas
    sin ning�n problema. No obstante, los algoritmos de ordenaci�n y el
    n�cleo del programa son independientes de la interfaz, lo cual hace
    posible su sustituci�n por cualquier otra siempre que se implementen las
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

  Los valores del vector a ordenar estar�n comprendidos entre 1 y un valor
  que le interese a la interfaz, ya que es �sta la que va a representarlos
  gr�ficamente. Esta funci�n devolver� un entero indicando ese valor l�mite.

  @return El m�ximo valor de los n�meros alojados en el vector a ordenar
  @post El valor devuelto no deber� superar los valores que puede devolver la funci�n rand()
*/
int CalculaRango();

/**@brief Prepara la interfaz de usuario del programa

  Esta funci�n es la responsable de preparar la interfaz de usuario que va
  a ofrecer el programa. Por defecto, la aplicaci�n inicializa ncurses y
  define las ventanas que van a utilizarse, una para mostrar el proceso y otra
  que act�a como consola.

  @return El m�ximo n�mero de elementos que puede representar en pantalla
  @post La funci�n debe evaluar, seg�n la representaci�n que vaya a efectuar,
  cu�ntos elementos puede representar y devolver ese n�mero como resultado. El
  n�cleo del programa crear� el vector a ordenar con ese n�mero exacto de elementos.
*/
int InicializaPantalla();

/**@brief Efect�a la presentaci�n del programa

  El n�cleo del programa llama a esta funci�n facilit�ndole la lista de
  algoritmos que hay disponibles y un entero con el n�mero de elementos en
  dicha lista. Lo que se espera es que la funci�n efect�e una presentaci�n
  al usuario de la finalidad del programa, espere un tiempo o una pulsaci�n
  de tecla y devuelva el control al programa principal sin hacer nada m�s.

  @param algoritmos Vector con los algoritmos de ordenaci�n registrados
  @param nAlgoritmos Entero indicando el n�mero de algoritmos existentes en el vector
  @return No hay valor de retorno
  @pre El programa llamar� a esta funci�n una �nica vez, al inicio de la ejecuci�n,
  por lo que es el lugar adecuado para mostrar instrucciones generales de uso.
  @post La funci�n debe dar oportunidad al usuario a leer la presentaci�n, si
  devuelve el control de inmediato al programa principal �ste avanzar� al paso
  siguiente y las instrucciones no podr�n ser le�das.
*/
void Presentacion(TAlgoritmo* algoritmos, int nAlgoritmos);

/**@brief Permite elegir los algoritmos a probar

  Esta funci�n es invocada al inicio de cada ciclo de prueba de algoritmos,
  siendo la encargada de mostrar al usuario los que hay disponibles y darle
  a elegir aquellos que quiere probar. Tambi�n debe dar la posibilidad de
  terminar el programa y salir. La interfaz por defecto utiliza ncurses
  para que el usuario se desplace con las teclas de cursor y vaya marcando
  y desmarcando algoritmos. Hecha la selecci�n, la funci�n debe devolver el
  control al programa principal.

  @param algoritmos Vector con los algoritmos disponibles
  @param nAlgoritmos Entero indicando el n�mero de elementos del vector
  @return Un valor @a boolean indicando si la aplicaci�n debe terminar o no
  @pre La funci�n debe ser cada de mostrar los @a nAlgoritmos y dar a elegir al usuario,
  ya sea mediante teclado o rat�n
  @pre La funci�n tiene que ofrecer una opci�n para terminar
  @post Si se elige la opci�n de finalizaci�n la funci�n debe devolver @a verdad,
  retornando @a falso en caso contrario
  @post La funci�n debe dar el valor @a verdad al campo @a elegido de cada
  algoritmo elegido por el usuario, ya que �ste es el mecanismo que permitir�
  al programa principal saber qu� algoritmos debe ejecutar
*/
boolean EnumeraAlgoritmos(TAlgoritmo* algoritmos, int nAlgoritmos);

/**@brief Representa gr�ficamente el vector

   Esta funci�n debe mostrar en la interfaz el contenido del vector de
   elementos que se est�n ordenando. El n�cleo del programa invoca a esta
   funci�n cuando va a iniciarse la prueba de un algoritmo de ordenaci�n.
   Internamente, el c�digo que gestiona la interfaz tambi�n lo llamada cada
   vez que se notifica un cambio.

  @param vector Vector con los n�meros que est�n orden�ndos
  @param nElementos N�mero de elementos que contiene el vector
  @return No hay valor de retorno
*/
void MuestraVector(int* vector, int nElementos);

/**@brief Destaca los vectores que van a ser intercambiados

  Esta funci�n destaca la representaci�n gr�fica de los vectores que acaban
  de ser intercambiados por el algoritmo de ordenaci�n.

  @param i1 �ndice del primer elemento a intercambiar
  @param i2 �ndice del segundo elemento a intercambiar
  @param v1 Valor del primer elemento a intercambiar
  @param v2 Valor del segundo elemento a intercambiar
  @return No hay valor de retorno
  @post La interfaz por defecto muestra destacadas en otro color las l�neas que
  representan a los elementos a intercambiar.
*/
void MuestraVectoresaIntercambiar(int i1, int i2, int v1, int v2);

/**@brief Notificaci�n de cambios en el vector

  Cada vez que el algoritmo de ordenaci�n que est� ejecut�ndose intercambia dos
  elementos del vector, llama a una funci�n de notificaci�n en el programa
  principal. Esa funci�n invocar� a �sta entreg�ndole como argumentos la
  estructura TEstado y el n�mero de elementos del vector. La interfaz puede
  proceder seg�n convenga, por defecto se vuelve a mostrar el vector de elementos
  mediante la funci�n MuestraVector. Lo m�s importante es que esta funci�n debe
  detectar si el usuario quiere cancelar la ejecuci�n, devolviendo @a verdad en
  caso de que as� sea.

  @param estado Puntero a la estructura TEstado del proceso de ordenaci�n que
  est� ejecut�ndose
  @param nElementos N�mero de elementos que contiene el vector
  @return Un valor de tipo @a boolean indicando si debe interrumpirse el proceso
  @post El n�cleo del programa no introduce retardo alguno en el proceso de
  ordenaci�n, siendo �sta tarea de la interfaz. Esta funci�n puede ser el lugar
  m�s adecuado para establecer ese retardo de manera adecuada.
*/
boolean MuestraNotificacion(TEstado* estado, int nElementos);

/**@brief Notifica del inicio de un algoritmo de ordenaci�n

  Cada vez que va a iniciarse la ordenaci�n del vector mediante un algoritmo de
  los elegidos, el programa principal invoca a esta funci�n facilit�ndole el
  nombre del algoritmo. La interfaz puede utilizar ese dato como convenga. Por
  defecto se usa para mostrarlo en la consola, la ventana de la parte inferior
  de la pantalla.

  @param nombre Nombre descriptivo del algoritmo de ordenaci�n
  @return No hay valor de retorno
*/
void MuestraInicioAlgoritmo(char* nombre);

/**@brief Notifica del fin de un algoritmo de ordenaci�n

  Cada vez que se termina la ejecuci�n de un algoritmo de ordenaci�n, el
  programa principal invoca a esta funci�n indic�ndole si el orden final de
  los elementos ha sido correcto o no.

  @param ordenado Indica si el vector ha quedado bien ordenado
  @return No hay valor de retorno
  @pre Que el valor recibido por esta funci�n sea @a falso puede indicar dos
  circunstancias diferentes: que el algoritmo probado no funcione adecuadamente,
  y el vector no haya quedado bien ordenado, o bien que el proceso haya sido
  interrumpido al devolver @a verdad la funci�n @a MuestraNotificacion de la
  propiedad interfaz, en cuyo caso no puede saber si el algoritmo funciona o no
*/
void MuestraFinAlgoritmo(boolean ordenado);

/**@brief Resumen los resultados de los algoritmos probados

  Cuando se termina la prueba de la lista de algoritmos seleccionados, se
  invoca a esta funci�n para que muestre los resultados al usuario.

  @param algoritmos Vector con los algoritmos existentes
  @param estado Vector con las estructuras TEstado que contienen los resultados
  @param nAlgoritmos N�mero de algoritmos registrados
  @return No hay valor de retorno
  @pre Al invocar a esta funci�n, la estructura TAlgoritmo que representa a cada
  algoritmo tendr� el campo @a elegido a @a verdad o a @a falso, dato que debe
  utilizarse para saber qu� algoritmos se han ejecutado.
  @post La funci�n es responsable de poner a @a falso el campo @a elegido de
  cada algoritmo una vez que ya no le sea �til y, en cualquier caso, antes de
  de devolver el control al programa principal.
*/
void MuestraResumen(TAlgoritmo* algoritmos, TEstado* estado, int nAlgoritmos);

/**@brief Pone fin a la interfaz de usuario

  El programa principal invoca a esta funci�n para dar oportunidad a que la
  interfaz se cierre apropiadamente.

  @return No hay valor de retorno
*/
void FinInterfaz();

#endif /* __INTERFAZ_H__ */

