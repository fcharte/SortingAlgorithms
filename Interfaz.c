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

/* Función que muestra la lista de algoritmos y permite elegir los que
  se quieren probar */
boolean EnumeraAlgoritmos(TAlgoritmo* algoritmos,int nAlgoritmos)
{
   int i, tecla;

   // Mostraremos la lista de algoritmos en la ventana superior
   wclear(wProceso);
   wattron(wProceso,COLOR_PAIR(2));
   wattron(wProceso,A_BOLD);
   EscribeCentrado(0,"Algoritmos de ordenación disponibles - Sorting algorithms available");

   // Tres columnas con los nombres de los algoritmos y un índice entre corchetes
   for(i=0;i<nAlgoritmos;i++) {
      wmove(wProceso,3+i/3,5+25*(i%3));
      wprintw(wProceso, "[%d] %s",i,algoritmos[i].nombre);
   }

   // Más instrucciones
   wprintw(wProceso,"\n\nUtiliza las teclas de desplazamiento del cursor y ");
   wprintw(wProceso,"la barra espaciadora  para elegir los algoritmos que ");
   wprintw(wProceso,"quieres analizar. Pulsa INTRO para comenzar el proceso ");
   wprintw(wProceso,"o ESC para terminar");
   wrefresh(wProceso);

   i=0; // Índice del algoritmo seleccionado
   do {
      // Situar el cursor en el lugar adecuado
      wmove(wProceso,3+i/3,6+25*(i%3));
      wrefresh(wProceso);
      tecla=wgetch(wProceso); // y esperar al usuario

      // según la tecla que se haya pulsado
      switch(tecla) {
        case 32: // la barra espaciado marca/desmarca el algoritmo actual
          algoritmos[i].elegido=!algoritmos[i].elegido;
          wattron(wProceso,algoritmos[i].elegido?COLOR_PAIR(3):COLOR_PAIR(2));
          wattron(wProceso,A_BOLD);
          wprintw(wProceso,"%d",i);
          wattron(wProceso,COLOR_PAIR(2));
          break;
        case KEY_UP: // desplazamiento hacia arriba
          i=i>2?i-3:i;
          break;
        case KEY_DOWN: // desplazamiento hacia abajo
          i=i<nAlgoritmos-3?i+3:i;
          break;
        case KEY_LEFT: // desplazamiento hacia la izquierda
          i=i?i-1:i;
          break;
        case KEY_RIGHT: // desplazamiento hacia la derecha
          i=i<nAlgoritmos-1?i+1:i;
          break;
      }
      // hasta que se pulse ESC o INTRO
   } while(tecla!=27&&tecla!=10&&tecla!=13);

   if(tecla!=27) { // Si no se ha pulsado ESC
      wmove(wProceso,3,3);
      // más instrucciones
      wprintw(wProceso, "A continuación se utilizará  esta ventana para ");
      wprintw(wProceso,"representar gráficamente los elementos que van ");
      wprintw(wProceso,"ordenándose en un vector de enteros generado ");
      wprintw(wProceso,"aleatoriamente, mientras en la ventana inferior ");
      wprintw(wProceso,"se facilita información sobre el proceso. En ");
      wprintw(wProceso,"cualquier momento puedes usar la tecla ESC para ");
      wprintw(wProceso,"detener el algoritmo en curso y pasar al siguiente.");
      wprintw(wProceso, "\n\nPulsa una tecla para comenzar ... - Press a key to start");
      wrefresh(wProceso);
      wgetch(wProceso);
      return falso;
   } else
     return verdad; // Si se ha pulsado ESC lo notificamos para terminar
}

/* Muestra los vectores que van a intercambiarse */
void MuestraVectoresaIntercambiar(int i1, int i2, int v1, int v2)
{
  if(i2>=COLS-2) {
    wmove(wProceso,0,i1);
    wvline(wProceso,' ',LINES-8);

    // y las ponemos en su nueva posición
    wattron(wProceso,COLOR_PAIR(2));
    wmove(wProceso,(LINES-8-v2)/2,i1);
    wvline(wProceso,ACS_VLINE,v2);
    wrefresh(wProceso);
    return;
  }
  // La línea del primer elemento a intercambiar aparece en rojo
  wattron(wProceso,COLOR_PAIR(4));
  wmove(wProceso,(LINES-8-v1)/2,i1);
  wvline(wProceso,ACS_VLINE,v1);
  // y la línea del segundo elemento en verde
  wattron(wProceso,COLOR_PAIR(5));
  wmove(wProceso,(LINES-8-v2)/2,i2);
  wvline(wProceso,ACS_VLINE,v2);
  wrefresh(wProceso);

  // Eliminamos esas líneas
  wmove(wProceso,0,i1);
  wvline(wProceso,' ',LINES-8);
  wmove(wProceso,0,i2);
  wvline(wProceso,' ',LINES-8);

  // y las ponemos en su nueva posición
  wattron(wProceso,COLOR_PAIR(2));
  wmove(wProceso,(LINES-8-v1)/2,i2);
  wvline(wProceso,ACS_VLINE,v1);
  wmove(wProceso,(LINES-8-v2)/2,i1);
  wvline(wProceso,ACS_VLINE,v2);
}

/* Notificación de intercambio de elementos */
boolean MuestraNotificacion(TEstado* estado, int nElementos)
{
  int tecla;
  boolean retorno=falso; // Indicación de que hay que interrumpir

  // Establecemos el retardo
  delay_output(retardo);
  // y comprobamos si hay alguna pulsación de tecla
  tecla=wgetch(wProceso);

  switch(tecla) { // dependiendo de la tecla pulsada
    case 27:
         retorno=verdad; // interrumpimos el algoritmo
         break;
    case '-':
         // incrementamos el retardo
         retardo=retardo<1000?retardo+10:retardo;
         break;
    case '+':
         // o lo reducimos
         retardo=retardo>10?retardo-10:retardo;
         break;
  }

  estado->nIntercambios++; // Incrementar el número de intercambios

  // y mostrar la información de cómo va el proceso en la consola
  wmove(wConsola,2,25);
  wprintw(wConsola, "%7d",estado->nOperaciones);
  wmove(wConsola,2,40);
  wprintw(wConsola, "%7d",estado->nIntercambios);
  wrefresh(wConsola);

  return retorno;
}
