#include <stdio.h>
#include <limits.h>
#include <stdbool.h>


int	GetCeilIndex(int arr[], int tailIndices[], int l, int r, int key)
{
	while (r - l > 1)
	{
		int m = 1 + (r - l) / 2;
		if (arr[tailIndices[m]] >= key)
			r = m;
		else
			l = m;
	}
	return (r);
}

int	LongestIncreasingSubsequence(int arr[], int lenght)
{
	int tailIndices[lenght + 1];
	int i = 0;
	while (i < lenght + 1)
		tailIndices[i++] = 0;
	int prevIndices[lenght + 1];
	i = 0;
	while (i < lenght)
	{
		printf("%d\t", arr[i++]);
	}
	
	i = 0;
	while (i < lenght + 1) {
		prevIndices[i++] = -1;
	}
	int	len = 1;
	i = 1;
	while (i < lenght)
	{
		if (arr[i] < arr[tailIndices[0]])
		{
			tailIndices[0] = i;
		}
		else if (arr[i] > arr[tailIndices[len - 1]])
		{
			prevIndices[i] = tailIndices[len - 1];
			tailIndices[len++] = i;
		}
		else
		{
			int	pos = GetCeilIndex(arr, tailIndices, -1, len - 1, arr[i]);
			prevIndices[i] = tailIndices[pos - 1];
			tailIndices[pos] = i;
		}
		i++;
	}
	printf("LIS of given input\n");
	i = tailIndices[len - 1];
	while (i >= 0)
	{
		printf("%d\t", arr[i]);
		i = prevIndices[i];
	}
	printf("\n");
	return  (len);
}


//int main()
//{
//	int	arr[] = {2, 5, 3, 7, 11, 8, 10, 13, 6};
//	const int	lenght = sizeof(arr) / sizeof(int);
//
//	int n = LongestIncreasingSubsequence(arr[lenght], lenght);
//	printf("%d\n", n);
//}

