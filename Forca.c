#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include "forca.h"

char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

void abertura(){
    printf("*******************\n");
    printf("*  Jogo da Forca  *\n");
    printf("*******************\n\n");
}

void tentativa(){
    char chute;
    scanf(" %c", &chute);
      
    chutes[chutesdados] = chute;
    chutesdados++;

}

int jachutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void escolhepalavra() {
    FILE* f;

    f = fopen("palavras.txt", "r");

    if(f == 0) {
        printf("Erro abrindo arquivo: %s\n", strerror(errno));
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int chuteserrados(){

    int erros = 0;

    for(int i = 0; i < chutesdados; i++){
        int existe = 0;
        
        for(int j = 0; j < (int)strlen(palavrasecreta); j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }

        if (!existe) erros++;
    }
    return erros;
}

int enforcou(){
    

    return chuteserrados()>= 7;
}

int ganhou(){
    for(int i = 0; i < (int)strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

void desenhaforca(){


    int erros = chuteserrados();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%C    \n",(erros >= 1 ? '(' : ' '),(erros >= 1 ? '_' : ' '),(erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c   \n",(erros >= 3 ? '\\' : ' '),(erros >= 2 ? '|' : ' '),(erros >= 4 ? '/' : ' '));
    printf(" |       %c     \n",(erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n",(erros >= 5 ? '/' : ' '),(erros >= 6 ? '\\' : ' '));
    printf(" |            \n");
    printf("_|___          \n");
    printf("\n\n");
    
    if (erros == 6){
        printf("Ultima chance!\n\n");
    }
    
    for (int i = 0; i < (int)strlen(palavrasecreta); i++)  {

            int achou = jachutou(palavrasecreta[i]);

            if (achou){
                printf("%c ", palavrasecreta[i]);
            }   
            else{
                printf("_ ");
            }
            
        }
        printf("\n");
}

void novapalavra(){
    char quer;

    printf("Voce quer adcionar uma nova palavra? (S/N)\n");
    scanf(" %c", &quer);

    if(quer == 'S'){
        char novapalavra[20];
        printf("Qual a nova palavra?\n");
        scanf("%s", novapalavra);
        
        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Erro abrindo arquivo: %s\n", strerror(errno));
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);   
    }

}

void letrasusadas(){

    printf("Chutes: ");
    for (int i = 0; i < chutesdados; i++) {
        printf("%c ", chutes[i]);
    }
    printf("\n");
}

int main(){

    escolhepalavra();

    do{

        abertura();
        letrasusadas();
        desenhaforca();
        tentativa();
        system("cls");
    
    } while (!ganhou() && !enforcou());
    
    if(ganhou()){
        printf("A palavra Secreta era: %s\n", palavrasecreta);
        printf("  _______     \n");     
        printf(" |/      |    \n");     
        printf(" |            \n");     
        printf(" |            \n");     
        printf(" |       (_)  \n");        
        printf(" |       /|\\  \n");        
        printf(" |        |   \n");      
        printf("_|___    / \\ \n\n");
        printf("\nVOCE GANHOU!!!\n\n");
        printf("   '._==_==_=_.'\n");
        printf("   .-\\:      /-.\n");
        printf("  | (|:.     |) |\n");
        printf("   '-|:.     |-'\n");
        printf("     \\::.    /\n");
        printf("      '::. .'\n");
        printf("        ) (\n");
        printf("      _.' '._\n");
        printf("     '-------'\n");
    }
    else{
        printf("A palavra Secreta era: %s\n", palavrasecreta);
        printf("  _______     \n");     
        printf(" |/      |    \n");     
        printf(" |      (_)   \n");     
        printf(" |       |    \n");     
        printf(" |      /|\\  \n");        
        printf(" |      / \\  \n");        
        printf(" |            \n");      
        printf("_|___         \n\n");
        printf("     .-'~~~`-.\n");
        printf("   .'         `.\n");
        printf("   |  R  I  P  |\n");
        printf("   |           |\n");
        printf("   |           |\n");
        printf(" \\\\|           |//\n");
        printf("^^^^^^^^^^^^^^^^^^^^^\n");
    }

    novapalavra();

    return 0;
}