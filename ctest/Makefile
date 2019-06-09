TEST_NAME = test_shell

TEST_MANAGER := test_runner.c \
				error_display.c \
				runner_utils.c

TEST_MANAGER := $(addprefix utils/, $(TEST_MANAGER))

FILES := pylst_test.c  \
		 hash_table_test.c \
		 t_line_allocation_test.c \
		 t_char_allocation_tests.c \
		 t_cursor_alloc.c \
		 t_char_selection_test.c \
		 t_char_insert_test.c \
		 cursor_dependent_selection_tests.c \
		 grammar_test.c \


FILES := $(addprefix tests/, $(FILES))

ERROR_SRCS := t_char_error.c \
			  default_error.c \
			  t_pylst_error.c \


ERROR_SRCS := $(addprefix error_creation/, $(ERROR_SRCS))

SRCS := $(FILES) \
		$(TEST_MANAGER) \
		$(ERROR_SRCS) \
		functions_adding.c

OBJS = $(SRCS:%.c=%.o)

LIB_TMP = ../libtmp.a

LIB_FT = ../Libft/libft.a

LIBS= $(LIB_TMP) $(LIB_FT)

CPPFLAGS := $(shell find ../include ../Libft . -type d)
CPPFLAGS := $(addprefix -I, $(CPPFLAGS))

all:$(TEST_NAME)

$(TEST_NAME):$(OBJS) $(LIBS)
	gcc $^ $(CPPFLAGS)  -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(TEST_NAME)

re:fclean all

run: $(TEST_NAME)
	./$(TEST_NAME)

##############################################
#				Librairies rules			 #
##############################################

$(LIB_TMP):
	make test -C $(dir $@)

$(LIB_FT):
	make -C $(dir $@)

.PHONY: run all clean fclean re $(LIB_TMP)
.DEFAULT_GOAL = all
