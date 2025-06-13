#include <stdio.h>

catfile(FILE *f);

main(int argc, char *argv[])
{
    int i;
    FILE *fp;

    if (argc == 1)
    {
        catfile(stdin);
        return 0;
    } 
    else for (i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "rb");
        if (NULL == fp)
        {
            fputs("File not found.", stderr);
            return 1;
        }

        catfile(fp);
        fclose(fp);
    }

    
}

catfile(FILE *f)
{
    int c;
    while ((c = fgetc(f)) != EOF)
    {
        fputc(c, stdout);
    }
}