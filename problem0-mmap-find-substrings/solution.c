#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

// Программе передаются два аргумента: имя файла и строка для поиска.
// Необходимо найти все вхождения строки в текстовом файле,
// используя отображение на память с помощью системного вызова mmap.
// На стандартный поток вывода вывести список всех позиций (с нуля),
// где встречается искомая строка, по одной на строку.

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <search_string>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    struct stat st;
    fstat(fd, &st);

    char *data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    char *search = argv[2];
    int len = strlen(search);
    for (int i = 0; i <= st.st_size - len; i++) {
        if (strncmp(data + i, search, len) == 0) {
            printf("%d\n", i);
        }
    }

    munmap(data, st.st_size);
    close(fd);

    // TODO: откройте файл, получите его размер через fstat,
    //       отобразите в память через mmap,
    //       найдите все вхождения argv[2] и выведите их позиции

    return 0;
}
