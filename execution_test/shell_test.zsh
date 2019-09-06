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

#Check depending of the arguments
#which file or folder have to be used.

if [ $# -eq 0 ]
then
    SCRIPTS=$(pwd)/scripts
elif [ $# -eq 1 ]
then
    SCRIPTS=$(pwd)/$1
else
    echo "$0: Too much arguments." >&2
    exit 1
fi

#Color for display

YELLOW="\033[0;1;33m"
GREEN="\033[0;1;32m"
RED="\033[0;1;31m"
RESET="\033[0;m"

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

	cd $SHELL_DIR
    display_name=$(basename $1)
    echo "${YELLOW}Test for ${display_name}:${RESET}"
    ./${SHELL_NAME} $1 > $user_output 2>&1 
    bash $1 > $bash_output 2>&1 
    diff $user_output $bash_output
    diff_res=$?
    rm -f $user_output $bash_output
    if [ $diff_res -eq 0 ]
    then
        echo "${GREEN}Sucess.${RESET}"
    else
        echo "${RED}Failure on $1.${RESET}"
    fi
	cd -
}

#Run each file of the given folder.

folder_test()
{
    local display_name

	#for filename in $SCRIPTS
    for filename in $(find ${SCRIPTS} -type f | grep -Ev ".*.sw[pno]")
	do
        file_test $filename
	done
}

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
