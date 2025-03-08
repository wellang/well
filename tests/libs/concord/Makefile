WELL= ../../../well
WFLAGS= -i -cc "-ldiscord -lcurl -lpthread"

all: a.out

a.out:
	$(WELL) main.well $(WFLAGS)

clean:
	rm *.o *.s a.out
