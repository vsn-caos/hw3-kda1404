#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Программе на стандартный поток ввода задается арифметическое выражение
// в синтаксисе языка python3. Необходимо вычислить это выражение и вывести результат.
// Использовать дополнительные процессы запрещено — нужно использовать exec.

int main(void) {
    char expression[1024];
    char command[1024];
    
    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        return 1;
    }
    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }

    snprintf(command, sizeof(command), "print(%s)", expression);

    char *python_args[] = {
        "python3",
        "-c",
        command,
        NULL
    };

    execvp("python3", python_args);

    perror("execvp");
    // TODO: прочитайте выражение из stdin,
    //       затем вызовите execvp/execlp для запуска python3,
    //       который вычислит и выведет результат.
    //       Подсказка: python3 -c "print(<выражение>)"

    return 1;
}
