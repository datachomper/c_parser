/* This program takes a valid c declaration and parses it into english */
/* TODO: Make it translate into samuel l jackson english */

#include <stdio.h>
#include <ctype.h>

//TODO: Find the largest token string size and set this properly
#define MAXTOKENLEN 127

struct token {
	char string[MAXTOKENLEN];
};

struct token tstack[255];

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s \"crazy c declaration\"\n", argv[0]);
		return -1;
	}

	/* Print string to be parsed */
	char *line = argv[1];
	//TODO: Remove demo line
	line = "int *((*fp)[10])()";
	printf("Parsing %s\n", line);
	

	/* Push tokens onto stack from left to right until first identifier is read */ 
	char *c = line;
	int x = 0;
	struct token *sp = &tstack[0];
	for (int i = 0; c[i] != 0; i++) {
		if (isalnum(c[i])) {
			// It's a word symbol or identifier
			printf("alpha: %c\n", c[i]);
			printf("char: %c x: %d\n", c[i], x);
			sp->string[x] = c[i];
			x++;
		} else {
			/* Skip spaces? */
			if (c[i] == ' ') continue;

			/* Finish string if we were tracking one with x */
			if (x) {
				printf("char: %c x: %d\n", c[i], x);
				sp->string[x] = 0;
				x = 0;
				sp++;
			}

			// It's one of *()[]
			printf("not alpha: %c\n", c[i]);
			sp->string[0] = c[i];
			sp->string[1] = 0;
			sp++;
		}
	}

	/* DEBUG: Print out all symbols on the stack */
	printf("Dumping stack:\n");
	sp = &tstack[0];
	while (sp->string[0]) {
		printf("%s ", sp->string);
		sp++;
	}

	return 0;
}
