Summary:
 * Don't get excited. Literally all this program does is take a c style declaration string and translate it into english language. C declaration routine adopted from http://www.ceng.metu.edu.tr/~ceng140/c_decl.pdf

Example:
```
> parse.exe "char * const *(*myfunc)()"
  Parsing char * const *(*myfunc)()
  myfunc is a pointer to a function returning pointer to read-only pointer to char
```

TODO:
 * Process and print array sizes
 * Process and translate function arguments
 * Translate into "Samuel L Jackson" speech
 * Add more test cases
 * Handle syntax errors
