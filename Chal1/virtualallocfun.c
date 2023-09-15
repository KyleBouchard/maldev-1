#include <windows.h>
#include "fnprintf.h"

void virtual_alloc_test(LPVOID lpAddress, SIZE_T dwSize) {
	LPVOID lpData = VirtualAlloc(lpAddress, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (lpData == NULL) {
		DWORD dwLastError = GetLastError();
		fnprintf("Could not allocate %zu bytes @ 0x%p -> %u\n", dwSize, lpAddress, dwLastError);
		return;
	}

	fnprintf("ask: 0x%p -> VirtualAlloc: 0x%p\n", lpAddress, lpData);
	fnprintf("\t[0x%p - 0x%p]\n", lpAddress, (LPBYTE)lpAddress + dwSize);

	VirtualFree(lpData, 0, MEM_RELEASE);
}

int stage2(void) {
	virtual_alloc_test((LPVOID)0x0, 128);
	virtual_alloc_test((LPVOID)0x12341234, 128);
	virtual_alloc_test((LPVOID)0x123412341234, 128);
	virtual_alloc_test((LPVOID)0x700000000000, 128);
	virtual_alloc_test((LPVOID)0x7ffffffe0000, 4096);
	virtual_alloc_test((LPVOID)0x7ffffffe0000, 0x10000);
	virtual_alloc_test((LPVOID)0x7ffffffe0000, 0x10001);

	return 0;
}