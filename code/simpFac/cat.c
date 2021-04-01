#include "animal.h"

void catEat(){
	printf("meow meow eat...\n");
}

void catJump(){
	printf("meow meow jump\n");
}

struct Animal cat = { .name = "meow", .peat = catEat, .pjump = catJump };

//struct Animal* joinCat(struct Animal *phead);
struct Animal* joinCat(struct Animal *phead)
{
	if(phead == NULL)
		return &cat;
	else {
		cat.next = phead;
		phead = &cat;
		return phead;
	}
}

