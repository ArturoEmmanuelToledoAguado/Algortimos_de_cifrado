#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char alf[] = {'a','b','c','d','e','f','g','h','i','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

void playfair(){
    char clave[100], *claveLow= calloc(strlen(clave)+1, sizeof(char));
    char text[100], *textLow= calloc(strlen(text)+1, sizeof(char));
    char matriz[5][5];
    int cont=0,cont2=0;//clave alfabeto
    char textEs[100];
    int i=0,j=0;

    printf("Ingrese una clave: ");
    scanf("%s",&clave);
    fflush(stdin);
    //Clave a minusculas
    for(int i=0; i<strlen(clave); i++)
        claveLow[i]=tolower((unsigned char)clave[i]);
    printf("Clave: %s\n",claveLow);

    printf("Ingrese el mensaje: ");
    fgets(text,100,stdin);
    fflush(stdin);
    //Mensaje a minusculas
    for(int i=0; i<strlen(text); i++)
        textLow[i]=tolower((unsigned char)text[i]);
    fflush(stdin);
    //Mensaje sin espacios
    while(textLow[i]!='\0'){
        if(textLow[i]!=' '){
            textEs[j]=textLow[i];
            fflush(stdin);
            j++;
        }
        i++;
    }

    //Letras repetidas
    i=0,j=1;
    while(j<=strlen(textEs)){
        //Si son letras = agregamos un valor (recorremos las letras)
        if(textEs[i]==textEs[j]){
            for (int k=strlen(textEs)+1;k>j;k--){
                textEs[k]=textEs[k-1];
                fflush(stdin);
            }
            textEs[j]='x';//Sustituimos letra repetida
            fflush(stdin);
        }
        i=i+2;
        j=j+2;
    }

    //Modulo para hacer pares y rellenar con x
    if(strlen(textEs)%2!=0){
        textEs[strlen(textEs)+1]='\0';
        textEs[strlen(textEs)]='x';
    }

    //Llenado de la matriz con nada
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            matriz[i][j]='\0';

    //Llenar la matriz con la clave
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(cont<strlen(claveLow)) {
                matriz[i][j]=claveLow[cont];
                cont++;
            }
        }
    }

    //Llenar la matriz con el alfabeto
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++){
            if(matriz[i][j]=='\0'){
                matriz[i][j]=alf[cont2];
                for(int k=0; k<strlen(claveLow); k++){
                    if(alf[cont2]==claveLow[k])
                        matriz[i][j]=alf[++cont2];
                }
                cont2 ++;
            }
        }
    }

    //Mostramos la matriz
    for (int i=0; i<5; i++) {
        for (int j = 0; j < 5; j++)
            printf("[%c]", matriz[i][j]);
        printf("\n");
    }
    printf("\n");

    i=0,j=1;
    while(j<=strlen(textEs)){
        int f1,f2,c1,c2;
        //Cambiar j por i
        if(textEs[i]=='j')
            textEs[i]='i';
        fflush(stdin);
        //Obtenemos las coordenadas
        for(int x=0; x<5; x++){
            for(int y=0; y<5; y++){
                if(textEs[i]==matriz[x][y]){
                    f1=x;
                    c1=y;
                }
                if(textEs[j]==matriz[x][y]){
                    f2=x;
                    c2=y;
                }
            }
        }
        if(f1==f2){//Regla 1
            textEs[i]=matriz[f1][(c1+1)%5];
            textEs[j]=matriz[f1][(c2+1)%5];
        }else if(c1==c2){//Regla 2
            textEs[i]=matriz[(f1+1)%5][c1];
            textEs[j]=matriz[(f2+1)%5][c1];
        }else{//Regla 3
            textEs[i]=matriz[f1][c2];
            textEs[j]=matriz[f2][c1];
        }
        i=i+2;
        j=j+2;
    }
    printf("El mensaje cifrado es: ");
    for(int i=0; i<strlen(textEs); i++){
        printf("%c",textEs[i]);
        if(i%2!=0)
            printf(" ");
    }
}

int main() {
    playfair();
    return 0;
}