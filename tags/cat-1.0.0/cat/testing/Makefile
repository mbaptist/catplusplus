##########################################################
# Modify this section to suit your system's needs
##########################################################

CXX = g++ -O3 -funroll-loops -fexpensive-optimizations  

########################################################################

INCLUDE = -I..

LIB = -L..

OBJECTS = testcat.o

########################################################################


###########################################################
# No modification should be necessary from thin point on
###########################################################

all: testcat

testcat: $(OBJECTS)
	$(CXX) $(LIB) -o testcat $(OBJECTS) -lcat

%.o: %.C *.h
	$(CXX) $(INCLUDE) -c $<

clean:
	@rm -rfv *~ *.o testcat

