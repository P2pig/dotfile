#include <stdio.h>
#include <stdlib.h>

int nClasses  = 5; // number of classes per year grade
int nStudents = 5; // number of students per class

struct YearGrade
{
        struct Class *class;
};

struct Class
{
        struct Class *next;
        struct Student *student;
};

struct Student
{
        struct Student *next;
        int chinese;
        int math;
        int english;
};

struct YearGrade *initYearGrade()
{
        struct YearGrade *yGrade;
        yGrade = (struct YearGrade *) malloc(sizeof(struct YearGrade));
        yGrade->class = NULL;

        return yGrade;
}

struct Class *initClass()
{
        struct Class *class;
        class =(struct Class *) malloc(sizeof(struct Class));
        class->next = NULL;
        class->student == NULL;

        return class;
}

struct Student *initStudent()
{
        struct Student *student;
        student = (struct Student *) malloc(sizeof(struct Student));
	student-> next = NULL;

        printf("Chinese: ");
        scanf("%d", &student->chinese);
        printf("Math: ");
        scanf("%d", &student->math);
        printf("English: ");
        scanf("%d", &student->english);

        return student;
}

struct Class *createStudents(struct Class *class)
{
	struct Student *student = NULL;
	struct Student *new     = NULL;

	int i;
	for(i = 0; i < nStudents; i++)
	{
		printf("-----Student %d-----\n", i+1);
		new = initStudent();
		if(student == NULL)
		{
			student = new;
			class->student = new;
		} else {
			student->next = new;
			student = student->next;
		}
	}

	return class;
}

struct YearGrade *createClasses(struct YearGrade *yGrade)
{
	struct Class *class = NULL;
	struct Class *new   = NULL;

	int i;
	for(i = 0; i < nClasses; i++)
	{
		printf("======Class %d======\n", i+1);
		new = initClass();
		new = createStudents(new);
		if(class == NULL)
		{
			class = new;
			yGrade->class = new;
		} else {
			class->next = new;
			class = class->next;
		}
	}

	return yGrade;
}

void calculateGrade(struct Student *student)
{
	struct Student *p = NULL;
	p = student;

	int min;
	int max;
	int average;

	int i = 0;
	while(p != NULL)
	{
		average = 0;
		min = max = p->chinese;

		if(min > p->math)    { min = p->math; }
		if(min > p->english) { min = p->english; }
		if(max < p->math)    { max = p->math; }
		if(max < p->english) { max = p->english; }

		average += p->chinese + p->math + p->english;
		average /= 3;

		printf("Student %d: Min: %d, Max: %d, Average: %d\n", ++i, min, max, average);
		p = p->next;	
	}
}

void showGrade(struct YearGrade *yGrade)
{
	struct Class *class = NULL;
	class = yGrade->class;

	int i = 0;
	while(class != NULL)
	{
		printf("================Class %d================\n", ++i);

		calculateGrade(class->student);

		class = class->next;
	}

}

int main()
{
	struct YearGrade *year1  = initYearGrade();

	year1 = createClasses(year1);

	showGrade(year1);

	return 0;
}
