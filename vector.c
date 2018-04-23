#include <stdio.h>
#include "vector.h"

int main()
{
	void *vec = vector_init(int);

	for (int i = 0; i < 15; i++)
		vector_append(vec, i);

	for (int i = 0; i < 15; i++) {
		int tmp;
		printf("pos: %d = %d\n", i, vector_get(vec, i, tmp));
	}

	vector_destroy(vec);

	return 0;
}
