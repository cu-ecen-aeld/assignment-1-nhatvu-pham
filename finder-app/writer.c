#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments");
        closelog();
        return 1;
    }

    const char *file = argv[1];
    const char *text = argv[2];

    syslog(LOG_DEBUG, "Writing %s to %s", text, file);

    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        syslog(LOG_ERR, "Error opening file %s", file);
        closelog();
        return 1;
    }

    ssize_t result = write(fd, text, strlen(text));
    if (result == -1)
    {
        syslog(LOG_ERR, "Error writing to file %s", file);
        close(fd);
        closelog();
        return 1;
    }

    close(fd);
    closelog();

    return 0;
}
