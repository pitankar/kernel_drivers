The Device Driver presented here is supposed to be the most basic one. As of now, it is able to allow 1byte worth of read and write.I have tried it with kernel 4.2 and seems to work fine. I am not sure if this will also work with Kernel versions prior to 2.6. Other details are as follows:
* The install.sh can be used to get started.
  - The script will make the modules.
  - create the device ***pit*** in /dev
  - remove the device entry
  - to install module use: 
  ```
  ./install.sh add
  ```
  - to remove the module use: 
  ```
  ./install.sh remove
  ```
- To write use:
  ```
  $ echo "a">/dev/pit
  ```
- To read use:
  ```
  $ cat /dev/pit
  ```
- Done. That is what the driver does.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

That's all :)

