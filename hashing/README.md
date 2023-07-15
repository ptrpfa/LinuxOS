## Question 1: Linux Kernel Module, User Space Application & Bash Script
---
### Script Automation
To enable the automated running of the bash script upon startup, perform the following steps:
1. Create a `count.txt` counter file in your user's home directory, whilst ensuring the counter value is initialised to `0`. An example is shown below:
    ```
    echo 0 > /home/pi/count.txt
    ```
2. Add the following code (also available [here](bashrc.sh)) to the end of your `.bashrc` file, ensuring that the file paths are pointing to the correct files:
    ```
    # Open .bashrc file on a text editor
    nano ~/.bashrc

    # Add the following code to the end of your ~/.bashrc file:

    # Initialise variables
    SCRIPT="/linux/CSC1107_assignment/CSC1107_Group_2.sh"
    COUNTER_FILE="/home/pi/count.txt"
    COUNTER=$(cat $COUNTER_FILE)

    # Check if counter value exceeds 3
    if [ $COUNTER -le 2 ]; then
        # Run script
        sudo $SCRIPT
        # Increment counter
        ((COUNTER++))
        # Update counter file with updated counter value
        echo $COUNTER > $COUNTER_FILE
    fi
    ```
    Adding these instructions in your ~/.bashrc file will allow the automated execution of the script during startup for up to 3 times.
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
    *Ensure that all source code files and folders are present in the `source_dir` !*

3. Run the bash script using the following command:
    ```
    sudo ./CSC1107_Group_2.sh
    ```

    A demo run of the bash script is provided below or [here](https://www.youtube.com/watch?v=XhTe-5jQOa4):
    [![Bash Script Demo](/docs/bash_1.png)](https://www.youtube.com/watch?v=XhTe-5jQOa4)
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
    make complete
    ```

    The `complete` option automates the following steps, which could be executed independently to build and compile both the user and kernel space programs separately:
    - Build and compile loadable Linux kernel module
        ```
        make
        ```
    - Compile user space program
        ```
        gcc CSC1107_Group_2_user.c -Wall -Wextra -Werror -pedantic -std=c99 -lssl -lcrypto -o CSC1107_Group_2_user    

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
    make complete_clean
    ```

    A sample of the program output is provided below:
    ![Standalone_1](/docs/standalone_1.png)
    ![Standalone_2](/docs/standalone_2.png)
