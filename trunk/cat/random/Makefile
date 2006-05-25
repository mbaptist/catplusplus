##########################################################
# Modify this section to suit your system's needs
##########################################################

CXX = g++ -O3 -funroll-loops -fexpensive-optimizations 

########################################################################

INCLUDE = -I..

OBJECTS = random.o

########################################################################


###########################################################
# No modification should be necessary from thin point on
###########################################################

all: $(OBJECTS)

%.o: %.C *.h
	$(CXX) $(INCLUDE) -c $<

clean:
	@rm -rfv *~ *.o

