#include <stdio.h>
#include <stdlib.h>

void fgetCode(){
    FILE *fP = fopen("file1","r");
    
    if (fP == NULL) {
        exit(1);
    }

    char *buffer = malloc(50);

    while(fgets(buffer, 49, fP) != NULL) {
        printf("%s", buffer);
    }

    fclose(fP);
}

void getlineCode(){
    FILE *fP = fopen("file1", "r");

    if (fP == NULL) {
        exit(2);
    }

    char *buffer = NULL;
    size_t size = 0;
    ssize_t c = 0;

    while ((c = getline(&buffer, &size, fP)) != -1) {
        printf("line: %s", buffer);
        printf("size: %ld\n", size);
        printf("c   : %ld\n", c);
    }
    fclose(fP);
}


int main(){
    printf("FGETS: \n\n");
    fgetCode();

    printf("\nGETLINE: \n\n");
    getlineCode();

    return 0;
}

/* 
FGETS:

test file for line1
line 2
ffhdsjakfhdsjakfhsajkflhsdjfkshdfj
fhdjsaklfhdsjakfhuivnm

GETLINE:

line: test file for line1
size: 32
c   : 20
line: line 2
size: 32
c   : 7
line: ffhdsjakfhdsjakfhsajkflhsdjfkshdfj
size: 64
c   : 35
line: fhdjsaklfhdsjakfhuivnm
size: 64
c   : 23
*/
