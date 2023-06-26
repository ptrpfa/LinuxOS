#!/bin/bash

#1
echo "Current user:"
whoami

#2
echo "Current working directory:"
pwd

#3
sudo adduser --force-badname CSC1107_Group_2
echo "New user created"

#4
sudo sed -i 's/CSC1107_Group_2:\/bin\/sh/CSC1107_Group_2:\/bin\/bash/' /etc/passwd
echo "Changed default shell"

#5
grep CSC1107_Group_2 /etc/passwd

#6
folder_name="Folder_Group_2" 			#rmb to chg directory accordingly
home_dir="/home"				#rmb to chg directory accordingly

if [-d "$home_dir/$folder_name"]; then
	echo "Deleting $folder_name"
	rm -rf "$home_dir/$folder_name"
else
	echo "Creating $folder_name"
	mkdir "$home_dir/$folder_name"
fi

#7
cd "$home_dir/$folder_name"

#8
source_dir="/home/pi/linux/CSC1107_assignment" 	#rmb to change directory accordingly
cp "$source_dir/CSC1107_Group_2_kernel.c" .
cp "$source_directory/CSC1107_Group_2_user.c" .
cp "$source_directory/Makefile" .
echo "Successfully copied 3 files"

#9
make
echo "Compiled successfully"

#10
ls

#11
sudo insmod CSC1107_Group_2.ko
echo "Inserted kernel module"

#12
lsmod | grep CSC1107_Group_2_kernel

#13
modinfo CSC1107_Group_2_kernel.ko

#14
echo "Last 5 messages in the kernel log buffer: "
dmesg | tail -n 5

#15
gcc CSC1107_Group_2_user.c -o CSC1107_Group_2_user
echo "Compiled user space application program"

#16
echo "Executing..."
./CSC1107_Group_2_user

#17 - no action by bash script
#18 - no action by bash script

#19
echo "Last 12 lines of syslog:"
tail -n 12 /var/log/syslog

#20
sudo rmmod CSC1107_Group_2_kernel
echo "Removed loadable kernel module"

#21
echo "Last 3 messages of kernel log buffer:"
dmesg | tail -n 3

#22
sudo deluser CSC1107_Group_2
echo "Successfully deleted user"

#23
grep CSC1107_Group_2 /etc/passwd

#24
echo "Current working dir:"
pwd

#25
ls

#26
echo "The bash shell script of CSC1107_Group_2 has finished all tasks, and stop here."
