/*
** INTERNSHIP, 2020
** creating mailing list
** File description:
** list of addresses separated by a new line
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


int    put_nbr(int nb, int fd)
{
    int modulo = 0;
    char v;

    if (nb <= 9 && nb >= 0) {
         v = nb + '0';
        write(fd, &v, 1);
    }
    if (nb < 0) {
	v = '-';    
        write(fd, &v, 1);
        nb = nb * (- 1);
        if (nb <= 9 && nb >= 0)
            put_nbr(nb, fd);
    }
    if (nb > 9) {
        modulo = nb % 10;
        put_nbr(nb / 10, fd);
	v = modulo + '0';
        write(fd, &v, 1);
    }
    return (0);
}


int main()
{
    int fd = open("mailing.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
    int count = 1;
    char *string = "@mail.com";
    char c = 10;
    while (count < 1000001) {
	put_nbr(count, fd);
	write(fd, string, 9);
	write(fd, &c, 1);
	++count;
    }
    close(fd);    
    return (0);
       	

}
