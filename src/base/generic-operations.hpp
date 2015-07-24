#ifndef GENERIC_OPERATIONS_
#define GENERIC_OPERATIONS_

#include <stdlib.h>
#include <assert.h>
#include <string>
#include <algorithm>

#include "base\generic-type-definitions.hpp"

// Get min value of a and b
#define MIN(a, b) ((a) < (b) ? (a) : (b))
// Get max value of a and b
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Align pointer to desired alignment
#define PTR_ALIGN_UPPER(ptr, alignment) \
	((ptr) = (char *) ((((UINTPTR) (ptr)) + ((UINTPTR) ((alignment) - 1))) & ~((UINTPTR) ((alignment) - 1))))

#define PTR_ALIGN_LOWER (ptr, alignment) \
	((ptr) = (char *)(((UINTPTR) (ptr)) & ~((UINTPTR)((aligment) -1)))

#define STRING_TO_LOWER(a) \
	std::transform((a).begin(), (a).end(), (a).begin(), ::tolower)
#endif // GENERIC_OPERATIONS_