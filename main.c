

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef long long int lli;

char T[3];
char* token;
int N, C, S, W;

char* line;
size_t len = 0;
int isLetterOrDigit(int c){
    return('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c<= '9');
}



void level0(void){
    getline(&line, &len, stdin);
    if (W != N)
    {
        printf("DATA LOST\n");
        exit(1);
    }
    
    char** matrix = (char **) malloc(S * sizeof(char *));
    if (matrix == NULL){
        perror("malloc error\n");
        exit(EXIT_FAILURE);
    }
    
    for (int r = 0; r < S; r++) {
        matrix[r] = (char *) malloc(N * sizeof(char));
        if (matrix[r] == NULL){
            perror("malloc error\n");
            exit(EXIT_FAILURE);
        }
    }
    
    //Use the same calculations as the project. column is the disk while stripe is the row.
    int chunkNumber, col, row, sectorIndex = 0;
    while (getline(&line, &len, stdin) != -1) {
        while ((token = strsep(&line, " \n"))) {
            if (strcmp(token, "")) {
                row = sectorIndex / N;
                col = sectorIndex % N;
                matrix[row][col] = atoi(token);
                sectorIndex++;
            }
        }
    }
    
    sectorIndex = 0;
    while (sectorIndex < S * N) {
        chunkNumber = sectorIndex / C;
        col = chunkNumber % N;
        row = (chunkNumber / N) * C + (sectorIndex % C);
        if (isLetterOrDigit(matrix[row][col]))
            putchar(matrix[row][col]);
        
        else
            putchar('_');
        sectorIndex++;
    }
    putchar('\n');
}


void level1(void){
    if (2*W < N) {
        printf("DATA LOST\n");
        return;
    }
    getline(&line, &len, stdin);
    char* message = malloc(S * sizeof(char));
    int byte;
    for (int index = 0; index < S; index++) {
        getline(&line, &len, stdin);
        sscanf(line, "%d",&byte);
        if ( !isLetterOrDigit(byte))
            byte = (int) '_';
        message[index] = byte;
    }
    printf("%s\n",message);
    
}

int** getMissingDisk(void){
    if (W+1 < N){
        printf("DATA LOST\n");
        exit(EXIT_FAILURE);
    }
    getline(&line, &len, stdin);
    lli sum = 0;lli missingDisk = -1;
    
    if (W!=N) {
        while ((token = strsep(&line, " \n"))) {
            if (strcmp(token,"")) {
                sum += atoi(token);
            }
        }
        missingDisk = ((W * (W + 1)) / 2) - sum;
    }
    
    int** matrix = malloc(S * sizeof(int*));
    if (matrix == NULL) {
        printf("DATA LOST\n");
        exit(EXIT_FAILURE);
    }
    
    for (int r = 0; r < S; r ++) {
        matrix[r] = calloc(N, sizeof(int));
        if (matrix[r] == NULL) {
            printf("DATA LOST\n");
            exit(EXIT_FAILURE);
        }
    }
    
    
    for (int r = 0; r < S; r++) {
        getline(&line, &len, stdin);
        int missingBlock = 0, c = 0;
        
        while ((token = strsep(&line, " \n"))) {
            if(strcmp(token, "")){
                matrix[r][c] = atoi(token);
                missingBlock ^= matrix[r][c];
                c++;
                if (c == missingDisk) c++;
                
        }
        }
        if (missingDisk != -1)
            matrix[r][missingDisk] = missingBlock;
    }
    return matrix;
}


void level4(void){
    if (W+1 < N){
        printf("DATA LOST\n");
        exit(EXIT_FAILURE);
    };
    int** matrix = getMissingDisk();
    char* message = (char* ) malloc(S * (N - 1) * sizeof(char));
    for (int row = 0; row < S; row++) {
        for (int col = 0; col < N - 1; col++) {
            
            if (isLetterOrDigit(matrix[row][col]))
                message[row * (N - 1) + col] = matrix[row][col];
            else
                message[row * (N - 1) + col] = '_';
        }
    }
    printf("%s\n",message);
    
}



void level5(void){
    if (W+1 < N){
        printf("DATA LOST\n");
        exit(EXIT_FAILURE);
    };
    
    int** matrix = getMissingDisk();
    
    for (int sector = 0; sector < N * S; sector++) {
        int row = (sector / N);
        int parityBlock = N - 1 - (row % (N));
        int col = (parityBlock + 1 + (sector % (N))) % N;
        
        if ((row + col) % N == N - 1)
            continue;
        if (isLetterOrDigit(matrix[row][col]))
            putchar(matrix[row][col]);
        else putchar('_');
    }
    putchar('\n');
}


void level01(void){
    int* disks = (int*) calloc(N, sizeof(int));
    if (disks == NULL) {
        perror("malloc error\n");
        exit(EXIT_FAILURE);
    }
    
    int diskCount = 0;
    getline(&line, &len, stdin);
    while ((token = strsep(&line, " \n"))) {
        if (strcmp(token, "")) {
            int disk = atoi(token);
            disks[disk] = 1;
            diskCount++;
            }
    }
    int leftHalf = 1, rightHalf = 1;
    for (int d = 0; d < N/2; d++) {
        if (!disks[d]) {
            leftHalf = 0;
            break;
        }
    }
    for (int d = N/2; d < N; d++) {
        if (!disks[d]) {
            rightHalf = 0;
            break;
        }
    }
    if (!(leftHalf || rightHalf)) {
        printf("DATA LOST\n");
        exit(EXIT_FAILURE);
    }
    
    
    int* columns = (int*) malloc(diskCount * sizeof(int));
    for (int i = 0, j = 0; i < N;  i++ ) {
        columns[j] = i;
        if (disks[i])
            j++;
    }
    
    
    int** matrix = (int**) malloc(S * sizeof(int*));
    if (matrix == NULL) {
        perror("malloc error\n");
        exit(EXIT_FAILURE);
    }
    for (int r = 0; r < S; r++) {
        matrix[r] = (int*) malloc(N/2 * sizeof(int));
        if (matrix[r] == NULL) {
            perror("malloc error\n");
            exit(EXIT_FAILURE);
        }
        getline(&line, &len, stdin);
        int index = 0;
        while ((token = strsep(&line, " \n"))) {
            if (strcmp(token, "")) {
                int c = columns[index];
                if (c >= N/2) {
                    c -= N/2;
                }
                matrix[r][c] = atoi(token);
                index++;
            }
        }
    }
    
    

    
    
    for (int r = 0; r < S; r++) {
        for (int c = 0; c < N/2; c++) {
            if (isLetterOrDigit(matrix[r][c]))
                putchar(matrix[r][c]);
            else
                putchar('_');
        }
    }
    putchar('\n');
    
}


void level10(void){
    int* disks = (int*) calloc(N, sizeof(int)) ,diskCount = 0;
    getline(&line, &len, stdin);
    while ((token = strsep(&line, " \n"))) {
        if (strcmp(token, "")) {
            int disk = atoi(token);
            disks[disk] = 1;
            diskCount++;
        }
    }
    
    for (int i = 0; i < N; i += 2) {
        if (!(disks[i] || disks[i + 1])) {
            printf("DATA LOST\n");
            exit(EXIT_FAILURE);
        }
    }
    int* columns = (int*) malloc(diskCount * sizeof(int));
    for (int i = 0, j = 0; i < N; i++) {
        columns[j] = i;
        j+=disks[i];
    }
    
    int** matrix = (int **) malloc(S * sizeof(int*));
    if (matrix == NULL) {
        perror("malloc error\n");
        exit(EXIT_FAILURE);
    }
    
    for (int r = 0; r < S; r++) {
        matrix[r] = (int*) malloc(N/2 * sizeof(int));
        if (matrix[r] == NULL) {
            perror("malloc error\n");
            exit(EXIT_FAILURE);
        }
        getline(&line, &len, stdin);
        int index = 0;
        while ((token = strsep(&line, " \n"))) {
            if (strcmp(token, "")) {
                int c = columns[index];
                c = (c - c%2) / 2;
                matrix[r][c] = atoi(token);
                index++;
            }
        }
        for (int c = 0; c < N/2; c++) {
            if (isLetterOrDigit(matrix[r][c]))
                putchar(matrix[r][c]);
            else
                putchar('_');
        }
    }
    


    putchar('\n');
}


int main(int argc, const char * argv[]) {
    
    //Read the raid level, amount of disks, chunk size, stripes, and w
    getline(&line, &len, stdin);
    sscanf(line, "%s %d %d %d %d", T, &N, &C, &S, &W);
    if (strcmp(T, "0") == 0)
        level0();
    else if (strcmp(T, "1") == 0)
        level1();
    else if (strcmp(T, "4") == 0)
        level4();
    else if (strcmp(T, "01") == 0)
        level01();
    else if (strcmp(T, "10") == 0)
        level10();
    else if (strcmp(T, "5") == 0)
        level5();
}
