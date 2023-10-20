#include "shell.h"

int my_bfree(void **pointer)
{
	int my_freed = 0;

	switch (pointer && *pointer)
	{
	case 1:
		free(*pointer);
		*pointer = NULL;
		my_freed = 1;
		break;
	}

	return (my_freed);
}

