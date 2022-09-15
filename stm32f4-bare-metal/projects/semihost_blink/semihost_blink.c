#include "stm32f411xe.h"

/*************************************************
* struct declarations
*************************************************/
typedef struct _FileInput{
    char* path;
    int perms;
    int path_length
} FileInput;

typedef struct _ReadInput{
    int fd;
    void* buff;
    int num_bytes
} ReadInput;

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
int open_host_file(FileInput* file);
int read_host_file_to_mem(ReadInput* read_input);
int int_to_str(char* buf, int i, int size);
int str_len(char* str);

int println_char_custom(char c);


/*************************************************
* main code starts from here
*************************************************/
int main(void){

    RCC->AHB1ENR |= 0x00000009;

   
    GPIOD->MODER &= 0xFCFFFFFF;   // Reset bits 25:24 to clear old values
    //GPIOD->MODER |= 0x01000000;   // Set MODER bits 25:24 to 01
    GPIOD->MODER |= 0x55000000; // Set MODER bits 31:24 to 01

    char* high_path = "/Users/jacksondgrady/Desktop/zhong_research/stm32f4-bare-metal/projects/semihost_blink/high.txt";
    char* low_path = "/Users/jacksondgrady/Desktop/zhong_research/stm32f4-bare-metal/projects/semihost_blink/low.txt";
    FileInput high;
    high.path = high_path;
    high.path_length = str_len(high_path);
    high.perms = 2;

    FileInput low;
    low.path = low_path;
    low.path_length = str_len(low_path);
    low.perms = 2;

    println_str("opening files...");

    int high_fd = open_host_file(&high);
    int low_fd = open_host_file(&low);

    println_str("opened files");
    // *ptr |= (1 << 12);
    //*(ptr) = 1;

    ReadInput green_led;
    green_led.fd = high_fd;
    green_led.buff = 0x40020C14;
    green_led.num_bytes = 4;

    //println_str("writing to target memory...");
    
    while(1){

        green_led.fd = high_fd;

        read_host_file_to_mem(&green_led);


        for(int i = 0; i < 500000; i++){

        }
        green_led.fd = low_fd;

        read_host_file_to_mem(&green_led);

        for(int i = 0; i < 500000; i++){
            
        }


    }

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

int println_char_custom(char c){
    int ret = syscall(0x1FF, (int)&c);
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

int open_host_file(FileInput* file){
    return syscall(0x01, (int)file);
}

int read_host_file_to_mem(ReadInput* read_input){
    return syscall(0x06, (int)read_input);
}

int str_len(char* str){
    int i = 0;
    while(1){
        if(str[i++] == '\0'){
            break;
        }
        if(i > 1000000){
            return -1;
        }
    }
    return i - 1;
}