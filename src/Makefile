GCC   = /usr/bin/gcc
FLAGS = -Wall -Wextra -g
LIBS  =
EXEC  = tinybecc

all: tbecc_misc.o aes_test.o tbecc_f2x.o tbecc_int.o tbecc_f2x_283.o tbecc_aes.o 
	$(GCC) $(FLAGS) *.o -o $(EXEC) $(LIBS) 

tbecc_misc.o: tbecc_misc.c tinyBECC.h tbecc_misc.h
	$(GCC) -c $(FLAGS) tbecc_misc.c

aes_test.o: aes_test.c tbecc_aes.h tinyBECC.h
	$(GCC) -c $(FLAGS) aes_test.c

tbecc_f2x.o: tbecc_f2x.c tinyBECC.h tbecc_misc.h tbecc_f2x.h
	$(GCC) -c $(FLAGS) tbecc_f2x.c

tbecc_int.o: tbecc_int.c tinyBECC.h tbecc_misc.h tbecc_int.h
	$(GCC) -c $(FLAGS) tbecc_int.c

tbecc_f2x_283.o: tbecc_f2x_283.c tinyBECC.h tbecc_misc.h tbecc_f2x.h \
 tbecc_f2x_283.h
	$(GCC) -c $(FLAGS) tbecc_f2x_283.c

tbecc_aes.o: tbecc_aes.c tbecc_aes.h tinyBECC.h
	$(GCC) -c $(FLAGS) tbecc_aes.c

clean:
	rm *~ *.o $(EXEC)
