NAME = 21sh
REAL_NAME = tmpsh

CC = gcc
CFLAGS = -Wall -Wextra -Wno-error=unused-result -O3 -g #-fsanitize=address #-pedantic#-Wconversion #  -Wall -Wextra -Werror 
CPPFLAGS = $(addprefix -I , $(INCLUDES))

include sources.d

ifeq (test, $(MAKECMDGOALS))
SOURCES := $(filter-out $(MAIN_FILE), $(SOURCES))
endif

#according to a given c file, transform it in a hidden file format
#Exemple : 'my/folder/file.o' will be 'my/folder/.file.o'
get_hidden_obj = $(addprefix ., $(notdir $(1)))
hidden_format = $(addprefix $(dir $(1)), $(call get_hidden_obj, $(1)))
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


#Retrieve all includes file by listing all directories in INCLUDES_FOLDER
INCLUDES = $(shell find $(INCLUDE_FOLDER:%/=%) -type d)

INCLUDES += $(LIB_INCLUDES)

all: get_lib $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -ltermcap $^ -o $@ #-lncurses -ltinfo
	ln -f -s $@ $(REAL_NAME)

clean:
	#Use clean rule of lib if the called command is also clean, skip otherwise
	{ [ "$(MAKECMDGOALS)" = "$@" ] && $(MAKE) -C $(LIBDIR) $@ ;} || true
	rm -rf $(OBJS)

fclean:clean
	$(MAKE) -C $(LIBDIR) $@
	rm -rf $(NAME) $(REAL_NAME) shell_debug $(TEST_LIB)

proper:fclean
	$(MAKE) -C $(LIBDIR) $@
	rm -rf $(DEPENDENCIES)

re: fclean all

rep: proper all

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
