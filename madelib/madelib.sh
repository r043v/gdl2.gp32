#!/bin/sh
# Quick and dirty shellscript to change EABI verison of archives

if [ -z $DEVKITARM ]
then
  echo "Set DEVKITARM in your environment!"
fi

export PATH=$DEVKITARM/bin:$PATH

   objects=*.o
   for object in $objects
   do
     echo $object
     if [ -e $object ]
     then
       change-eabi $object

     fi
   done
   
   arm-eabi-ar -rcs lib.a $objects
   rm $objects