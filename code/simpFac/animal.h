#include <stdio.h>

struct Animal{
	char name[128];
	int sex;
	int age;
	void (* peat)();
	void (* pjump)();
	struct Animal *next;
};

struct Animal* joinCat(struct Animal *phead);
struct Animal* joinDog(struct Animal *phead);
