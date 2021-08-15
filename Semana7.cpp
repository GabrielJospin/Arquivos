struct Registro{
    int v1;
    int v2;
    int custo;
}REGISTRO;

int custoByAresta(char* path, int v1, int v2){

    if(v1>9|| v2>9 || v1 < 0 || v2 < 0)
        return -1;

    FILE* arq;
    int error = openFile(path,READ,&arq);
    if(error != 0)
        return error;

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