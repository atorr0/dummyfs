#include <stdio.h>

int main()
{
    printf( __FILE__ " compilation (" __DATE__ " " __TIME__ ")\n");

    printf("fopen() points to: %p\n", fopen);

    FILE *f= fopen(".", "r");
    printf("fopened\n");
    fclose(f);

    printf("end\n");

    return 0;
}
