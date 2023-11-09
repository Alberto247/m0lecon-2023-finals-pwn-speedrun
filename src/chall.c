#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
char name[64];

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

void downloadPage(){
    struct _locals{
        char filename[70];
        char URL[128];
        char *args[5];
        struct stat st;
    } locals;
    locals.args[0]=0x0;
    locals.args[1]=0x0;
    locals.args[2]=0x0;
    locals.args[3]=0x0;
    locals.args[4]=0x0;
    printf("Your URL: ");
    fgets(locals.URL, 228, stdin);
    locals.URL[strcspn(locals.URL, "\n")] = 0;
    strncpy(locals.filename, "/tmp/", 5);
    rand_string(locals.filename+5, 64);
    locals.args[0]="wget";
    locals.args[1]="-O";
    locals.args[2]=locals.filename;
    locals.args[3]=locals.URL;
    int child = fork();
    if(child==-1){
        exit(-1);
    }
    if(child==0){
        execvp("wget", locals.args);
        exit(0);
    }
    int status;
    wait(&status);
    if (WIFEXITED(status) && WEXITSTATUS(status)==0){
        printf("\n------------------------------------------\n");
        FILE *f=fopen(locals.filename, "r");
        fstat(fileno(f), &locals.st);
        int size=locals.st.st_size;
        for(int x=0; x<size; x++){
            putchar(getc(f));
        }
        printf("\n------------------------------------------\n");
    }
}

void setBuffs(){
        setvbuf(stdin,(char *)0x0,2,0);
        setvbuf(stdout,(char *)0x0,2,0);
        setvbuf(stderr,(char *)0x0,2,0);
}

void initRandom(){
    FILE *r = fopen("/dev/urandom", "r");
    int tmp;
    fread(&tmp, sizeof(int), 1, r);
    srand(tmp);
    tmp=0;
}

int main(){
    setBuffs();
    initRandom();
    printf("Please write your name on the visitor's book: ");
    fgets(name, 64, stdin);
    downloadPage();
}