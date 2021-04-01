#include <stdio.h>

int main()
{
	int c = 'M';

	for(int i = 0; i <= 13 ; i++)
	{
		for(int j = i-1; j > 0; j--)
		{
			printf("_");
		} 

		int l = c-i;
		for(int k = 77; k > l; k--)
		{
			printf("%c", k);
		}

		putchar('\n');
	}

	return 0;
}
