# http://stackoverflow.com/questions/14639794/getting-make-to-create-object-files-in-a-specific-directory
# http://stackoverflow.com/questions/5178125/how-to-place-object-files-in-separate-subdirectory
# http://stackoverflow.com/questions/22997731/makefile-destination-directory
CC = gcc
CFLAGS = -g -Wall -Wno-main -Wno-char-subscripts
EXE = traffic
DST_DIR = dst
DST_EXE = $(addprefix $(DST_DIR)/, $(EXE))
#LIBS = -l
EXE_OPTS =

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

default: $(DST_EXE)

# Étape de compilation
$(DST_DIR)/%.o: %.c $(HEADERS) | build_dirs
	$(CC) $(CFLAGS) -c $< -o $@

# Étape d'éditions de liens
# Les lignes suivantes contenant "$(CC)" commencent par un caractère TAB
# $@, $^, $< correspondent respectivement à la cible, les dépendances,
# la première dépendance
$(DST_EXE): $(addprefix $(DST_DIR)/, $(OBJECTS))
	$(CC) $^ -Wall -o $@

build_dirs:
	@mkdir -p $(DST_DIR)

clean:
	-rm -r $(DST_DIR)

run: $(DST_EXE)
	./$(DST_EXE) $(EXE_OPTS)

gdb: $(DST_EXE)
	gdb ./$(DST_EXE) $(EXE_OPTS)

valgrind: $(DST_EXE)
	valgrind --leak-check=full ./$(DST_EXE) $(EXE_OPTS)

.PHONY: default build_dirs clean run gdb valgrind
