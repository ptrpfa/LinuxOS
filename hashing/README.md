## Question 1: Linux Kernel Module, User Space Application & Bash Script
---
### Script Usage
1. Transfer all project files to your Raspberry Pi under the `/linux/CSC1107_assignment/` directory. You can run the following commands to do so:
    ```
    # On Raspberry Pi
    sudo mkdir /linux/CSC1107_assignment
    mkdir ~/Desktop/transfers

    # On host machine (transfer files to Raspberry Pi's ~/Desktop/transfers directory)
    cd <directory containing project files>
    scp -r * <username>@<domain or IP address>:~/Desktop/transfers 

    # On Raspberry Pi
    sudo mv ~/Desktop/transfers/* /linux/CSC1107_assignment
    ```

2. Ensure all folders in the `CSC1107_Group_2.sh` bash script's variables are defined correctly:
    ```
    NEW_USER=CSC1107_Group_2
    home_dir=$(sudo -u "$SUDO_USER" -H sh -c 'echo $HOME')	
    folder_name="Folder_Group_2" 							
    source_dir="/linux/CSC1107_assignment"
    ```
    *Ensure that all source code files and folders are in the present in the `source_dir` !*

3. Run the bash script using the following command:
    ```
    sudo ./CSC1107_Group_2.sh
    ```

    A demo run of the bash script is provided below:
    [![Bash_Run](/docs/bash_1.png)](/docs/bash_run.mov)
    Screenshots:
    ![Bash_1](/docs/bash_1.png)
    ![Bash_2](/docs/bash_2.png)
    ![Bash_3](/docs/bash_3.png)
    ![Bash_4](/docs/bash_4.png)
    ![Bash_5](/docs/bash_5.png)

## Standalone Usage: Kernel Hash Module
---
To just run the Linux Kernel Module and its User Space application, following the instructions below.

### Program Usage
1. Transfer all project files to your Raspberry Pi under the `/linux/CSC1107_assignment/` directory. You can run the following commands to do so:
    ```
    # On Raspberry Pi
    sudo mkdir /linux/CSC1107_assignment
    mkdir ~/Desktop/transfers

    # On host machine (transfer files to Raspberry Pi's ~/Desktop/transfers directory)
    cd <directory containing project files>
    scp -r * <username>@<domain or IP address>:~/Desktop/transfers 

    # On Raspberry Pi
    sudo mv ~/Desktop/transfers/* /linux/CSC1107_assignment
    ```
2. Run the `Makefile` using the command:
    ```
    cd /linux/CSC1107_assignment
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
    sudo ./CSC1107_Group_2_user
    ```
    Enter your hashing algorithm of choice and try to play around with the program. Observe the updates in the kernel ring buffer as well.
7. To clean up, run the following commands:
    ```
    sudo rmmod CSC1107_Group_2_kernel 
    make clean
    ```

    A sample of the program output is provided below:
    ![Standalone_1](/docs/standalone_1.png)
    ![Standalone_2](/docs/standalone_2.png)
