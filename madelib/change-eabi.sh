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
   
   objects=*.o
   for object in $objects
   do
     echo $object
     if [ -e $object ]
     then
       change-eabi $object
     fi
   done
   rm $archive
   arm-eabi-ar -rcs $archive $objects
   rm $objects
  fi
done
