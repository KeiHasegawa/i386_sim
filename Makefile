UNAME := $(shell uname)

ifneq (,$(findstring CYGWIN,$(UNAME)))
	DLL = libsim.dll
else
	DLL = libsim.so
endif

TAG = TAGS

all:$(DLL) $(TAG)

$(DLL):Makefile

LD_FLAG = ../../bfd/libbfd.a ../../libiberty/libiberty.a

ifneq (,$(findstring CYGWIN,$(UNAME)))
	LD_FLAG += ../../intl/libintl.a ../../zlib/libz.a -liconv
endif

OBJS = sim.o callback.o

$(DLL):$(OBJS)
	g++ -g3 -o $@ $(OBJS) -shared $(LD_FLAG)

EXTRA_FLAG = -fPIC -I../../include -I. -DPACKAGE -I../../bfd

%.o : %.cpp
	g++ -g3 -o $@ -c $< $(EXTRA_FLAG)

callback.o:../common/callback.c
	gcc -g3 -c $< -o $@ $(EXTRA_FLAG)

$(TAG):$(DLL)
	mktags.exe -o $@ -e $<

clean:
	rm -f $(DLL) $(TAG) $(OBJS) *.j *~

