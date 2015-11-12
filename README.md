The Device Driver presented here is supposed to be the most basic one. As of now, it is able to allow 1byte worth of read and write.I have tried it with kernel 4.2 and seems to work fine. I am not sure if this will also work with Kernel versions prior to 2.6. Other details are as follows:
* The install.sh can be used to get started.
  - The script will make the modules.
  - create the device pit in /dev
  - remove the device entry
  - to install module use: ./install.sh add
  - to remove the module use: ./install.sh remove

* It is to be noted that as of now the Major number is hardcoded into the script. This might need to be changed by you in case ./install add fails. Or other wise you can yourself do things (Which would be better I guess)

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Working without using the install.sh script
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
1. get into the folder where these files live.
2. Change mode to root. Execute sudo su. Enter password. Done.
3. Enter the command:
   make clean
4. Followed  by:
   make all
5. Assuming no error occurs. Execute the following:
   insmod pit.ko
6. The Kernel module is now pushed into the kernel. In order for you to be able to use it. You need to create a file in /dev folder.
7. You would need the major number before you proceed. Get that by executing the following:
   dmesg | tail -10 | grep MAJOR
8. you should see a string [ MAJOR: xxx ] where xxx is the number you need.
9. Create an entry in /dev as follows:
   mknod /dev/pit c xxx 0
10. Now you can read and write a character into the file /dev/pit (the device)
11. To write use:
    echo "a">/dev/pit
12. To read use:
    cat /dev/pit
13. Done. That is what the driver does.
14. To uninstall use:
    rmmod pit

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

That's all :)

