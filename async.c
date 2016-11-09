#include<aio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include"scheduler.h"
#include<stdio.h>
#include<stdlib.h>
struct aiocb aiocbp;

ssize_t read_wrap(int fd, void * buf, size_t count) 
{
      
   memset(&aiocbp,0,sizeof(struct aiocb));

   aiocbp.aio_nbytes = count;  	

   if (fd!= 0)
   {
	aiocbp.aio_offset=lseek(fd,0, SEEK_CUR);
	printf ("\n file descriptor is not zero");
   }
	 aiocbp.aio_fildes = fd;
	 aiocbp.aio_buf = buf;
	 aiocbp.aio_sigevent.sigev_notify = SIGEV_NONE ;
   
   if (aio_read(&aiocbp) == -1)
   {
	return errno;
	
   }


  while (aio_error(&aiocbp) == EINPROGRESS)
  {  
			printf("\nbefore yielding in async call\n");
			yield();
  }	

  aiocbp.aio_offset=lseek(fd,count, SEEK_CUR);		
//free(buf);
 return  aio_return(&aiocbp);
  
}

	

