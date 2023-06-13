/*
프로그램 내용 : 랜덤 배열 정렬 프로그램 시간 측정
실습일 : 2023.06.08
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define arraySize 50000

// 선택 정렬
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

// 삽입 정렬
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

//버블 정렬
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

//셸 정렬 (gap 만큼 떨어진 요소들을 삽입, 정렬)
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

//셸 정렬
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

//합병 정렬을 위한 합병
static void merge(int list[], int left, int mid, int right)
{
	int i, j, k = left, l;
	static int sorted[arraySize];
	for (i = left, j = mid + 1; i <= mid && j <= right;)
		sorted[k++] = (list[i] <= list[j]) ? list[i++] : list[j++];
	if (i > mid)
		for (l = j; l <= right; l++, k++)
			sorted[k] = list[l];
	else
		for (l = i; l <= mid; l++, k++)
			sorted[k] = list[l];
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

//합병 정렬
void merge_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

//퀵정렬을 위한 분할
int partition(int list[], int left, int right)
{
	int pivot, tmp;
	int low, high;
	low = left + 1;
	high = right;
	pivot = list[left];
	while (low <= high)
	{
		while (low <= right && list[low] <= pivot)
			low++;
		while (high >= left && list[high] > pivot)
			high--;
		if (low < high)
			SWAP(list[low], list[high], tmp);
	}
	SWAP(list[left], list[high], tmp);
	return high;
}

//퀵정렬
void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right)
	{
		q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

//라이브러리 퀵정렬을 위한 비교 함수
int compare(const void* arg1, const void* arg2)
{
	if (*(int *)arg1 > *(int *)arg2) return 1;
	else if (*(int *)arg1 < *(int *)arg2) return -1;
	else return 0;
}

int main()
{
	//랜덤한 정수로 된 배열 생성과 복사
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
	for (int i = 0; i < arraySize; i++)
	{
		list1[i] = list[i];
	}

	//선택 정렬을 이용한 정렬 시간 측정
	double Time[10];
	double total = 0;
	for (int i = 0; i < 10; i++)
	{
		start = (double)clock() / CLOCKS_PER_SEC;
		selection_sort(list1, arraySize);
		finish = (double)clock() / CLOCKS_PER_SEC;
		Time[i] = finish - start;
		//배열 복구
		for (int i = 0; i < arraySize; i++)
		{
			list1[i] = list[i];
		}
		total += Time[i];
	}
	double arvTime = total / 10;
	printf("선택 정렬 평균 수행 시간 : %lf\n", arvTime);

	//삽입 정렬을 이용한 정렬 시간 측정
	total = 0;
	for (int i = 0; i < 10; i++)
	{
		start = (double)clock() / CLOCKS_PER_SEC;
		insertion_sort(list1, arraySize);
		finish = (double)clock() / CLOCKS_PER_SEC;
		Time[i] = finish - start;
		//배열 복구
		for (int i = 0; i < arraySize; i++)
		{
			list1[i] = list[i];
		}
		total += Time[i];
	}
	arvTime = total / 10;
	printf("삽입 정렬 평균 수행 시간 : %lf\n", arvTime);

	//버블 정렬을 이용한 정렬 시간 측정
	total = 0;
	for (int i = 0; i < 10; i++)
	{
		start = (double)clock() / CLOCKS_PER_SEC;
		bubble_sort(list1, arraySize);
		finish = (double)clock() / CLOCKS_PER_SEC;
		Time[i] = finish - start;
		//배열 복구
		for (int i = 0; i < arraySize; i++)
		{
			list1[i] = list[i];
		}
		total += Time[i];
	}
	arvTime = total / 10;
	printf("버블 정렬 평균 수행 시간 : %lf\n", arvTime);

	//셸 정렬을 이용한 정렬 시간 측정
	total = 0;
	for (int i = 0; i < 10; i++)
	{
		start = (double)clock() / CLOCKS_PER_SEC;
		shell_sort(list1, arraySize);
		finish = (double)clock() / CLOCKS_PER_SEC;
		Time[i] = finish - start;
		//배열 복구
		for (int i = 0; i < arraySize; i++)
		{
			list1[i] = list[i];
		}
		total += Time[i];
	}
	arvTime = total / 10;
	printf("셸 정렬 평균 수행 시간 : %lf\n", arvTime);

	//합병 정렬을 이용한 정렬 시간 측정
	total = 0;
	for (int i = 0; i < 10; i++)
	{
		start = (double)clock() / CLOCKS_PER_SEC;
		merge_sort(list1, 0, arraySize - 1);
		finish = (double)clock() / CLOCKS_PER_SEC;
		Time[i] = finish - start;
		//배열 복구
		for (int i = 0; i < arraySize; i++)
		{
			list1[i] = list[i];
		}
		total += Time[i];
	}
	arvTime = total / 10;
	printf("합병 정렬 평균 수행 시간 : %lf\n", arvTime);

	//정의 퀵 정렬을 이용한 정렬 시간 측정
	total = 0;
	for (int i = 0; i < 10; i++)
	{
		start = (double)clock() / CLOCKS_PER_SEC;
		quick_sort(list1, 0, arraySize - 1);
		finish = (double)clock() / CLOCKS_PER_SEC;
		Time[i] = finish - start;
		//배열 복구
		for (int i = 0; i < arraySize; i++)
		{
			list1[i] = list[i];
		}
		total += Time[i];
	}
	arvTime = total / 10;
	printf("정의 퀵 정렬 평균 수행 시간 : % lf\n", arvTime);

	//라이브러리 퀵 정렬을 이용한 정렬 시간 측정
	total = 0;
	for (int i = 0; i < 10; i++)
	{
		start = (double)clock() / CLOCKS_PER_SEC;
		qsort((void *)list1, arraySize, sizeof(int), compare);
		finish = (double)clock() / CLOCKS_PER_SEC;
		Time[i] = finish - start;
		//배열 복구
		for (int i = 0; i < arraySize; i++)
		{
			list1[i] = list[i];
		}
		total += Time[i];
	}
	arvTime = total / 10;
	printf("라이브러리 퀵 정렬 평균 수행 시간 : % lf\n", arvTime);
}
