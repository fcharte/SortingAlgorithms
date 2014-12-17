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
