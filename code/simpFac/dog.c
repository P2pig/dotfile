#include "animal.h"

void dogEat(){
	printf("ka ka eat\n");
}

void dogJump(){
	printf("ka ka jump\n");
}

struct Animal dog = { .name = "kaka", .peat = dogEat, .pjump = dogJump };

struct Animal* joinDog(struct Animal *phead)
{
	if(phead == NULL)
		return &dog;
	else {
		dog.next = phead;
		phead = &dog;
		return phead;
	}
}

