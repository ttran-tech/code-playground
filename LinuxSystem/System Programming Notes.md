# System Programming Notes

## System Calls
- *System calls* (*syscalls*) - are functions invocation that made from user space into the kernel to request some service or resources from the OS.

- Example of system calls:
    - ```read()```, ```write()```, ```get_thread_area()```, ```set_tid_address()```, etc.

### Invoke Syscalls
- Usermode applications are not allow to directly execute kernel code or manipulate kernel data.

## Kernel
- The core of the Operation System (OS).