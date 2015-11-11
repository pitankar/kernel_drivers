/*
 * Author: Piyush Itankar
 * Module: Demo Character Drive
 * Date:   10th Nov' 2015
 */

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include "pit.h"

// Init module
static int _init_(void){
    
    // Get a Major Number
    if ( 0 == alloc_chrdev_region( &pit_dev, 0, 1, "pit") )
      printk(KERN_ALERT "__ pit is here __ [ MAJOR:%d ]", pit_dev);
    else
      printk(KERN_ALERT "Failed to Register Device");
    
    pit_dev_area = kmalloc(sizeof(struct dev_area), GFP_KERNEL);
    memset(pit_dev_area, 0, sizeof(struct dev_area));

    pit_dev_area->pit_cdev.owner = THIS_MODULE;
    return 0;

}

// Exit Module
void _exit_(void){
 
    unregister_chrdev_region(pit_dev,1);
    kfree( pit_dev_area );
    printk(KERN_ALERT " __pit was here__ ");

}

module_init(_init_);
module_exit(_exit_);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Piyush Itankar, pitankar@gmail.com");

