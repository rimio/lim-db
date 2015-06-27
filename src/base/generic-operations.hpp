#ifndef GENERIC_OPERATIONS_
#define GENERIC_OPERATIONS_

#include "base\generic-type-definitions.hpp"

// Get min value of a and b
#define MIN(a, b) ((a) < (b) ? (a) : (b))
// Get max value of a and b
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Align pointer to desired alignment
#define PTR_ALIGN(ptr, alignment) \
	((ptr) = (char *) ((((UINTPTR) (ptr)) + ((UINTPTR) ((alignment) - 1))) & ~((UINTPTR) ((alignment) - 1))))

#endif // GENERIC_OPERATIONS_