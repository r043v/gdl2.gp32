#!/bin/sh
# Quick and dirty shellscript to change EABI verison of archives

if [ -z $DEVKITARM ]
then
  echo "Set DEVKITARM in your environment!"
fi

export PATH=$DEVKITARM/bin:$PATH

for archive in *.a 
do
 if [ -e $archive ]
 then

   arm-eabi-ar -x $archive
 fi
done
