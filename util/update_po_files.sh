#!/bin/bash

for i in *.po
do 
	mv $i $i.old

	wget http://www.iro.umontreal.ca/translation/maint/wget/$i

	if test -f $i
	then 
		rm -f $i.old
	fi
done
