/**
   @file interfaz.c
   @version 1.0
   @author Francisco Charte Ojeda
   @brief Implementación de la interfaz de usuario

   Este módulo implementa una interfaz de usuario basada en texto con ncurses,
   lo cual permite su compilación en distintos sistemas operativos obteniendo
   prácticamente el mismo resultado.
*/

#include <curses.h>
#include "Interfaz.h"

int retardo=100; /** Retardo por defecto de una décima de segundo */
WINDOW *wProceso, /** Ventana donde se mostrará el proceso de ordenación */
       *wConsola; /** Ventana de comunicación de resultados */

/* Devuelve el rango de los valores */
int CalculaRango()
{
   // que dependerá del número de líneas disponibles en pantalla
   return (LINES-8);
}

/* Inicializa la interfaz de usuario */
int InicializaPantalla()
{
   int nElementos; /* Número de elementos que pueden representarse en pantalla */

   /* Inicialización de ncurses */
   initscr();
   raw();
   noecho();
   start_color();

   /* Configuración de las parejas de colores que van a utilizarse */
   init_pair(1,COLOR_WHITE,COLOR_BLUE);
   init_pair(2,COLOR_YELLOW,COLOR_BLUE);
   init_pair(3,COLOR_BLUE,COLOR_WHITE);
   init_pair(4,COLOR_RED,COLOR_BLUE);
   init_pair(5,COLOR_GREEN,COLOR_BLUE);

   /* Se podrán representar tantos elementos como columnas haya menos 2 */
   nElementos=COLS-2;

   /* Preparación del borde y colores de la ventana inferior, que actuará
     como consola */
   wConsola=newwin(6, COLS, LINES-6,0);
   wattron(wConsola,COLOR_PAIR(1));
   wattron(wConsola,A_BOLD);
   wborder(wConsola, 0, 0, 0, 0, 0, 0, 0, 0);
   wrefresh(wConsola);
   delwin(wConsola);
   wConsola=newwin(4, COLS-2, LINES-5,1);
   wattron(wConsola,COLOR_PAIR(1));
   wattron(wConsola,A_BOLD);
   wbkgdset(wConsola,COLOR_PAIR(1));
   wclear(wConsola);

   /* Preparación del borde y colores de la ventana superior, en la que
      se representar  el proceso de ordenación */
   wProceso=newwin(LINES-6,COLS,0,0);
   wattron(wProceso,COLOR_PAIR(2));
   wborder(wProceso, 0, 0, 0, 0, 0, 0, 0, 0);
   wattron(wProceso,A_BOLD);
   wrefresh(wProceso);
   delwin(wProceso);
   wProceso=newwin(LINES-8,COLS-2,1,1);
   wattron(wProceso,COLOR_PAIR(2));
   wattron(wProceso,A_BOLD);
   wbkgdset(wProceso,COLOR_PAIR(2));
   wclear(wProceso);
   wrefresh(wProceso);
   nodelay(wProceso,verdad);
   keypad(wProceso,verdad);

   return nElementos;  /* Devolvemos el número de elementos a representar */
}

/* Presentación del programa */
void Presentacion(TAlgoritmo* algoritmos, int nAlgoritmos)
{
   int i;

   /* Unos cuantos mensajes con instrucciones */
   EscribeCentrado(0,"Algoritmos de ordenación - Sorting algorithms");
   EscribeCentrado(1,"Francisco Charte Ojeda");
   wmove(wProceso,4,3);
   wprintw(wProceso,"Este programa permite comprobar el funcionamiento de ");
   wprintw(wProceso,"diferentes algoritmos de ordenación, mostrando visualmente ");
   wprintw(wProceso,"el proceso que siguen y calculando el número de  operaciones");
   wprintw(wProceso," y  de intercambios que se llevan a cabo en cada caso. Su ");
   wprintw(wProceso,"finalidad es exclusivamente didáctica, por ello está  abierto ");
   wprintw(wProceso,"a la adición de otros algoritmos con gran sencillez.\n");

   /* Indicamos el número de algoritmos existentes y mostramos el nombre de
     cada uno de ellos */
   wprintw(wProceso,"\n  Actualmente hay registrados %d algoritmos: ", nAlgoritmos);
   for(i=0;i<nAlgoritmos;i++)
      wprintw(wProceso, "%s - ",algoritmos[i].nombre);
   wprintw(wProceso,"\n\n  Pulsa una tecla para comenzar a utilizar el programa - Press a key to start");

   wrefresh(wProceso);
   wgetch(wConsola);
}