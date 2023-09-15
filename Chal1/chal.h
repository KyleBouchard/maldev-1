#ifndef _CHAL_COMMON_H
#define _CHAL_COMMON_H

typedef struct custom_allocator {
	void *(*custom_alloc)(size_t);
	void (*custom_free)(void*);
} custom_allocator_t;

custom_allocator_t ca_chal1;
custom_allocator_t ca_chal2;

void chal(const custom_allocator_t* const custom_allocator);

#endif /* _CHAL_COMMON_H */