#ifndef GENERIC_CONSTANTS_
#define GENERIC_CONSTANTS_

#include "base\generic-type-definitions.hpp"

#ifndef MIN_INT8
#define MIN_INT8 ((INT8) 0x80)
#endif
#ifndef MAX_INT_8
#define MAX_INT8 ((INT8) 0x7F)
#endif

#ifndef MIN_UINT8
#define MIN_UINT8 ((UINT8) 0x00)
#endif
#ifndef MAX_UINT8
#define MAX_UINT8 ((UINT8) 0xFF)
#endif

#ifndef MIN_INT16
#define MIN_INT16 ((INT16) 0x8000)
#endif
#ifndef MAX_INT16
#define MAX_INT16 ((INT16) 0x7FFF)
#endif

#ifndef MIN_UINT16
#define MIN_UINT16 ((UINT16) 0x0000)
#endif
#ifndef MAX_UINT16
#define MAX_UINT16 ((UINT16) 0xFFFF)
#endif

enum ArithmeticOperators {
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	MODULO
};

enum LogicalOperators {
	OR,
	AND,
	NOT
};

enum CompareOperators {
	EQ,
	NOT_EQ,
	LT,
	LT_EQ,
	GT,
	GT_EQ
};

#endif // GENERIC_CONSTANTS_