#include "minishell.h"

int debug_parse_double_quote(char *str, int *i)
{
	int j;
	int insinglequote;
	int indoublequote;

	insinglequote = 0;
	indoublequote = 0;
	j = 0;
	
	printf("Starting parse at position %d, char: '%c'\n", *i, str[*i]);
	
	while ((str[*i + j] != ' ' && str[*i + j] != '|' && str[*i + j] != '\0')
		|| (indoublequote == 1 || insinglequote == 1))
	{
		printf("j=%d, char='%c', indoublequote=%d, insinglequote=%d\n", 
			j, str[*i + j], indoublequote, insinglequote);
		
		if (str[*i + j] == '\0')
		{
			printf("Reached end of string!\n");
			if (indoublequote == 1 || insinglequote == 1)
			{
				printf("ERROR: Unclosed quote detected\n");
				return (-1);
			}
			break;
		}
		
		if (str[*i +j] == '"' && !insinglequote)
		{
			indoublequote = !indoublequote;
			printf("  -> double quote toggled, now indoublequote=%d\n", indoublequote);
		}
		else if (str[*i +j] == '\'' && !indoublequote)
		{
			insinglequote = !insinglequote;
			printf("  -> single quote toggled, now insinglequote=%d\n", insinglequote);
		}
		j++;
		
		if (j > 50) // Safety check to prevent infinite loop
		{
			printf("ERROR: Loop safety break at j=%d\n", j);
			break;
		}
	}
	printf("Exited loop with j=%d\n", j);
	return (0);
}

int main()
{
	char *test = "echo \"hello' \"";
	int i = 5; // Position of the first quote
	
	printf("Testing string: %s\n", test);
	printf("Starting from position %d\n", i);
	
	debug_parse_double_quote(test, &i);
	
	return (0);
}
