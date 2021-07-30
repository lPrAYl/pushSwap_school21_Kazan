#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int ceilIndex(int subsequence[],
              int startLeft,
              int startRight,
              int key){
	
	int mid = 0;
	int left = startLeft;
	int right = startRight;
	int ceilIndex = 0;
	bool ceilIndexFound = false;
	
	for (mid = (left + right) / 2; left <= right && !ceilIndexFound; mid = (left + right) / 2) {
		if (subsequence[mid] > key) {
			right = mid - 1;
		}
		else if (subsequence[mid] == key) {
			ceilIndex = mid;
			ceilIndexFound = true;
		}
		else if (mid + 1 <= right && subsequence[mid + 1] >= key) {
			subsequence[mid + 1] = key;
			ceilIndex = mid + 1;
			ceilIndexFound = true;
		} else {
			left = mid + 1;
		}
	}
	
	if (!ceilIndexFound) {
		if (mid == left) {
			subsequence[mid] = key;
			ceilIndex = mid;
		}
		else {
			subsequence[mid + 1] = key;
			ceilIndex = mid + 1;
		}
	}
	
	return ceilIndex;
}


int longestIncrSub(int numbers[], const int lenght)
{
	if (lenght <= 1)
		return (1);
	
	int lis_lenght = 1;
	int subsequence[lenght];
	int indexes[lenght];
	
	for (int i = 0; i < lenght; ++i)
		subsequence[i] = INT_MAX;
	
	subsequence[0] = numbers[0];
	indexes[0] = 0;

	
	for (int i = 1; i < lenght; ++i)
	{
		indexes[i] = ceilIndex(subsequence, 0, i, numbers[i]);
		if (lis_lenght < indexes[i])
			lis_lenght = indexes[i];
	}
	printf("%d\n", lenght);
	return (lis_lenght + 1);
}


int main()
{
	int numbers[] = {0, 4, 5, 1, 2, 3};
	
	const int lenght = sizeof(numbers)/sizeof(int);
	int res = longestIncrSub(numbers, lenght);
	printf("%d\n", res);
	
}
