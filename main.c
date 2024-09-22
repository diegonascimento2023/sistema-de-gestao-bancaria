
#include "agencia.h"
#include "contaBancaria.h"

Agencia *ler_agencias(FILE *file); // Apenas a declaração de ler_agencias

int main() {
    Agencia *raiz_agencias = NULL;

    // Tentar abrir o arquivo para leitura
    FILE *file = fopen("dados.txt", "r");
    if (file) {
        // Ler agências do arquivo
        raiz_agencias = ler_agencias(file);
        fclose(file);
    } else {
        // Se o arquivo não existe, criar um novo
        file = fopen("dados.txt", "w");
        if (file) {
            fclose(file);
        }
    }

    int opcao;
    do {
        printf("\n1. Adicionar nova agência");
        printf("\n2. Adicionar nova conta bancária");
        printf("\n3. Listar todas as agências e contas bancárias");
        printf("\n4. Buscar agência pelo código");
        printf("\n5. Sair");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int codigo;
                char nome[51], localizacao[101], horario[20];
                printf("Digite o código da agência: ");
                scanf("%d", &codigo);
                printf("Digite o nome da agência: ");
                scanf(" %[^\n]", nome);
                printf("Digite a localização da agência: ");
                scanf(" %[^\n]", localizacao);
                printf("Digite o horário da agência: ");
                scanf(" %[^\n]", horario);

                Agencia *novaAgencia = criar_agencia(codigo, nome, localizacao, horario);
                inserir_agencia(&raiz_agencias, novaAgencia);

                // Salvar a nova agência imediatamente no arquivo
                file = fopen("dados.txt", "a");
                if (file) {
                    fprintf(file, "Agencia %d\tNome:%s\tLocalizacao:%s\tHorario:%s\n", 
                            codigo, nome, localizacao, horario);
                    fclose(file);
                }
                break;
            }
            case 2: {
                int numero, agenciaNumero;
                char nomeCliente[51], dataAbertura[11], status[10];
                float saldo;

                printf("Digite o número da conta: ");
                scanf("%d", &numero);
                printf("Digite o número da agência: ");
                scanf("%d", &agenciaNumero);
                
                // Verificar se a agência existe
                Agencia *agencia = buscar_agencia(raiz_agencias, agenciaNumero);
                if (agencia == NULL) {
                    printf("Agência não encontrada.\n");
                    char opcaoNovo;
                    printf("Deseja criar uma nova agência (s/n) ou ver as agências disponíveis (v)? ");
                    scanf(" %c", &opcaoNovo);
                    
                    if (opcaoNovo == 's') {
                        // Criar nova agência
                        int codigo;
                        char nome[51], localizacao[101], horario[20];
                        printf("Digite o código da nova agência: ");
                        scanf("%d", &codigo);
                        printf("Digite o nome da nova agência: ");
                        scanf(" %[^\n]", nome);
                        printf("Digite a localização da nova agência: ");
                        scanf(" %[^\n]", localizacao);
                        printf("Digite o horário da nova agência: ");
                        scanf(" %[^\n]", horario);

                        Agencia *novaAgencia = criar_agencia(codigo, nome, localizacao, horario);
                        inserir_agencia(&raiz_agencias, novaAgencia);
                    } else if (opcaoNovo == 'v') {
                        listar_agencias(raiz_agencias);
                    }
                    agencia = buscar_agencia(raiz_agencias, agenciaNumero);
                }

                if (agencia) {
                    printf("Digite o nome do cliente: ");
                    scanf(" %[^\n]", nomeCliente);
                    printf("Digite a data de abertura (dd/mm/aaaa): ");
                    scanf(" %[^\n]", dataAbertura);
                    printf("Digite o saldo: ");
                    scanf("%f", &saldo);
                    printf("Digite o status da conta: ");
                    scanf(" %[^\n]", status);

                    // Criar a nova conta
                    ContaBancaria *novaConta = criar_conta(numero, agenciaNumero, nomeCliente, dataAbertura, saldo, status);
                    inserir_conta(&(agencia->contas), novaConta);

                    // Salvar a nova conta no arquivo
                    file = fopen("dados.txt", "a");
                    if (file) {
                        fprintf(file, "\tConta %d\tCliente:%s\tData:%s\tSaldo:%.2f\tStatus:%s\n", 
                                numero, nomeCliente, dataAbertura, saldo, status);
                        fclose(file);
                    }
                }
                break;
            }
            case 3:
                listar_agencias(raiz_agencias);
                break;
            case 4: {
                int codigo;
                printf("Digite o código da agência: ");
                scanf("%d", &codigo);
                Agencia *agencia = buscar_agencia(raiz_agencias, codigo);
                if (agencia) {
                    printf("Agência encontrada: %d, Nome: %s, Localização: %s, Horário: %s\n",
                           agencia->codigo, agencia->nome, agencia->localizacao, agencia->horario);
                    listar_contas_agencia(agencia->contas, agencia->codigo);
                } else {
                    printf("Agência não encontrada.\n");
                }
                break;
            }
        }
    } while (opcao != 5);

    // Libera memória e salva tudo antes de sair
    file = fopen("dados.txt", "w"); // Reabre para salvar tudo
    if (file) {
        salvar_agencias(raiz_agencias, file);
        fclose(file);
    }

    liberar_agencias(raiz_agencias);
    return 0;
}
