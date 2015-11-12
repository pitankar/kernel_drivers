#/bin/bash

# Script to create a device entry in the /dev directory
# Add of remove the module

#Check if porperly executed
if [ $# -ne 1 ] 
then
  echo "Usage: $0 [ option: add/remove ]"
  exit
fi

#Remove the module
if [ $1 = "remove" ]
then 
  rmmod pit
  if [ $? -ne 0 ]
  then
    echo "Module not present. Cannot Unload. Exitting."
    exit
  fi
  rm /dev/pit
  echo "Module Removed from Kernel. Device /dev/pit is removed."
  
  # Keep the directory Clean
  make clean
  
  exit
fi

# Clean Modules
make clean

# Create Modules
make all

# Things went wrong. Report
if [ $? -ne 0 ]
then
  echo "Make Failed"
  exit
fi

#Add the module
if [ $1 = "add" ]
then
  insmod pit.ko
  mknod /dev/pit c 244 0
  echo "Module Pushed into the Kernel. Device Path /dev/pit"
  
  # Keep the directory Clean
  make clean
  
  exit
fi

exit
