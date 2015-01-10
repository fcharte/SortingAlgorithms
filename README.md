Educational implementation of sorting algorithms 
================================================

Several sorting algorithms implemented in plain C language, with an extensible approach (new algorithms can be connected)
and a simple visualization mechanishm aimed to understand how they work.

The C code is portable to Windows, GNU/Linux and OS X, as the user interface is based on the ncurses library.

The code is documented (in Spanish) with the [doxygen tool](http://www.stack.nl/~dimitri/doxygen/).

Algorithms implemented
----------------------

The algorithms currently implemented are the following:

* Bubble sort - `ordBurbuja()`
* Improved bubble sort - `ordBurbujaMejorado()`
* Selection sort - `ordSeleccion()`
* Insertion sort - `ordInsercion()`
* Shaker sort (also known as cocktail sort) - `ordSacudida()`
* Shell sort - `ordShell()`
* Quick sort - `ordQuick()`

Compilation
-----------

To compile this program you will need `gcc`, `ncurses` and `make`. A `Makefile` is provided along with the source code. Put all files, including the `Makefile`, in a directory, and type `make` to build the application. This will be the procedure to follow in GNU/Linux or OS X. 

If you use Windows, look for [Cygwin](https://www.cygwin.com/) to obtain the tools you will needed. The `curses.h` header file and the `libpdcurses.a` library are included in the `curses` folder of this repository.


