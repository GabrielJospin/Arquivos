#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
using namespace std;

//Meotode criado para a aula:
int creatTableByPositon(char* pathArchive, char* pathCreat);

struct Registro{
    int v1;
    int v2;
    int custo;
}REGISTRO;

struct Memory{
    int v1;
    int v2;
    byte position;
}MEMORY;


//<!-- DEFINE -->
#define MAX 5


//ERROS
#define NOTFOUND 404
#define ERROR 400

//MODOS DE OPERAÇÃO
#define ANNEX  "a"
#define READ_ANNEX "a+"
#define READ "r"
#define READ_BINARY "rb"
#define READ_WRITE  "r+"
#define WRITE "w"
#define WRITE_BINARY "wb"
#define NEWFILE  "w+"
#define NUMBER_MODES 8

//metodos
//
//x = fgetc(arc)  leitura
//x = fputc(caractere, arq)
//x = fgets(string, int max, arq)
//fputs(string,arq)


const char* modes[NUMBER_MODES]{
        "a",
        "a+",
        "r",
        "rb",
        "r+",
        "w",
        "wb",
        "w+"
};




int modeIsValid(char* mode){


    for(auto & i : modes) {
       if(strcmp(i,mode) != 0) {
           return 0;
       }
   }
    return ERROR;

}


int openFile(char *path, char* mode, FILE* *file){


    if(modeIsValid(mode) != 0){
        return ERROR;
    }


    if(!(*file = fopen(path,mode))){
       return NOTFOUND;
    }

    return 0;
}

int closeFile(FILE* file){
    return fclose(file);
}

int duplicate(char* pathFile, char* pathNewFile){

    int error;
    FILE* file;
    FILE* newFile;

    error = openFile(pathFile,(char*) READ,&file);
    if(error != 0)
        return error;

    error = openFile(pathNewFile,(char*)WRITE,&newFile);
    if(error != 0)
        return error;

    while(feof(file) == 0){
        char c = fgetc(file);
        fputc(c,newFile);
    }

    closeFile(file);
    closeFile(newFile);

    return 0;
}

int readDataBaseTxt (char* path){

    char c;
    int i, next;
    char name[MAX][10];
    int grade[MAX];
    FILE* file;

    int error = openFile(path,READ_BINARY,&file);
    if(error!=0){
        return error;
    }


    next = 0;
    while (!feof(file)){
        fscanf(file,"%[^/]%*c",name[next]);
        fscanf(file,"%d\n", &grade[next]);

        printf("%s", name[next]);
        printf("|%d\n",grade[next]);
        next++;
    }

    error = closeFile(file);
    if(error != 0){
        return error;
    }

    return 0;
}




int foundTxt(char* path, char* txt,int txtLength,bool* found){

    *found = false;
    FILE* file;

    int error = openFile(path,READ_BINARY,&file);
    if(error != 0){
        return error;
    }

    while (feof(file) == 0){
        char c;
        c = fgetc(file);
        if(c == txt[0]){
            for(int i = 1; i<txtLength; i++){
                c = fgetc(file);
                if(c != txt[i])
                    break;
            }
            c = fgetc(file);
            if(c == ' ' || c == '\r' || c == '\n'){
                *found = true;
                return  0;
            }
        }
    }

    return 0;
}

void printRegister(Registro registro){
    printf("%d | %s | %s | %d \n",
           &registro, registro.nrousp, registro.nome, registro.idade);
}

int criarRegistro(){
    FILE* file;

    string pathString = "..\\teste.dad";
    char *path = (char*)  malloc(sizeof(char) * pathString.length());
    strcpy(path,pathString.c_str());

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

    for (auto & aluno:alunos){
        printRegister(aluno);
    }

    int error = openFile(path,WRITE,&file);
    if(error != 0)
        return error;

    fwrite(alunos, sizeof(Registro),MAX,file);

    return closeFile(file);

}

int lerRegistros(){

    FILE* arq;
    string pathString = "..\\teste.dad";
    char *path = (char*)  malloc(sizeof(char) * pathString.length());
    strcpy(path,pathString.c_str());

    int error = openFile(path,READ,&arq);
    if(error != 0){
        return error;
    }
    Registro alunos[MAX];

    int next = 0;

    next = fread(alunos, sizeof(Registro), MAX, arq);
    if(next<1){
        printf("Arquivo vazio");
        return ERROR;
    }

    for(auto & i : alunos ){
        printf("%s| %s| %d|\n", i.nrousp, i.nome, i.idade);
    }


    error = closeFile(arq);
    if (error != 0){
        return error;
    }

    return 0;
}

int custoByAresta(char* path, int v1, int v2){

    if(v1>9|| v2>9 || v1 < 0 || v2 < 0)
        return -1;

    FILE* arq;
    int error = openFile(path,READ,&arq);
    if(error != 0)
        return -1;

    REGISTRO arestas[100];
    int next = 0;

    next = fread(arestas,sizeof(REGISTRO),100,arq);
    if(next<1){
        printf("Arquivo vazio")
        return -1;
    }

    for(int i=0;i<100;i++){
        REGISTRO temp = arestas[i];
        if(temp.v1 == v1 && temp.v2 == v2)
            return temp.custo;
    }

    return -1;
}


int creatTableByPositon(char* pathArchive, char* pathCreat){
    FILE* read;
    int error = openFile(pathArchive,"rb",&read);
    if(error != 0)
        return error;
    REGISTRO arestas[100];
    MEMORY memory[100];
    int next = 0;

    next = fread(arestas,sizeof(REGISTRO),100,arq);
    if(next<1){
        printf("Arquivo vazio")
        return 404;
    }
    for(int i=0;i<100;i++){
        REGISTRO temp = arestas[i];
        memory[i].v1 = temp.v1;
        memory[i].v2 = temp.v2;
        memory[i].position = sizeof(Registro) * i;
    }
    FILE* write;
    int error = openFile(pathCreat,"wb",&write);
    if(error != 0)
        return error;
    
    fwrite(memory, sizeof(MEMORY),100,file);
    
    return 0;

}


int newmethod(char* path,byte position1, byte position2){

    FILE* arq;
    int error = openFile(path,READ,&arq);
    if(error != 0)
        return error;

    Registro alunos[MAX];

    int next = 0;
    next = fread(alunos, sizeof(Registro), MAX, arq);lerRegistros();
    if(next<1){
        printf("Arquivo vazio");
        return ERROR;
    }

    Registro aux = alunos[position1/sizeof(Registro)];
    alunos[position2/sizeof(Registro)] = alunos[position1/sizeof(Registro)];
    alunos[position1/sizeof(Registro)] = aux;

    FILE* arq;
    int error = openFile(path,WRITE,&arq);
    if(error != 0)
        return error;

    fwrite(alunos, sizeof(Registro),MAX,file);

    return fclose(arq);
}



//  <!-- TESTES -->  </./>

int tryDupilcate(){
    string pathString = "..\\text.txt";
    string newpathString = "..\\text2.txt";



    char *path = (char*)  malloc(sizeof(char) * pathString.length());
    char *newpath = (char*)  malloc(sizeof(char) * newpathString.length());



    strcpy(path,pathString.c_str());
    strcpy(newpath,newpathString.c_str());

    int error = duplicate( path, newpath);

    return error;
}

int tryReadDataBaseTxt(){
    string pathString = "..\\grade.txt";
    char *path = (char*)  malloc(sizeof(char) * pathString.length());
    strcpy(path,pathString.c_str());

    int error = readDataBaseTxt(path);

    return error;
}

int tryFoundTxt(){
    string pathString = "..\\text.txt";
    string txtString = "marinheiros";
    char *path = (char*)  malloc(sizeof(char) * pathString.length());
    char *txt = (char*)  malloc(sizeof(char) * txtString.length());
    strcpy(path,pathString.c_str());
    strcpy(txt,txtString.c_str());

    bool teste = false;
    int error = foundTxt(path,txt,txtString.length(),&teste);

    if(teste)
        cout<<"encontrado\n";
    else
        cout<<"nao encontrado\n";

    return error;

}

int tryCriarRegistros(){
    int error = criarRegistro();

    if(error != 0){
        return error;
    }

    return lerRegistros();
}

int main() {

    int error;
//    error = tryDupilcate();
//    if(error!=0){
//        perror("Duplicate Error!!");
//        cout<<error<<"\n";
//    }

//    error = tryReadDataBaseTxt();
//    if(error!=0){
//        perror("Read Data Base Txt Error!!");
//        cout<<error<<"\n";
//    }

//    error = tryFoundTxt();
//    if(error!=0){
//        perror("found txt Error!!");
//        cout<<error<<"\n";
//    }

    error = tryCriarRegistros();
    if(error!=0){
        perror("creat register Error!!");
        cout<<error<<"\n";
    }




    return 0;
}
