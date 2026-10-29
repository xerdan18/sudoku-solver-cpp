# Resolvedor de Sudokus

Programa de terminal en C++ que lee un sudoku desde un archivo de texto, comprueba que sea válido y lo resuelve con **backtracking recursivo**.

```
> sudoku puzzles/facil.txt
5 3 . | . 7 . | . . .
6 . . | 1 9 5 | . . .
. 9 8 | . . . | . 6 .
------+-------+------
8 . . | . 6 . | . . 3
4 . . | 8 . 3 | . . 1
7 . . | . 2 . | . . 6
------+-------+------
. 6 . | . . . | 2 8 .
. . . | 4 1 9 | . . 5
. . . | . 8 . | . 7 9

Solucion:
5 3 4 | 6 7 8 | 9 1 2
6 7 2 | 1 9 5 | 3 4 8
1 9 8 | 3 4 2 | 5 6 7
------+-------+------
8 5 9 | 7 6 1 | 4 2 3
4 2 6 | 8 5 3 | 7 9 1
7 1 3 | 9 2 4 | 8 5 6
------+-------+------
9 6 1 | 5 3 7 | 2 8 4
2 8 7 | 4 1 9 | 6 3 5
3 4 5 | 2 8 6 | 1 7 9
```

## Compilar

El proyecto es un único archivo, `main.cpp`, y solo usa la biblioteca estándar de C++17.

**Windows (Visual Studio / Build Tools)**, desde la *Developer PowerShell*:

```bash
cl /EHsc /std:c++17 /W4 main.cpp /Fe:sudoku.exe
```

**Linux / macOS (g++ o clang++)**:

```bash
g++ -std=c++17 -Wall -O2 main.cpp -o sudoku
```

## Uso

```bash
sudoku <archivo>
```

Por ejemplo:

```bash
sudoku puzzles/facil.txt
```

El programa termina con código de salida `0` si resolvió el sudoku y `1` ante cualquier error (archivo inexistente, formato inválido, números repetidos o sudoku sin solución).

### Formato del archivo

9 líneas de 9 caracteres cada una. Cada carácter es un dígito del `1` al `9`, o un `0` o un `.` para las casillas vacías:

```
530070000
600195000
098000060
800060003
400803001
700020006
060000280
000419005
000080079
```

## Cómo funciona

El programa trabaja en tres pasos.

### 1. Lectura

`leerTablero` abre el archivo, comprueba que tenga 9 líneas de 9 caracteres y convierte cada carácter a un número en una matriz `int tablero[9][9]`, donde `0` representa una casilla vacía. Si algo falla, indica en qué línea y columna está el problema.

### 2. Validación

Antes de resolver, `tableroValido` comprueba que el sudoku de entrada no tenga números repetidos en ninguna fila, columna o caja de 3x3. Para cada casilla con número llama a `sePuedePoner`, que revisa:

- **la fila** y **la columna** de la casilla;
- **su caja de 3x3**, cuya esquina superior izquierda se calcula con `fila - fila % 3` y `col - col % 3`.

### 3. Resolución con backtracking

`resolver` es una función recursiva que llena una casilla por llamada:

```
resolver(tablero):
    buscar la primera casilla vacía
    si no hay ninguna → el sudoku está resuelto, devolver true

    para cada número del 1 al 9:
        si el número se puede poner en esa casilla:
            ponerlo
            si resolver(tablero) da true → devolver true
            si no, borrarlo (volver a 0) y probar el siguiente

    ningún número funcionó → devolver false
```

Cuando una casilla no admite ningún número, la función devuelve `false` y la ejecución vuelve a la llamada anterior, que borra su número y prueba el siguiente. Ese "volver atrás" es el *backtracking*: se recorren los caminos posibles como en un laberinto y se retrocede al chocar con una pared.

La misma función `sePuedePoner` sirve para validar la entrada y para decidir qué números probar al resolver.

## Archivos de prueba

En `puzzles/` hay un sudoku válido y varios casos para probar cada error:

| Archivo | Qué prueba |
|---|---|
| `facil.txt` | Sudoku válido con solución |
| `sin_solucion.txt` | Sudoku sin repetidos pero imposible de resolver |
| `repetido_fila.txt` | Número repetido en una fila |
| `repetido_caja.txt` | Número repetido en una caja de 3x3 (distinta fila y columna) |
| `corto.txt` | Archivo con menos de 9 líneas |
| `mal.txt` | Una línea con 8 caracteres |
| `letra.txt` | Un carácter no válido |

## Posibles mejoras

- Medir y mostrar el tiempo que tarda en resolver.
- Elegir primero la casilla con menos opciones posibles para resolver más rápido los sudokus difíciles.
- Generar sudokus nuevos.
