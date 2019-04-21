make -s -C ../Libft && cp ../Libft/libft.a .

TEST_NAME="test_shell"

TEST_MANAGER="test_runner.c error_display.c"
FILES="pylst_test.c hash_table_test.c t_line_allocation_test.c"

LIBS="../libtmp.a ../Libft/libft.a"

gcc ${TEST_MANAGER} ${FILES} -I ../Libft $LIBS -o $TEST_NAME || exit 1

./$TEST_NAME
