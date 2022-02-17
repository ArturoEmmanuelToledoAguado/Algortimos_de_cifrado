#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char alf[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

//Se define la matris de 5x5 para Playfair
int matrizVacia (char caracter, char matriz[5][5]){
    for(int  i=0; i<5; i++){
        for(int j=0; i<5; j++){
            //Comprobamos si el caracter esta dentro de la matriz
            if(caracter == matriz[i][j]){
                return 1;
            }
        }
    }
    return -1;
}

void ingresarDatos(char clave[], char matriz[5][5]){
    printf("\nEn ingresar datos");
    int f=0,c=0;
    int aux;
    //Llenamos la matriz con la clave
    printf("\nLleno matriz con clave");
    for(int i=0; i<strlen(clave); i++){
        aux = matrizVacia(clave[i],matriz);
        //Validamos el caracter j en ASCII (106)
        if(aux==-1 && clave[i]!=106){
            //Preguntamos si llegamos al fin de la columna
            if(c==5){
                //Aumentamos el contador de fila y reiniciamos columna
                f++;
                c=0;
            }
            //Guardamos el valor en la matriz y aumentamos contador columna
            matriz[f][c]=clave[i];
            c++;
        }
    }
    printf("\nClave lista\nResto alfabeto\n");
    //Llenamos el resto de la matriz con el alfabeto
    for(int i=0; i<strlen(alf); i++){
        printf("Antes de llenar\n");
        aux = matrizVacia(alf[i],matriz);
        printf("Llenado\n");
        //Validamos el caracter j en ASCII (106)
        if(aux==-1 && alf[i]!=106){
            if(c==5){
                f++;
                c=0;
            }
            matriz[f][c]=alf[i];
            c++;
        }
    }
    printf("Alfabeto listo");
}

void formato(char men2[], char menL[]){
    printf("\nEn formato");
    int i=0,j=0;
    //Quitamos los espacios
    for(int k=0; k<strlen(menL); k++){
        if(menL[i]!=32){//Código ASCII para espacio
            men2[j]=menL[k];
            j++;
        }
    }
    men2[j]='\0';
    j=1;
    while(j<=strlen(men2)){
        //Comprobamos si se repiten letras como ll
        if(men2[i]==men2[j]){
            //Recorremos la palabra y rellenamos con x
            for(int k=strlen(men2)+1; k>j; k--)
                men2[k]=men2[k-1];
            men2[j]='x';
        }
        i=i+2;
        j=j+2;
    }
    //Comprobamos que se puedan hacer pares de letras, de lo contrario se agrega espacio y una x
    if(strlen(men2)%2 != 0){
        men2[strlen(men2)+1]='\0';
        men2[strlen(men2)]='x';
    }
}

void playFair(){
    char clave[100], claveL[100];
    char men[100], menL[100];
    char matriz[5][5];
    printf("Ingrese clave: ");
    scanf("%s",&clave);
    fflush(stdin);
    printf("\nIngrese mensaje: ");
    scanf("%s",&men);
    fflush(stdin);
    //Clave a minusculas
    for(int i=0; i<strlen(clave); i++)
        claveL[i] = tolower((unsigned char) clave[i]);
    //Mensaje a minusculas
    for(int i=0; i<strlen(men); i++)
        menL[i] = tolower((unsigned char) men[i]);

    //Inicializar la matriz
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            matriz[i][j]='\0';
    printf("Ingreso Datos");
    ingresarDatos(claveL, matriz);
    printf("\nDatos ingresados");

    fflush(stdin);
    char men2[100];
    printf("\nFormato");
    formato(men2,menL);
    printf("\nFormato listo");
    int i=0,j=1;
    while(j<=strlen(men2)){
        int f1,f2,c1,c2;
        //Se remplazan j por i
        if(men2[i]=='j')
            men2[i]='i';
        //Obtencion de cordenadas en la matriz (regla 3 base)
        for(int x=0; x<5; x++){
            for(int y=0; y<5; y++){
                if(men2[i]==matriz[x][y]){
                    f1=x;
                    c1=y;
                }
                if(men2[j]==matriz[x][y]){
                    f2=x;
                    c2=y;
                }
            }
        }
        //Regla 1
        if(f1==f2){
            men2[i]=matriz[f1][(c1+1)%5];
            men2[j]=matriz[f1][(c2+1)%5];
        }else if(c1==c2){//Regla 2
            men2[i]=matriz[(f1+1)%5][c1];
            men2[j]=matriz[(f2+1)%5][c2];
        }else{//Regla 3
            men2[i]=matriz[f1][c2];
            men2[j]=matriz[f2][c2];
        }
        i=i+2;
        j=j+2;
    }
    printf("El mensaje cifrado es: ");
    for(int i=0; i<strlen(men2); i++)
        printf("%c",men2[i]);
}

int main() {
    playFair();
    return 0;
}