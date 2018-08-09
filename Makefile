OPTFLAGS = -march=native -mtune=native -O2
CXXFLAGS += -g -Wall -Wextra -Wno-unused-parameter -std=c++11 -fPIC -Wno-unused-variable
CXXFLAGS += -I $(DEPSRC)/libsnark -I $(DEPSRC)/libsnark/depends/libfqfft -I $(DEPSRC)/libsnark/depends/libff -DUSE_ASM -DCURVE_ALT_BN128
LDFLAGS += -flto

DEPSRC=depsrc
DEPINST=depinst

LDLIBS += -L . -lsnark -lgmpxx -lgmp -lff -lprocps
LDLIBS += -lboost_system

all:
	$(CXX) -o test.o src/test.cpp -c $(CXXFLAGS)
	$(CXX) -o test test.o $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) test.o test
