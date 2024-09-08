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


int comparaContas(const char *conta1, const char *conta2) {
    while (*conta1 && *conta2) {
        char c1 = tolower(*conta1);
        char c2 = tolower(*conta2);

        if (c1 != c2) {
            return c1 - c2;
        }

        conta1++;
        conta2++;
    }

    return tolower(*conta1) - tolower(*conta2);
}


Lista *lista_insere_ordena(Lista *k, Contabancaria *conta)
{
    Lista *novo;
    Lista *ant = NULL;
    Lista *p = k;
    while (p != NULL && comparaContas(p->conta->cliente, conta->cliente) < 0)
    {
        ant = p;
        p = p->prox;
    }
    novo = (Lista *)malloc(sizeof(Lista));
    novo->conta = conta;
    if (ant == NULL)
    {
        novo->prox = k;
        k = novo;
    }
    else
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    return k;
}


Agenciabancaria *cadastrar_cliente(Contabancaria *contabancaria, Agenciabancaria *agenciabancaria)
{

    agenciabancaria->contas = lista_insere_ordena(agenciabancaria->contas, contabancaria);

    return agenciabancaria;
}