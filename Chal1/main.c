#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "chal.h"
#include "fnprintf.h"

void chal3() {
	size_t nums = 0;
	const size_t init_nums = 5;
	int* arr = (int*)malloc(sizeof(*arr) * init_nums);
	char cur, int_buf[16] = {0}; // -2147483648 -> 2147483647
	
	if (!arr) {
		fnprintf("fatal: could not allocate initial buffer to arr\n");
		return;
	}

	fnprintf("Enter 5 numbers (or more!): ");

	do {
		cur = getchar();
		const size_t len = strlen(int_buf);
		if (isspace(cur)) {
			if (len == 0)
				continue;

			if (++nums > init_nums) {
				int* old_arr = arr;

				if (!(arr = (int*)realloc(arr, nums * sizeof(*arr)))) {
					arr = old_arr;
					fnprintf("fatal: could not allocate buffer of %zu bytes to arr\n", nums * sizeof(*arr));
					break;
				}
			}

			arr[nums - 1] = atoi(int_buf);
			int_buf[0] = '\0';

			continue;
		} else if (len == (sizeof(int_buf) / sizeof(*int_buf)) - 1) {
			fnprintf("too big number (%s...)\n", int_buf);
			int_buf[0] = '\0';
			while (!isspace(getchar()));

			continue;
		}

		int_buf[len] = cur;
		int_buf[len + 1] = '\0';
	} while (cur != '\n');

	fnprintf("Your numbers:\n");
	for (size_t i = 0; i < nums; ++i)
		fnprintf("\t%d\t=\t0x%08x\n", arr[i], arr[i]);

	free(arr);
}

int main() {
	puts("CHAL 1");
	chal(&ca_chal1);

	puts("CHAL 2");
	chal(&ca_chal2);

	puts("CHAL 3");
	chal3();

	return 0;
}