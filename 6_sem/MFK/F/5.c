int find_max_array (int size, int a[]);

int 
find_max_array (int size, int a[])
{
	int max = a[0];
	for (int i = 1; i < size; i++)
		if (a[i] > max)
			max = a[i];

	return max;
}
