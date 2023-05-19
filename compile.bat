windres -i .\resources.rc --input-format=rc -o icon.res -O coff
gcc -fdiagnostics-color=always -c -g main.c -o main.o
gcc main.o icon.res -o final.exe