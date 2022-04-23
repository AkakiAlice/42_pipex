#include "libft.h"

static size_t	token_count(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'')
					i++;
			}
			nb++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (nb);
}


static char	**free_matrix(char **matrix, size_t i)
{
	while ((int)i >= 0)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i--;
	}
	free(matrix);
	matrix = NULL;
	return (matrix);
}

static void	letter_aloc(char **matrix, char const *s, char c, size_t nb_token)
{
	size_t	len_ptr;
	size_t	i;

	i = 0;
	while (i < nb_token)
	{
		if (*s == c)
		{
			s++;
		}
		if (*s != c && *s != '\'')
		{
			len_ptr = 0;
			while (s[len_ptr] != c && s[len_ptr])
				len_ptr++;
			matrix[i] = ft_substr(s, 0, len_ptr);
			if (matrix[i] == NULL)
				free_matrix(matrix, i);
			s = s + len_ptr;
		}
		len_ptr = 0;
		if (*s == '\'')
		{
			s++;
			while (s[len_ptr] != '\'')
				len_ptr++;
			//s--;
			//len_ptr++;
			//len_ptr++;
			matrix[i] = ft_substr(s, 0, len_ptr);
			s = s + len_ptr;
			s++;
			while(*s == c)
				s++;
		}
		i++;
	}
	matrix[i] = NULL;
}

char	**ft_split2(char const *s, char c)
{
	char	**matrix;
	size_t	nb_token;

	if (!s)
		return (NULL);
	nb_token = token_count(s, c);
	matrix = (char **)malloc(((sizeof(char *)) * (nb_token + 1)));
	if (!matrix)
		return (NULL);
	letter_aloc(matrix, s, c, nb_token);
	return (matrix);
}

/*int main()
{
	int i = 0;
	char **a;
	a = ft_split2("tr ' X' T", ' ');
	while (a[i])
	{
		ft_printf("[%i] = [%s]\n", i, a[i]);
		i++;
	}
	return(0);
}*/
