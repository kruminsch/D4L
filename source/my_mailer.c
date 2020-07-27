/*
** INTERNSHIP, 2020
** My mailer
** File description:
** Learning Threads
*/

#include "../include/get_next_line.h"
#include "../include/mailing.h"

char *post_box(char *message, size_t  size, int status)
{
    static char *my_message;
    int i = 0;
    
    if (status == 0) {
        my_message = malloc(sizeof(char) * (size + 1));
	while (message[i] != '\0') {
            my_message[i] = message[i];
            ++i;
        }
        my_message[i] = '\0';
    }
    if (status == 1) {
        printf("%s\n", my_message);
    }
    if (status == 3)
	free(my_message);
    return (NULL);
}

//U can switch off post_box function if u dont want to print the message
void *thr_func(void *str) {
    char *email;
    if (NULL == (email = malloc(sizeof(char) * MAX_ADDRESS_LENGTH))) {
        write(2, "Oops, something strange happend\n!", 31);
        exit(EXIT_FAILURE);
    }
    strcpy(email,str);
    free(str);
    printf("Sending email to %s\n", email);
    post_box(NULL, 8, 1);
    usleep(500000);
    printf("an email has been sent to %s\n", email);
    free(email);
    return (NULL);
}

int getting_ready(int ac, char **av)
{
    int fd;	
    size_t size;
    
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        write(1, "./USAGE\n", 8);
        write(1, "Please enter a short message as first argument\n", 47);
        write(1, "Give a path to mailing_list_file(txt) as a second argument\n", 59);
        write(1, "make sure it consists of valid email addresses separated \
by a new line\n", 72);
        write(1, "U could also run ./gen for creating a testing list of 1000000 \
entries\n", 70);
        exit(0);
    }
    if (ac != 3) {
        write(2, "Wrong number of arguments, please try with -h\n", 46);
        exit(EXIT_FAILURE);
    }
    size = strlen(av[1]);
    post_box(av[1], size, 0);
    if ( 0 > (fd = open(av[2], O_RDONLY))) {
        write(2, "Problem opening mailing list\n", 29);
	write(2, "Please, try with -h\n", 20); 
        exit(EXIT_FAILURE);
    }	
    return (fd);
}

int main(int ac, char **av)
{
    int fd = getting_ready(ac, av);	
    int count = 0;
    int count1 = 0;
    char *s = get_next_line(fd);
    pthread_t *realthreads;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    if (NULL == (realthreads = malloc(sizeof(pthread_t) * MAX_THREADS))) {
        write(2, "very strange!\n", 14);
        exit(EXIT_FAILURE);
    }		    
    while (s) {
        while (s && count < 1000002) {
            if (0 != pthread_create(&realthreads[count1], &attr, thr_func, s))
                break;
            ++count;
	    ++count1;
	    s = get_next_line(fd);
	}
	for (int i = 0; i < count1; ++i) {
            pthread_join(realthreads[i], NULL);
        }
	count1 = 0;
    }
    if (count > 1000000) {
        write(1, "You told there will be just 1000000!\n", 37);
    }	
    pthread_attr_destroy(&attr);
    free(realthreads);
    post_box(NULL, 0, 3);
    return (0);
}
