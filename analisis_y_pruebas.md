# Analisis y pruebas

## Analisis

**Entradas:** `N`, `M`, limites `L` y `U`, y una matriz de `N x M` enteros.

**Salidas:** eventos e impacto total por fila, mayor racha e inicio, conteos por columna, fila prioritaria y columna destacada.

**Restricciones:** `1 <= N,M <= 30`, `0 <= L <= U <= 1000` y cada valor de la matriz entre 0 y 1000. Si alguna falla, se imprime solamente `ERROR`.

**Arreglos y variables:** matriz fija `values[30][30]`; vectores para eventos e impacto por fila, racha maxima e inicio por fila, y eventos por columna. `firstValue` guarda la primera lectura de la fila; `currentStreak` y `currentStreakStart` permiten recorrer las rachas.

## Pseudocodigo

```text
Leer N, M, L, U
Si N o M no esta entre 1 y 30: imprimir ERROR y terminar
Si L < 0, U > 1000 o L > U: imprimir ERROR y terminar
Leer la matriz; si algun valor no esta entre 0 y 1000: imprimir ERROR y terminar

Para cada fila:
    f = primer valor de la fila
    rachaActual = 0
    Para cada columna j:
        Si j >= 1 y L <= f - valor <= U:
            impacto = f - valor + 1
            incrementar eventos e impacto de la fila
            incrementar eventos de la columna
            incrementar rachaActual y actualizar racha maxima
            Si la racha maxima mejora, guardar su inicio
        Si no:
            rachaActual = 0
    Comparar fila para prioridad: racha, impacto, eventos, indice menor

Elegir la columna con mas eventos; conservar la primera en empate
Si no hubo eventos: prioridad = 0 y columna = 0
Imprimir filas, conteos por columna, prioridad y columna
```

En una racha empatada no se reemplaza el inicio guardado, por lo que se conserva la primera. La primera columna nunca puede generar un evento. Los datos de la matriz no se modifican.

## Prueba de escritorio: caso 01 del PDF

`N=3`, `M=5`, `L=5`, `U=15`.

| Fila | Valores | Reducciones desde el primero (columnas 2 a 5) | Eventos | Impactos | Racha maxima e inicio |
|---|---|---|---|---|---|
| 1 | 5, 15, 30, 10, 25 | -10, -25, -5, -20 | Ninguno | 0 | 0, 0 |
| 2 | 25, 10, 5, 20, 30 | 15, 20, 5, -5 | Columnas 2 y 4 | 16 + 6 = 22 | 1, 2 |
| 3 | 10, 20, 15, 5, 35 | -10, -5, 5, -25 | Columna 4 | 6 | 1, 4 |

Conteos por columna: `0 1 0 2 0`. La fila 2 gana por impacto total entre las filas con racha maxima 1. La columna destacada es la 4.

### Entrada

```text
3 5 5 15
5 15 30 10 25
25 10 5 20 30
10 20 15 5 35
```

### Salida esperada

```text
FILA 1 EVENTOS 0 IMPACTO 0 RACHA 0 INICIO 0
FILA 2 EVENTOS 2 IMPACTO 22 RACHA 1 INICIO 2
FILA 3 EVENTOS 1 IMPACTO 6 RACHA 1 INICIO 4
COLUMNAS 0 1 0 2 0
PRIORIDAD 2
COLUMNA 4
```

## Pruebas propias

### Prueba propia 1: dimension minima y ausencia de eventos

**Entrada**

```text
1 1 0 1000
1000
```

**Salida esperada**

```text
FILA 1 EVENTOS 0 IMPACTO 0 RACHA 0 INICIO 0
COLUMNAS 0
PRIORIDAD 0
COLUMNA 0
```

**Justificacion:** con una sola columna no se evalua ningun evento; comprueba tambien los resultados especiales cuando no hay eventos.

### Prueba propia 2: empates de prioridad y de columna

**Entrada**

```text
2 4 1 1
10 9 10 9
10 9 10 9
```

**Salida esperada**

```text
FILA 1 EVENTOS 2 IMPACTO 4 RACHA 1 INICIO 2
FILA 2 EVENTOS 2 IMPACTO 4 RACHA 1 INICIO 2
COLUMNAS 0 2 0 2
PRIORIDAD 1
COLUMNA 2
```

**Justificacion:** ambas filas empatan en racha, impacto y cantidad de eventos, por lo que se elige la fila 1. Las columnas 2 y 4 empatan; se elige la columna 2.

### Prueba de validacion adicional: dimension invalida

**Entrada**

```text
0 3 0 1
```

**Salida esperada**

```text
ERROR
```

**Justificacion:** `N=0` es invalido; el programa debe terminar antes de leer la matriz.

## Cobertura y compilacion

Los adjuntos estaban desplazados: el archivo `caso_01.in` contenia la lista descriptiva; cada entrada estaba en el adjunto `.out` del mismo numero y las salidas esperadas de los casos 01 a 16 estaban en el `.in` del numero siguiente. Se reconstruyeron los pares correctos en `pruebas/` sin modificar los adjuntos originales.

Resultado de ejecucion: casos 01 a 16, comparados con las salidas proporcionadas, pasaron. El adjunto contenia la entrada del caso 17, pero no su salida oficial; `pruebas/caso_17.out` contiene la salida calculada segun la regla del enunciado. Los 17 casos pasaron al comparar la salida del programa con sus archivos esperados; el caso 17 no cuenta como comparacion contra una salida oficial recibida.

Compilacion sugerida:

```text
gcc -std=c11 -Wall -Wextra 20260322.c -o reto
```