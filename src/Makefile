GCC = gcc
FLAGS = -Wall -v
FLAGS_STATIC = -static
DEBUG?=
RM = rm -f
CP = cp -v -f

WIN_GCC = i686-w64-mingw32-gcc
WIN_FLAGS = -Wall -v

OBJECTS=steamfontsizer.c steamfontsizer.h

all: steamfontsizer win32 linux32 linux64

steamfontsizer.o: $(OBJECTS)
	$(GCC) $(FLAGS) $(DEBUG) -c -o $@ $<
	@echo $(OBJECTS)

steamfontsizer: steamfontsizer.o
	$(GCC) $(FLAGS) $(DEBUG) -o $@ $<
	$(CP) $@ ../bin/

win32: steamfontsizer-w32.exe
	$(CP) $< ../win32/steamfontsizer.exe

steamfontsizer-w32.o: $(OBJECTS)
	$(WIN_GCC) $(WIN_FLAGS) -c -o $@ $<
	@echo $(OBJECTS)

steamfontsizer-w32.exe: steamfontsizer-w32.o
	$(WIN_GCC) $(WIN_FLAGS) -o $@ $<

linux32: steamfontsizer-linux32
	$(CP) $< ../linux32/steamfontsizer

steamfontsizer-linux32.o: $(OBJECTS)
	$(GCC) $(FLAGS) $(FLAGS_STATIC) -m32 -c -o $@ $<
	@echo $(OBJECTS)

steamfontsizer-linux32: steamfontsizer-linux32.o
	$(GCC) $(FLAGS) $(FLAGS_STATIC) -m32 -o $@ $<

linux64: steamfontsizer-linux64
	$(CP) $< ../linux64/steamfontsizer

steamfontsizer-linux64.o: $(OBJECTS)
	$(GCC) $(FLAGS) $(FLAGS_STATIC) -c -o $@ $<
	@echo $(OBJECTS)

steamfontsizer-linux64: steamfontsizer-linux64.o
	$(GCC) $(FLAGS) $(FLAGS_STATIC) -o $@ $<

clean:
	$(RM) steamfontsizer steamfontsizer.o steamfontsizer-w32.exe steamfontsizer-w32.o steamfontsizer-linux32 steamfontsizer-linux32.o steamfontsizer-linux64 steamfontsizer-linux64.o
	$(RM) ../bin/steamfontsizer
