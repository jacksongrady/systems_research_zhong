

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv){
    FILE* f = fopen("../register_data/program_0_registers.txt", "rw");
    unsigned int test;
    char * line = NULL;
    while(fscanf(f, "(15) pc (/32): %x", &test) != 1){
        getline(&line, &len, f);
    }
    printf("%x", test);

    // sprintf(buffer, "%x %x %x", 0x7ffffc, 0x0a, 0x0);
    // fwrite(buffer,sizeof(buffer),1,f);

    // for(int i = 0; i<10; i++)
    //     printf("%x ", buffer[i]);


    return 0;
}