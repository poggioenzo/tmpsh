# This auto-generated file please don't edit it.

SOURCES_DIR = src/

COMMON_SRCS	:= 

COMMON_SRCS := $(addprefix $(SOURCES_DIR), $(COMMON_SRCS))

CHAR_UTILS_DIR = char_utils/

CHAR_UTILS := char_selection.c \
			  delete_char_range.c \
			  t_char_allocation.c \
			  t_char_utils.c \

CHAR_UTILS := $(addprefix $(CHAR_UTILS_DIR), $(CHAR_UTILS))

CURSOR_MOVEMENT_DIR = cursor_movement/

CURSOR_MOVEMENT_SRCS := cursor_move.c \
						line_move.c \
						standard_move.c \
						word_move.c
						
CURSOR_MOVEMENT_SRCS := $(addprefix $(CURSOR_MOVEMENT_DIR), $(CURSOR_MOVEMENT_SRCS))

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

KEYPRESS_DIR = keypress_functions/

KEYPRESS_SRCS := char_deletion.c \
				 newline_keypress.c \
				 $(NEWLINE_UTILS) \

KEYPRESS_SRCS := $(addprefix $(KEYPRESS_DIR), $(KEYPRESS_SRCS))

SOURCES+=src/char_concatenation.c
SOURCES+=src/cursor_dependent_selection.c
SOURCES+=src/debug.c
SOURCES+=src/display.c
SOURCES+=src/edition.c
SOURCES+=src/prompt.c
SOURCES+=src/prompt_field.c
SOURCES+=src/screen_size.c
SOURCES+=src/shell_setup.c
SOURCES+=src/t_caps_utils.c
SOURCES+=src/t_cursor_utils.c
SOURCES+=src/termios_setter.c
SOURCES+=src/t_char_insert.c
SOURCES+=src/file/replace_home.c
SOURCES+=src/clipboard.c
SOURCES+=src/signal_handler.c

SOURCES += $(COMMON_SRCS) \
		   $(addprefix $(SOURCES_DIR), $(CURSOR_MOVEMENT_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(CHAR_UTILS)) \
		   $(addprefix $(SOURCES_DIR), $(HISTORY_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(LINE_UTILS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(KEYPRESS_SRCS)) \

