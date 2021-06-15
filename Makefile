DLL = libsim.so

TAG = TAGS

all:$(DLL) $(TAG)

OBJS = sim.o callback.o

$(DLL):$(OBJS)
	g++ -g3 -o $@ $(OBJS)  -shared

EXTRA_FLAG = -fPIC -I../../include -I. -DPACKAGE

%.o : %.cpp
	g++ -g3 -o $@ -c $< $(EXTRA_FLAG)

callback.o:../common/callback.c
	gcc -g3 -c $< -o $@ $(EXTRA_FLAG)


$(TAG):$(DLL)
	mktags.exe -o $@ -e $<

clean:
	rm -f $(DLL) $(TAG) $(OBJS) *.j *~

