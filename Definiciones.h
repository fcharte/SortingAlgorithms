#ifndef __DEFINICIONES_H__
#define __DEFINICIONES_H__

/**@brief Para indicadores y banderas */
typedef enum {false=0,true} boolean;

/**@brief Información que cada algoritmo devolverá al programa principal */
typedef struct {
   int indice;
   int deElemento, aElemento;
   int nOperaciones, nIntercambios;
   int *vector;
} TEstado;

/**@brief Firma de la función de notificación */
typedef boolean (*Informa)(TEstado*);

/**@brief Firma de las funciones de ordenación */
typedef void (*Ordena)(int [], int, Informa, TEstado*);

/**@brief Información que registro de los algoritmos */
typedef struct {
   char* nombre;
   Ordena f;
   boolean elegido;
} TAlgoritmo;



#endif /* __DEFINICIONES_H__ */

