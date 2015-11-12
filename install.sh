#/bin/bash

# Script to create a device entry in the /dev directory
# Add of remove the module

#Check if porperly executed
if [ $# -ne 1 ] 
then
  echo "Usage: $0 [ option: add/remove ]"
  exit
fi

#Add the module
if [ $1 = "add" ]
then
  insmod pit.ko
  mknod /dev/pit c 244 0
  echo "Module Pushed into the Kernel. Device Path /dev/pit"
  exit
fi

#Remove the module
if [ $1 = "remove" ]
then 
  rmmod pit
  rm /dev/pit
  echo "Module Removed from Kernel. Device /dev/pit is removed."
  exit
fi

exit
