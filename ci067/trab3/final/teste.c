#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int** convol(int **pgm, int linha, int coluna,int kern[3][3]){
    int** Res;
    int x,y, sum = 0;
    Res = (int **) malloc(sizeof(int *)*linha);
    for (x=0; x < linha; x++){      
        Res[x] = (int *) malloc(sizeof(int)*coluna);  
    }   
    
    for (x=1; x < linha-1; x++){   
        for (y=1; y < coluna-1; y++){
            
            sum += kern[0][0]*pgm[x-1][y-1];
            sum += kern[0][1]*pgm[x][y-1];
            sum += kern[0][2]*pgm[x+1][y-1]; 
            sum += kern[1][0]*pgm[x-1][y]; 
            sum += kern[1][1]*pgm[x][y]; 
            sum += kern[1][2]*pgm[x+1][y];
            sum += kern[2][0]*pgm[x-1][y+1];
            sum += kern[2][1]*pgm[x][y+1];
            sum += kern[2][2]*pgm[x+1][y+1];
            Res[x][y] = sum;
            sum = 0;
             
        }
    }
    return (Res);
}

int ** contorno(int ** Gx, int ** Gy, int linha, int coluna){
    int ** Result;
    int x, y;
    Result = (int **) malloc(sizeof(int *)*linha);
    for (x=0; x < linha; x++){      
        Result[x] = (int *) malloc(sizeof(int)*coluna);  
    }
    int Magn;
        for (x=1; x < linha-1; x++){
        for (y=1; y < coluna-1; y++){
            Magn = (Gx[x][y]*Gx[x][y])+(Gy[x][y]*Gy[x][y]);
            Result[x][y] = sqrt(Magn);
        }
    }
    return(Result);
}

void imprimeImg(int **placa, int lin, int col){
    int x,y;
    for (x=0; x < lin; x++){
        for (y=0; y < col; y++){
            printf("%d ", placa[x][y]);
        }
    }
}

int** inicializaImg(FILE *pgm, int linha, int coluna){
    int** placa;
    int x,y;
    placa = (int **) malloc(sizeof(int *)*linha);
    for (x=0; x < linha; x++){      
        placa[x] = (int *) malloc(sizeof(int)*coluna);  
    }   
    for (x=0; x < linha; x++){
        for (y=0; y < coluna; y++){
            fscanf(pgm,"%d", &placa[x][y]);
        }
    }
    //printf("%d %d\n",x,y);
    //imprimeImg(placa, linha, coluna);
    
    return (placa);
}




int main(int argc, char* argv[]){
    fflush(stdin);
    //printf("chegou aqui!" );
    FILE *imagemPgm;
    int **matrizImg = NULL;
    int lin, col,ton;
    char tipo[10];
    int kernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernelY[3][3] = {{1, 2, 1},  {0, 0, 0},  {-1, -2, -1}};
    int **sobel_x = NULL;
    int **sobel_y = NULL;
    int **Result_sobel = NULL;

    //abre o arquivo
    imagemPgm = fopen(argv[1], "r");     
    rewind(imagemPgm);

    //le os atributos
    fscanf(imagemPgm," %s %d %d %d", tipo, &lin, &col, &ton);
    //printf("chegou aqui!" );
    //le o conteudo da img
    matrizImg = inicializaImg(imagemPgm, lin, col);
    //printf("chegou aqui!" );

    //convolucao X
    sobel_x = convol(matrizImg, lin, col, kernelX);

    //convolucao Y
    sobel_y = convol(matrizImg, lin, col, kernelY);
    
    //calculo de magnitude final
    Result_sobel = contorno(sobel_x, sobel_y, lin, col);


    //limiar = bordaLimiar(matrizImg, lin, col);
    //binarizaPlaca(matrizImg, lin, col, limiar);
    
    printf("%s \n", tipo);
    printf("%d %d \n", lin, col);
    printf("%d \n", ton);

 
    imprimeImg(Result_sobel, lin, col);
    fflush(stdout);
    return 0;
}


