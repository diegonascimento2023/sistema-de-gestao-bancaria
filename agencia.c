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


Agenciabancaria *cadastrar_conta(Agenciabancaria *agencia)
{

    char cliente[51], data[12], status[11];
    int numero;
    float saldo;
    // Variaveis utilizadas nas veririficações
    int nomeValido = 0;         // Variável para verificar se o nome da agência fornecido é válido
    bool entradaValida = false; // Variável para verificar se a data de abertura fornecida é válida
    int statusValido = 0;       // Variável para verificar se o status da conta fornecido é válido
    int numContaValido = 0;     // Variável para verificar se o numero da conta fornecido é válido
    char input[20];
    int saldoValido = 0;        // Variável para verificar se o saldo da conta fornecido é válido

    // Verifica se o nome do cliente fornecido é válido
    do
    {
        printf("Informe o nome do cliente: ");
        scanf(" %[^\n]", cliente);
        getchar(); // Limpar o buffer

        nomeValido = 1;
        for (int i = 0; cliente[i] != '\0'; i++)
        {
            if (!isalpha(cliente[i]) && !isspace(cliente[i]))
            {
                nomeValido = 0;
                break;
            }
        }

        if (!nomeValido)
        {
            printf("O nome digitado contém caracteres inválidos.\n");
        }
    } while (!nomeValido);

    // Verifica se a data de abertura fornecida é válida
    do
    {
        printf("Informe a data de abertura da conta (dd/mm/aaaa): ");
        scanf(" %11[^\n]", data);

        // Verifica se a entrada tem 10 caracteres, incluindo duas barras
        if (strlen(data) == 10)
        {
            // Verifica se os caracteres nas posições 2 e 5 são barras
            if (data[2] == '/' && data[5] == '/')
            {
                // Verifica se os caracteres restantes são dígitos numéricos
                bool isNumeric = true;
                for (int i = 0; i < 10; i++)
                {
                    if (i != 2 && i != 5 && !isdigit(data[i]))
                    {
                        isNumeric = false;
                        break;
                    }
                }
                if (isNumeric)
                {
                    entradaValida = true;
                }
            }
        }

        if (!entradaValida)
        {
            printf("Formato de data inválido. Por favor, tente novamente.\n");
        }
    } while (!entradaValida);

    // Verifica se o status da conta fornecido é válido
    do
    {
        printf("Informe o status da conta (ativa, desativada, bloqueada): ");
        scanf(" %10[^\n]", status);
        getchar(); // Limpar o buffer

        statusValido = 1;
        for (int i = 0; status[i] != '\0'; i++)
        {
            if (!isalpha(status[i]) && !isspace(status[i]))
            {
                statusValido = 0;
                break;
            }
        }

        if (!statusValido)
        {
            printf("O status digitado contém caracteres inválidos.\n");
        }
    } while (!statusValido);

    // Verifica se o numero da conta fornecido é válido
    while (1) {
        printf("Informe o numero da conta: ");
        if (fgets(input, sizeof(input), stdin)) {
            int valido = 1;

            for (int i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i]) && input[i] != '\n') {
                    valido = 0;
                    break;
                }
            }

            if (valido && sscanf(input, "%d", &numero) == 1) {
                numContaValido = 1;
                break; // Saia do loop se o número for válido
            } else {
                printf("Entrada inválida. Digite novamente (somente números):\n");
            }
        }
    }

   while (1) {
        printf("Informe o saldo da conta: ");
        char input[20];
        if (fgets(input, sizeof(input), stdin)) {
            int valido = 1;
            char *endptr;

            // Converte a entrada para um número de ponto flutuante
            saldo = strtof(input, &endptr);

            if (endptr == input) {
                valido = 0;
            } else {
                // Verifica se há caracteres não numéricos após o número
                for (int i = 0; input[i] != '\0'; i++) {
                    if (!isdigit(input[i]) && input[i] != '.' && input[i] != '\n') {
                        valido = 0;
                        break;
                    }
                }
            }

            if (valido) {
                saldoValido = 1;
                break; // Sai do loop se o saldo for válido
            } else {
                printf("Entrada inválida. Digite novamente (somente números):\n");
            }
        }
    }

    Contabancaria *aux = criar_conta(cliente, data, saldo, status, numero);

    agencia = cadastrar_cliente(aux, agencia);
    return agencia;
}


void listar_agencias(Agenciabancaria **agencias, int qntagencias)
{
    printf("\nTODAS AS CONTAS CADASTRADAS NO SISTEMA\n");
    for (int i = 0; i < qntagencias; i++)
    {
        Agenciabancaria *agencia = agencias[i];
        printf("\tAgencia %d\n", i + 1);
        printf("Nome: %s\tCódigo: %d\tLocalização: %s\tHorário: %s\n", agencias[i]->nome, agencias[i]->codigo, agencias[i]->localizacao, agencias[i]->horario);
        Lista *contas = agencia->contas;
        if (contas == NULL)
        {
            printf("Nao há contas cadastradas nessa agencia.\n");
        }
        else
        {
            printf("Contas cadastradas na agencia:\n");
            while (contas != NULL)
            {
                Contabancaria *conta = contas->conta;
                printf("Cliente: %s\tNúmero: %d\tSaldo: %.2f\tStatus: %s\n", conta->cliente, conta->numero, conta->saldo, conta->status);
                contas = contas->prox;
            }
            printf("\n");
        }
    }
}


Agenciabancaria *remove_conta(Agenciabancaria *agencia, int numero)
{

    if (agencia->contas == NULL)
    {
        return agencia;
    }
    agencia->contas = lista_remove(agencia->contas, numero);
    return agencia;
}


void liberar_agencia(Agenciabancaria *agencia)
{
    if (agencia == NULL)
        return;

    liberar_lista_contas(agencia->contas);
    free(agencia);
}


void liberar_agencias(Agenciabancaria **agencias, int qnt)
{
    for (int i = 0; i < qnt; i++)
    {
        liberar_agencia(agencias[i]);
    }
    free(agencias);
}


void salva_arquivo(Agenciabancaria **agencias, int qntdagencias)
{
    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrira \n");
    }
    for (int i = 0; i < qntdagencias; i++)
    {
        Agenciabancaria *agencia = agencias[i];
        fprintf(arquivo, "Agencia %d\tNome:%s\tCodigo:%d\tLocalizacao:%s\tHorario:%s\n", i + 1, agencia->nome, agencia->codigo, agencia->localizacao, agencia->horario);
        Lista *contas = agencia->contas;
        while (contas != NULL)
        {
            Contabancaria *conta = contas->conta;
            fprintf(arquivo, "Cliente:%s\tData:%s\tSaldo:%.2f\tStatus:%s\tNumero:%d\n", conta->cliente, conta->data, conta->saldo, conta->status, conta->numero);
            contas = contas->prox;
        }
    }
    fclose(arquivo);
}


Agenciabancaria **ler_arquivo(Agenciabancaria **agencias, int *qntd)
{
    FILE *arquivo;
    int i = 0;
    char linha[200];
    char *token;
    Contabancaria aux;

    arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao inicializar arquivo.\n");
        exit(1);
    }
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        char *test = strstr(linha, "Agencia");
        if (test != NULL)
        {
            if (i >= *qntd)
            {
                agencias = realloc(agencias, (*qntd + 1) * sizeof(Agenciabancaria *));
                if (agencias == NULL)
                {
                    printf("Erro ao alocar memoria \n");
                    exit(1);
                }
                agencias[*qntd] = malloc(sizeof(Agenciabancaria));
                if (agencias[*qntd] == NULL)
                {
                    printf("Erro ao alocar memoria \n");
                    exit(1);
                }
                (*qntd)++;
            }
            token = strtok(linha, ":");
            token = strtok(NULL, "\t");
            strcpy(agencias[i]->nome, token);
            token = strtok(NULL, ":");
            token = strtok(NULL, "\t");
            agencias[i]->codigo = atoi(token);
            token = strtok(NULL, ":");
            token = strtok(NULL, "\t");
            strcpy(agencias[i]->localizacao, token);
            token = strtok(NULL, ":");
            token = strtok(NULL, "\n");
            strcpy(agencias[i]->horario, token);
            i++;
        }

        else
        {
            token = strtok(linha, ":");
            token = strtok(NULL, "\t");
            strcpy(aux.cliente, token);
            token = strtok(NULL, ":");
            token = strtok(NULL, "\t");
            strcpy(aux.data, token);
            token = strtok(NULL, ":");
            token = strtok(NULL, "\t");
            aux.saldo = atof(token);
            token = strtok(NULL, ":");
            token = strtok(NULL, "\t");
            strcpy(aux.status, token);
            token = strtok(NULL, ":");
            token = strtok(NULL, "\n");
            aux.numero = atoi(token);
            if (agencias[i - 1] == NULL)
            {
                printf("Erro \n");
                exit(1);
            }
            Contabancaria *conta = criar_conta(aux.cliente, aux.data, aux.saldo, aux.status, aux.numero);
            agencias[i - 1] = cadastrar_cliente(conta, agencias[i - 1]);
        }
    }
    fclose(arquivo);
    return agencias;
}