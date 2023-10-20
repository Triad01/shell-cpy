#include "shell.h"
/**
 * my_memset - entry point
 * @sy: char sy
 * @by: vahr by
 * @ny: int ny
 * Return: sy
 */
char *my_memset(char *sy, char by, unsigned int ny)
{
	unsigned int in = 0;

	if (ny > 0)
	{
		do {
			sy[in] = by;
			in++;
		} while (in < ny);
	}

	return (sy);
}
/**
 * my_ffree - entry point
 * @pap: my pap
 */
void my_ffree(char **pap)
{
	int in;
	char **ab = pap;

	if (!pap)
		return;

	for (in = 0; pap[in]; in++)
	{
		free(pap[in]);
	}

	free(ab);
}
/**
 * my_realloc - entry
 * @myold_size: old size
 * @mynew_size: new size
 * @myptr: pointer
 * Return: pin
 */
void *my_realloc(void *myptr, unsigned int myold_size, unsigned int mynew_size)
{
	char *pin;

	switch (!myptr)
	{
		case 1:
			return (malloc(mynew_size));
		default:
			break;
	}

	switch (!mynew_size)
	{
		case 1:
			return (free(myptr), NULL);
		default:
			break;
	}

	switch (mynew_size == myold_size)
	{
		case 1:
			return (myptr);
		default:
			break;
	}

	pin = malloc(mynew_size);
	if (!pin)
		return (NULL);

	myold_size = myold_size < mynew_size ? myold_size : mynew_size;

	do {
		pin[myold_size - 1] = ((char *)myptr)[myold_size - 1];
		myold_size--;
	} while (myold_size);

	free(myptr);
	return (pin);
}

