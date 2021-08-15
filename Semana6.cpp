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

