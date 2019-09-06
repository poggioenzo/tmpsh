#!/bin/zsh

#Directory and name of the shell

if [ "$USER" = epoggio ]
then
	SHELL_DIR=~/git/tmpsh
else if [ "$USER" = simrossi ]
	SHELL_DIR=~/Documents/tmpsh
fi
SHELL_NAME="tmpsh"

#Files to test

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

file_test()
{
    local display_name

	cd $SHELL_DIR
	
    display_name=$(basename $1)
    echo "${YELLOW}Test for ${display_name}:${RESET}"
    diff <(./${SHELL_NAME} $1 2>&1) <(bash $1 2>&1)
    if [ $? -eq 0 ]
    then
        echo "${GREEN}Sucess.${RESET}"
    else
        echo "${RED}Failure.${RESET}"
    fi
	cd -
}

folder_test()
{
    local display_name

	#for filename in $SCRIPTS
    for filename in $(find ${SCRIPTS} -type f | grep -Ev ".*.sw[pno]")
	do
        file_test $filename
	done
}

export TEST_42SH=True
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
