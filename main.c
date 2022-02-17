#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char alf[] = {'a','b','c','d','e','f','g','h','i','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

char *Mat(char matriz[5][5]){

}

void playfair(){
    char clave[100], *claveLow= calloc(strlen(clave)+1, sizeof(char));
    char text[100];
    char matriz[5][5];
    int cont=0,cont2=0;//clave alfabeto
    int i=0,j=0;

    printf("Ingrese una clave: ");
    scanf("%s",&clave);
    fflush(stdin);
    //Clave a minusculas
    for(int i=0; i<strlen(clave); i++)
        claveLow[i]=tolower((unsigned char)clave[i]);
    printf("Clave: %s\n",claveLow);

    printf("Ingrese el mensaje: ");
    fflush(stdin);
    fgets(text,100,stdin);
    //Quitamos salto de linea
    for(int i=0; i<strlen(text); i++)
        if (text[i] == '\n')
            text[i] = '\0';

    //Mensaje a minusculas
    for(int i=0; i<strlen(text); i++) {
        if((int )text[i]>=65 && (int )text[i]<=90)
            text[i] = (char )((int )text[i]+32);
        else if((int )text[i]>=97 && (int )text[i]<=122)
            text[i] = (char )((int )text[i]);
    }

    //Mensaje sin espacios
    while(text[i]!='\0'){
        if(text[i]!=' '){
            text[j]=text[i];
            fflush(stdin);
            j++;
        }
        i++;
    }

    //Letras repetidas
    i=0,j=1;
    while(j<=strlen(text)){
        //Si son letras = agregamos un valor (recorremos las letras)
        if(text[i]==text[j]){
            for (int k=strlen(text)+1;k>j;k--){
                text[k]=text[k-1];
                fflush(stdin);
            }
            text[j]='x';//Sustituimos letra repetida
            fflush(stdin);
        }
        i=i+2;
        j=j+2;
    }

    //Modulo para hacer pares y rellenar con x
    if(strlen(text)%2!=0){
        text[strlen(text)+1]='\0';
        text[strlen(text)]='x';
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
    printf("\n");
    for (int i=0; i<5; i++) {
        for (int j = 0; j < 5; j++)
            printf("[%c]", matriz[i][j]);
        printf("\n");
    }
    printf("\n");

    i=0,j=1;
    while(j<=strlen(text)){
        int f1,f2,c1,c2;
        //Cambiar j por i
        if(text[i]=='j')
            text[i]='i';
        fflush(stdin);
        //Obtenemos las coordenadas
        for(int x=0; x<5; x++){
            for(int y=0; y<5; y++){
                if(text[i]==matriz[x][y]){
                    f1=x;
                    c1=y;
                }
                if(text[j]==matriz[x][y]){
                    f2=x;
                    c2=y;
                }
            }
        }
        if(f1==f2){//Regla 1
            text[i]=matriz[f1][(c1+1)%5];
            text[j]=matriz[f1][(c2+1)%5];
        }else if(c1==c2){//Regla 2
            text[i]=matriz[(f1+1)%5][c1];
            text[j]=matriz[(f2+1)%5][c1];
        }else{//Regla 3
            text[i]=matriz[f1][c2];
            text[j]=matriz[f2][c1];
        }
        i=i+2;
        j=j+2;
    }
    printf("El mensaje cifrado es: ");
    for(int i=0; i<strlen(text); i++){
        printf("%c",text[i]);
        if(i%2!=0)
            printf(" ");
    }
}

void desPlayfair(){
    char text[100], text2[100];
    char clave[100];
    char matriz[5][5];
    int cont=0, cont2=0;//clave alfabeto

    printf("Ingrese una clave: ");
    scanf("%s",&clave);
    fflush(stdin);
    //Clave a minusculas
    for(int i=0; i<strlen(clave); i++) {
        printf("%i", clave[i]);
        if((int )clave[i]>=65 && (int )clave[i]<=90)
            clave[i] = (char )((int )clave[i]+32);
        else if((int )clave[i]>=97 && (int )clave[i]<=122)
            clave[i] = (char )((int )clave[i]);
    }
    printf("\n %i \n",strlen(clave));
    printf("Clave: %i %s\n",strlen(clave),clave);

    //Llenar la matriz con nada
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            matriz[i][j]='\0';

    //Llenar la matriz con la clave
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(cont<strlen(clave)) {
                matriz[i][j]=clave[cont];
                cont++;
            }
        }
    }
    fflush(stdin);

    //Llenar la matriz con el alfabeto
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++){
            if(matriz[i][j]=='\0'){
                matriz[i][j]=alf[cont2];
                for(int k=0; k<strlen(clave); k++){
                    if(alf[cont2]==clave[k])
                        matriz[i][j]=alf[++cont2];
                }
                cont2 ++;
            }
        }
    }

    //Mostramos la matriz
    printf("\n");
    for (int i=0; i<5; i++) {
        for (int j = 0; j < 5; j++)
            printf("[%c]", matriz[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    playfair();
    //desPlayfair();
    return 0;
}