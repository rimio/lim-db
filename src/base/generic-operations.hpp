#ifndef GENERIC_OPERATIONS_
#define GENERIC_OPERATIONS_

#include <stdlib.h>
#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>

#include "base\generic-type-definitions.hpp"

// Get min value of a and b
#define MIN(a, b) ((a) < (b) ? (a) : (b))
// Get max value of a and b
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Align pointer to desired alignment
#define PTR_ALIGN(ptr, alignment) \
	((ptr) = (char *) ((((UINTPTR) (ptr)) + ((UINTPTR) ((alignment) - 1))) & ~((UINTPTR) ((alignment) - 1))))

#define STRING_TO_LOWER(a) \
	std::transform((a).begin(), (a).end(), (a).begin(), ::tolower)

template<class T>
inline void vector_clear_and_delete (std::vector<T*>& clearme) {
	T *t = NULL;

	while (!clearme.empty ()) {
		t = clearme.back ();
		clearme.pop_back ();

		delete t;
	}
};


#endif // GENERIC_OPERATIONS_