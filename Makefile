NAME = tmpsh

CC = gcc
CFLAGS = -g -Wall -Wextra #-fsanitize=address#-pedantic#-Wconversion #  -Wall -Wextra -Werror 
CPPFLAGS = $(addprefix -I , $(INCLUDES_LIST))

include sources.d

ifeq (test, $(MAKECMDGOALS))
SOURCES := $(filter-out $(MAIN_FILE), $(SOURCES))
endif

#according to a given c file, transform it in a hidden file format
#Exemple : 'my/folder/file.o' will be 'my/folder/.file.o'
hidden_format = $(shell python -c "file = '$(1)'.split('/');print('/'.join(file[:-1]) + '/.' + file[-1])")
convert_src = $(strip $(call hidden_format, $(1:%.c=%.o)))

#Transform each %.c source file in the corresponding %.o file in an hidden file format.
OBJS = $(foreach file, $(SOURCES:%.c=%.o), $(call hidden_format, $(file)))

LIB_INCLUDES = Libft/ Libft/hash_table
LIB = Libft/libft.a
TEST_LIB = libtmp.a
LIBDIR = $(dir $(LIB))

INCLUDE_FOLDER = include/
SOURCES_FOLDER = src/
DEPENDENCIES_FOLDER = dependencies/

DEPENDENCIES = $(patsubst $(SOURCES_FOLDER)%.c, $(DEPENDENCIES_FOLDER)%.d, $(SOURCES))

#Remove duplicate directory name, used with $(call ...) function
select_dir = $(shell python -c "files = '$(1)'; files = set(files.split(' ')); print(' '.join(files).strip())")

INCLUDES = $(patsubst $(SOURCES_FOLDER)%.c, $(INCLUDE_FOLDER)%.h, $(SOURCES))
INCLUDES_LIST := $(foreach file, $(INCLUDES), $(dir $(file)))
INCLUDES_LIST := $(call select_dir, $(INCLUDES_LIST))

INCLUDES_LIST += $(LIB_INCLUDES)

all: get_lib $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -ltermcap $^  Libft/libft.a -o $@

clean:
	#Use clean rule of lib if the called command is also clean, skip otherwise
	{ [ "$(MAKECMDGOALS)" = "$@" ] && $(MAKE) -C $(LIBDIR) $@ ;} || true
	rm -rf $(OBJS)

fclean:clean
	$(MAKE) -C $(LIBDIR) $@
	rm -rf $(NAME) shell_debug $(TEST_LIB)

proper:fclean
	$(MAKE) -C $(LIBDIR) $@
	rm -rf $(DEPENDENCIES)

re: fclean all

$(LIB): get_lib

get_lib:
	$(MAKE) -C $(LIBDIR)

######################################
# 			Test rules               #
######################################

test:$(TEST_LIB)

$(TEST_LIB): $(OBJS) $(LIB)
	ar -rc $@ $(OBJS)

#######################################
# Generique rules for %.o and for %.d #
#######################################
%.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(filter %.c, $^) -o $@

$(DEPENDENCIES_FOLDER)%.d:$(SOURCES_FOLDER)%.c
	$(CC) -MM $(CPPFLAGS) $(filter %.c, $^) | \
		sed -E "s~(.*\.o):(.*)~$(call convert_src, $(filter %.c, $^)) $@:\2~" > $@

.DEFAULT_GOAL = all

.PHONY:all clean fclean proper re get_lib test

ifeq (, $(filter $(MAKECMDGOALS), proper clean fclean))
include $(DEPENDENCIES)
endif
