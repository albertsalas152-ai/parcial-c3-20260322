#include <stdio.h>

#define MAX_SIZE 30

int main(void)
{
    int n, m, lower, upper;
    int values[MAX_SIZE][MAX_SIZE];
    int rowEvents[MAX_SIZE] = {0};
    int rowImpact[MAX_SIZE] = {0};
    int rowLongestStreak[MAX_SIZE] = {0};
    int rowStreakStart[MAX_SIZE] = {0};
    int columnEvents[MAX_SIZE] = {0};
    int hasAnyEvent = 0;
    int priorityRow = -1;
    int highlightedColumn = 0;

    if (scanf("%d %d %d %d", &n, &m, &lower, &upper) != 4) {
        printf("ERROR\n");
        return 0;
    }

    if (n < 1 || n > MAX_SIZE || m < 1 || m > MAX_SIZE) {
        printf("ERROR\n");
        return 0;
    }

    if (lower < 0 || lower > upper || upper > 1000) {
        printf("ERROR\n");
        return 0;
    }

    for (int row = 0; row < n; row++) {
        for (int column = 0; column < m; column++) {
            scanf("%d", &values[row][column]);
            if (values[row][column] < 0 || values[row][column] > 1000) {
                printf("ERROR\n");
                return 0;
            }
        }
    }

    for (int row = 0; row < n; row++) {
        int currentStreak = 0;
        int currentStreakStart = 0;
        int firstValue = values[row][0];

        for (int column = 0; column < m; column++) {
            int reduction = firstValue - values[row][column];
            int isEvent = column >= 1 && reduction >= lower && reduction <= upper;

            if (isEvent) {
                int impact = reduction + 1;

                rowEvents[row]++;
                rowImpact[row] += impact;
                columnEvents[column]++;
                hasAnyEvent = 1;

                if (currentStreak == 0) {
                    currentStreakStart = column + 1;
                }
                currentStreak++;

                if (currentStreak > rowLongestStreak[row]) {
                    rowLongestStreak[row] = currentStreak;
                    rowStreakStart[row] = currentStreakStart;
                }
            } else {
                currentStreak = 0;
            }
        }

        if (priorityRow == -1
                || rowLongestStreak[row] > rowLongestStreak[priorityRow]
                || (rowLongestStreak[row] == rowLongestStreak[priorityRow]
                    && rowImpact[row] > rowImpact[priorityRow])
                || (rowLongestStreak[row] == rowLongestStreak[priorityRow]
                    && rowImpact[row] == rowImpact[priorityRow]
                    && rowEvents[row] > rowEvents[priorityRow])) {
            priorityRow = row;
        }
    }

    for (int column = 0; column < m; column++) {
        if (columnEvents[column] > columnEvents[highlightedColumn]) {
            highlightedColumn = column;
        }
    }

    for (int row = 0; row < n; row++) {
        printf("FILA %d EVENTOS %d IMPACTO %d RACHA %d INICIO %d\n",
               row + 1,
               rowEvents[row],
               rowImpact[row],
               rowLongestStreak[row],
               rowStreakStart[row]);
    }

    printf("COLUMNAS");
    for (int column = 0; column < m; column++) {
        printf(" %d", columnEvents[column]);
    }
    printf("\n");

    if (hasAnyEvent) {
        printf("PRIORIDAD %d\n", priorityRow + 1);
        printf("COLUMNA %d\n", highlightedColumn + 1);
    } else {
        printf("PRIORIDAD 0\n");
        printf("COLUMNA 0\n");
    }

    return 0;
}