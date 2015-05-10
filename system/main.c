/*  main.c  - main */
/* Sample test case for lab 6 */

#include <xinu.h>


int main(int argc, char **argv)
{
	char wbuff[] = {"While disks provide a convenient means of permanent storage, they support only a simple and limited naming mechanism of the data they hold (the block number). File systems are used to overcoming this limitation by providing a more elaborate and useful naming mechanism for the data blocks on a disk. This original Xinu File System is a mini-file system with an elegant design that has a limited numbers of files, short file names, and no hierarchical directory structure; however, it allows files to grow dynamically. \r\nThe objective of this lab is to enhance the existing file system for Xinu. You will extend the functionality of the Xinu File System on top of the remote disk abstraction. You are going to transform the current flat file system into a new file system with hierarchical directory structure. \r\n"};
	int32 wbufflen = sizeof( wbuff );
	char rbuff[ wbufflen * 10 ];
	int32 rbufflen = sizeof( rbuff );
	int32 retval;
	int32 fd[10];
	int32 i, j;

	kprintf("Open remote disk\r\n");
	retval = open(RDISK,"XinuDisk","rw");
	if (retval == SYSERR){
		panic("Error: could not open the remote disk, check the server\n\r");
	}

	kprintf("Initializing file system\r\n");
	retval = lfscreate ( RDISK, 1000, 1024000);
	if( retval == SYSERR )
		panic("Initialize file system failed");

	kprintf("\r\nList root directory:\r\n");
	retval = lflistdirh( LFILESYS, "/" ); //list root dir
	if( retval == SYSERR )
		kprintf("Listing failed\r\n");
		
	// Create 5 directories
    /*
	char dirname [] = {"/DIR_1"};
	kprintf("\r\n");
	for( i=0; i<5; i++){
		dirname[5] = '1'+i;
		kprintf("Creating directory %s", dirname );
		retval = control(LFILESYS, LF_CTL_MKDIR, (int)dirname, 0);
		if( retval == SYSERR )
			kprintf("....failed");
		kprintf("\r\n");
	}
	
	//Open a file in each directory
	char filename [] = {"/DIR_1/file"};
	kprintf("\r\n");
	for( i=0; i<5; i++)
	{ 
		filename[5] = '1'+i;
		kprintf("Opening file at %s\r\n", filename);
		fd[i] = open(LFILESYS, filename, "rwn");
		kprintf("  Got the sudo device : %d \r\n", fd[i]);
	}
	*/
	// Write to first file
    /*
	kprintf("\r\nWriting %d characters to /DIR_1/file .... ", wbufflen );
	retval = write( fd[0], wbuff, wbufflen );
	if( retval == SYSERR )
		kprintf("Write failed \r\b");
	else
		kprintf("Write returned %d \r\n", retval );

	// Write to last file
	kprintf("\r\nWriting %d characters to /DIR_5/file \r\n", wbufflen*10 );
	int total = 0;
	for( i=0; i<10; i++ ){
		retval = write( fd[4], wbuff, wbufflen );
		if( retval == SYSERR )
			kprintf("Write failed \r\b");
		else {
			kprintf("Write returned %d \r\n", retval );
			total += retval;
		}
	}
	if( total != 0 )
		kprintf("Wrote a total of %d characters\r\n", total );
		
	//Go to the beginning of the file at /DIR_5/file
	seek(fd[4],0);
	
	//Read
	int wrong = 0;
	kprintf("\r\nReading %d characters.... ", rbufflen);
	retval = read( fd[4], rbuff, rbufflen );
	if( retval == SYSERR )
		kprintf("Read failed \r\n");
	else{ 
		kprintf("Read returned %d\r\n", retval );

		//check the words read
		for (j=0,i=0; j<retval; j++,i++)
		{
			i = i % wbufflen;
			if(rbuff[j]!=wbuff[i]){
				wrong ++; 
				kprintf("read wrong at i: %d (expect %c, got %c)\r\n", j, wbuff[i], rbuff[j]);
			}
			if( wrong >= 20 ) break; //stops printing after 20 characters wrong
		} 
		if( wrong == 0)
			kprintf("Congrats. Characters read matches characters wrote.\r\n");
	}
	
	
	//close all files
	kprintf("\r\nClosing all files \r\n");
	for( i=0; i<5; i++ ){
		retval = close( fd[i] );
		if( retval == SYSERR )
			kprintf("Close file /DIR_%d/file failed \r\n", i+1);
	}

	//list files
	kprintf("\r\nList root directory:\r\n");
	retval = lflistdirh( LFILESYS, "/" );
	if( SYSERR == retval ) 
		kprintf("  Listing failed\r\n");
	for( i=0; i<5; i++ ){
		dirname[5] = '1'+i;
		kprintf("\r\nList directory %s:\r\n", dirname);
		retval = lflistdirh( LFILESYS, dirname );
		if( SYSERR == retval ) 
			kprintf("  Listing failed\r\n");
	}

	kprintf("\n++++++++++++++++++++++++END++++OF++++BASIC+++++++++++++++++++++++++++++\n");
    */
	// Create 5 directories
    /*
	char dirname1 [] = {"/DI"};
	kprintf("\r\n");
	kprintf("Creating directory %s", dirname1 );
	retval = control(LFILESYS, LF_CTL_MKDIR, (int)dirname1, 0);
	if( retval == SYSERR ) {
		kprintf("....failed");
		return 0;
	}
	kprintf("\r\n");
	
	char dirname2 [] = {"/DI/DI"};
	kprintf("\r\n");
	kprintf("Creating directory %s", dirname2 );
	retval = control(LFILESYS, LF_CTL_MKDIR, (int)dirname2, 0);
	if( retval == SYSERR ) {
		kprintf("....failed");
		return 0;
	}
	kprintf("\r\n");
	

	char dirname3 [] = {"/DI/D1"};
	for( i=0; i<9; i++){
		dirname3[5] = '1'+i;
		kprintf("Creating directory %s",  dirname3 );
		retval = control(LFILESYS,  LF_CTL_MKDIR,  (int)dirname3,  0);
		if( retval == SYSERR )
			kprintf("....failed");
		kprintf("\r\n");
	}*/
    /*
	char filename1[] = {"/DI/D1/file"};
	kprintf("\r\n");
	for( i=0; i<5; i++)
	{ 
		filename1[5] = '1'+i;
		kprintf("Opening file at %s\r\n", filename1);
		fd[i] = open(LFILESYS, filename1, "rwn");
		kprintf("  Got the sudo device : %d \r\n", fd[i]);
	}

	//close all files
	kprintf("\r\nClosing all files \r\n");
	for( i=0; i<5; i++ ){
		retval = close( fd[i] );
		if( retval == SYSERR )
			kprintf("Close file /DI/DI/D%d/file failed \r\n", i+1);
	}
    */
    int total = 0;
    int wrong = 0;
	char dirname4 [] = {"/DI/DI/D1"};
	for( i=0; i<9; i++){
		dirname4[8] = '1'+i;
		kprintf("Creating directory %s",  dirname4 );
		retval = control(LFILESYS,  LF_CTL_MKDIR,  (int)dirname4,  0);
		if( retval == SYSERR )
			kprintf("....failed");
		kprintf("\r\n");
	}
	
	//Open a file in each directory
	char filename2 [] = {"/DI/DI/D1/file"};
	kprintf("\r\n");
	for( i=0; i<5; i++)
	{ 
		filename2[8] = '1'+i;
		kprintf("Opening file at %s\r\n", filename2);
		fd[i] = open(LFILESYS, filename2, "rwn");
		kprintf("  Got the sudo device : %d \r\n", fd[i]);
	}
	
	// Write to first file
	kprintf("\r\nWriting %d characters to /DI/DI/D1/file .... ", wbufflen );
	retval = write( fd[0], wbuff, wbufflen );
	if( retval == SYSERR )
		kprintf("Write failed \r\b");
	else
		kprintf("Write returned %d \r\n", retval );

	// Write to last file
	kprintf("\r\nWriting %d characters to /DI/DI/D5/file \r\n", wbufflen*10 );
	total = 0;
	for( i=0; i<9; i++ ){
		retval = write( fd[4], wbuff, wbufflen );
		if( retval == SYSERR )
			kprintf("Write failed \r\b");
		else {
			kprintf("Write returned %d \r\n", retval );
			total += retval;
		}
	}
	if( total != 0 )
		kprintf("Wrote a total of %d characters\r\n", total );
		
	//Go to the beginning of the file at /DIR_5/file
	seek(fd[4],0);
	
	//Read
	wrong = 0;
	kprintf("\r\nReading %d characters.... ", rbufflen);
	retval = read( fd[4], rbuff, rbufflen );
	if( retval == SYSERR )
		kprintf("Read failed \r\n");
	else{ 
		kprintf("Read returned %d\r\n", retval );

		//check the words read
	for (j=0,i=0; j<retval; j++,i++)
		{
			i = i % wbufflen;
			if(rbuff[j]!=wbuff[i]){
				wrong ++; 
				kprintf("read wrong at i: %d (expect %c, got %c)\r\n", j, wbuff[i], rbuff[j]);
			}
			if( wrong >= 20 ) break; //stops printing after 20 characters wrong
		} 
		if( wrong == 0)
			kprintf("Congrats. Characters read matches characters wrote.\r\n");
	}
	
	
	//close all files
	kprintf("\r\nClosing all files \r\n");
	for( i=0; i<5; i++ ){
		retval = close( fd[i] );
		if( retval == SYSERR )
			kprintf("Close file /DI/DI/D%d/file failed \r\n", i+1);
	}

	char filename3[] = {"/DI/DI/D1/file2"};
	kprintf("\r\n");
	for( i=0; i<5; i++)
	{ 
		filename3[8] = '1'+i;
		kprintf("Opening file at %s\r\n", filename3);
		fd[i] = open(LFILESYS, filename3, "rwn");
		kprintf("  Got the sudo device : %d \r\n", fd[i]);
	}

	//close all files
	kprintf("\r\nClosing all files \r\n");
	for( i=0; i<5; i++ ){
		retval = close( fd[i] );
		if( retval == SYSERR )
			kprintf("Close file /DI/DI/D%d/file failed \r\n", i+1);
	}

	//list files
    
	kprintf("\r\nList root directory:\r\n");
	retval = lflistdirh( LFILESYS, "/" );
	if( SYSERR == retval ) 
		kprintf("  Listing failed\r\n");
     /*
	kprintf("\r\nList invalid directory:\r\n");
	retval = lflistdirh( LFILESYS, "/IN/" );
	if( SYSERR == retval ) {
		kprintf("  Passed\r\n");
	}
	else { 
		kprintf("  Failed\r\n");
	}*/
    
    char dirname2 [] = {"/DI/DI"};
kprintf("Creating directory %s again, this should return SYSERR\n", dirname2 );
	retval = control(LFILESYS, LF_CTL_MKDIR, (int)dirname2, 0);
	if( retval == SYSERR ) {
		kprintf("...success");
	} else {
		kprintf("...failed");
	}
	kprintf("\r\n");
    /*
	kprintf("\r\nList directory %s:\r\n", "/DI/DI");
	retval = lflistdirh( LFILESYS, "/DI/DI/" );
	if( SYSERR == retval ) 
		kprintf("  Listing failed\r\n");
	*/
	for( i=0; i<9; i++ ){
		dirname4[8] = '1'+i;
		kprintf("\r\nList directory %s:\r\n",  dirname4);
		retval = lflistdirh( LFILESYS,  dirname4);
		if( SYSERR == retval ){ 
			kprintf("  Listing failed\r\n");
		}
	}
	return OK;
}
