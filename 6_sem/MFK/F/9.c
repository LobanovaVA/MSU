void swap_negmax_last(int size, int a[]);

void swap_negmax_last(int size, int a[])
{
	int max = 0, ind  = 0;;
	for (int i = 0; i < size; i++)
		if (a[i] < 0 && (max == 0 || a[i] > max))
		{
			ind  = i;
			max = a[i];
		}

	if (max == 0)
		return;

	a[ind] = a[size - 1];
	a[size - 1] = max;

	return;
}