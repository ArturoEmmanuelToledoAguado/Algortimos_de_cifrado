#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char alf2[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

void date();
void menu();
void write();
int submenu();
char * cleanphrase(char phrase[]);
void write(int);
void playfair(int);
void desPlayfair();
void vigenere(int);
void trans(int);

int main() {
    menu();
    return 0;
}

void date(){
    time_t t;
    struct tm *tm;
    t = time(NULL);
    tm = localtime(&t);
    printf("\t\t\t%02d-%02d-%02d\n", tm->tm_mday, tm->tm_mon, 1900+tm->tm_year);
    printf("\tBaeza Ramirez Luis Gerardo 2012010273\n");
    printf("\tSeleccione una Opcion\n");
}

int submenu(){
    char valref;
    int returnvalue;
    do{
        system("cls");
        date();
        printf("1.Cifrar texto\n2.Ver texto cifrado\n3.Descifrar texto\n4.Regresar\n");
        fflush(stdin);
        scanf("%c", &valref);
        returnvalue = valref - '0';
        switch(returnvalue){
            case 1 || 2 || 3:
                return returnvalue;
            case 4:
                printf("Adios");
                returnvalue = 0;
                break;
            default:
                printf("invalid");
                break;
        }
    }while(valref != '4');
}

void write(int valor) {
    FILE *file;
    char phrase[1024];

    if (valor == 1){
        file = fopen("Textoacifrar.txt", "w+");
        if (file == NULL){
            printf("No se ha podido abrir el archivo.\n");
            exit(1);
        }
        printf("Introduce el mensaje a cifrar\n");
        fflush(stdin);
        fgets(phrase,1024,stdin);
        char *ph = cleanphrase(phrase);
        fprintf(file,"%s", ph);
        fclose(file);
        system("pause");
    }else if (valor == 2){
        file = fopen("ClavePF.txt", "w+");
        if (file == NULL){
            printf("No se ha podido abrir el archivo.\n");
            exit(1);
        }
        printf("Ingrese una clave: ");
        fflush(stdin);
        fgets(phrase,1024,stdin);
        for(int i=0; i<strlen(phrase); i++)
            phrase[i]=tolower((unsigned char)phrase[i]);
        printf("Clave: %s\n",phrase);
        char *ph = cleanphrase(phrase);
        fprintf(file,"%s", ph);
        fclose(file);
    }
}

void menu(){
    char valref;
    int valor;
    do{
        system("cls");
        date();
        printf("1.Introducir texto a cifrar\n2.Cifrado Playfair\n3.Cifrado Vigenere\n4.Transposicion con clave\n5.Salir\n");
        scanf("%c",&valref);

        switch(valref){
            case '1':
                write(1);
                break;
            case '2':
                valor = submenu();
                (valor == 0)?:playfair(valor);
                break;
            case '3':
                valor = submenu();
                (valor == 0)?:vigenere(valor);
                break;
            case '4':
                valor = submenu();
                (valor == 0)?:trans(valor);
                break;
            case '5':
                printf("Adios");
                break;
            default:
                printf("invalid");
                break;
        }
    }while(valref != '5');

}

char * cleanphrase(char phrase[]){
    int i = 0;
    while(i <= 1024){
        if(phrase[i] == '\n'){
            phrase[i] = '\0';
        }
        i++;
    }
    return phrase;
}

void playfair(int valRef){
    system("cls");
    char clave[100], *claveLow= calloc(strlen(clave)+1, sizeof(char));
    char text[100];
    char matriz[5][5];
    int cont=0,cont2=0;//clave alfabeto
    int i=0,j=0;

    if( valRef == 1){
        write(2);
    }

    printf("Ingrese el mensaje: ");
    fflush(stdin);
    fgets(text,100,stdin);
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
                matriz[i][j]=alf2[cont2];
                for(int k=0; k<strlen(claveLow); k++){
                    if(alf2[cont2]==claveLow[k])
                        matriz[i][j]=alf2[++cont2];
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
    printf("\n");
}

void desPlayfair(){
    system("cls");
    char text[100];
    char clave[100];
    char matriz[5][5];
    int cont=0, cont2=0;//clave alfabeto
    int i=0,j=0;

    //Mensaje
    printf("Ingrese un mensaje: ");
    fflush(stdin);
    fgets(text,100,stdin);
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
    //Quitamos salto de linea
    for(int i=0; i<strlen(text); i++)
        if (text[i] == '\n')
            text[i] = '\0';

    //Clave
    printf("Ingrese una clave: ");
    scanf("%s",&clave);
    fflush(stdin);
    //Clave a minusculas
    for(int i=0; i<strlen(clave); i++) {
        if((int )clave[i]>=65 && (int )clave[i]<=90)
            clave[i] = (char )((int )clave[i]+32);
        else if((int )clave[i]>=97 && (int )clave[i]<=122)
            clave[i] = (char )((int )clave[i]);
    }

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
                matriz[i][j]=alf2[cont2];
                for(int k=0; k<strlen(clave); k++){
                    if(alf2[cont2]==clave[k])
                        matriz[i][j]=alf2[++cont2];
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

    //Decodificación
    i=0,j=1;
    while(j<=strlen(text)){
        int f1,f2,c1,c2;
        //Reemplazamos i por j
        if(text[i]=='j')
            text[i]='i';
        //Obtenemos las coordenadas
        for(int x=0;x<5;x++){
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
            if((c1-1)<0)
                text[i]=matriz[f1][4];//No max de columna
            else
                text[i]=matriz[f1][c1-1];
            if ((c2-1)<0)
                text[j]=matriz[f1][4];
            else
                text[j]=matriz[f1][c2-1];
        }else if(c1==c2){//Regla 2
            if((f1-1)<0)
                text[i]=matriz[4][c1];
            else
                text[i]=matriz[f1-1][c1];
            if((f2-1)<0)
                text[j]=matriz[4][c2];
            else
                text[j]=matriz[f2-1][c2];
        }else{
            text[i]=matriz[f1][c2];
            text[j]=matriz[f2][c1];
        }
        i=i+2;
        j=j+2;
    }

    //Mensaje
    printf("\n El mensaje descifrado es: ");
    for(int i=0;i<strlen(text);i++){
        printf("%c",text[i]);
        if(i%2!=0)
            printf(" ");
    }
    printf("\n");
}

void vigenere(int ValRef){
    system("cls");
    int coordenada1,coordenada2,coordenada3;
    char text[100],clave[100];
    fflush(stdin);
    int i=0,j=0;

    //Ingreso de mensaje
    printf("Ingrese el mensaje: ");
    fgets(text,100,stdin);
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
    //Quitamos salto de linea
    for(int i=0; i<strlen(text); i++)
        if (text[i] == '\n')
            text[i] = '\0';

    //Ingreso clave
    printf("Ingrese la clave: ");
    scanf("%s",&clave);
    fflush(stdin);
    //Clave a minusculas
    for(int i=0; i<strlen(clave); i++) {
        if((int )clave[i]>=65 && (int )clave[i]<=90)
            clave[i] = (char )((int )clave[i]+32);
        else if((int )clave[i]>=97 && (int )clave[i]<=122)
            clave[i] = (char )((int )clave[i]);
    }

    //Cifrado
    int cont=0;
    for(int i=0; i<strlen(text); i++){
        if(text[i]!=32){//32 = espacio en ASCII
            for(j=0; j<strlen(alf2); j++){//Recorremos el alfabeto
                if(text[i]==alf2[j])
                    coordenada1 = j;//Coordenada del mensaje en la tabla
                if(clave[cont%strlen(clave)]==alf2[j])
                    coordenada2 = j;//Coordenada de la clave en la tabla
            }
            //Ontenemos el caracter cifrado
            coordenada3 = (coordenada1+coordenada2)%26;
            text[i]=alf2[coordenada3];
            cont ++;
        }
    }
    printf("El mensaje cifrado es: %s\n",text);
}

void desVigenere(){
    system("cls");
    int coordenada1,coordenada2,coordenada3;
    char text[100],clave[100];
    fflush(stdin);
    int i=0,j=0;

    //Mensaje
    printf("Ingrese un mensaje: ");
    fflush(stdin);
    fgets(text,100,stdin);
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
    //Quitamos salto de linea
    for(int i=0; i<strlen(text); i++)
        if (text[i] == '\n')
            text[i] = '\0';

    //Clave
    printf("Ingrese una clave: ");
    scanf("%s",&clave);
    fflush(stdin);
    //Clave a minusculas
    for(int i=0; i<strlen(clave); i++) {
        if((int )clave[i]>=65 && (int )clave[i]<=90)
            clave[i] = (char )((int )clave[i]+32);
        else if((int )clave[i]>=97 && (int )clave[i]<=122)
            clave[i] = (char )((int )clave[i]);
    }

    //Descifrado
    int cont=0;
    for(int i=0; i<strlen(text); i++){
        if(text[i]!=32){//Espacio en ASCII
            for(int j=0; j<strlen(alf2); j++){
                if(text[i]==alf2[j])
                    coordenada3=j;
                if(clave[cont%strlen(clave)]==alf2[j])
                    coordenada1=j;
            }if((coordenada3-coordenada1)<0)
                coordenada2=26+(coordenada3-coordenada1);
            else
                coordenada2=(coordenada3-coordenada1)%26;
            text[i]=alf2[coordenada2];
            cont++;
        }
    }
    printf("El mensaje descifrado es: %s\n",text);
}

void trans(int ValRef) {
    system("cls");
    char text[100];
    int orden[5]={0, 0, 0, 0, 0};

    //Clave
    printf("\tIngrese la orden (numeros del 1-5 en desorden)\n");
    for(int i=0;i<5;i++){
        printf("Ingrese un numero: ");
        scanf("%i", &orden[i]);
        for(int j=0;j<=i;j++){
            if(orden[i] == orden[j - 1]){
                printf("Numero ya ingresado, ingrese otro\n");
                i--;
            }else if(orden[i] >= 6 || orden[i] <= 0){
                printf("Numero no valido, ingrese otro\n");
                i--;
            }
        }
    }

    //Mensaje
    printf("\nIngrese un mensaje: ");
    fflush(stdin);
    fgets(text, 100, stdin);
    //Mensaje a minusculas
    for (int i = 0; i < strlen(text); i++) {
        if ((int) text[i] >= 65 && (int) text[i] <= 90)
            text[i] = (char) ((int) text[i] + 32);
        else if ((int) text[i] >= 97 && (int) text[i] <= 122)
            text[i] = (char) ((int) text[i]);
    }
    //Mensaje sin espacios
    int i = 0, j = 0;
    while (text[i] != '\0') {
        if (text[i] != ' ') {
            text[j] = text[i];
            fflush(stdin);
            j++;
        }
        i++;
    }
    //Quitamos salto de linea
    for (int i = 0; i < strlen(text); i++)
        if (text[i] == '\n')
            text[i] = '\0';
    //Modulo para hacer bloques de 5 y rellenar con x
    for (int i = 0; i < strlen(text); i++) {
        if (strlen(text) % 5 != 0) {
            text[strlen(text) + 1] = '\0';
            text[strlen(text)] = 'x';
        }
    }
    //Quitamos salto de linea
    for (int i = 0; i < strlen(text); i++)
        if (text[i] == '\n')
            text[i] = '\0';

    //Cifrado
    char aux[5];
    int k=0,k1=0;
    fflush(stdin);
    int cont=(strlen(text))/5;
    char ciftext[strlen(text)];

    //Uso de auxiliar para guardar 5 caracteres
    for(int i = 0; i < cont; i++){
        for(int j=i*5; j<((i+1)*5);j++) {
            aux[k]=text[j];
            k++;
        }
        k=0;
        //Quitamos el inicio de encabezado (☺)
        for (int i = 0; i < strlen(aux); i++)
            if (aux[i] == 1)//Codigo ASCII para inicio de encabezado(☺)
                aux[i] = '\0';
        //Se reacomodan los caracteres en base a la orden en ciftex
        for(int j=0;j<strlen(aux);j++){
            fflush(stdin);
            ciftext[k1]=aux[orden[j] - 1];
            k1++;
        }
    }
    //Eliminador de basura
    for(int m=0;m<strlen(ciftext);m++){
        if(m>=strlen(text))
            ciftext[m]=NULL;
    }
    printf("El mensaje cifrado es: %s\n",ciftext);
}

void desTranClave(){
    system("cls");
    char text[100];
    int clave[5]={0,0,0,0,0}, orden[5]={1,2,3,4,5};

    //Clave
    printf("\tIngrese la clave (numeros del 1-5 en desorden)\n");
    for(int i=0;i<5;i++){
        printf("Ingrese un numero: ");
        scanf("%i", &clave[i]);
        for(int j=0;j<=i;j++){
            if(clave[i]==clave[j-1]){
                printf("Numero ya ingresado, ingrese otro\n");
                i--;
            }else if(clave[i]>=6 || clave[i]<=0){
                printf("Numero no valido, ingrese otro\n");
                i--;
            }
        }
    }

    //Mensaje
    printf("\nIngrese un mensaje: ");
    fflush(stdin);
    fgets(text, 100, stdin);
    //Mensaje a minusculas
    for (int i = 0; i < strlen(text); i++) {
        if ((int) text[i] >= 65 && (int) text[i] <= 90)
            text[i] = (char) ((int) text[i] + 32);
        else if ((int) text[i] >= 97 && (int) text[i] <= 122)
            text[i] = (char) ((int) text[i]);
    }
    //Mensaje sin espacios
    int i = 0, j = 0;
    while (text[i] != '\0') {
        if (text[i] != ' ') {
            text[j] = text[i];
            fflush(stdin);
            j++;
        }
        i++;
    }
    //Quitamos salto de linea
    for (int i = 0; i < strlen(text); i++)
        if (text[i] == '\n')
            text[i] = '\0';
    //Modulo para hacer bloques de 5 y rellenar con x
    for (int i = 0; i < strlen(text); i++) {
        if (strlen(text) % 5 != 0) {
            text[strlen(text) + 1] = '\0';
            text[strlen(text)] = 'x';
        }
    }
    //Quitamos salto de linea
    for (int i = 0; i < strlen(text); i++)
        if (text[i] == '\n')
            text[i] = '\0';

    //Descifrado
    char aux[5], aux2[5];
    int k=0,k1=0;
    fflush(stdin);
    int cont=(strlen(text))/5;
    char desciftext[strlen(text)];

    //Uso de auxiliar para guardar 5 caracteres
    for(int i = 0; i < cont; i++){
        for(int j=i*5; j<((i+1)*5);j++) {
            aux[k]=text[j];
            k++;
        }
        k=0;
        //Quitamos el inicio de encabezado (☺)
        for (int i = 0; i < strlen(aux); i++)
            if (aux[i] == 1)//Codigo ASCII para inicio de encabezado(☺)
                aux[i] = '\0';
        //Se reacomodan los caracteres en base al orden
        for(int j=0;j<strlen(aux);j++){
            fflush(stdin);
            aux2[clave[j]-1]=aux[j];
        }
        //Eliminador de basura
        for(int m=0;m<strlen(aux2);m++){
            if(m>=strlen(aux))
                aux2[m]=NULL;
        }
        for(int n=0;n<strlen(aux2);n++){
            desciftext[k1]=aux2[n];
            k1++;
        }
    }
    //Eliminador de basura
    for(int m=0;m<strlen(desciftext);m++){
        if(m>=strlen(text))
            desciftext[m]=NULL;
    }
    printf("El mensaje descifrado es: %s\n",desciftext);
}