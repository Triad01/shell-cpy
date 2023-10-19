/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	if (dest == src || src == 0)
		return dest;

	for (int i = 0; src[i]; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return dest;
}
/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	if (str == NULL)
		return NULL;

	int length = 0;
	while (str[length])
		length++;

	char *ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
		return NULL;

	for (int i = 0; i <= length; i++)
	{
		ret[i] = str[i];
	}

	return ret;
}
/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	if (!str)
		return;

	for (int i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
