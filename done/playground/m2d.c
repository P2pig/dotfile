#include <stdio.h>

int main() {


	int k = 123;
	int q = 456;

	int* const n = &k;

	printf("n: %d\n", *n);
	n = q;	

	printf("n: %d\n", *n);


	int const *n1;
	int* const n2;




	return 0;

}
