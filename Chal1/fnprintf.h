#ifndef _FNPRINTF_H
#define _FNPRINTF_H

#include <stdio.h>

#define fnprintf(...) do { \
	printf("[%s] ", __func__); \
	printf(__VA_ARGS__); \
} while (0)

#endif /* _FNPRINTF_H */