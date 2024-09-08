struct agenciabancaria
{

    char nome[51];
    int codigo;
    char localizacao[31];
    Lista *contas;
    char horario[15];
};


Agenciabancaria *criar_agencia(char *nome, int codigo, char *localizacao, char *horario)
{

    Agenciabancaria *criar_agencia = (Agenciabancaria *)malloc(sizeof(Agenciabancaria));
    if (criar_agencia == NULL)
    {

        printf("Variavel criar_agencia nao foi alocada dinamicamente! \n");
        exit(1);
    }
    strcpy(criar_agencia->nome, nome);
    criar_agencia->codigo = codigo;
    strcpy(criar_agencia->localizacao, localizacao);
    strcpy(criar_agencia->horario, horario);
    criar_agencia->contas = NULL;

    return criar_agencia;
}