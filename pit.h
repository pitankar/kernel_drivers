/******************************************
 * Author: Piyush Itankar
 * Module: Demo Character Drive
 * Date:   10th Nov' 2015
 ******************************************/

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<asm/uaccess.h>

/*
 * File operations Functions Prototypes
 */
static int pit_open(struct inode *, struct file *);
static ssize_t pit_read(struct file *, char *, size_t, loff_t *);
static ssize_t pit_write (struct file *, const char *, size_t, loff_t *);
static int pit_release(struct inode *, struct file *);

/*
 * Saves the Major and Minor number
 */
static dev_t pit_dev = 0;
static char buf;
/*
 * Devce structure. cbuff is on byte memory space
 * would be used to read and write a byte.
 */
struct dev_area{
  char cbuff;
  struct cdev pit_cdev;
} *pit_dev_area;

/*
 * File operations table for the device
 * Only OPEN, READ, WRITE and CLOSE calls to 
 * be supported so far
 */
struct file_operations pit_fops = {
	owner:   THIS_MODULE,
	open:    pit_open,
	read:    pit_read,
	write:   pit_write,
	release: pit_release
};
