#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char * argv[]){
	int fd;
	// this is the address to which the file will be mapped to process' address space
	void * fileMemory;
	int readValue;

	//create file which will be mapped
	fd = open("./toread.txt", O_RDWR , S_IRUSR | S_IWUSR );

	// mapping to address space
	// 1st arg- address of the process address space where the file will be mapped to
	// 2nd arg- length of the file in bytes that will be mapped into the address space
	// 3rd arg- Write permission is given
	// 4th arg- Because of MAP_SHARED value any change made to the file will be visible to other
	// process sharing the file immediately
	// 5th arg- the file descriptor pointer
	fileMemory = mmap( 0, 0x10, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0 );

	//once the mapping has been created there's no point in keeping the file open
	//so close it down
	close( fd );

	// now you are free to write to the memory map
	scanf( fileMemory, "%d", &readValue );

	// release the memory i.e. unmap the memory
	munmap( fileMemory, 0x10 );

}
