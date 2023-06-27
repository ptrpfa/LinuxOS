obj-m += CSC1107_Group_2_kernel.o
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
ccflags-y += $(C_FLAGS)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CC) $(CFLAGS) CSC1107_Group_2_user.c -lssl -lcrypto -o CSC1107_Group_2_user

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm CSC1107_Group_2_user
