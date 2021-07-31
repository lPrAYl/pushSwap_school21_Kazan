#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#include "../push_swap.h"

int main()
{
	int j;
	
	int numbers[] = {2, 7, 1, 4, 3, 5, 4, 6, 2, 5, 8, 3};
	
	const int lenght = sizeof(numbers)/sizeof(int);
	int d[lenght];
	int i = 0;
	while (i < lenght) {
		d[i] = 0;
		i++;
	}
	i = 0;
	while (i < lenght)
	{
		j = 0;
		int n = 0;
		while (j < i)
		{
			if (numbers[j] < numbers[i] && d[j] >= n)
				n = d[j];
			j++;
		}
		d[i] = n + 1;
		printf("%d ", d[i]);
		i++;
	}
	printf("\n");
	int index;
	i = 0;
	int max = INT_MIN;
	while (i < lenght)
	{
		max = ft_max(max, d[i]);
		if (max == d[i])
			index = i;
		i++;
		//printf("%d ", max);
	}
	int res[max];
	res[max] = numbers[index];
	//printf("\n%d ", res[max]);
	while (d[index] > 1)
	{
		//printf("\n%d ", d[index]);
		j = index - 1;
		//printf("\n%d ", d[index] - 1);
		while ((numbers[j] >= numbers[index]) || (d[j] != (d[index] - 1)))
			j--;
		//printf("\n%d ", j);
		//printf("\n%d ", res[max]);
		printf("\n%d ", res[max]);
		res[--max] = numbers[j];
		index = j;
		//printf("\n%d ", index);
	}
	//printf("\n%d ", max);
	printf("\n%d ", index);
}


