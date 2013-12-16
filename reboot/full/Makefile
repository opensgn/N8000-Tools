all: clean
	gcc -c __reboot.S
	gcc -c __set_errno.cpp
	gcc -c android_reboot.c
	gcc -c reboot.c
	gcc -s *.o -o reboot

clean:
	rm -f reboot *.o
