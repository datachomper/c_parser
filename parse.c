/* This program takes a valid c declaration and parses it into english */
/* TODO: Make it translate into samuel l jackson english */

#include <stdio.h>
#include <ctype.h>

//TODO: Find the largest token string size and set this properly
#define MAXTOKENLEN 127

struct Token {
	char string[MAXTOKENLEN];
};

struct Token tstack[255];

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
	line = "int *((*fp)[10])()";
	printf("Parsing %s\n", line);
	
	struct Token *sp = &tstack[0];
	while (!get_token(&line, sp++));

#if 0
	/* Push tokens onto stack from left to right until first identifier is read */ 
	char *c = line;
	int x = 0;
	struct Token *sp = &tstack[0];
	for (int i = 0; c[i] != 0; i++) {
		if (isalnum(c[i])) {
			// It's a word symbol or identifier
			sp->string[x] = c[i];
			x++;
		} else {
			/* Skip spaces? */
			if (c[i] == ' ') continue;

			/* Finish string if we were tracking one with x */
			if (x) {
				sp->string[x] = 0;
				x = 0;
				sp++;
			}

			// It's one of *()[]
			sp->string[0] = c[i];
			sp->string[1] = 0;
			sp++;
		}
	}
#endif

	/* DEBUG: Print out all symbols on the stack */
	printf("Dumping stack:\n");
	sp = &tstack[0];
	while (sp->string[0]) {
		printf("%s ", sp->string);
		sp++;
	}

	return 0;
}
