enum { SYM_NUMBER, SYM_NAME, SYM_CHAR };

typedef struct _symbol {
	int tag;
	union {
		long number;
		char *name;
		char ch;
	} content;
} Symbol;

