#!/bin/zsh

#Directory and name of the shell

if [ "$USER" = epoggio ]
then
	SHELL_DIR=~/git/tmpsh
else if [ "$USER" = simrossi ]
	SHELL_DIR=~/Documents/tmpsh
fi

SHELL_NAME="tmpsh"
TEST_DIRECTORY=$(pwd)/
SHELL_EXECUTABLE=${TEST_DIRECTORY}../${SHELL_NAME}

#Check depending of the arguments
#which file or folder have to be used.



#Color for display

YELLOW="\033[0;1;33m"
GREEN="\033[0;1;32m"
RED="\033[0;1;31m"
RESET="\033[0;m"

create_memcheck_file()
{
    local directory;
    local filename;

    directory=$(dirname $1)
    filename=$(basename $1)
    echo $directory/.$filename.memcheck
}

#Perfom the test of single file, compare the bash output with
#the given shell.
#Run the user shell with the given script, and do the same with
#bash. Compare the result of both output.

file_test()
{
    local display_name
    local user_output="${TEST_DIRECTORY}.user_file_output.test"
    local bash_output="${TEST_DIRECTORY}.bash_file_output.test"
    local diff_res
    local memcheck_file

    #Display filename before the test.
    display_name=$(basename $1)
    echo "${YELLOW}Test for ${display_name}:${RESET}"

    #Perform the test. Redirect tested shell's ouput and
    #bash's output in different files.
    #Diff them at the end.
    #
    #Use Valgrind if expected
    if [ "$VALGRIND" = "true" ]
    then
        memcheck_file=$(create_memcheck_file $1)
        local valgrind_command="valgrind --leak-check=full
            --show-leak-kinds=all "
        valgrind_command+=" --log-file=$memcheck_file"
        $(echo $valgrind_command) ${SHELL_EXECUTABLE} $1 > $user_output 2>&1 
    else
        ${SHELL_EXECUTABLE} $1 > $user_output 2>&1 
    fi
    bash $1 > $bash_output 2>&1 
    diff $user_output $bash_output
    diff_res=$?

    #Clean up the test
    rm -f $user_output $bash_output

    #Display success or failure message
    if [ $diff_res -eq 0 ]
    then
        echo "${GREEN}Sucess.${RESET}"
    else
        echo "${RED}Failure on $1.${RESET}"
    fi
}

#Run each file of the given folder.

folder_test()
{
    local display_name

	#for filename in $SCRIPTS
    for filename in $(find ${SCRIPTS} -type f | grep -Ev -e ".*.sw[pno]" -e ".*.memcheck")
	do
        file_test $filename
	done
}

VALGRIND=false
usage()
{
    echo "Syntax : $1 [-h] [-l] [filename | foldername]"
}

# Check if -l options is activate, to leave valgrind logs

while getopts ":l" opt; do
    case $opt in
      l)
          VALGRIND=true
          ;;
      \?)
          echo "Invalid option: -$OPTARG" >&2
          ;;
    esac
done

shift $((OPTIND - 1))

# Use scripts folder by default.
# Otherwise, use given folder or filename to perfom the test.

if [ $# -eq 0 ]
then
    SCRIPTS=$(pwd)/scripts
elif [ $# -eq 1 ]
then
    SCRIPTS=$(pwd)/$1
else
    echo "$0: Too many arguments."
    usage $0 && exit 1
fi

#Depending of user argument, run a single file, or each file
#of the given folder.

if [ -d "$SCRIPTS" ]
then
	echo "${YELLOW}< Your output | bash output >${RESET}\n"
    folder_test
elif [ -f "$SCRIPTS" ]
then
	echo "${YELLOW}< Your output | bash output >${RESET}\n"
    file_test $SCRIPTS
else
    echo "$0: $1 is not an allowed file type." >&2
fi
