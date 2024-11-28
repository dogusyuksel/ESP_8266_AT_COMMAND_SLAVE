#!/bin/bash

cd projects
current_dir=$(pwd)

files=$(find . -name 'sdkconfig.old')
while IFS= read -r line; do
   rm -rf $line 
done <<< "$files"

echo "returning success"
exit 0
