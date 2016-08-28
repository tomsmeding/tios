#ifndef __VARS__
#define __VARS__

#include "stdlib.h"
#include "stdio.h" // nah

typedef enum varType {
	REAL = 0x00,      // Real number
	LIST = 0x01,      // List
	MAT = 0x02,       // Matrix
	EQU = 0x03,       // Equation
	STRNG = 0x04,     // String
	PROG = 0x05,      // Program
	PROT_PROG = 0x06, // Protected program (Hidden from EDIT menu)
	PICT = 0x07,      // Picture
	GDB = 0x08,       // Graph Database
	NEW_EQU = 0x0B,    // New Equation
	CPLX = 0x0C,      // Complex number
	CLIST = 0x0D,     // Complex list
	APP_VAR = 0x15,   // AppVar
	TEMP_PROG = 0x16  // Temporary program
} varType;

typedef struct Variable {
	char *name;
	varType type;
	bool archived;
	void *tableStorage;
	void *dataStorage;
	uint8_t romPage;
} Variable;

Variable *createVariable(
	char *name,
	varType type,
	uint8_t archiveStatus,
	void *dataAddress,
	void *tableAddress
) {
	Variable *var = malloc(sizeof(struct Variable));

	var->name = name;
	var->type = type;
	var->archived = archiveStatus != 0;
	var->dataStorage = dataAddress;
	var->tableStorage = tableAddress;

	return var;
}

// Stores the Variable given at the given pointer, returns the same pointer back.
Variable *storeVariable(Variable *self) {
	// TODO
	return self;
}

// Returns a pointer to the the variable matching the given variable name, will
// be NULL when not found.
Variable *getVariable(char *name) __naked {
	__asm
		push ix
		ld ix, #0
		add ix, sp

		ld l, 4(ix)
		ld h, 5(ix)
		rst #0x28
		.dw #0x42F1 // _ChkFindSym
		jr c, getvar_notfound

		getvar_found:
			push hl // hl contains tableAddress
			push de // de contains dataAddress
			ld l, b // b contains archiveStatus
			push hl
			and a, #0x1f // a contains obj type
			ld l, a
			push hl

			call _createVariable
			pop af
			pop af
			pop af
			pop af
			jr getvar_end

		getvar_notfound:
			ld l, #0x0
			ld h, #0x0

		getvar_end:
			pop ix
			ret
	__endasm;
}

// void _delVarArc(void *tableEntry, void *dataStorage, uint8_t romPage) {
// 	__asm
// 		ld l, 4(ix)
// 		ld h, 5(ix)
// 
// 		ld e, 6(ix)
// 		ld d, 7(ix)
// 
// 		ld b, 8(ix)
// 
// 		rst #0x28
// 		.dw #0x4FC6 // _DelVarArc
// 	__endasm;
// }
// void deleteVariable(Variable *var) {
// 	return _delVarArc(var->tableEntry, var->dataStorage, var->romPage);
// }

#endif
