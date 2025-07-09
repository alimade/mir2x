#!/bin/bash

# needs apngasm from: https://github.com/apngasm/apngasm
# the legacy apngasm looks buggy and can not setup correct frame delay
#
# install
#
#       sudo add-apt-repository ppa:zero-tsuki/ppa
#       sudo apt-get update
#       sudo apt-get install apngasm

if [ $# -eq 0 ]
then
    echo "Usage: $0 <mhxy-icons-dir>"
    exit 1
fi

if [ ! -d $1 ]
then
    echo "Error: $1 is not a directory"
    exit 1
fi

cd $1

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 128 129
do
    if [ -f ${i}_1.png ]
    then
        apngasm -o out_${i}.png ${i}_*.png -F -d 150
    fi
done
