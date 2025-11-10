CXX ?= g++
AR  ?= ar

libaudiofile.a: audiofile.o
	$(AR) rcs libaudiofile.a audiofile.o

audiofile.o: audiofile.cpp audiofile.h aupvlist.h
	$(CXX) -std=gnu++11 -DNDEBUG -fno-rtti -fno-exceptions -fvisibility-inlines-hidden -O2 -I. -c audiofile.cpp

clean:
	rm -f audiofile.o libaudiofile.a

.PHONY: clean
