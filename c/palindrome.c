#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palindrome(char *);

int main(int argc, char * argv[])
{
	int rep = palindrome(argv[1]);
	if(rep==1)
		printf("Cette phrase est un palindrome\n");
	else
		printf("Cette phrase n'est pas un palindrome\n");

	return EXIT_SUCCESS;
}

int palindrome(char *s)
{
	int i=0,res = 1;
	char t[strlen(s)];
	squeeze(s,t,' ');
	minuscule(t);
	while(i<strlen(t))
	{
		if(t[i]!=t[strlen(t)-i-1])
			res=0;
		i++;
	}
	return res;
}
