MAIN_FILE = src/shell_main.c

SOURCES_DIR = src/

COMMON_SRCS := char_concatenation.c \
			   cursor_dependent_selection.c \
			   debug.c \
			   display.c \
			   edition.c \
			   t_cursor_utils.c \
			   prompt_loop.c

COMMON_SRCS := $(addprefix $(SOURCES_DIR), $(COMMON_SRCS)) \
			   $(MAIN_FILE)

CHAR_UTILS_DIR = char_utils/

CHAR_UTILS := char_selection.c \
			  delete_char_range.c \
			  t_char_allocation.c \
			  t_char_utils.c \
              t_char_insert.c \

CHAR_UTILS := $(addprefix $(CHAR_UTILS_DIR), $(CHAR_UTILS))

HISTORY_DIR = history/

HISTORY_SRCS := file_management.c \
				get_next_command.c \
				history_adding.c \
				history_manager.c \
				history_manager_utils.c \
				history_store.c \
				t_hist_allocation.c \

HISTORY_SRCS := $(addprefix $(HISTORY_DIR), $(HISTORY_SRCS))

LINE_UTILS_DIR = line_utils/

LINE_UTILS_SRCS := t_line_allocation.c \
				   t_line_utils.c

LINE_UTILS_SRCS := $(addprefix $(LINE_UTILS_DIR), $(LINE_UTILS_SRCS))


NEWLINE_UTILS := char_skip.c \
				 line_extend.c \
				 operand_check.c \
				 operand_deletion.c \
				 syntax_error.c \
				 t_operand_allocation.c \
				 t_operand_utils.c \
				 get_next_char.c \

NEWLINE_UTILS := $(addprefix newline_utils/, $(NEWLINE_UTILS))

CLIPBOARD_UTILS := cut_functions.c

CLIPBOARD_UTILS := $(addprefix clipboard_utils/, $(CLIPBOARD_UTILS))


CURSOR_MOVEMENT_SRCS := cursor_move.c \
						line_move.c \
						standard_move.c \
						word_move.c

CURSOR_MOVEMENT_SRCS := $(addprefix cursor_movement/, $(CURSOR_MOVEMENT_SRCS))

KEYPRESS_DIR = keypress_functions/

KEYPRESS_SRCS := char_deletion.c \
				 newline_keypress.c \
				 clipboard.c \
				 eof.c \
				 char_analysis.c \
				 $(NEWLINE_UTILS) \
				 $(CLIPBOARD_UTILS) \
                 $(CURSOR_MOVEMENT_SRCS)

KEYPRESS_SRCS := $(addprefix $(KEYPRESS_DIR), $(KEYPRESS_SRCS))

PROMPT_CONF :=  prompt.c \
				prompt_field.c \
				shell_setup.c \

PROMPT_CONF := $(addprefix prompt/, $(PROMPT_CONF))

CONFIGURATION_DIR = configuration/

CONFIGURATION_SRCS :=  screen_size.c \
					   signal_handler.c \
					   t_caps_utils.c \
					   termios_setter.c \
					   environ_utils.c \
					   $(PROMPT_CONF)

CONFIGURATION_SRCS := $(addprefix $(CONFIGURATION_DIR), $(CONFIGURATION_SRCS))

BUILTINS_DIR = builtins/

BUILTINS_SRCS := cd.c \
				 env.c \
				 setenv.c \
				 unsetenv.c \
                 echo.c \
				 exit.c \

BUILTINS_SRCS := $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRCS))

EXECUTION_DIR = execution/

EXECUTION_SRCS := fd_management.c \
                  rights_file.c \
                  foreground.c \

EXECUTION_SRCS := $(addprefix $(EXECUTION_DIR), $(EXECUTION_SRCS))

FILE_DIR = file/

FILE_SRCS := replace_home.c \
			 file_utils.c \
			 replace_home.c \
			 path_check.c \

FILE_SRCS := $(addprefix $(FILE_DIR), $(FILE_SRCS))

GRAMMAR_DIR = grammar/

GRAMMAR_SRCS := grammar_init.c \
                parsing.c \
                grammar_utils.c \
                store_attributes_1.c \
                store_attributes_2.c \
                grammar_print.c \
                grammar_print_attributes.c \

GRAMMAR_SRCS := $(addprefix $(GRAMMAR_DIR), $(GRAMMAR_SRCS))

TOKENIZER_DIR = tokenizer/

TOKENIZER_SRCS := tokenizer.c \
									tokenizer_utils.c \

TOKENIZER_SRCS := $(addprefix $(TOKENIZER_DIR), $(TOKENIZER_SRCS))

TAGSTOKENS_DIR = tagstokens/

TAGSTOKENS_SRCS :=	init_tagstokens.c \
					str_tagstokens.c \
					iter_tagstokens.c \
					tagging_tagstokens.c \
					delitems_tagstokens.c \
					strip_tagstokens.c \
					update_length_tagstokens.c \
					copy_tagstokens.c\
					append_tagstokens.c\
					free_tagstokens.c\


TAGSTOKENS_SRCS := $(addprefix $(TAGSTOKENS_DIR), $(TAGSTOKENS_SRCS))



AST_DIR = ast_build/

AST_SRCS := $(GRAMMAR_SRCS) \
						$(TOKENIZER_SRCS) \
						$(TAGSTOKENS_SRCS) \

AST_SRCS := $(addprefix $(AST_DIR), $(AST_SRCS)) \

SOURCES += $(COMMON_SRCS) \
		   $(addprefix $(SOURCES_DIR), $(CHAR_UTILS)) \
		   $(addprefix $(SOURCES_DIR), $(HISTORY_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(LINE_UTILS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(KEYPRESS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(CONFIGURATION_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(FILE_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(BUILTINS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(EXECUTION_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(AST_SRCS)) \
