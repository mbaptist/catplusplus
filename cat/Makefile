##########################################################
# Modify this section to suit your system's needs
##########################################################

CXX = g++ -O3 -funroll-loops -fexpensive-optimizations  

###########################################################
# No modification should be necessary from thin point on
###########################################################

INSTALL_ROOT = /usr/local

LIBCAT_OBJS = ./random/random.o 

all: libcat doc test

clean:
	@rm -fv *~ *.o *.so *.a
	$(MAKE) -C ./random clean
	$(MAKE) -C ./doc clean
	$(MAKE) -C ./testing clean

libcat: libcat_a libcat_so

libcat_a: subdirs $(LIBCAT_OBJS)
	ar rcs libcat.a $(LIBCAT_OBJS)

libcat_so: subdirs $(LIBCAT_OBJS)
	$(CXX) -shared -o libcat.so $(LIBCAT_OBJS)

subdirs:
	$(MAKE) -C ./random

doc:
	$(MAKE) -C ./doc

test: libcat
	$(MAKE) -C ./testing

install:
	install -c -m 644 *.h $(INSTALL_ROOT)/include/cat
	install -c -m 644 random/*.h $(INSTALL_ROOT)/include/cat/random
	install -c -m 644 tiny/*.h tiny/*.C $(INSTALL_ROOT)/include/cat/tiny
	install -c -m 644 array/*.h array/*.C $(INSTALL_ROOT)/include/cat/array
	install -c -m 644 traits/*.h traits/*.C $(INSTALL_ROOT)/include/cat/traits
	install -c -m 644 libcat.a libcat.so $(INSTALL_ROOT)/lib
	install -c -m 644 doc/* $(INSTALL_ROOT)/share/doc
uninstall:
	cd $(INSTALL_ROOT)/include && @rm -rfv cat
	cd $(INSTALL_ROOT)/lib && @rm -rfv libcat*

