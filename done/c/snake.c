#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void iniNcurses()
{
	initscr();
	keypad(stdscr,1);
	noecho();
}

struct Snake
{
	int row;
	int col;
	struct Snake *next;
};

#define UP    1
#define DOWN  -1
#define LEFT  2
#define RIGHT -2

int key, dir;
struct Snake *head, *tail;
struct Snake food;

void initFood()
{
	food.row = rand() % 20;
	food.col = rand() % 20;
}

int hasSnake(int row, int col)
{
	struct Snake *p = head;
	while(p != NULL)
	{
		if(p->row == row && p->col == col)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int hasFood(int row, int col)
{
	if(food.row == row && food.col == col)
	{
		return 1;
	}
	return 0;
}

void initMap()
{

	move(0, 0);
	int row = 20;
	int col = 20;

	int i, j;
	for(i = 0; i < row; i++)
	{
		if(i == 0) // first row
		{
			for(j =0; j < col; j++)
			{
				printw("--");
			}
			printw("\n");
		} 

		if(i >= 0 || i <= row) // row = 0~20
		{
			for(j = 0; j <= col; j++)
			{
				if(j == 0 || j == 20)
				{
					printw("|");
				}
				else if(hasSnake(i,j))
				{
					printw("[]");
				}
				else if(hasFood(i,j))
				{
					printw("##");
				}
				else
				{
					printw("  ");
				}
			}
			printw("\n");
		}	
		if(i == row-1) // last row
		{
			for(j =0; j < row; j++)
			{
				printw("--");
			}
			printw("\n");

		}

	}
	printw("\nBy Docky %d\n", key);
}

void addSnakeNode()
{
	struct Snake *new = (struct Snake *) malloc(sizeof(struct Snake));
	new->next = NULL;

	switch(dir)
	{
		case UP:
			new->row = tail->row-1;
			new->col = tail->col;
			break;
		case DOWN:
			new->row = tail->row+1;
			new->col = tail->col;
			break;
		case LEFT:
			new->row = tail->row;
			new->col = tail->col-1;
			break;
		case RIGHT:
			new->row = tail->row;
			new->col = tail->col+1;
			break;
	}
	tail->next = new;
	tail = new;
}


void initSnake()
{
	struct Snake *p;
	while(head != NULL)
	{
		p = head;
		head = head->next;
		free(p);
	}

	initFood();
	head = (struct Snake *) malloc(sizeof(struct Snake));
	head->row = 1;
	head->col = 1;
	head->next = NULL;

	tail = head;

	dir = RIGHT;
	addSnakeNode();
	addSnakeNode();
}

void deleteNode()
{
	struct Snake *p;
	p = head;

	head = head->next;
	free(p);
}

int isSnakeDie()
{
	if(tail->row < 0 || tail->col == 0 || tail->row == 20 || tail->col == 20)
	{
		return 1;
	}

	struct Snake *p;
	p = head;

	while(p->next != NULL)
	{
		if(tail->row == p->row && tail->col == p->col)
		{
			return 1;
		}
		p = p->next;
	}

	return 0;

}

void moveSnake()
{
	addSnakeNode();

	if(hasFood(tail->row, tail->col))
	{
		initFood();
	}
	else
	{
		deleteNode();
	}

	if(isSnakeDie())
	{
		initSnake();
	}
}

void* refreshScreen()
{
	while(1)
	{
		initMap();
		moveSnake();	
		refresh();

		usleep(100000);
	}
}

void turn(int direction)
{
	if(abs(dir) != abs(direction))
	{
		dir = direction;
	}
}

void* changeDirection()
{
	while(1)
	{
		key = getch();
		switch(key)
		{
			case KEY_DOWN:
				turn(DOWN);
				break;
			case KEY_UP:
				turn(UP);
				break;
			case KEY_LEFT:
				turn(LEFT);
				break;
			case KEY_RIGHT:
				turn(RIGHT);
				break;
		}
	}
}

int main ()
{
	iniNcurses();
	initSnake();

	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1, NULL, refreshScreen, NULL);
	pthread_create(&t2, NULL, changeDirection, NULL);


	while(1);
	endwin();

	return 0;
}
