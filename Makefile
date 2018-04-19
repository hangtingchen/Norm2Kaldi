cc=gcc

norm2kaldi:main.o ini.o hmath.o
	${cc} -lm -o norm2kaldi main.o ini.o hmath.o

main.o:main.c hmath.h ini.h
	${cc} -c main.c

hmath.o:hmath.c hmath.h
	${cc} -c hmath.c

ini.o:ini.c ini.h
	${cc} -c ini.c

clean:
	rm -f norm2kaldi *.o
