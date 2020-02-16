diskinfo.c
This c file copies contents of a disk image file, into a struct using the appropriate addresses to read the content, which is then placed in a struct to be printable. The aim of this file is to print the superblock and FAT block info. 

disklist.c
This c file copies contents of a disk image file, by jumping the address location in the disk image in order to display the status where it is a file or directory, the it's size, the filename and creation date, time, year, etc. 
