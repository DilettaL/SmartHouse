#include <stdio.h>
#include <pthread.h>
#include <readline/readline.h>

pthread_mutex_t m1, m2;

void *stampa1(){
	while (1){
	pthread_mutex_lock(&m1);
	char * buffer = readline("Il mio primo thread");
	pthread_mutex_unlock (&m2);
	}
	pthread_exit(0);
}

void *stampa2(){
	while(1){
	pthread_mutex_lock(&m2);
	printf("Il mio secondo thread\n");

	pthread_mutex_unlock(&m1);
	}
	pthread_exit(0);
}

int main (){
	pthread_t t1,t2;
	
	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	pthread_mutex_lock (&m2);

	pthread_create (&t1, NULL, stampa1, NULL);
	pthread_create (&t2, NULL, stampa2, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
return 0;
}
