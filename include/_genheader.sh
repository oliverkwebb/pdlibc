#!/bin/sh

for header in $@; do

exec > include/$header.h

UPPER=$(echo $header | tr 'a-z' 'A-Z')

cat << EOF
#ifdef _${UPPER}_H
#define _${UPPER}_H


#endif
EOF

shift
done
