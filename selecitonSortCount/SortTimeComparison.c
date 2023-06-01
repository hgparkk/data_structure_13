/*
프로그램 내용 : 랜덤 배열 정렬 프로그램 시간 측정
실습일 : 2023.06.01
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define arraySize 50000

void printArray(int arr[], int n, char* str)
{
	int i;
	printf("%s = ", str);
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
	}
}

int main()
{
	long seed = time(NULL);
	srand(seed);
	double start, finish;
	int list[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		int r = rand() % 1000;
		list[i] = r;
	}
	int list1[arraySize];
	int list2[arraySize];
	int list3[arraySize];
	int list4[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		list1[i] = list[i];
		list2[i] = list[i];
		list3[i] = list[i];
		list4[i] = list[i];
	}
	start = (double)clock()/CLOCKS_PER_SEC;
	selection_sort(list1, arraySize);
	finish = (double)clock() / CLOCKS_PER_SEC;
	double selectionTime = finish - start;
	start = (double)clock() / CLOCKS_PER_SEC;
	insertion_sort(list2, arraySize);
	finish = (double)clock() / CLOCKS_PER_SEC;
	double insertionTime = finish - start;
	start = (double)clock() / CLOCKS_PER_SEC;
	bubble_sort(list3, arraySize);
	finish = (double)clock() / CLOCKS_PER_SEC;
	double BubbleTime = finish - start;
	start = (double)clock() / CLOCKS_PER_SEC;
	shell_sort(list4, arraySize);
	finish = (double)clock() / CLOCKS_PER_SEC;
	double ShellTime = finish - start;
	printf("수행 시간 1 : %lf\n", selectionTime);
	printf("수행 시간 2 : %lf\n", insertionTime);
	printf("수행 시간 3 : %lf\n", BubbleTime);
	printf("수행 시간 4 : %lf", ShellTime);
}
