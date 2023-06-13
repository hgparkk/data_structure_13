/*
프로그램 내용 : 정렬 프로그램
실습일 : 2023.06.01
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

#define arraySize 100

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

// 힙정렬을 위한 힙 구현
typedef int HNode;
#define Key(n) (n)

HNode heap[arraySize + 10];
int heap_size;

#define Parent(i) (heap[i/2])
#define Left(i) (heap[i*2])
#define Right(i) (heap[i*2+1])

void init_heap() { heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap() { return (heap_size == arraySize + 10 - 1); }
HNode fine_heap() { return heap[1]; }

void insert_heap(HNode n)
{
	int i;
	if (is_full_heap()) return;
	i = ++(heap_size);
	while (i != 1 && Key(n) > Key(Parent(i)))
	{
		heap[i] = Parent(i);
		i /= 2;
	}
	heap[i] = n;
}

HNode delete_heap()
{
	HNode hroot, last;
	int parent = 1, child = 2;
	hroot = heap[1];
	last = heap[heap_size--];
	while (child <= heap_size)
	{
		if (child < heap_size && Key(Left(parent)) < Key(Right(parent)))
			child++;
		if (Key(last) >= Key(heap[child])) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = last;
	return hroot;
}

//힙정렬
void heapsort(int list[], int n)
{
	init_heap();
	for (int i = 0; i < n; i++)
	{
		insert_heap(list[i]);
	}
	for (int i = n; i >= 0; i--)
	{
		list[i] = Key(delete_heap());
	}
}

int main()
{
	int list[9] = { 5,3,8,4,9,1,6,2,7 };
	heapsort(list, 8);
	for (int i = 0; i < 9; i++)
	{
		printf("%d ", list[i]);
	}
}
