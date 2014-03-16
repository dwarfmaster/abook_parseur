include param.mk
OBJS=storage.o parser.o

all : $(LIB)

$(LIB) : $(OBJS)
	$(CC) $(CFLAGS)    -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	@touch $(LIB) $(OBJS)
	@rm    $(LIB) $(OBJS)

rec : clean all

.PHONY: all clean rec


