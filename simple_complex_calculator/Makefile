OBJECT1=main_1
OBJECT2=main_2
MYLIB_OBJ1=complex_num
MYLIB_OBJ2=complex_add complex_sub complex_mul complex_div
CFLAGS=-Wall -g
LDLIBS1=-lm -Lplugins/ -lst_$(MYLIB_OBJ1)
LDLIBS2=-lm -Lplugins/ -lsh_$(MYLIB_OBJ1)
LDLIBS3=-lm -ldl
CC=gcc

all:
	$(CC) $(CFLAGS) -o $(OBJECT1)_1.out $(OBJECT1).c $(LDLIBS1)
	$(CC) $(CFLAGS) -o $(OBJECT1)_2.out $(OBJECT1).c $(LDLIBS2)
	$(CC) $(CFLAGS) -o $(OBJECT2).out $(OBJECT2).c $(LDLIBS3)

install: static shared_1 shared_2
	

uninstall: 
	@if [ -d ./plugins/ ] ; then \
		rm -rf ./plugins ; \
	fi

static:
	cd src ; \
	$(CC) -c $(MYLIB_OBJ1).c ; \
	ar rc libst_$(MYLIB_OBJ1).a $(MYLIB_OBJ1).o ; \
	ranlib libst_$(MYLIB_OBJ1).a ; \
	rm -f *.o
	@if ! [ -d ./plugins/ ] ; then \
		mkdir plugins ; \
	fi
	mv ./src/*.a ./plugins/

shared_1:
	cd src ; \
	$(CC) -fPIC -c $(MYLIB_OBJ1).c ; \
	$(CC) -shared -o libsh_$(MYLIB_OBJ1).so $(MYLIB_OBJ1).o ; \
	rm -f *.o
	@if ! [ -d ./plugins/ ] ; then \
		mkdir plugins ; \
	fi
	mv ./src/*.so ./plugins/

shared_2:
	./create_shared_libs.sh $(CC) "$(MYLIB_OBJ2)"
	@if ! [ -d ./plugins/ ] ; then \
		mkdir plugins ; \
	fi
	mv ./src/*.so ./plugins/

clean:
	rm -f *.out
