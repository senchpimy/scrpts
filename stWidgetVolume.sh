#!/bin/bash
showalsamixer(){
killall stWidget
stWidget -z 8 -g 30x40+1195+20 -e alsamixer
}

case $BUTTON in 
	1)stWidget -z 8 -g 30x40+1195+20 -e alsamixer;;
	2)killall stWidget;;
esac

