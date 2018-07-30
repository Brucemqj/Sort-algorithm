#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Selection sort
template <class T> T* Select_sort(T a[], int len)
{
	int length = len;//len(a);
	int le = sizeof(a);
	int lel = sizeof(a[9]);
	if (length <= 1)
	{
		return a;
	}
	for (int i = 0; i < length; i++)
	{
		int min = i;
		for (int j = i + 1; j < length; j++)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		my_swap(a, i, min);
	}
	return a;
}

template <class T> inline void my_swap(T a[], int i, int min)
{
	T tmp = a[i];
	a[i] = a[min];
	a[min] = tmp;
}

//------------------------------------------

//Insert sort
template <class T> void Insert_sort(T a[], int len, int st, int end)
{
	int length = len;//len(a);
	if (length <= 1)
	{
		return;
	}
	for (int i = st; i < st+length; i++)
	{
		//for (int j = i; j > 0; j--)
		//{
		//	if (a[j] < a[j - 1])
		//	{
		//		my_swap(a, j, j - 1);
		//	}
		//	else break;
		//}
		int j = i;
		while (a[j] < a[j - 1]&&j>0)
		{
			my_swap(a, j, j - 1);
			j--;
		}
	}
	return;
}
//------------------------------------------------

//Shell sort
template <class T> void Shell_sort(T a[], int len)
{
	int length = len;//len(a);
	if (length <= 1)
	{
		return;
	}
	int h = 1;
	while (h < length / 3)
	{
		h = h + h + h + 1; //sequence of 3*x+1 as the stride of sort
	}
	int p = 0;
	while (h >= 1)
	{
		for (int i = h; i < length; i++)
		{
			for (int j = i; j >= h; j -= h)
			{
				if (a[j] < a[j - h])
				{
					my_swap(a, j, j - h);
					p++;
				}
			}
		}
		h = h / 3;
	}
	return;
}
//-------------------------------------------------

//Merge Sort
template <class T> void Merge_sort(T a[], const int len, const int st, const int end)
{
	//static_assert(len == end - st, "Array length or start/end error");
	if (len <= 1)
	{
		return;
	}
	int med = st + len / 2;
	//if (len < 10) //当二分的子序列长度较小时，直接使用Insert sort排序可以加快速度
	//{
	//	Insert_sort(a, len, st, end);
	//	return;
	//}
	Merge_sort<int>(a, med-st, st, med);
	Merge_sort<int>(a, end-med, med, end);
	
	Merge(a, st, med, a, med, end);
}

template <class T> void Merge(T a[], const int st_a, const int end_a, T b[], const int st_b, const int end_b)
{
	int len_a = end_a - st_a;
	int len_b = end_b - st_b;
	if (len_a == 0) ;
	if (len_b == 0) ;
	int i(st_a), j(st_b), k(0);
	T* c = new T[len_a+len_b];
	while (i < end_a && j < end_b)
	{
		if (a[i] < b[j])
		{
			c[k] = a[i];
			k++;
			i++;
		}
		else
		{
			c[k] = b[j];
			k++;
			j++;
		}
	}
	if (i == end_a)
	{
		while (j < end_b)
		{
			c[k] = b[j];
			k++;
			j++;
		}
	}
	if (j == end_b)
	{
		while (i < end_a)
		{
			c[k] = a[i];
			k++;
			i++;
		}
	}
	for (int i = st_a; i < st_a + len_a + len_b; i++)
	{
		a[i] = c[i - st_a];
	}
	delete[]c;
}
//-----------------------------------------------------------


//Quick Sort
template <class T> void Quick_sort1(T a[], int len, int st, int end)
{
	
	
}

void quickSort(int a[], int left, int right)
{
	int i = left;
	int j = right;
	int temp = a[left];
	if (left >= right)
		return;
	while (i != j)
	{
		while (i<j&&a[j] >= temp)
			j--;
		if (j>i)
			a[i] = a[j];//a[i]已经赋值给temp,所以直接将a[j]赋值给a[i],赋值完之后a[j],有空位
		while (i<j&&a[i] <= temp)
			i++;
		if (i < j)
			a[j] = a[i];
	}
	a[i] = temp;//把基准插入,此时i与j已经相等R[low..pivotpos-1].keys≤R[pivotpos].key≤R[pivotpos+1..high].keys
	quickSort(a, left, i - 1);/*递归左边*/
	quickSort(a, i + 1, right);/*递归右边*/
}

template <class T> void Quick_sort2(T a[], int low, int high) //Quick_sort2速度比quickSort慢，可能是因为在本函数内调用了另一个函数partition
{
	if (low < high)
	{
		int mid = partition(a, low, high);
		Quick_sort2(a, low, mid);
		Quick_sort2(a, mid + 1, high);
	}
}

template <class T> int partition(T a[], int low, int high)
{
	int i(low), j(high - 1);
	int p = i;
	T key = a[j];
	while (i < high)
	{
		if (a[i] < key)
		{
			my_swap(a,i,p);
			++p;
		}
		++i;
	}
	my_swap(a,p,j);
	return p;
}

//-----------------------------------------

//3 Way Quick Sort
template <class T> void threeWay_Quicksort(T a[], int len, int low, int high)
{
	int lt(low), gt(high-1);
	int pivot = a[low];
	if (high -low <= 1) return;
	int i = low;
	while (i <= gt)
	{
		if (a[i] < pivot) my_swap(a, i++, lt++);
		else if (a[i] > pivot && i < gt)
		{
			if (a[gt] <= pivot)
			{
				my_swap(a, i, gt--);
			}
			else --gt;
		}
		else i++;
	}
	threeWay_Quicksort<T>(a, lt - low, low, lt);
	threeWay_Quicksort<T>(a, high - gt, gt, high);
	return;
}
//------------------------------------------
class Test
{
public:
	Test(int a, int b) { p = a; q = b; };
	Test(const Test& t)
	{
		p = t.p;
		q = t.q;
		printf("Invoke Copy constructor function");
	}

private:
	int p, q;
};
//------------------------------------------
int main()
{
	const int n = 20000;
	//Test ta(1, 2);
	//Test tb(ta); //或者Test tb = ta; 单独使用 tb = ta是不会认为调用拷贝构造函数的。赋值构造函数作用一：用一个对象初始化另一个对象；二：函数参数有一个是类；三：一个函数返回值是一个类，也调用拷贝构造函数
	//int* p = new int[5];
	//p[0] = 1;
	//printf("%d,%d,%d....", p,&p,p[0]);
	//char* q = new char[4];
	//q[0] = 'a';
	//printf("->%d,%d,%d", q, &q, q[0]);
	int a[n],b[n],c[n],d[n],e[n],f[n];
	srand( (unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		a[i] = b[i] = c[i] = d[i] = e[i] = f[i] = int(rand() % 100) - 20;
	}
	clock_t t1, t2, t3, t4, t5, t6, t7, t8;
	t1 = clock();
	int* a1 = Select_sort<int>(a, n);
	t2 = clock();
	Insert_sort<int>(b, n, 0, n);
	t3 = clock();
	Shell_sort<int>(c, n);
	t4 = clock();
	Merge_sort<int>(d, n, 0, n);
	t5 = clock();
	//int tq[] = { 3,2,4,1,5 };
	quickSort(e, 0, n-1);
	//Quick_sort2<int>(tq, 0, 5);
	//Quick_sort<int>(e, n, 0, n);
	//Quick_sort2<int>(a, 0, n);
	t6 = clock();
	Quick_sort2(e, 0, n); t7 = clock();
	threeWay_Quicksort<int>(f, n, 0, n);
	t8 = clock();

	/*for (int i = 0; i < 5; i++)
	{
		std::cout << tq[i] << " ";
	}
	std::cout << "quick sort end" << std::endl;*/

	cout << "Select Sort consumes time: " << (double)(t2 - t1) << endl;
	cout << "Insert Sort consumes time: " << (double)(t3 - t2) << endl;
	cout << "Shell Sort consumes time: " << (double)(t4 - t3) << endl;
	cout << "Merge Sort consumes time: " << (double)(t5 - t4) << endl;
	cout << "Quick Sort consumes time: " << (double)(t6 - t5) << endl;
	cout << "Quick Sort2 consumes time: " << (double)(t7 - t6) << endl;
	cout << "3 Way Quick Sort consumes time: " << (double)(t8 - t7) << endl;
	/*for (int i = 0; i < n; i++)
	{
		std::cout << a1[i] <<" ";
	}
	std::cout << "select sort end" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << b[i] <<" ";
	}
	std::cout << "insert sort end" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << c[i] << " ";
	}
	std::cout << "shell sort end" << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::cout << d[i] << " ";
	}
	std::cout << "merge sort end" << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::cout << e[i] << " ";
	}
	std::cout << "quick sort end" << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::cout << f[i] << " ";
	}
	std::cout << "3 way quick sort end" << std::endl;*/

	//std::cout << b[0] <<b[1]<<b[2]<<b[3]<< std::endl;

	int ii = 9999, count = 0;
	while (ii)
	{
		ii = ii & (ii - 1);
		count++;
	}

	system("pause");
	return 0;
}