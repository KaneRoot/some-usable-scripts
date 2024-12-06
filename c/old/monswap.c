#include <stdio.h>
#include <string.h>
#include <malloc.h>
void swap(char**,char**);

int main( int argc, char **argv)
{
	char * a = "Coucou";
	char * b = "Pas Coucou";
	printf("a : %s || b : %s\n",a,b);
	swap(&a,&b);
	printf("a : %s || b : %s\n",a,b);

}
void swap(char **a, char **b)
{
	char * temp = *a;
	*a = *b;
	*b = temp;
}
