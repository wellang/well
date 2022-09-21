# Libwesm

## Memory handler

* **salloc:** *assign string (aquivalent to '=')*
```C
char* salute = salloc("Hi"); // Hi
```

* **resalloc:** *append string (aquivalent to '+=')*
```C
char* salute = resalloc(salute, "!!"); // Hi!!
```

* **unsalloc:** *clean string*
```C
unsalloc(salute); // ''
```
