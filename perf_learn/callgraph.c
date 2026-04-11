#include <stdio.h>
#include <stdlib.h>

#define SIZE ((4 * 1024 * 1024))
#define NUM_ROUNDS 256

static char data[SIZE];


#define COMPUTE(N, CH) \
  do { \
    unsigned i, j; \
    for (j = 0; j < (N); ++j) { \
      for (i = 0; i < SIZE; ++i) { \
        data[i] = CH + i + j; \
      } \
      escape(data); \
    } \
  } while (0)



__attribute__((always_inline))
static inline void escape(void *p) {
  __asm__ volatile ("" : : "r"(p) : "memory");
}


__attribute__((noinline))
void D() {
  COMPUTE(1, 'D');
}


__attribute__((noinline))
void C() {
  D();
  COMPUTE(NUM_ROUNDS, 'C');
}


__attribute__((noinline))
void B() {
  COMPUTE(NUM_ROUNDS, 'B');
  C();
  C();
}


__attribute__((noinline))
void A() {
  COMPUTE(NUM_ROUNDS, 'A');
  B();
  C();
  B();
}


int main() {
  COMPUTE(NUM_ROUNDS, 'M');
  A();
  A();
  return 0;
}