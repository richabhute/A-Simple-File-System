#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

struct __attribute__((__packed__)) superblock{
    uint8_t   fs_id[8];
    uint16_t  block_size;
    uint32_t  file_system_block_count;
    uint32_t  fat_start_block;
    uint32_t  fat_block_count;
    uint32_t  root_dir_start_block;
    uint32_t  root_dir_block_count;
};

struct __attribute__((__packed__)) dir_entry{
    uint8_t status;
    uint32_t starting_block;
    uint32_t block_count;
    uint32_t size;
    //struct dir_entry_timedate create_time;
    //struct dir_entry_timedate modify_time;
    uint8_t filename[31];
    uint8_t unused[6];
};

struct __attribute__((__packed__)) dir_entry_timedate{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};


int print_DirList(int fd, struct stat buffer)
{
    //int status = fstat(fd, &buffer);
    char* address = mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
    struct superblock* block;
    block = (struct superblock*)address; 

    int blocksize = 0;
    memcpy(&blocksize, address+8, 2);
    blocksize = htons(blocksize);
    
    //Root Info. Extract

    int rootStart = ntohl(block->root_dir_start_block);
    int rootBlocks =  ntohl(block->root_dir_block_count);
    
    int pos_start = blocksize*rootStart;
    int pos_end = blocksize*(rootBlocks+rootStart);
    
    int count = 0;

    while(pos_start < pos_end)
    {
        struct dir_entry* root;
        root = (struct dir_entry*)address+pos_start;

        int status=0;
        memcpy(&status, address+pos_start, 1);
     
        if(status==3)
        {
            printf("F ");
        }else if(status == 5)
        {
            printf("D ");
            
        }else
        {
            break;
        }

        //Printing out Size and Filename

        int size;
        char filename[31];
        memcpy(&size, address+pos_start+9, 4);
        size = ntohl(size);   
        strcpy(filename, address+pos_start+27);

        printf("%d\t%s ", size, filename);
        
        //Printing Time

        int year, month, date;
        memcpy(&year,address+pos_start+13, 2);
        year = htons(year);
        memcpy(&month,address+pos_start+15, 1);
        memcpy(&date,address+pos_start+16, 1);

        printf("%d/%d/%d ", year, month, date);

        int hour, min, sec;
        memcpy(&hour, address+pos_start+17, 1);
        memcpy(&min, address+pos_start+18, 1);
        memcpy(&sec, address+pos_start+19, 1);

        printf("%d:%d:%d ", hour, min, sec);
          
        printf("\n");

        pos_start = pos_start + 64;     
    }   
    return 0;
}

int main(int argc, char* argv[]) 
{
    int fd = open(argv[1], O_RDWR);
 	struct stat buffer;

    print_DirList(fd, buffer);

    //close(fd);   
}








