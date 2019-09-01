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
    SCRIPT_DIR=$(pwd)/scripts
elif [ $# -eq 1 ]
then
    SCRIPT_DIR=$(pwd)/$1
else
    echo "$0: Too much arguments." >&2
    exit 1
fi

#Color for display

YELLOW="\033[0;1;33m"
GREEN="\033[0;1;32m"
RED="\033[0;1;31m"
RESET="\033[0;m"

run_tests()
{
    local display_name

	cd $SHELL_DIR
	
	echo "${YELLOW}< Your output | bash output >${RESET}\n"

	#for filename in $SCRIPTS
    for filename in $(find ${SCRIPT_DIR} -type f | grep -Ev ".*.sw[pno]")
	do
        display_name=$(basename $filename)
		echo "${YELLOW}Test for ${display_name}:${RESET}"
		diff <(./${SHELL_NAME} $filename) <(bash $filename)
		if [ $? -eq 0 ]
		then
			echo "${GREEN}Sucess.${RESET}"
		else
			echo "${RED}Failure.${RESET}"
		fi
	done
	cd -
}

run_tests
