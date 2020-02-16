# A-Simple-File-System

Implement utilities that perform operations on a file system similar to Microsoft’s FAT file system with some improvement.

Implementing:

./diskinfo test.img
	Will need to read the file system super block and use the information in the super block to read the FAT

./disklist test.img
	Will display the contents of the root directory or a given sub-directory in the file system
