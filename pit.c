/******************************************
 * Author: Piyush Itankar
 * Module: Demo Character Drive
 * Date:   10th Nov' 2015
 ******************************************/

#include "pit.h"

// Open
static int pit_open(struct inode *inode, struct file *filp){
    struct dev_area *dev;
    
    dev = container_of(inode->i_cdev, struct dev_area, pit_cdev);
    filp->private_data = dev;

    printk(KERN_ALERT "pit: OPEN call\n");
    return 0;
}

// Read
static ssize_t pit_read(struct file *fp, char __user *buff, size_t count, loff_t *off){
    struct dev_area *dev;
    dev = fp->private_data;

    if( *off == 0 ){
      mutex_lock_interruptible( &dev->m );
        copy_to_user( buff, &dev->cbuff, 4);
        printk(KERN_ALERT "pit: READ call");	
      mutex_unlock( &dev->m );

      (*off)++;
      return 1;
    }

    return 0;
}

// Write
static ssize_t pit_write (struct file *fp, const char __user *buff, size_t count, loff_t *off){
    struct dev_area *dev;

    dev = fp->private_data;
    mutex_lock_interruptible( &dev->m );
      copy_from_user( &dev->cbuff, buff, 1 );
      printk(KERN_ALERT "pit: WRITE call");
    mutex_unlock( &dev->m );

    return count ;
}

// Release
static int pit_release(struct inode *inode, struct file *filp){
    printk(KERN_ALERT "pit: RELEASE call");
    return 0;
}

// Init module
static int _init_(void){
    // Get a Major Number
    if ( 0 == alloc_chrdev_region( &pit_dev, 0, 1, "pit") )
      printk( KERN_EMERG "pit: __pit is here __ [ MAJOR:%d, MINOR:%d ]", MAJOR(pit_dev), MINOR(pit_dev) );
    else
      printk( KERN_ALERT "Failed to Register Device" );
    
    pit_dev_area = kmalloc( sizeof(struct dev_area), GFP_KERNEL );
    memset( pit_dev_area, 0, sizeof(struct dev_area) );

    pit_dev_area->pit_cdev.owner = THIS_MODULE;
    cdev_init( &pit_dev_area->pit_cdev, &pit_fops );

    pit_class = class_create( THIS_MODULE, "chardrv" );
    device_create( pit_class, NULL, pit_dev, NULL, "pit" );
    mutex_init( &pit_dev_area->m );

    cdev_add( &pit_dev_area->pit_cdev, pit_dev, 1 );
    return 0;
}

// Exit Module
void _exit_( void ){
    cdev_del( &pit_dev_area->pit_cdev );
    device_destroy( pit_class, pit_dev );
    class_destroy( pit_class );
    unregister_chrdev_region( pit_dev, 1 );
    kfree( pit_dev_area );
    printk( KERN_ALERT " __pit was here__ " );
}

module_init( _init_ );
module_exit( _exit_ );

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Piyush Itankar, <pitankar@gmail.com>" );
MODULE_DESCRIPTION( "Simple Character Driver" );
