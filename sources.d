MAIN_FILE = src/shell_main.c

SOURCES_DIR = src/

COMMON_SRCS := char_concatenation.c \
			   cursor_dependent_selection.c \
			   debug.c \
			   display.c \
			   t_cursor_utils.c \
			   prompt_loop.c\
               file_runner.c \

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
                 line_extend.c \
				 $(CLIPBOARD_UTILS) \
                 $(CURSOR_MOVEMENT_SRCS)

KEYPRESS_SRCS := $(addprefix $(KEYPRESS_DIR), $(KEYPRESS_SRCS))

PROMPT_CONF :=  prompt.c \
				prompt_field.c \
				shell_setup.c \

PROMPT_CONF := $(addprefix prompt/, $(PROMPT_CONF))

VARIABLES_DIR = variables/

VARIABLES_SRCS := environ_utils.c \
                  environ_setup.c \
                  local_variables.c \
                  variables_management.c \

VARIABLES_SRCS := $(addprefix $(VARIABLES_DIR), $(VARIABLES_SRCS))


CONFIGURATION_DIR = configuration/

CONFIGURATION_SRCS :=  screen_size.c \
					   signal_handler.c \
					   t_caps_utils.c \
					   termios_setter.c \
					   reset_signals.c \
                       level_increment.c \
                       $(VARIABLES_SRCS) \
					   $(PROMPT_CONF)

CONFIGURATION_SRCS := $(addprefix $(CONFIGURATION_DIR), $(CONFIGURATION_SRCS))

BUILTINS_DIR = builtins/

BUILTINS_SRCS := cd.c \
				 cd_finder.c \
				 cd_canon.c \
				 cd_canon_utils.c \
				 env.c \
				 envvar_builtins.c \
				 localvar_builtins.c \
                 echo.c \
				 exit.c \
				 argparser.c \
				 hash.c \
				 bg_fg.c \
				 jobs.c \
				 unalias.c \
				 alias.c \
				 export.c \
				 type.c \
				 builtins_builder.c \
				 background_utils.c \

BUILTINS_SRCS := $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRCS))

JOBCONTROL_DIR = job_control/

JOBCONTROL_SRCS := backgroundjobs.c \
				   control.c \
				   job.c \

JOBCONTROL_SRCS := $(addprefix $(JOBCONTROL_DIR), $(JOBCONTROL_SRCS))

EXECUTOR_DIR = executor/

EXECUTOR_SRCS := exec_command.c \
				 argv_formater.c \
				 run_ast.c \
				 run_ast_utils.c \
                 subast_command.c \
                 subshell.c \
                 cmdsubst_replacement.c \
                 cmdsubst_runner.c \
				 tagstoken_replacement.c \

EXECUTION_SRCS := $(addprefix $(EXECUTOR_DIR), $(EXECUTOR_SRCS))

EXECUTION_DIR = execution/

EXECUTION_SRCS := fd_management.c \
                  foreground.c \
                  assignation.c \
                  variable_replacement.c \
                  exec_file.c \
                  forker.c \
                  sigmask_modif.c \
                  heredoc_apply.c \
                  redirection_opener.c \
                  setup_redirection.c \
				  $(JOBCONTROL_SRCS) \
				  $(EXECUTION_SRCS) \

EXECUTION_SRCS := $(addprefix $(EXECUTION_DIR), $(EXECUTION_SRCS))

FILE_DIR = file/

FILE_SRCS := replace_home.c \
			 file_utils.c \
			 replace_home.c \

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
					str_command_tagstokens.c \
					iter_tagstokens.c \
					tagging_tagstokens.c \
					delitems_tagstokens.c \
					strip_tagstokens.c \
					update_length_tagstokens.c \
					copy_tagstokens.c \
					append_tagstokens.c \
					free_tagstokens.c \
					find_tagstokens.c \
					check_syntax_tagstokens.c \
					clear_stack_tagstokens.c \
					replace_alias_tagstokens.c \
					skip_openning_tagstokens.c \


TAGSTOKENS_SRCS := $(addprefix $(TAGSTOKENS_DIR), $(TAGSTOKENS_SRCS))


SHIFTREDUCE_DIR = shiftreduce/

SHIFTREDUCE_SRCS :=	check_forbidden_shiftreduce.c \
					tagstokens_shiftreduce.c \
					keyinstack_shiftreduce.c \
					reduce_all_shiftreduce.c \



SHIFTREDUCE_SRCS := $(addprefix $(SHIFTREDUCE_DIR), $(SHIFTREDUCE_SRCS))


AST_DIR = ast/

AST_SRCS :=	free_ast.c\
			init_ast.c\
			split_branch_ast.c\
			str_ast.c\


AST_SRCS := $(addprefix $(AST_DIR), $(AST_SRCS))


ACB_DIR = acb/

ACB_SRCS :=	check_redirection_acb.c\
			init_acb.c\
			str_acb.c\
			free_acb.c\
			check_subast_acb.c\
			set_subast_type_acb.c\


ACB_SRCS := $(addprefix $(ACB_DIR), $(ACB_SRCS))


REDIRECTIONFD_DIR = redirectionfd/

REDIRECTIONFD_SRCS :=	get_heredoc_redfd.c\
						init_redfd.c\
						str_redfd.c\
						free_redfd.c\


REDIRECTIONFD_SRCS := $(addprefix $(REDIRECTIONFD_DIR), $(REDIRECTIONFD_SRCS))


UTILS_DIR = utils/

UTILS_SRCS :=	split_shift.c\

UTILS_SRCS := $(addprefix $(UTILS_DIR), $(UTILS_SRCS))


FREE_DIR = free_memory/

FREE_SRCS := free_manager.c \
			 free_type1.c \
			 free_execution.c \


FREE_SRCS := $(addprefix $(FREE_DIR), $(FREE_SRCS))

AST_DIR = ast_build/


AST_BUILD_DIR = ast_build/

AST_BUILD_SRCS := $(GRAMMAR_SRCS) \
						$(TOKENIZER_SRCS) \
						$(TAGSTOKENS_SRCS) \
						$(SHIFTREDUCE_SRCS) \
						$(AST_SRCS) \
						$(ACB_SRCS) \
						$(REDIRECTIONFD_SRCS) \
						$(UTILS_SRCS) \

AST_BUILD_SRCS := $(addprefix $(AST_BUILD_DIR), $(AST_BUILD_SRCS)) \

SOURCES += $(COMMON_SRCS) \
		   $(addprefix $(SOURCES_DIR), $(CHAR_UTILS)) \
		   $(addprefix $(SOURCES_DIR), $(HISTORY_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(LINE_UTILS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(KEYPRESS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(CONFIGURATION_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(FILE_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(BUILTINS_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(EXECUTION_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(AST_BUILD_SRCS)) \
		   $(addprefix $(SOURCES_DIR), $(FREE_SRCS)) \
