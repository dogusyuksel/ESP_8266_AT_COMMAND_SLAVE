#!/bin/bash

if [ "$#" -eq 1 ]; then
    cd $1

    make clean && make

    retval=$?
    if [ $retval -ne 0 ]
    then
        echo "returning fail:$retval"
        exit $retval
    fi
    echo "build success for $1"
    exit 0
fi

cd projects
current_dir=$(pwd)

files=$(find . -iname 'makefile')
while IFS= read -r line; do
    parentdir="$(dirname "$line")"
    echo ""
    echo "============== navigating $current_dir/$parentdir directory =============="
    cd $current_dir/$parentdir

    make clean && make

    retval=$?
    if [ $retval -ne 0 ]
    then
        echo "returning fail:$retval"
        exit $retval
    else
        echo "============== leaving $current_dir/$parentdir directory successfully =============="
    fi
done <<< "$files"

echo "returning success"
exit 0
