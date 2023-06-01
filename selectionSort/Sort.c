/*
프로그램 내용 : 정렬 프로그램
실습일 : 2023.06.01
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void printArray(int arr[], int n, char* str)
{
	int i;
	printf("%s = ", str);
	for (i = 0; i < n; i++) printf("%3d", arr[i]);
	printf("\n");
}

void printStep(int arr[], int n, int val)
{
	int i;
	printf("  Step %2d = ", val);
	for (i = 0; i < n; i++) printf("%3d", arr[i]);
	printf("\n");
}

void selection_sort(int list[], int n)
{
	int i, j, least, tmp;
	for (i = 0; i < n - 1; i++)
	{
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], tmp);
		printStep(list, n, i + 1);
	}
}

void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++)
	{
		key = list[i];
		for (j = i - 1; i >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];
		list[j + 1] = key;
		printStep(list, n, i);
	}
}

void bubble_sort(int list[], int n)
{
	int i, j, bChanged, tmp;
	for (i = n - 1; i > 0; i--)
	{
		bChanged = 0;
		for (j = 0; j < i; j++)
		{
			if (list[j] > list[j + 1])
			{
				SWAP(list[j], list[j + 1], tmp);
				bChanged = 1;
			}
		}
		if (!bChanged) break;
		printStep(list, n, i - 1);
	}
}

int ascend(int x, int y) { return y - x; }
int descend(int x, int y) { return x - y; }

void insertion_sort_fn(int list[], int n, int(*f)(int, int))
{
	int i, j, key;
	for (i = 1; i < n; i++)
	{
		key = list[i];
		for (j = i - 1; j >= 0 && f(list[j], key) < 0; j--)
			list[j + 1] = list[j];
		list[j + 1] = key;
		printStep(list, n, i);
	}
}

static void sortGapInsertion(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap)
	{
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n)
{
	int i, gap, count = 0;
	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			sortGapInsertion(list, i, n - 1, gap);
		printStep(list, n, ++count);
	}
}

int main()
{
	int list[9] = { 5,3,8,4,9,1,6,2,7 };
	int list1[9];
	int list2[9];
	int list3[9];
	int list4[9];
	int list5[9];
	for (int i = 0; i < 9; i++)
	{
		list1[i] = list[i];
		list2[i] = list[i];
		list3[i] = list[i];
		list4[i] = list[i];
		list5[i] = list[i];
	}
	printArray(list1, 9, "Original ");
	selection_sort(list1, 9);
	printArray(list1, 9, "Selection");
	selection_sort(list2, 9);
	printArray(list2, 9, "Insertion");
	selection_sort(list3, 9);
	printArray(list3, 9, "Bubble");
	insertion_sort_fn(list4, 9, descend);
	printArray(list4, 9, "Descend");
	shell_sort(list5, 9);
	printArray(list5, 9, "Shell");
}
