#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
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

void printFlag(){
    FILE* fptr = fopen("/flag.txt", "r"); 
    if (fptr == NULL) 
    { 
        printf("Cannot open flag file \n"); 
        exit(0); 
    } 
  
    // Read contents from file 
    char c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fptr); 
    } 
  
    fclose(fptr); 
    
}

void downloadPage(){
    struct _locals{
        struct stat st;
        char filename[70];
        char URL[128];
        char *args[7];
    } locals;
    locals.args[0]=0x0;
    locals.args[1]=0x0;
    locals.args[2]=0x0;
    locals.args[3]=0x0;
    locals.args[4]=0x0;
    locals.args[5]=0x0;
    locals.args[6]=0x0;
    printf("Your URL: ");
    gets(locals.URL);
    locals.URL[strcspn(locals.URL, "\n")] = 0;
    strncpy(locals.filename, "/tmp/", 5);
    rand_string(locals.filename+5, 64);
    printf("Your file will be saved at %s\n", locals.filename);
    locals.args[0]="wget";
    locals.args[1]="-q";
    locals.args[2]="-O";
    locals.args[3]=locals.filename;
    locals.args[4]=locals.URL;
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

void recoverPrintedFile(){
        struct _locals{
        struct stat st;
        char filename[70];
        char URL[128];
        char *args[6];
    } locals;
    locals.args[0]=0x0;
    locals.args[1]=0x0;
    locals.args[2]=0x0;
    locals.args[3]=0x0;
    locals.args[4]=0x0;
    locals.args[5]=0x0;
    printf("Your URL: ");
    fgets(locals.URL, 127, stdin);
    locals.URL[strcspn(locals.URL, "\n")] = 0;
    locals.URL[127]=0;
    strncpy(locals.filename, "/tmp/", 5);
    printf("Your filename: ");
    fgets(locals.filename+5, 64, stdin);
    if(strrchr(locals.filename+5, '/')!=NULL){
        puts("Sorry, no special characters allowed in filename.");
        return;
    }
    locals.filename[strcspn(locals.filename, "\n")] = 0;
    locals.filename[69]=0;
    locals.args[0]="wget";
    locals.args[1]="-q";
    locals.args[2]="--post-file";
    locals.args[3]=locals.filename;
    locals.args[4]=locals.URL;
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
}

void listNotes(){
    puts("I'm sorry but due to a cybersecurity attack our system is not currently available. We are sorry for the issue.");
}
void sellNote(){
    puts("I'm sorry but due to a cybersecurity attack our system is not currently available. We are sorry for the issue.");
}
void buyNote(){
    puts("I'm sorry but due to a cybersecurity attack our system is not currently available. We are sorry for the issue.");
}

void buysellMenu(){
    puts("1. List notes");
    puts("2. Sell notes");
    puts("3. Buy notes");
    puts("5. Back");
    printf("> ");
}

void buysell(){
    struct _locals{
        int64_t selection;
        int64_t pad1;
        int64_t pad2;
    } locals;
    
    while(1==1){
        buysellMenu();
        scanf("%ld", &locals.selection);
        getchar();
        if (locals.selection==1){
            listNotes();
        }else if (locals.selection==2){
            sellNote();
        }else if(locals.selection==3){
            buyNote();
        }else if(locals.selection==4){
            puts("No one bought your notes...");
        }else if(locals.selection==5){
            return;
        }else{
            printf("Action %ld is not in the menu\n", locals.selection);
        }
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

void mainMenu(){
    puts("Welcome to our service! What do you want to do?");
    puts("1. Buy or sell notes (NOT BOOKS)");
    puts("2. Print your document");
    puts("3. Recover printed file");
    puts("4. Update your user info");
    puts("5. Leave");
    printf("> ");
}

int main(){
    setBuffs();
    initRandom();
    int64_t selection;
    while(1){
        mainMenu();
        scanf("%ld", &selection);
        getchar();
        if(selection==1){
            buysell();
        }else if(selection==2){
            downloadPage();
        }else if(selection==3){
            recoverPrintedFile();
        }else if(selection==4){
            printf("Please provide us your name for future records: ");
            fgets(name, 64, stdin);
        }else if(selection==4){
            puts("Thanks for visiting us!");
            return 0;
        }else{
            printf("Action %ld is not in the menu\n", selection);
        }
    }
}