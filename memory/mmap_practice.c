#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

int main() {
    size_t len = 4096;
    int *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

    p[0] = 123;
    p[1] = 456;
    printf("p[0] = %d, p[1] = %d\n", p[0], p[1]);

    if (munmap(p, len) != 0) {
        perror("munmap");
        return -1;
    }
}