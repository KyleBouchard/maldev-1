#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "chal.h"
#include "fnprintf.h"
#include <windows.h>

custom_allocator_t ca_chal1 = {
	malloc,
	free
};

static void* virtual_alloc_wrap(size_t sz) {
	return VirtualAlloc(NULL, sz, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

static void virtual_free_wrap(void *ptr) {
	VirtualFree(ptr, 0, MEM_RELEASE);
}

custom_allocator_t ca_chal2 = {
	virtual_alloc_wrap,
	virtual_free_wrap
};

static void print_frame(void* ptr, size_t sz) {
	fnprintf("data @ %p:\n\t", ptr);

	for (size_t i = 0; i < sz; ++i)
		printf("%02x ", ((uint8_t*)ptr)[i]);

	putc('\n', stdout);
}

static void alloc_set_dealloc(const custom_allocator_t* const custom_allocator, size_t size) {
	static char cur_c = 'A';
	uint8_t* data = (uint8_t*)custom_allocator->custom_alloc(size);
	if (!data) {
		fnprintf("could not malloc %zu bytes\n", size);
		return;
	}

	fnprintf("alloc @ %p -> %zu bytes\n", data, size);

	print_frame(data, size);

	RtlFillMemory(data, size, cur_c);

	print_frame(data, size);

	++cur_c;

	custom_allocator->custom_free(data);
}

void chal(const custom_allocator_t *const custom_allocator) {
	const uint32_t new_data_val = 0x12345678;
	uint32_t* data = (uint32_t*)custom_allocator->custom_alloc(sizeof(*data));
	if (!data) {
		fnprintf("??? can't malloc\n");
		return;
	}
	print_frame(data, sizeof(*data));

	fnprintf("data 0x%04x -> 0x%04x\n", *data, new_data_val);
	*data = new_data_val;

	print_frame(data, sizeof(*data));

	custom_allocator->custom_free(data);

	fnprintf("freed data!\n");

	alloc_set_dealloc(custom_allocator, sizeof(*data));
	alloc_set_dealloc(custom_allocator, sizeof(*data) * 2);
	alloc_set_dealloc(custom_allocator, sizeof(*data) / 2);
}