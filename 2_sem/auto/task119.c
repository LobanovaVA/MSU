/*
 * Назовем весом столбца матрицы число, равное сумме только
 * положительных раностей a[i+1][j] - a[i][j] соседних
 * элементов этого столбца (т.е. возрастающих переходов от
 * i к i+1 для i=0,...,N-2). Если таких разностей нет, то
 * вес столбца положим равным нулю. Требуется переставить
 * столбцы матрицы так, чтобы они стояли по убыванию
 * (невозрастанию) своих весов. После этого надо вычислить
 * произведение полученной матрицы A на ее транспонированную
 * первую строку b, т.е. получить вектор c=Ab. Полученную
 * матрицы и вектор вывести в файл output.txt.
 * 
 * Матрица вещественных чисел задается в файле input.txt. В
 * этом файле сначала записаны два целых числа N --- число
 * строк и M --- число столбцов матрицы, а далее сама матрица
 * про строкам (строка матрицы в строке файле).
 * 
 * Ответ к задаче вывести в такой же форме в файле output.txt,
 * т.е. сначала размерности матрицы, а потом по строкам саму
 * переупорядоченную матрицу. После этого надо вывести пустую
 * строку и далее вектор, являющийся требуемым произведением
 * матрицы на вектор.
 * 
 * Если при вводе данных будут обнаржены некорректные ситуации
 * (файлы не открылись, они пустые, есть ошибки чтения,
 * некорректные размерности, недостаточное количество элементов
 * матрицы и т.п.), то считается, что задачу решить нельзя, и
 * функция main должнв завершиться с возвращаемым значением -1.
 * Если задача решена корректно, то функция main должна возвратить
 * значение 0.
 * 
 * При решении задачи память для хранения матрицы выделяется
 * динамически и только для этой матрицы и вектора --- результата
 * произведения матрицы на вектор-строку. Выделять динамически или
 * статически другие дополнительные массивы для промежуточных
 * вычислений не разрешается. По окнчании работы вся выделенная
 * память должна быть освобождена (memory leak не допускается).
 */

#include <stdlib.h>
#include <stdio.h>

/* В коде используется более классическое
   обозначение для размеров матрицы:
   m --- число уравнений, то есть строк,
   n --- число неизвестных, то есть столбцов. */

/* Чтение массива из файла. */
int readArray (FILE * f, double * a, int len);
/* Печать матрицы в файл. */
void printMatrix (FILE * f, double * a, int m, int n);
/* Вес j-го столбца матрицы a. */
double weight (double * a, int m, int n, int j);
/* Меняет местами i-ый и j-ый столбцы матрицы a. */
void swap (double * a, int m, int n, int i, int j);
/* Сортировка матрицы a. */
void sort (double * a, int m, int n);
/* Произвеение матрицы a на ее первый вектор-столбец. */
void mult (double * a, int m, int n, double * c);

int main (void) {
    double * a, * c;
    int m, n;
    
    FILE * fi, * fo;

    fi = fopen ("input.txt", "r");

    if ( fi == NULL ) {
        return -1;
    }

    fo = fopen ("output.txt", "w");

    if ( fo == NULL ) {
        fclose (fi);
        return -1;
    }

    if ( fscanf (fi, "%d%d", &m, &n) != 2 ) {
        fclose (fi);
        fclose (fo);
        return -1;
    }

    if ( m < 1 || n < 1 ) {
        fclose (fi);
        fclose (fo);
        return -1;
    }

    a = (double *) malloc (m * n * sizeof (double));

    if ( a == NULL ) {
        fclose (fi);
        fclose (fo);
        return -1;
    }

    c = (double *) malloc (m * sizeof (double));

    if ( c == NULL ) {
        fclose (fi);
        fclose (fo);
        free (a);
        return -1;
    }

    if ( readArray (fi, a, m * n) != 0 ) {
        fclose (fi);
        fclose (fo);
        free (a);
        free (c);
        return -1;

    }

    sort (a, m, n);
    printMatrix (stdout, a, m, n);
    fprintf (stdout, "\n");
    mult (a, m, n, c);

    printMatrix (fo, a, m, n);
    fprintf (fo, "\n");
    printMatrix (fo, c, m, 1);

    fclose (fi);
    fclose (fo);

    free (a);
    free (c);

    return 0;

}

int readArray (FILE * f, double * a, int len) {
    int i;

    for (i = 0; i < len; i++) {

        if ( fscanf (f, "%lf", a + i) != 1 ) {
            return -1;
        }

    }

    return 0;

}

void printMatrix (FILE * f, double * a, int m, int n) {
    int i, j;

    for (i = 0; i < m; i++) {

        for (j = 0; j < n; j++) {

            fprintf (f, "%f ", a[i * n + j]);

        }

        fprintf (f, "\n");

    }

    return;

}

double weight (double * a, int m, int n, int j) {
    double w = 0;
    int i;

    for (i = 0; i < m - 1; i++) {

        if ( a[(i + 1) * n + j] > a[i * n + j] ) {

            w += a[(i + 1) * n + j] - a[i * n + j];

        }

    }

    return w;

}

void swap (double * a, int m, int n, int i, int j) {
    double temp;
    int k;

    for (k = 0; k < m; k++) {

        temp = a[k * n + i];
        a[k * n + i] = a[k * n + j];
        a[k * n + j] = temp;

    }

    return;

}

/* Реализация сортировки пузырьком. */
void sort (double * a, int m, int n) {
    int i, j;

    for (i = 1; i < n; i++) {

        for (j = 1; j < n; j++) {

            if ( weight (a, m, n, j - 1) > weight (a, m, n, j) ) {

                swap (a, m, n, j - 1, j);

            }

        }

    }

    return;

}

void mult (double * a, int m, int n, double * c) {
    int i, j;

    for (i = 0; i < m; i++)  {

        c[i] = 0.;

        for (j = 0; j < n; j++) {

            c[i] += a[j] * a[i * n + j];

        }

    }

    return;

}