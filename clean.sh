#!/bin/sh

sed -i -e 's/^ \+//'g -e 's/ \+/ /g' $1
