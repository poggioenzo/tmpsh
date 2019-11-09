#/bin/zsh

if [ $# -ne 1 ]
then
    echo "$0: Not enough arguments."
    exit 1
fi

if ! [ -d "$1" ]
then
    echo "$0: '$1' not a directory" && exit 1
fi

SHELL_REF=$(dirname $0)
SHELL_DEST=$1

FILE_TO_COPY="
Libft/Makefile
Libft/libft.h
Libft/ft_strall.c

src/ast_build/tagstokens/routine_tagstokens.c
src/builtins/alias.c
src/builtins/builtins_builder.c
src/execution/executor/cmdsubst_runner.c
src/execution/job_control/control.c
src/ast_build/tagstokens/check_syntax_tagstokens.c
"

for file in $FILE_TO_COPY
do
    newfile=$SHELL_REF/$file
    destfile=$SHELL_DEST/$file
    echo copy $newfile as $destfile
    cp $newfile $destfile
done
