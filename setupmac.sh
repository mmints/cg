#!/bin/sh

BaseDir=cvws1617

sys=`uname -s`
if [ x$sys != xDarwin ] ; then
  echo " "
  echo "This script is for Mac OS X systems only (v10.7 or newer)"
  echo " "
  exit 2
fi

! command -v cmake > /dev/null && echo "Bitte erst 'cmake' installieren !!" && exit 1

echo " "
echo "Please choose your IDE:"
echo " "
echo " (1)  Eclipse with CDT"
echo " (2)  XCode"
echo " (3)  UNIX command line (make)"
echo " "

Gen=""
while [ x"$Gen" = x"" ]
  do
 printf "your choice (1-3): "
 read val
 case "$val" in
  1)
	Folder=BUILD_Eclipse; Gen="Eclipse CDT4 - Unix Makefiles"
	;;
  2)
	Folder=BUILD_Xcode; Gen="Xcode"
	;;
  3)
	Folder=BUILD_CLI; Gen="Unix Makefiles"
	;;
  *)
	echo "Wrong entry - please chose a number between 1 and 3"
	;;
 esac
done
# vorerst nur für Eclipse:

echo "Your choice: $Gen"

cd framework
fwdir=`pwd`
fail=""
for A in BV* CG*
  do
    [ -d "$A" ] || continue;
    cd $A
    [ -d "$Folder" ] || mkdir "$Folder"
    cd "$Folder"
    cmake -G"$Gen" ../src/
    status=$?
    if [ $status -ne 0 ] ; then fail="$fail $A/$Folder"; fi
    cd "$fwdir"
  done

if [ -z "$fail" ]
  then echo "Setup erfolgreich vorgenommen."
  else echo "\n!! Probleme bei der Erstellung von:\n     $fail"; exit 1
fi
exit 0
