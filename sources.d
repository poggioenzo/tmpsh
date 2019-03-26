# This auto-generated file please don't edit it.

SOURCES_DIR = src/

COMMON_SRCS	:= prompt_loop.c \

COMMON_SRCS := $(addprefix $(SOURCES_DIR), $(COMMON_SRCS))

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
					   $(PROMPT_CONF)

CONFIGURATION_SRCS := $(addprefix $(CONFIGURATION_DIR), $(CONFIGURATION_SRCS))

SOURCES+=src/char_concatenation.c
SOURCES+=src/cursor_dependent_selection.c
SOURCES+=src/debug.c
SOURCES+=src/display.c
SOURCES+=src/edition.c
SOURCES+=src/t_cursor_utils.c
SOURCES+=src/file/replace_home.c

SOURCES += $(COMMON_SRCS) \
		   $(addprefix $(SOURCES_DIR), $(CHAR_UTILS)) \
		   $(addprefix $(SOURCES_DIR), $(HISTORY_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(LINE_UTILS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(KEYPRESS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(CONFIGURATION_SRCS)) \

