#Para compilar:
gcc -o Calcular Calcular.c $(pkg-config --cflags --libs gtk+-3.0 gmodule-2.0)
