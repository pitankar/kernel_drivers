/*
 * Author: Piyush Itankar
 * Module: Demo Character Drive
 * Date:   10th Nov' 2015
 */

static dev_t pit_dev;

struct dev_area{
  char cbuff;
  struct cdev pit_cdev;
} *pit_dev_area;
