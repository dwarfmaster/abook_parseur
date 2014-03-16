include param.mk
OBJS=storage.o parser.o
TESTS=merger

all : $(LIB)

test : $(LIB) $(TESTS)

$(LIB) : $(OBJS)
	$(CC) $(CFLAGS)    -o $@ $^ $(LDFLAGS) -shared

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

% : %.cpp $(OBJS)
	$(CC) $(CFLAGS)    -o $@.prog $^ $(LDFLAGS)

clean :
	@touch $(LIB) $(OBJS)
	@rm    $(LIB) $(OBJS)

rec : clean all

.PHONY: all test clean rec


