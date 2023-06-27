#!/bin/bash

# Variables
NEW_USER=CSC1107_Group_2
home_dir=$(sudo -u "$SUDO_USER" -H sh -c 'echo $HOME')	#rmb to chg directory accordingly
folder_name="Folder_Group_2" 							#rmb to chg directory accordingly
source_dir="/linux/CSC1107_assignment" 					#rmb to change directory accordingly

# 1) Display the currently logged-in user in the Raspberry Pi on the screen.
echo -e "1) Current user:"
whoami

# 2) Display the current working directory on the screen.
echo -e "\n2) Current working directory:"
pwd

# 3) Create a new user in the OS named: CSC1107_Group_2
echo -e "\n3) Adding new user $NEW_USER.."
sudo adduser --force-badname $NEW_USER
echo -e "\nNew user created! Default shell is:"
cat /etc/passwd | grep "$NEW_USER" | cut -d ':' -f 7

# 4) Change the default shell for this new user from sh into bash in the file /etc/passwd.
sudo sed -i 's/CSC1107_Group_2:\/bin\/sh/CSC1107_Group_2:\/bin\/bash/' /etc/passwd
echo -e "\n4) Changed default shell to:"
cat /etc/passwd | grep "$NEW_USER" | cut -d ':' -f 7

# 5) Display the line containing the new user CSC1107_Group_2 in the file /etc/passwd on the screen using the grep command. It is to visual check if the default shell has been changed into bash for this new user.
echo -e "\n5) /etc/passwd entry for new user:"
grep CSC1107_Group_2 /etc/passwd

# 6) Check if the folder named Folder_Group_2 exists in your home directory. If yes, then delete the folder and all files inside. If not existing, then create a new folder here named Folder_Group_2.
if [ -d "$home_dir/$folder_name" ]; then
	echo -e "\n6) Deleting $home_dir/$folder_name and recreating it"
	rm -rf "$home_dir/$folder_name"
	mkdir "$home_dir/$folder_name"
else
	echo -e "\n6) Creating $home_dir/$folder_name"
	mkdir "$home_dir/$folder_name"
fi

# 7) Change directory into this new folder: Folder_Group_2
echo -e "\n7) Changing directory.."
cd "$home_dir/$folder_name"
echo -e "\nCurrent working directory:"
pwd

# 8) Copy the three files from the folder /linux/CSC1107_assignment/ into the new folder
sudo cp "$source_dir/CSC1107_Group_2_kernel.c" "$source_dir/CSC1107_Group_2_user.c" "$source_dir/Makefile" .
sudo cp -r "$source_dir"/* .
echo -e "\n8) Successfully copied 3 files (and other miscellaneous files!)\n"

# 9) Compile the loadable kernel module from CSC1107_Group_2_kernel.c using the Makefile utility.
make
echo -e "\n9) Compiled successfully"

# 10) List all files in the current folder.
echo -e "\n10) All files in the folder:"
ls -lR

# 11) Insert the compiled loadable kernel module into the Linux kernel.
sudo insmod CSC1107_Group_2_kernel.ko
echo -e "\n11) Inserted kernel module"

# 12) Use the Linux commands containing both lsmod and grep to display the information if this new loadable kernel module has been inserted to the kernel successfully.
echo -e "\n12) Kernel module loaded:"
lsmod | grep CSC1107_Group_2_kernel

# 13) Use modinfo command to display this loadable kernel module information.
echo -e "\n13) Kernel module information:"
modinfo CSC1107_Group_2_kernel.ko

# 14) Use dmesg command to display the last 5 messages in the kernel log buffer.
echo -e "\n14) Last 5 messages in the kernel log buffer: "
dmesg | tail -n 5

# 15) Compile the user space application program CSC1107_Group_2_user.c into an executable user space application named CSC1107_Group_2_user.
# This step is actually completed already in step 9
gcc CSC1107_Group_2_user.c -Wall -Wextra -Werror -pedantic -std=c99  -lssl -lcrypto -o CSC1107_Group_2_user
echo -e "\n15) Compiled user space application program"

#16) Invoke and execute the executable user space program, CSC1107_Group_2_user
echo -e "\n16) Executing user space program...\n(No action by bash script for steps 17 & 18!)\n"
sudo ./CSC1107_Group_2_user

# 17) - no action by bash script
# {Not for action by the bash shell script} Observe the printed-out message on the screen. When the user space application program displays the message on the screen 
# to indicate that it is waiting for the user keyboard input, either by “Enter” key or “Space” key. Please key in “Enter” or “Space” on your keyboard by the user.

# 18) - no action by bash script
# {Not for action by the bash shell script} Observe the printed-out message on the screen if the user space program prints out the messages for five items highlighted 
# in red font on the top of Page 4. The user space application program should stop all operations now. 

# 19) Use the Linux command to display the last 12 lines of the /var/log/syslog file, in order to check if the messages printed in the /var/log/syslog file by the program.
echo -e "\n19) Last 12 lines of syslog:"
tail -n 12 /var/log/syslog

# 20) Next, it is time to remove the loadable kernel module from the Linux kernel. Use the Linux command to remove it. 
sudo rmmod CSC1107_Group_2_kernel
echo -e "\n20) Removed loadable kernel module"

# 21) Use dmesg command to display the last 3 messages in the kernel log buffer. It is to see if the loadable kernel module is removed successfully. 
echo -e "\n21) Last 3 messages of kernel log buffer:"
dmesg | tail -n 3

# 22) Delete the user CSC1107_Group_2 from the OS of your Raspberry Pi. 
sudo deluser $NEW_USER
sudo rm -rf /home/CSC1107_Group_2
echo -e "\n22) Successfully deleted user"

# 23) Display if the line containing the new user CSC1107_Group_2 is still in the file /etc/passwd on the screen using the grep command. If return nothing, it means the user name is deleted successfully. 
if grep -q "CSC1107_Group_2" /etc/passwd; then
  echo -e "\n23) User 'CSC1107_Group_2' is still present!"
else
  echo -e "\n23) User 'CSC1107_Group_2' is deleted successfully!"
fi

# 24) Display the current working directory on the screen.
echo -e "\n24) Current working dir:"
pwd
# 25) List all the files in the current working directory.
echo -e "\n25) All files in the current working directory:"
ls -lR

# 26) Print a message on the screen “The bash shell script of CSC1107_Group_2 has finished all tasks, and stop here.”. 
echo -e "\n26) The bash shell script of CSC1107_Group_2 has finished all tasks, and stop here."
