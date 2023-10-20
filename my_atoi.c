#include "shell.h"

int my_interactiveness(info_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->reader <= 2);
}

int my_isdelimeter(char charact, char *delimeter)
{
	int a;
	for (a = 0; delimeter[a] != '\0'; a++)
	{
		if (delimeter[a] == charact)
		{
			return (1);
		}
	}
	return (0);
}

int my_alphabet(int input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
		return (1);
	else
		return (0);
}

int my_atoi(char *strings)
{
	int i = 0, sgn = 1, fg = 0, out = 0;
	unsigned int score = 0;

	while (strings[i] != '\0' && fg != 2)
	{
		switch (strings[i])
		{
			case '-':
				sgn *= -1;
				break;
			default:
				if (strings[i] >= '0' && strings[i] <= '9')
				{
					fg = 1;
					score *= 10;
					score += (strings[i] - '0');
				}
				else if (fg == 1)
				{
					fg = 2;
				}
				break;
		}
		i++;
	}

	if (sgn == -1)
	{
		out = -score;
	}
	else
	{
		out = score;
	}

	return (out);
}

