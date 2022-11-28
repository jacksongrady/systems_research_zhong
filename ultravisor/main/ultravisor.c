#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER 2048
#define MAX_PROGRAMS 4

void reset_target(void);
void halt_target(void);
void send_command(char * cmd);
void resume_target(void);
void send_commandf(char * cmd, int prog_no);
void send_command_out(char * cmd, char* filename);

void set_block0(int prog_no);
void set_block1(int prog_no);
void set_block2(int prog_no);
void set_regs(int prog_no);

void set(int prog_no);

void get_block0(int prog_no);
void get_block1(int prog_no);
void get_block2(int prog_no);
void get_regs(int prog_no);

void get(int prog_no);

//char ** PROGRAM_FILES = NULL;
char PROGRAM_FILES[MAX_PROGRAMS][MAX_BUFFER];

int main(int argc, char** argv){

    if(argc <= 1){
        printf("No arguments given. Please list all bin files for UltraVisor applications as arguments.");
        return 1;
    }

    if(argc > MAX_PROGRAMS +  1){
        printf("Cannot run this many programs");
        return 1;
    }
    char buff[MAX_BUFFER];
    char cmd[MAX_BUFFER];
    char cwd[MAX_BUFFER];

    //PROGRAM_FILES = malloc( (argc - 1) * sizeof(char *));

    getcwd(cwd, MAX_BUFFER);
    //reset_target();
    halt_target();
    send_command("flash protect 0 0 7 off");
    for(int i = 1; i < argc; i++){
        char * flash_cmd = malloc(sizeof(MAX_BUFFER));
        sprintf(buff, "flash write_image erase unlock %s/%s 0x8000000 bin", cwd, argv[i]);
        memcpy(PROGRAM_FILES[i - 1], buff, MAX_BUFFER);
        send_command("flash erase_sector 0 0 7");
        send_command(buff);
        reset_target();
        halt_target();
        if(i < argc - 1)
            get(i - 1);
    }
    resume_target();

    unsigned int prog_no = argc - 2;
    while(1){
        sleep(30); //sleep for one minute
        halt_target();
        get(prog_no);
        prog_no = (prog_no + 1) % (argc - 1);
        set(prog_no);
        resume_target();
    }
    // for(int i = 0; i < argc - 1; i++){
    //     free(PROGRAM_FILES[i]);
    // }
    // free(PROGRAM_FILES);
    return 0;
}

void reset_target(void){
    send_command("reset");
}

void halt_target(void){
    send_command("halt");
}

void resume_target(void){
    send_command("resume");
}

void send_command(char * cmd){
    char tcl_cmd[MAX_BUFFER];
    sprintf(tcl_cmd, "(echo \"%s\"; echo \"exit\") | netcat localhost 4444", cmd);
    //printf("%s", tcl_cmd);
    system(tcl_cmd);
    //memset(tcl_cmd, 0, MAX_BUFFER);
}

void send_command_out(char * cmd, char* filename){
    char tcl_cmd[MAX_BUFFER];
    sprintf(tcl_cmd, "(echo \"%s\"; echo \"exit\") | netcat localhost 4444 > %s", cmd, filename);
    //printf("%s", tcl_cmd);
    system(tcl_cmd);
    //memset(tcl_cmd, 0, MAX_BUFFER);
}

//replaces instance of %d in command with the program number
void send_commandf(char * cmd, int prog_no){
    char tcl_cmd[MAX_BUFFER];
    char cmd_1[MAX_BUFFER];

    sprintf(cmd_1, cmd, prog_no);
    sprintf(tcl_cmd, "(echo \"%s\"; echo \"exit\") | netcat localhost 4444", cmd_1);
    //printf("%s", tcl_cmd);
    system(tcl_cmd);
    //memset(tcl_cmd, 0, MAX_BUFFER);
}

// void send_commandf_block(char ** cmd, int prog_no, int num_commands){
//     char tcl_cmd[MAX_BUFFER];
//     char cmd_1[MAX_BUFFER];

//     for(int i = 0; i < num_commands; i++){
//         sprintf(cmd_1, cmd[i], prog_no);

//     }


//     sprintf(cmd_1, cmd, prog_no);
//     sprintf(tcl_cmd, "(echo \"%s\";  sleep 1;) | telnet localhost 4444", cmd_1);
//     //printf("%s", tcl_cmd);
//     system(tcl_cmd);
//     memset(tcl_cmd, 0, MAX_BUFFER);
// }

void set_block0(int prog_no){
    send_command("reset halt");
    send_commandf("flash erase_sector 0 0 7", prog_no);
    send_command(PROGRAM_FILES[prog_no]);
    reset_target();
    halt_target();
    //send_commandf("flash write_image erase unlock program_%d_flash.bin 0x8000000 bin", prog_no);
    send_commandf("load_image program_%d_alias.bin 0x0", prog_no);
    send_commandf("load_image program_%d_sys.bin 0x1FFF0000", prog_no);
    send_commandf("load_image program_%d_otp.bin 0x1FFF7800", prog_no);
    send_commandf("load_image program_%d_op.bin 0x1FFFC000", prog_no);
}
void set_block1(int prog_no){
    send_commandf("load_image program_%d_SRAM.bin 0x20000000", prog_no);
}
void set_block2(int prog_no){
    send_commandf("load_image program_%d_APB1.bin 0x40000000", prog_no);
    send_commandf("load_image program_%d_APB2.bin 0x40010000", prog_no);
    send_commandf("load_image program_%d_AHB1_1.bin 0x40020000", prog_no);
    send_commandf("load_image program_%d_AHB1_2.bin 0x40021C00", prog_no);
    send_commandf("load_image program_%d_AHB1_3.bin 0x40023000", prog_no);
    send_commandf("load_image program_%d_AHB1_4.bin 0x40023800", prog_no);
    send_commandf("load_image program_%d_AHB1_5.bin 0x40026000", prog_no);
    send_commandf("load_image program_%d_AHB2.bin 0x50000000", prog_no);
    send_commandf("load_image program_%d_cortex_periph.bin 0xE0000000", prog_no);
}
void set_regs(int prog_no){
    char cmd[MAX_BUFFER];
    sprintf(cmd, "(python3 ../script_lib/set_regs.py %d; echo \"exit\") | netcat localhost 4444", prog_no);
    system(cmd);
    char buff[MAX_BUFFER];
    sprintf(buff, "../register_data/temp_%d.txt", prog_no);
    FILE* f = fopen(buff, "rw");
    unsigned int test;
    char * line = NULL;
    while(fscanf(f, "(15) pc (/32): %x", &test) != 1){
        getline(&line, &len, f);
    }
    fclose(f);
    char cmd1[MAX_BUFFER];
    sprintf(cmd1, "write_memory 0x2002ffc %x 32", test);
    send_command("write_memory ");
    send_command("reg pc 0x807FC00");
}

void set(int prog_no){
    set_block0(prog_no);
    set_block1(prog_no);
    set_block2(prog_no);
    set_regs(prog_no);
}

void get_block0(int prog_no){
    send_commandf("dump_image program_%d_alias.bin 0x0 0x80000", prog_no);
    //send_commandf("dump_image program_%d_flash.bin 0x08000000 0x80000", prog_no);
    send_commandf("dump_image program_%d_sys.bin 0x1FFF0000 0x7A10", prog_no);
    send_commandf("dump_image program_%d_otp.bin 0x1FFF7800 0x210", prog_no);
    send_commandf("dump_image program_%d_op.bin 0x1FFFC000 0x10", prog_no);
}
void get_block1(int prog_no){
    send_commandf("dump_image program_%d_SRAM.bin 0x20000000 0x20000", prog_no);
}
void get_block2(int prog_no){
    send_commandf("dump_image program_%d_APB1.bin 0x40000000 0x7400", prog_no);
    send_commandf("dump_image program_%d_APB2.bin 0x40010000 0x5400", prog_no);
    send_commandf("dump_image program_%d_AHB1_1.bin 0x40020000 0x1400", prog_no);
    send_commandf("dump_image program_%d_AHB1_2.bin 0x40021C00 0x400", prog_no);
    send_commandf("dump_image program_%d_AHB1_3.bin 0x40023000 0x400", prog_no);
    send_commandf("dump_image program_%d_AHB1_4.bin 0x40023800 0x400", prog_no); //DOES NOT COPY 0X400 BTYES OF FLASH INTERFACE REGISTERS
    send_commandf("dump_image program_%d_AHB1_5.bin 0x40026000 0x800", prog_no);
    send_commandf("dump_image program_%d_AHB2.bin 0x50000000 0x40000 ", prog_no);
    send_commandf("dump_image program_%d_cortex_periph.bin 0xE0000000 0x100000", prog_no);
}
void get_regs(int prog_no){
    char buff[MAX_BUFFER];
    sprintf(buff, "../register_data/program_%d_registers.txt", prog_no);
    send_command_out("reg", buff);
    send_command("reg");
    //printf("GETTING REGISTERS\n");
}

void get(int prog_no){
    get_block0(prog_no);
    get_block1(prog_no);
    get_block2(prog_no);
    get_regs(prog_no);
}