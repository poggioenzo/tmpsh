make -s -C ../Libft && cp ../Libft/libft.a .

gcc pylst_test.c test_runner.c error_display.c -I ../Libft ../Libft/libft.a -o test_libft || exit 1

./test_libft
