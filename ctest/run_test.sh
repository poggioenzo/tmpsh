make -s -C ../Libft && cp ../Libft/libft.a .

TEST_MANAGER="test_runner.c error_display.c"
FILES="pylst_test.c hash_table_test.c "

gcc ${TEST_MANAGER} ${FILES} -I ../Libft ../Libft/libft.a -o test_libft || exit 1

./test_libft
