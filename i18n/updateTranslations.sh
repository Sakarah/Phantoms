#!/bin/bash
find ../src -name "*.cpp" -or -name "*.h" > src-files
xgettext --files-from=src-files --from-code utf-8 -ktr -k_tr_ -kwtr -kntr:1,2 -knftr:1,2 -kwnftr:1,2 -o phantoms.pot
rm src-files

for lang in *
do
    if [ -d $lang ]
    then 
        msgmerge $lang/$lang.po phantoms.pot -U
    fi
done
