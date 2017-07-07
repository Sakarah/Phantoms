#!/bin/bash
for lang in *
do
    if [ -d $lang ]
    then 
        mkdir -p $lang/LC_MESSAGES
        msgfmt -o $lang/LC_MESSAGES/phantoms.mo $lang/$lang.po
    fi
done
