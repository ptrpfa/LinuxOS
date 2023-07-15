obj-m += CSC1107_Group_2_kernel.o
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
ccflags-y += $(C_FLAGS)
MODULE = CSC1107_Group_2_kernel

# Default option to build loadable Linux kernel module
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Option to install loadable Linux kernel module
install:
	rmmod $(MODULE)
	insmod $(MODULE).ko

# Option to clean loadable Linux kernel module files
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# Option to build user space program
user:
	$(CC) $(CFLAGS) CSC1107_Group_2_user.c -lssl -lcrypto -o CSC1107_Group_2_user

# Option to clean user space program files
user_clean:
	rm CSC1107_Group_2_user

# Option to build both loadable Linux kernel module and user space programs
complete:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CC) $(CFLAGS) CSC1107_Group_2_user.c -lssl -lcrypto -o CSC1107_Group_2_user

# Option to clean both loadable Linux kernel module and user space program files
complete_clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm CSC1107_Group_2_user