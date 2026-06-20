#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Программе передается аргумент — целое число N > 0.
// Необходимо создать N-1 дополнительных процессов таким образом,
// чтобы у каждого процесса было не более одного дочернего процесса.
// Каждый из процессов должен вывести ровно одно число так,
// чтобы на выходе получилась строка: 1 2 3 4 ... N
// Между числами — ровно один пробел, строка завершается символом '\n'.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    for (int i = 1; i <= n; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            printf("%d", i);
            if (i < n) {
                printf(" ");
            } else {
                printf("\n");
            }
            return 0;
        } else {
            wait(NULL);
            if (i == n) {
                return 0;
            }
        }
    }

    // TODO: создайте цепочку из N процессов (каждый не более чем с одним потомком).
    //       Каждый процесс выводит одно число. Порядок вывода должен быть 1 2 3 ... N.

    return 0;
}
