#include <stdio.h>
//
//
//
//
//
//
//
//
int main()
{
    printf( __FILE__ " compilation (" __DATE__ " " __TIME__ ")\n");

    printf("fopen() points to: %p\n", fopen);

    //
    //
    //
    // -BEGIN DO NOT CHANGE-
    // This next line of code must be at line 21 (as there's a programmatic breakpoint @dodemo.sh)
    FILE *f= fopen(".", "r");
    // -END DO NOT CHANGE-

    printf("fopened\n");
    fclose(f);

    printf("end\n");

    return 0;
}
