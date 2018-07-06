#include "find_determinant.h"

void	ft_error_usage(void)
{
	printf("Usage:\n./find_determinant <matrix[0][0]> ... <matrix[n][n]>\n");
	exit(1);
}

void	ft_error_smth(void)
{
	printf("Something went wrong... Try again\n");
	ft_error_usage();
}

int	check_if_valid(int ac)
{
	int	i = 1;
	int	res = 0;

	while (i <= ac / 2)
	{
		if (i * i == ac)
		{
			res = i;
			break ;
		}
		i++;
	}
	return (res);
}

int 	get_int(char *s, int *val)
{
	long	ret;

	for (int i = 0; s[i] != '\0'; i++)
	{	
		if (!isdigit(s[i]))
			return (-1);
	}
	ret = strtol(s, NULL, 10);
	if (ret > 2147483647 || ret < -2147483648)
		return (-1);
	*val = (int)ret;
	return (0);
}

void	free_arr(int ***arr, int size)
{
	if (arr == NULL)
		return ;

	int **tmp = *arr;
	for (int i = 0; i < size; i++)
		free(tmp[i]);
	free(tmp);
	*arr = NULL;
}

int	**ft_make_matrix(char **av, int size)
{
	int	**arr = (int**)malloc(sizeof(int*) * (size));
	if (arr == NULL)
		ft_error_smth();
	int k = 1;
	for (int i = 0; i < size; i++)
	{
			arr[i] = (int*)malloc(sizeof(int) * (size));
			if (arr[i] == NULL)
				ft_error_smth();
			for (int j = 0; j < size; j++)
			{
				if (get_int(av[k++], &arr[i][j]))
				{
					free_arr(&arr, size);
					return (NULL);
				}
			}
	}
	return (arr);
}

void	find_cofactor(int **mat, int **tmp, int pos, int q, int n)
{
	int	i = 0;
	int	j = 0;

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != pos && col != q)
			{
				tmp[i][j++] = mat[row][col];
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

int     find_determinant(int **mat, int size)
{
	int	res = 0;

	if (size == 1)
        return mat[0][0];
	int	**tmp = (int**)malloc(sizeof(int*) * size);
	if (tmp == NULL)
		ft_error_smth();
	for (int i = 0; i < size; ++i)
		{
			tmp[i] = (int*)calloc(sizeof(int), size);
			if (tmp[i] == NULL)
				ft_error_smth();		
		}
	int	sign = 1;
	for (int i = 0; i < size; i++)
	{
		find_cofactor(mat, tmp, 0, i, size);
		res += sign * mat[0][i] * find_determinant(tmp, size - 1);
		sign = -sign;
	}
	free_arr(&tmp, size);
	return (res);
}

int  	main(int ac, char **av)
{
	int	size;
	int 	**arr;

	if (ac == 1)
	{
		printf("Error: no arguments provided\n");
		ft_error_usage();
	}
	if (ac == 2)
	{
		int val;
		if (get_int(av[1], &val))
		{
			ft_error_smth();
			return (1);
		}
		printf("Determinant: %d\n", val);
		return (0);
	}
	if (!(size = check_if_valid(ac - 1)))
		ft_error_usage();
	arr = ft_make_matrix(av, size);
	if (arr == NULL)
		ft_error_smth();
	int res = find_determinant(arr, size);
	printf("Determinant: %d\n", res);
	free_arr(&arr, size);
	return (0);
}
