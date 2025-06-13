#include <stdio.h>
#include <string.h>

int is_path(char *s);
search_paths(char *e);

char cur_path[256];
char *current;
char *which_prog;

int search_path();

main(int argc, char* argv[], char *env[])
{
    char **e;

    if (argc < 2) {
        printf("Usage: which <prog>\n");
        return;
    }
    which_prog = argv[1];

    strcpy(cur_path, ".");
    if (0 == search_path())
    {
        return;
    }

    for (e = env; e != NULL; e++)
    {
        if (is_path(*e)) {
            //puts(*e);
            search_paths(*e);
            break;
        }
    }    
}


int is_path(char *s)
{
    return !strncasecmp(s, "PATH=", 5);
}

char *next_path()
{
    int i = 0;
    while (*current != ';')
    {
        cur_path[i++] = *(current++);
    }
    cur_path[i] = 0;
    ++current;

    return cur_path;
}

int check_exe()
{
    FILE *fp;

    //printf("check executable: %s\n", cur_path);

    if ((fp = fopen(cur_path, "r")) != 0)
    {
        fclose(fp);

        puts(cur_path);
        return 0;
    }

    return 1;
}

int search_path()
{
    FILE *fp;

    strcat(cur_path, "\\");
    strcat(cur_path, which_prog);
    
    if ( 0 == check_exe() ) {
        return 0;
    }

    strcat(cur_path, ".exe");
    if ( 0 == check_exe() ) {
        return 0;
    }

    cur_path[strlen(cur_path) - 4] = 0;
    strcat(cur_path, ".bat");
    if ( 0 == check_exe() ) {
        return 0;
    }

    return 1;
}

search_paths(char *e)
{
    char *p;

    current = &(e[5]);
    for (p = next_path(); strlen(p) != 0; p = next_path()) {
        search_path();
    }    
}
