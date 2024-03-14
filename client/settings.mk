# Libraries
LIBS=commons pthread readline m

# Custom libraries' paths
STATIC_LIBPATHS=

# Compiler flags
CDEBUG=-g -Wall -DDEBUG -fdiagnostics-color=always
CRELEASE=-O3 -Wall -DNDEBUG -fcommon

# Arguments when executing with start, memcheck or helgrind
ARGS=

# Valgrind flags
MEMCHECK_FLAGS=--track-origins=yes
HELGRIND_FLAGS=
