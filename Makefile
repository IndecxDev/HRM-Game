# x86_64-w64-mingw32-g++
CC = g++
CFLAGS = --static

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/out

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR) # Create binary directory if it doesn't exist
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	if [ -f "$(BINDIR)"/out* ] ; then rm "$(BINDIR)"/out* ; fi

run: $(EXECUTABLE)
	./$(EXECUTABLE)

all: $(EXECUTABLE)
