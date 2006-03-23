##########################################################
# Modify this section to suit your system's needs
##########################################################

CXX = g++ -O3 -m32

###########################################################
# No modification should be necessary from thin point on
###########################################################

INSTALL_LIST = *.h *.C

INSTALL_ROOT = /usr/local

LIBCAT_OBJS = random.o 

all: libcat testcat

clean:
	@rm -fv *~ *.o testcat

libcat: libcat_a libcat_so

libcat_a: $(LIBCAT_OBJS)
	ar rcs libcat.a $(LIBCAT_OBJS)

libcat_so: $(LIBCAT_OBJS)
	$(CXX) -shared -o libcat.so $(LIBCAT_OBJS)

random.o: random.C random.h
	$(CXX) -c random.C

test: testcat

testcat: testcat.o
	$(CXX) -g -o testcat testcat.o

testcat.o: testcat.C *.h *.C
	$(CXX) -g -c testcat.C

install:
	install -c -m 644 $(INSTALL_LIST) $(INSTALL_ROOT)/include/cat
	install -c -m 644 libcat.a libcat.so $(INSTALL_ROOT)/lib
uninstall:
	cd $(INSTALL_ROOT)/include && @rm -rfv cat
	cd $(INSTALL_ROOT)/include && @rm -rfv libcat*

