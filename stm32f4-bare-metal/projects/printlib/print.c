#include "stm32f411xe.h"

/*************************************************
* function declarations
*************************************************/
int main(void);
int syscall(int nr, int arg);
int print_char(char c);
int print_int(int i);
int print_str(char* str);
int println_char(char c);
int println_int(int i);
int println_str(char* str);
int int_to_str(char* buf, int i, int size);



/*************************************************
* main code starts from here
*************************************************/
int main(void){
    char a = 'A';
    char b = 'b';
    char c = 'c';
    char d = 'd';
    char e = 'e';
    print_char(a);
    print_char(b);
    print_char(c);
    println_char(d);
    println_char(e);
    println_int(100023202);
    println_str("hello this is a test");

    while (1){

    }
    __asm("NOP"); // Assembly inline can be used if needed
    return 0;
}

int syscall(int nr, int arg){
    int res = 0;
    __asm(  
            "mov r0, %[num];"
            "mov r1, %[argument];"
            "bkpt #0xab;"
            "mov %[result], r0"
            : [result] "=r" (res)
            : [num] "r" (nr), [argument] "r" (arg)
        );
    return res;
}

int print_char(char c){
    return syscall(0x03, (int)&c);
}

int print_str(char* str){
    return syscall(0x04, (int)str);
}

//does not support numbers > 10^1000
int print_int(int i){
    char str[1000];
    int ret = int_to_str(str, i, 1000);
    if(ret < 0){
        return ret;
    }
    return print_str(str);

}

//does not support numbers > 10^1000
int int_to_str(char* buf, int i, int size){
    char reversed[size];
    int count = 0;
    while(1){
        reversed[count++] = (i % 10) + 48;
        i /= 10;
        if(count + 1 >= size){
            return -1;
        }
        if(i == 0){
            break;
        }
    }

    count--;

    for(int j = 0; j <= count; j++){
        buf[j] = reversed[count - j];
    }

    buf[count + 1] = '\0';

    return 1;

}

int println_char(char c){
    int ret = syscall(0x03, (int)&c);
    if(ret >= 0)
        return print_char('\n');
    else
        return ret;
}

int println_str(char* str){
    int ret = syscall(0x04, (int)str);
    if(ret >= 0)
        return print_char('\n');
    else
        return ret;
}

//does not support numbers > 10^1000
int println_int(int i){
    char str[1000];
    int ret = int_to_str(str, i, 1000);
    if(ret < 0){
        return ret;
    }
    ret = print_str(str);
    if(ret >= 0)
        return print_char('\n');
    else
        return ret;

}

