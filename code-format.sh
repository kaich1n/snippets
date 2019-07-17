#!/usr/bin/env bash
[ $# -lt 1 ] && exit 1

#
# clang-format >= 3.8.0
# manual indent: clang-format off/on in source code
#
if [[ -z $CLANG_FORMAT ]] ; then
    CLANG_FORMAT=clang-format
fi

if NOT type $CLANG_FORMAT 2> /dev/null ; then
    echo "No appropriate clang-format found."
    exit 1
fi

SOURCE_FILES=`find $@ -type f \( -name '*.h' -o -name '*.c' -o -name '*.cpp' \)`
for i in $SOURCE_FILES
do
    $CLANG_FORMAT -i -style=file $i
done

