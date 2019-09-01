#!/bin/zsh

#Directory and name of the shell

SHELL_DIR="/Users/simrossi/Documents/tmpsh"
SHELL_NAME="tmpsh"

#Files to test

SCRIPT_DIR=scripts

SCRIPTS=$(find $(pwd)/${SCRIPT_DIR} -type f)

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

	for filename in "$SCRIPTS"
	do
        echo LOOP
        echo "|$filename|"
        echo END
        display_name=$(basename $filename)
		echo "${GREEN}Test for ${display_name}:${RESET}"
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
