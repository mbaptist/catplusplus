
CPP=g++ -Wall 

INSTALL_LIB_DIR = /usr/local/lib

INSTALL_LIST = sl*.h sl*.C


all: testcat

clean:
	rm -f *~ *.o test_slate

testcat: testcat.o
	$(CPP) -g -o testcat testcat.o

test_slate.o: test_slate.C *.h
	$(CPP) -g -c testcat.C

install:
	mkdir $(INSTALL_LIB_DIR)/cat
	install -c -m 644 $(INSTALL_LIST) $(INSTALL_LIB_DIR)/cat

uninstall:
	rm -rf $(INSTALL_LIB_DIR)/cat

