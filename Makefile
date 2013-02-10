# Makefile based off of example from http://content.gpwiki.org/index.php/Makefile

# The compiler
C++ = gcc

# Specify the main target
TARGET = example.o
# Default build type (release or debug)
TYPE = debug
# Which directories contain source files
DIRS = source example
# Which directories contain header files
INCS = include 
# Which libraries are linked
LIBS = pthread
# The static libraries to include
SLIBS =
# The target architecture
ARCH = x64

# The next blocks change some variables depending on the build type
ifeq ($(TYPE), debug)
CCPARAM = -Wall -Werror -pedantic -std=c99 -g -I$(INCS)
MACROS =
endif

ifeq ($(TYPE), release)
CCPARAM = -Wall -Werror -pedantic -std=c99 -O2 -I$(INCS)
MACROS = NDEBUG
endif

# Add directories to the include and library paths
INCPATH = .
LIBPATH = 

# Which files to add to backups, apart from the source code
EXTRA_FILES = Makefile

# Where to store object and dependancy files.
STORE = .make-$(TYPE)
# Makes a list of the source (.cpp) files.
SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.c))
# List of header files.
HEADERS := $(foreach DIR,$(INCS),$(wildcard $(INCS)/*.h))
# Makes a list of the object files that will have to be created.
OBJECTS := $(addprefix $(STORE)/, $(SOURCE:.c=.o))
# Same for the .d (dependancy) files.
DFILES := $(addprefix $(STORE)/,$(SOURCE:.c=.d))

# Specify phony rules. These are rules that are not real files.
.PHONY: clean backup dirs

# Main target. The @ in front of a command prevents make from displaying
# it to the standard output.
$(TARGET): dirs $(OBJECTS)
		@echo Linking $(TARGET).
		@$(C++) -o $(TARGET) $(OBJECTS) $(SLIBS) $(LDPARAM) $(foreach LIBRARY, \
			$(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB))

# Rule for creating object file and .d file, the sed magic is to add
# the object path at the start of the file because the files gcc
# outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: %.c
		@echo Creating object file for $*...
		@$(C++) -Wp,-MMD,$(STORE)/$*.dd $(CCPARAM) $(foreach INC,$(INCPATH),-I$(INC))\
				$(foreach MACRO,$(MACROS),-D$(MACRO)) -c $< -o $@
		@sed -e '1s/^\(.*\)$$/$(subst /,\/,$(dir $@))\1/' $(STORE)/$*.dd > $(STORE)/$*.d
		@rm -f $(STORE)/$*.dd

# Empty rule to prevent problems when a header is deleted.
%.h: ;

# Cleans up the objects, .d files and executables.
clean:
		@echo Making clean.
		@-rm -f $(foreach DIR,$(DIRS),$(STORE)/$(DIR)/*.d $(STORE)/$(DIR)/*.o)
		@-rm -f $(TARGET)

# Backup the source files.
backup:
		@-if [ ! -e .backup ]; then mkdir .backup; fi;
		@zip .backup/backup_`date +%d-%m-%y_%H.%M`.zip $(SOURCE) $(HEADERS) $(EXTRA_FILES)

# Create necessary directories
dirs:
		@-if [ ! -e $(STORE) ]; then mkdir $(STORE); fi;
		@-$(foreach DIR,$(DIRS), if [ ! -e $(STORE)/$(DIR) ]; \
		 then mkdir $(STORE)/$(DIR); fi; )
		@-$(foreach DIR,$(INCS), if [ ! -e $(STORE)/$(DIR) ]; \
		 then mkdir $(STORE)/$(DIR); fi; )

run: $(TARGET)
		./$(TARGET)

valgrind: $(TARGET)
		valgrind --leak-check=full ./$(TARGET)

gdb: $(TARGET)
		gdb ./$(TARGET)

# Includes the .d files so it knows the exact dependencies for every
# source.
-include $(DFILES)$(target) $(bins) 
