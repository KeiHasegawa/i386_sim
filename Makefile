DLL = libsim.so

TAG = TAGS

all:$(DLL) $(TAG)

$(DLL):Makefile

OBJS = sim.o callback.o

LD_FLAG = ../../bfd/libbfd.a ../../libiberty/libiberty.a

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

