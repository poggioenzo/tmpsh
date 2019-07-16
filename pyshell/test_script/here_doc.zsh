#!/usr/bin/env bash

if [ "$1" = 0 ]
then
    echo ok
else
    echo NoOk && echo stop 
    cat <<- EOF     < ~/.bash_history
            THE File        totest      s
EOF
fi

