#include "doom_nukem.h"

int		check_file(int fd)
{
	if (fd == -1 || read(fd, 0, 0) < 0)
	{
		ft_putstr("empty file or it's directory\n");
		return (0);
	}
	return (1);
}

void	*ft_realloc(void *ptr, size_t size)
{
	char *newptr;

	if (!size && ptr)
	{
		if (!(newptr = (char *)malloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (newptr);
	}
	if (!(newptr = (char *)malloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, size);
		ft_memdel(&ptr);
	}
	return (newptr);
}

t_posf	atof_posf(const char *s, t_posf posf, int exp)
{
	int c;
	int sign;
	int i;

	exp = 0;
	sign = 1;
	i = posf.pos;
	posf.value = 0.0;
	if (s[0 + posf.pos] == '-' && posf.pos++)
		sign = -1;
	while ((c = s[0 + posf.pos++]) != '\0' && ISDIGIT(c))
		posf.value = posf.value * 10.0 + (c - '0');
	if (c == '.')
		while ((c = s[0 + posf.pos++]) != '\0' && ISDIGIT(c) || exp--)
			posf.value = posf.value * 10.0 + (c - '0');
	while (ISDIGIT(c))
	{
		i = i * 10 + (c - '0');
		c = s[0 + posf.pos++];
	}
	while (exp++ < 0)
		posf.value *= 0.1;
	posf.value *= sign;
	return (posf);
}