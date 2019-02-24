#include <linux/kernel.h>   // For printk
#include <linux/string.h>   // For strcpy, strcat, strlen
#include <linux/slab.h>     // For kmalloc, kfree
#include <linux/uaccess.h>  // For copy_from_user, copy_to_user
#include <linux/syscalls.h> // For SYSCALL_DEFINE4

// Definition of the system call
SYSCALL_DEFINE4(hello_world,
  const char __user *, str,    // Input name
  const unsigned int, str_len, // Length of input name
  char __user *, buf,          // Output buffer
  unsigned int, buf_len) {     // Length of output buffer
  // The kernel stack variable supposed to keep the content
  // of the input buffer
  char name[64];
  // The kernel stack variable supposed to keep the final
  // output message.
  char message[96];

  printk("System call fired!\n");
  if (str_len >= 64) {
    printk("Too long input string.\n");
    return -1;
  }

  // Copy data from user space into kernel space
  if (copy_from_user(name, str, str_len)) {
    printk("Copy from user space failed.\n");
    return -2;
  }

  // Build up the final message
  strcpy(message, "Hello ");
  strcat(message, name);
  strcat(message, "!");

  // Check if the final message can be fit into the output binary
  if (strlen(message) >= (buf_len - 1)) {
    printk("Too small output buffer.\n");
    return -3;
  }

  // Copy back the message from the kernel space to the user space
  if (copy_to_user(buf, message, strlen(message) + 1)) {
    printk("Copy to user space failed.\n");
    return -4;
  }

  // Print the sent message into the kernel log
  printk("Message: %s\n", message);
  return 0;
}
