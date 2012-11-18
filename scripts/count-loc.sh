#!/bin/sh

cloc --write-lang-def=.lang
echo "PowerShell" >> .lang
echo "    filter remove_matches ^\s*#" >> .lang
echo "    extension ps1" >> .lang

cloc Makefile scripts src --read-lang-def=.lang --quiet

rm -f .lang

