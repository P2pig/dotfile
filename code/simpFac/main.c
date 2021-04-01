#include "animal.h"
#include <string.h>

struct Animal* 
findUtilByName(char* target, struct Animal* phead)
{
	struct Animal *current = phead;
	while(current != NULL)
	{
		if(strcmp(current->name, target) == 0)
			return current;
		current = current->next;
	}

	printf("Empty\n");
	return NULL;
}

int main()
{
	char buf[128] = {'\0'};
	struct Animal *phead = NULL;
	phead = joinCat(phead);
	phead = joinDog(phead);

	scanf("%s", buf);
	struct Animal* temp = findUtilByName(buf, phead);
	if(temp != NULL) {
		temp->peat();
		temp->pjump();
	}

	return 0;
}
