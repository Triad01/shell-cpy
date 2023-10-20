#include "shell.h"
/**
 * my_bfree - frees a pointer and sets the address to NULL;
 * @pointer: address of the pointer to be freed
 * Return: always an integer
 */

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

