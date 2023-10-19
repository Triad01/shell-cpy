#include "shell.h"
/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	if (n > 0) {
		do {
			s[i] = b;
			i++;
		} while (i < n);
	}

	return s;
}
/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	for (int i = 0; pp[i]; i++) {
		free(pp[i]);
	}

	free(a);
}
/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the old block or a new block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	switch (!ptr)
	{
		case 1:
			return malloc(new_size);
		default:
			break;
	}

	switch (!new_size)
	{
		case 1:
			return free(ptr), NULL;
		default:
			break;
	}

	switch (new_size == old_size)
	{
		case 1:
			return ptr;
		default:
			break;
	}

	p = malloc(new_size);
	if (!p)
		return NULL;

	old_size = old_size < new_size ? old_size : new_size;

	do {
		p[old_size - 1] = ((char *)ptr)[old_size - 1];
		old_size--;
	} while (old_size);

	free(ptr);
	return p;
}

