/* This program takes a valid c declaration and parses it into english */
/* TODO: Make it translate into samuel l jackson english */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

//TODO: Find the largest token string size and set this properly
#define MAXTOKENLEN 127
#define NUM_SYMBOLS 20

char symbols[NUM_SYMBOLS][MAXTOKENLEN] = {"short", "char", "int","long","double","float","unsigned","signed",
					  "volatile", "extern", "static", "const", "struct", "enum", "union"};

struct Token {
	char string[MAXTOKENLEN];
	enum {NOT_IDENT, IDENT} class;
};

struct Token tstack[255];

void classify_token(struct Token *t) {
	/* Quick classify single char tokens */
	if (t->string[1] == '\0') {
		t->class = NOT_IDENT;
		return;
	}
	
	/* Handle alphanumeric tokens */
	for (int i = 0; i < NUM_SYMBOLS; i++) {
		if (!strcmp(t->string, symbols[i])) {
			t->class = NOT_IDENT;
			return;
		}
	}

	/* No matches on known static symbols, must be an identifier */
	t->class = IDENT;
}

/* Pass: String and token struct */
/* Returns: Next token in string or NULL */
/* 	    Increments s past returned token */
int get_token(char **s, struct Token *t) {
	char *x = t->string;

	/* Skip past spaces */
	while (isblank(**s)) { (*s)++; }
	
	/* Return false at EOL */
	if (**s == '\0')
		return -1;

	/* Single char symbol detection */
	if (!isalnum(**s)) {
		*x++ = **s;
		(*s)++;
	} else {
		/* Multi-char symbol detection */
		while (isalnum(**s) && (**s != '\0') && !isblank(**s)) {
			*x++ = **s;
			(*s)++;
		}
	}
	
	*x = '\0';
	classify_token(t);

	return 0;
}

int main(int argc, char **argv)
{
	//TODO: Remove comment block in order to pass in strings
	#if 0
	if (argc < 2) {
		printf("Usage: %s \"crazy c declaration\"\n", argv[0]);
		return -1;
	}
	#endif

	/* Print string to be parsed */
	char *line = argv[1];
	//TODO: Remove demo line
	//line = "char* const *(*next)()";
	//line = "unsigned int* const *(*next)()";
	line = "unsigned int* const *(*next[10])()";
	printf("Parsing %s\n", line);
	
	/* From left to right push all tokens to the stack until the first
	 * identifier is found */
	struct Token *sp = &tstack[0];
	while (!get_token(&line, sp)) {
		if (sp->class == IDENT)
			break;
		sp++;
	}

	printf("%s is a ", sp->string);

	/* Main decoder loop */
	while (1) {
		struct Token this;

		/* First move to the right */
		if (!get_token(&line, &this)) {
			if (this.string[0] == '[') {
				while (this.string[0] != ']')
					get_token(&line, &this);
				printf("array of ");
			}
			if (this.string[0] == '(') {
				while (this.string[0] != ')')
					get_token(&line, &this);
				printf("a function returning ");
			}
		}

		/* Then move to the left */
		moveleft:
		sp--;

		if (sp->string[0] == '(') {
			while (this.string[0] != ')')
				get_token(&line, &this);
			continue;
		}

		/* If const, volatile, or *, continue reading left */
		if (sp->string[0] == '*') {
			printf("pointer to ");	
			goto moveleft;
		} else if (!strcmp(sp->string, "volatile")) {
			printf("volatile ");	
			goto moveleft;
		} else if (!strcmp(sp->string, "const")) {
			printf("read-only ");	
			goto moveleft;
		} else {
			/* Remaining tokens form basic declaration */
			printf("%s ", sp->string);
		}

		/* If stack pointer hits the beginning of the stack, exit */
		if (sp == &tstack[0])
			break;
	}

	return 0;
}
