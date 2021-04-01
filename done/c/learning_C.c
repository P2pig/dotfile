#include <stdio.h>
#include <stdlib.h>

struct node
{
	int value;
	struct node *next;
};

void traverse(struct node *head)
{
	struct node *current;
	current = head;
	
	while(current != NULL)
	{
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}
/*
int insertAfter(struct node *head, int data, struct node *new)
{
	struct node *current = head;

	while(current != NULL)
	{
		if(current->value == data)
		{
			new->next = current->next;
			current->next = new;
			return 1;
		}
		current = current->next;
	}

	return 0;
}

struct node *insertBefore(struct node *head, int value, struct node *new)
{
	struct node *current = head;

	if(current->value == value)
	{
		new->next = head;
		return new;
	}

	while(current->next != NULL)
	{
		if(current->next->value == value)
		{
			new->next = current->next;
			current->next = new;
			return head;
		}
		current = current->next;
	}

	return head;
}
*/

struct node *deleteNode(struct node *head, int value)
{
	struct node *current = head;

	if(current->value == value)
	{
		current = current->next;
		free(head);
		return current;
	}

	while(current->next != NULL)
	{
		if(current->next->value == value)
		{
			// struct noce *delete = current->next;
			current->next = current->next->next;
			// free(delete);
			return head;
		}

		current = current->next;
	}

	return head;
}

int changeValue(struct node *head, int value, int newValue)
{
	while(head != NULL)
	{
		if(head->value == value)
		{
			head->value = newValue;
			return 1;
		}
		head = head->next;
	}

	return 0;
}

int searchValue(struct node *head, int value)
{
	while(head != NULL)
	{
		if(head->value == value)
		{
			return 1;
		}
		head = head->next;
	}

	return 0;
}

struct node *insertBefore_frag(struct node *head, struct node *new)
{

	if(head == NULL)
	{
		head = new;
	}
	else
	{
		// insert before head
		new->next = head;
		head = new;
	}
	traverse(head);
	return head;
}

struct node *insertBefore(struct node *head)
{
	int input;
	struct node *new;

	while(1)
	{
		printf("Insert data: ");
		scanf("%d", &input);
		new = (struct node *) malloc(sizeof(struct node));
		new->value = input;

		if(input == 0)
		{
			//finiish
			printf("finish\n");
			free(new);
			return head;
		}
		else
		{
			head = insertBefore_frag(head, new);
		}
	}
}

struct node *insertAfter_frag(struct node *head, struct node *new)
{

	if(head == NULL)
	{
		head = new;
	}

	struct node *current = head;
	while(current->next != NULL)
		current = current->next;

	current->next = new;
	traverse(head);
	return head;
}

struct node *insertAfter(struct node *head)
{
	int input;
	struct node *new;

	while(1)
	{
		printf("Insert data: ");
		scanf("%d", &input);
		new = (struct node *) malloc(sizeof(struct node));
		new->value = input;

		if(input == 0)
		{
			printf("finish\n");
			free(new);
			return head;
		}
		else
		{
			head = insertAfter_frag(head, new);
		}
	}
}

int main()
{
	struct node *head = NULL;
	head = insertBefore(head);
	traverse(head);
	head = insertAfter(head);
	traverse(head);

	struct node *n1 = NULL;
	n1 = (struct node *) malloc(sizeof(struct node));
	n1->value = 1000;

	printf("insert before...\n");
	head = insertBefore_frag(head, n1);

	struct node *n2 = NULL;
	n2 = (struct node *) malloc(sizeof(struct node));
	n2->value = 1000;

	printf("insert after...\n");
	head = insertAfter_frag(head, n2);

	return 0;
}
