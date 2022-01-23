#include <stdio.h>
#include <stdlib.h>

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

int find_word_grid(int rows, int cols, char *word, char** mat){
    int found = 0;
    int ctr = 0;
    int i,j;

    //asumsi setiap huruf pasti ada dalam puzzle
    i = 0;
    j = 0;
    while (!found) {

    }
    
}

int find_word_line();

int match_word_right(char** mat,char *target, int word_length, int text_length, int r, int c) {
    //kamus
    int i = 0;
    int j;
    int found = 0;
    while((i <= text_length-word_length) && (!found)) {
        j = 0;
        while (j < word_length && mat[r][i+j] == target[j]) {
            j += 1;
        }

        if (j == word_length) {
            found = 1;
        }
        else {
            i += 1;
        }
    }

    if (found) {
        return i;
    }
    else {
        return -1;
    }
}


int main(void)
{

    int rows = 0;
    int cols = 0;
    int word_ctr = 0;

    //cari banyak kolom, baris, dan banyak kata yang akan dicari
    get_rows_columns("input.txt",&rows,&cols,&word_ctr);

    //alokasi matriks untuk word grid
    char** mat=malloc(rows*sizeof(char*)); 
    for(int i=0;i<rows;++i) {
        mat[i]=malloc(cols*sizeof(char)); 
    }

    //baca matriks dan masukkan hasil kedalam mat
    char* word[20];
    FILE *f;
    f = fopen ("input.txt", "r");

    //mengubah matriks dalam file menjadi variable matriks
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
            fscanf(f, "%c ", &mat[i][j]);
    }

    //memulai algoritma pencarian
    for (int i = 0; i < word_ctr; i++) {
        fscanf(f,"%s", &word);
        printf("%s\n",word);
    }
    fclose (f);


    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }


    return 0;
}