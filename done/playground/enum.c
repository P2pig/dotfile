#include <stdio.h>

enum color { black, white, gold, blue, pink };
typedef enum color iphoneColor;

int main() { 
	iphoneColor c = gold;

	printf("color: %d\n", c);
}

