cd C:\MinGW\bin\master
gcc -c myfunc.c
gcc -c myinit.c
gcc -c master.c
gcc master.o myinit.o myfunc.o -o master
cls
master