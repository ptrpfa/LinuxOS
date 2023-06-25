## Question 1: Kernel Hash Module
---

### Program Usage
1. Transfer all files to your Raspberry Pi under the `/linux/CSC1107_assignment/` directory.
2. Run the `Makefile` using the command:
    ```
    make
    ```
3. Open two terminals, one for viewing the `dmesg` outputs, and another for running commands.
4. On the first terminal, run the following command to keep viewing the `dmesg` contents:
    ```
    dmesg -wH
    ```
5. On the other terminal, insert the `CSC1107_Group_2_kernel.ko` module using the following command:
    ```
    sudo insmod CSC1107_Group_2_kernel.ko
    ```
    Observe the updates in the kernel ring buffer.
6. Run the user client program using the following command:
    ```
    sudo ./client
    ```
    Enter your hashing algorithm of choice and try to play around with the program. Observe the updates int he kernel ring buffer as well.
7. To clean up, run the following commands:
    ```
    sudo rmmod CSC1107_Group_2_kernel 
    make clean
    ```