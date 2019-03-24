# This auto-generated file please don't edit it.

SOURCES_DIR = src/

SOURCES+=src/char_concatenation.c
SOURCES+=src/cursor_dependent_selection.c
SOURCES+=src/cursor_move.c
SOURCES+=src/debug.c
SOURCES+=src/display.c
SOURCES+=src/edition.c
SOURCES+=src/newline_keypress.c
SOURCES+=src/prompt.c
SOURCES+=src/prompt_field.c
SOURCES+=src/screen_size.c
SOURCES+=src/shell_setup.c
SOURCES+=src/t_caps_utils.c
SOURCES+=src/t_char_insert.c
SOURCES+=src/t_char_utils.c
SOURCES+=src/t_cursor_utils.c
SOURCES+=src/t_line_utils.c
SOURCES+=src/termios_setter.c
SOURCES+=src/t_bracket_utils.c
SOURCES+=src/get_next_char.c
SOURCES+=src/line_deletion.c
SOURCES+=src/file/replace_home.c
SOURCES+=src/history.c
SOURCES+=src/history_manager.c
SOURCES+=src/clipboard.c
SOURCES+=src/signal_handler.c

CURSOR_MOVEMENT_DIR = cursor_movement/

CURSOR_MOVEMENT_SRCS := standard_move.c
CURSOR_MOVEMENT_SRCS := $(addprefix $(CURSOR_MOVEMENT_DIR), $(CURSOR_MOVEMENT_SRCS))


SOURCES += $(addprefix $(SOURCES_DIR), $(CURSOR_MOVEMENT_SRCS))
