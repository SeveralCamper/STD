#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Запрашиваем анонимную разделяемую память на 4096 байт
    // PROT_READ | PROT_WRITE - разрешаем чтение и запись
    // MAP_SHARED | MAP_ANONYMOUS - разделяемое анонимное отображение
    int *shared_mem = mmap(NULL, 4096, PROT_READ | PROT_WRITE, 
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0) { // Дочерний процесс
        *shared_mem = 42; // Записываем значение
        printf("Child: wrote %d\n", *shared_mem);
    } else { // Родительский процесс
        sleep(1); // Ждём, пока дочерний процесс запишет значение
        printf("Parent: read %d\n", *shared_mem);
    }

    // Освобождаем память
    munmap(shared_mem, 4096);
    return 0;
}
