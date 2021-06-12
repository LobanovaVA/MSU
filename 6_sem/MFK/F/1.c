void sort_array (int size, int a[]);

void 
sort_array (int size, int a[])
{
	int tmp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (a[j] > a[j + 1])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
}
