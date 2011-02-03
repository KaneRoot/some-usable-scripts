#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void squeeze( char *s, char *t, char c );

int main(int argc, char **argv)
{
	char s[10];
	char t[10];
	scanf("%s",s);
	squeeze(s,t,'a');
	printf("%s\n",t);
}

void squeeze( char *s , char *t, char c)
{	
	int i = 0;
	int k = 0;
	while( s[i] != '\n' && s[i] != '\0' )
	{
		if (s[i] != c && k < strlen(t))
		{
			t[k] = s[i];
			k++;
		}
		i++;
	}
	t[k]='\0';
}

void miroir ( char *s, char *t)
{
	while( *s != '\0')
	{			
	}
}
