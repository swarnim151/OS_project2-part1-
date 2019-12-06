/*------------------------------------------------------*/
/* Skeleton for the synchronization Lab .   assignment 	*/
/*------------------------------------------------------*/
/* Note:						                        */
/* -----						                        */
/* 1. E = Elephant					                    */
/* 2. D = Dog						                    */
/* 3. C = Cat					                    	*/
/* 4. M = Mouse						                    */
/* 5. P = Parrot					                    */
/*------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define  CHILD		0       /* Return value of child proc from fork call */

int main()
{
	/*  sempahores */
  sem_t * elephant_mice;
	sem_t * dog_cat;
	sem_t * cat_parrot;
	sem_t * mouse_parrot;
	int pid;		/* Process id after fork call */
	int i;	/* Loop index. */
	int N;		/* Number of requests to process */
	int status;  	/* Exit status of child process. */
	int type;           /* Type of animal */
	int fd, zero=0,*counter_ptr;
	
  //opening the file and mapping it into memory to hold the shared counter
  fd = open("zoo.txt",O_RDWR|O_CREAT,S_IRWXU);
  write(fd, &zero, sizeof(int));
  counter_ptr = mmap(NULL, sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  close(fd);
	
	/* Initialization of semaphores. */
	
	if ((elephant_mice = sem_open("elephant_mice_semaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
		perror("semaphore initilization");
		exit(1);}
  
	if ((dog_cat = sem_open("dog_cat_semaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
		perror("semaphore initilization");
		exit(1);}
	
	if ((cat_parrot = sem_open("cat_parrot_semaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
		perror("semaphore initilization");
		exit(1);}
	
	if ((mouse_parrot = sem_open("mouse_parrot_sempahore", O_CREAT, 0644, 1)) == SEM_FAILED) {
		perror("semaphore initilization");
		exit(1);}

	printf("How many request to process: \n");
	scanf("%d",&N);

	for (i=1; i<=N; i++) {
			printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
			fflush(stdout);
			scanf("%d",&type);
			if ((pid = fork()) == -1) {
					/* Fork failed! */
				perror("fork");
				exit(1);
			}
        
	if (pid == CHILD) {
			pid = getpid();
			switch (type) {

				case 1: /* Elephant code*/
					printf("     Elephant process with pid %d wants in.\n",pid);
					fflush(stdout);
					sem_wait(elephant_mice);
					printf("     Elephant process with pid %d is in.\n",pid);
					fflush(stdout);
					sleep(rand()%10);
					printf("     Elephant process with pid %d is out.\n",pid);
					sem_post(elephant_mice);    
					fflush(stdout); 
					break;

				case 2:  /*Dog code*/
					printf("     Dog process with pid %d wants in.\n",pid);
					fflush(stdout);
					sem_wait(dog_cat);
					printf("     Dog process with pid %d is in.\n",pid);
					fflush(stdout);
					sleep(rand()%10);
					printf("     Dog process with pid %d is out.\n",pid);
					sem_post(dog_cat);
					fflush(stdout);
					break;

				case 3: /*Cat Code*/
					printf("     Cat process with pid %d wants in.\n",pid);
					fflush(stdout);
					sem_wait(dog_cat);
					sem_wait(cat_parrot);
					printf("     Cat process with pid %d is in.\n",pid);
					fflush(stdout);
					sleep(rand()%10);
					printf("     Cat process with pid %d is out.\n",pid);
					sem_post(dog_cat);
					sem_post(cat_parrot);
					fflush(stdout);
					break;

				case 4: /*Mouse code*/
					printf("     Mouse process with pid %d wants in.\n",pid);
					fflush(stdout);
					sem_wait(mouse_parrot);
					sem_wait(elephant_mice);
					printf("     Mouse process with pid %d is in.\n",pid);
					fflush(stdout);
					sleep(rand()%10);
					printf("     Mouse process with pid %d is out.\n",pid);
					sem_post(mouse_parrot);
					sem_post(elephant_mice);
					fflush(stdout); 
					break;

				case 5: /*Parrot  Code*/
					printf("     Parrot process with pid %d wants in.\n",pid);
					fflush(stdout);
					sem_wait(mouse_parrot);
					sem_wait(cat_parrot);
					printf("     Parrot process with pid %d is in.\n",pid);
					fflush(stdout);
					sleep(rand()%10);
					printf("     Parrot process with pid %d is out.\n",pid);
					sem_post(mouse_parrot);
					sem_post(cat_parrot);
					fflush(stdout);
					break;
					}
			exit(0);
	}
	}  
    /* Now wait for the child processes to finish */
	for (i=1; i<=N; i++) {
		pid = wait(NULL);
		printf("Child (pid = %d) exited with status %d.\n", pid, status);
		fflush(stdout);
	}
}



