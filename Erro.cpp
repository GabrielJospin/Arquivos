#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
using namespace std;


struct Registro{
    char nrousp[7];
    char nome[13];
    int idade;
}REGISTRO;

//<!-- DEFINE -->
#define MAX 5

void printRegister(Registro registro){
    printf("%d | %s | %s | %d \n",
           &registro, registro.nrousp, registro.nome, registro.idade);
}

void metodo(){
    Registro alunos[5];

    memset(alunos,0,sizeof(alunos));


    int idadeBase = 17;
    for (int i = 0; i < 5; ++i) {
        alunos[i].idade = idadeBase+i;
    }

    for (int i = 0; i < 5; ++i) {
        string num = "1234567";
        strcpy(alunos[i].nrousp,num.c_str());
    }

    for (int i = 0; i < 5; ++i) {
        string nome = "NomeDoCarinha";
        strcpy(alunos[i].nome,nome.c_str());
    }

    for (int i = 0; i<5; i++){
        printRegister(alunos[i]);
    }

}

int main(){
    metodo();
}
