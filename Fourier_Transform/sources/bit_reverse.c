#include <stdio.h>
#include <math.h>

unsigned int bitrev(unsigned int inp,unsigned int numbits);
int log_2(int n);

int main() {
  int M = 8;
  unsigned int i;
  unsigned int log2n = log_2(M);

  for(i = 0; i < M; i++) {
    printf("\n%i -> %i", i, bitrev(i,log2n));
  }

  printf("\n");
	return 0;
}

 unsigned int bitrev(unsigned  int input, unsigned int N) {
  unsigned int i, reversed = 0;
  for (i = 0; i < N; i++)
  {
    reversed = (reversed << 1) | (input & 1);
    input = input >> 1;
  }
  return reversed;
}


int log_2(int n)
{
  int res;
  for (res=0; n >= 2; res++)
    n = n >> 1;
  return res;
}
