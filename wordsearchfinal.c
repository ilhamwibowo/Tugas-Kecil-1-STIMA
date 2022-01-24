#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_rows_columns(char* filename, int *rows, int *cols,int *word_ctr){
    FILE *file;
    file = fopen (filename, "r");
    char buff;
    char buffore;
    //mencari rows and columns dari matrix
    while (1)
    {
        fscanf(file, "%c", &buff);
        if (buff == 10 && buffore == 10) {
            break;
        }
        else if (buff == 10) {
            *rows += 1;
        }
        else if (buff != ' ' && *rows == 0) {
            *cols += 1;
        }
        buffore = buff;
    }

    //mencari jumlah kata yang akan dicari
    while(1) {
        if (fscanf(file, "%c", &buff) != EOF) {
            if (buff == 10) {
                *word_ctr += 1;
            }
        }
        else {
            *word_ctr += 1;
            break;
        }
    }  
    fclose (file);
}

int is_point_in(int a, int b, int** mat, int length){
    int exist = 0;
    for (int i = 0;i < length;i++) {
        if (mat[i][0] == a && mat[i][1] == b) {
            exist = 1;
            break;
        }
    }

    if (exist) {
        return 1;
    }
    else {
        return 0;
    }
}


int print_word(char** grid, int dir,int row,int col, int word_length, int R, int C){
    int x[8] = {0, 1, 1, 1, 0,-1,-1,-1}; //geser baris
    int y[8] = {1, 1, 0,-1,-1,-1, 0, 1};//pergeseran kolom
    int i,j;

    //insisialisasi matriks untuk menyimpan posisi word pada grid
    int** position=malloc(word_length*sizeof(int*)); 
    for(i=0;i<word_length;++i) {
        position[i]=malloc(2*sizeof(int)); 
    }

    //mengisi matriks dengan posisi word
    int rptr = row;
    int cptr = col;
    for (i = 0;i < word_length;i++) {
        position[i][0] = rptr;
        position[i][1] = cptr;
        rptr += x[dir];
        cptr += y[dir];
    }

    //mencetak kata sesuai posisinya pada grid 
    for (i = 0; i < R;i++) {
        for (j = 0; j < C; j++) {
            if (is_point_in(i,j,position,word_length)) {
                printf("%c ", grid[i][j]);
            }
            else {
                printf("- ");
            }
        }
        printf("\n");
    }

    free(position);
}

void find_word(char** grid, int row, int col, int *ctr, char* word, int R, int C)
{
    int x[8] = {0, 1, 1, 1, 0,-1,-1,-1}; //geser baris
    int y[8] = {1, 1, 0,-1,-1,-1, 0, 1};//pergeseran kolom
    // If first character of word doesn't
    // match with given starting point in grid.
    if (grid[row][col] != word[0]) {
        *ctr += 1;
        return;
    }
 
    int len = strlen(word);
 
    // Search word in all 8 directions
    // starting from (row, col)
    for (int dir = 0; dir < 8; dir++) {
        int k;
        int rowdir = row + x[dir];
        int coldir = col + y[dir];
 
        for (k = 1; k < len; k++) {
            *ctr += 1;
            if (rowdir >= R || rowdir < 0 || coldir >= C || coldir < 0) {
                break;
            }
            else if (grid[rowdir][coldir] != word[k]) {
                break;
            }
            else {
                rowdir += x[dir];
                coldir += y[dir];
            }

        }
        //kata sudah ditemukan
        if (k == len) {
            print_word(grid, dir,row,col,len,R,C);
            return;
        }
    }
    return;
}

int search_word_grid(char** grid, char* word, int R, int C)
{
    int temp_ctr = 0;
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            find_word(grid, row, col,&temp_ctr, word, R, C);
        }
    }
    return temp_ctr;
}   

// int match_word(char** mat,char *target, int word_length, int text_length, int r, int c) {
//     //kamus
//     int i = 0;
//     int j;
//     int found = 0;
//     while((i <= text_length-word_length) && (!found)) {
//         j = 0;
//         while (j < word_length && mat[r][i+j] == target[j]) {
//             j += 1;
//         }

//         if (j == word_length) {
//             found = 1;
//         }
//         else {
//             i += 1;
//         }
//     }

//     if (found) {
//         return i;
//     }
//     else {
//         return -1;
//     }
// }


int main(void)
{

    int rows = 0;
    int cols = 0;
    int word_ctr = 0;
    clock_t start_time, end_time;
    double elapsed;
    int counter = 0;

    char filenm[100];
    printf("Masukkan nama file yang ingin digunakan : ");
    scanf("%s", &filenm);
    printf("%s", filenm);

    //cari banyak kolom, baris, dan banyak kata yang akan dicari
    get_rows_columns(filenm,&rows,&cols,&word_ctr);

    //alokasi matriks untuk word grid
    char** mat=malloc(rows*sizeof(char*)); 
    for(int i=0;i<rows;++i) {
        mat[i]=malloc(cols*sizeof(char)); 
    }

    //baca matriks dan masukkan hasil kedalam mat
    char* word[20];
    FILE *f;
    f = fopen (filenm, "r");

    //mengubah matriks dalam file menjadi variable matriks
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
            fscanf(f, "%c ", &mat[i][j]);
    }
    printf("\n");
    printf("SEARCHING ALGORITHM STARTING ... ");
    printf("\n");
    start_time = clock();

    //memulai algoritma pencarian
    for (int i = 0; i < word_ctr; i++) {
        fscanf(f,"%s", &word);
        printf("\n%s\n\n", word);
        counter += search_word_grid(mat, word, rows, cols);
    }
    end_time = clock();
    elapsed = (((double)(end_time - start_time))/ CLOCKS_PER_SEC);
    fclose (f);

    printf("\n");
    printf("SEARCH COMPLETED,\nTIME TAKEN : %f seconds,\n%d TOTAL COMPARISON", elapsed,counter);
    printf("\n");
    // for(int i = 0; i < rows; ++i)
    // {
    //     for(int j = 0; j < cols; ++j) {
    //         printf("%c ", mat[i][j]);
    //     }
    //     printf("\n");
    // }


    return 0;
}