typedef struct agenciabancaria Agenciabancaria;



//funcao para criar agencia bancaria
Agenciabancaria *criar_agencia(char *nome, int codigo, char *localizacao, char *horario);

// Funcao para comparar duas strings, ignorando a diferenciaÃ§Ã£o entre maiÃºsculas e minÃºsculas.
int comparaContas(const char *conta1, const char *conta2);

//funcao para lista em ordem
Lista *lista_insere_ordena(Lista *k, Contabancaria *conta);

// funcao para cadastrar cliente
Agenciabancaria *cadastrar_cliente(Contabancaria *contabancaria, Agenciabancaria *agenciabancaria);

// Cadastrar conta nas agencias 
Agenciabancaria *cadastrar_conta(Agenciabancaria *agencia);

// funcao para listar agencias
void listar_agencias(Agenciabancaria **agencias, int qtdagencias);

// funcao para salvar arquivo
void salvar_arquivo(Agenciabancaria **agencias, int qtdagencias);

// funcao para abrir arquivo salvo
Agenciabancaria **ler_arquivo(Agenciabancaria **agencias, int *qnta);

// funcao para remover conta
Agenciabancaria *remove_conta(Agenciabancaria *agencia, int numero);

// funcao para liberar memoria 
void liberar_agencia(Agenciabancaria *agencia);

// funcao para liberar memoria
void liberar_agencias(Agenciabancaria **agencias, int qnta);