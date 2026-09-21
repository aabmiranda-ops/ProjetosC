
#include <stdio.h>
#include <string.h> 
#define TAM_BUFFER 100


void limpar_buffer_entrada(void);
void ler_string_segura(char *buffer, int tamanho);


void mascarar_dados(char *dado);
int  validar_senha(const char *senha);


void cifrar_cesar(char *texto, int deslocamento);
void descifrar_cesar(char *texto, int deslocamento);
void cifrar_xor(unsigned char *dado, int tamanho, char chave);
void exibir_hexadecimal(const unsigned char *dado, int tamanho);


int main(void)
{
    int opcao;
    char buffer[TAM_BUFFER];

    do {
        printf("\n=== SafeConsole ===\n");
        printf("1 - Mascarar dado sensivel\n");
        printf("2 - Validar senha\n");
        printf("3 - Cifrar/Descifrar Cesar\n");
        printf("4 - Cifrar XOR (exibir em hexadecimal)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        limpar_buffer_entrada(); 

        switch (opcao) {

            case 1: {
                printf("Digite o dado sensivel (ex: CPF, cartao, token): ");
                ler_string_segura(buffer, TAM_BUFFER);
                mascarar_dados(buffer);
                printf("Dado mascarado: %s\n", buffer);
                break;
            }

            case 2: {
                printf("Digite a senha para validar: ");
                ler_string_segura(buffer, TAM_BUFFER);
                if (validar_senha(buffer))
                    printf("Senha forte! Atende aos criterios minimos.\n");
                else
                    printf("Senha fraca. Minimo 8 caracteres, com maiuscula, minuscula e digito.\n");
                break;
            }

        
            case 0:
                printf("Encerrando o SafeConsole...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}


void limpar_buffer_entrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void ler_string_segura(char *buffer, int tamanho)
{
    fgets(buffer, tamanho, stdin);

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0'; 
    }
}



void mascarar_dados(char *dado)
{
    int tamanho = strlen(dado);
    int i;

    
    for (i = 0; i < tamanho - 4; i++) {
        dado[i] = '*';
    }
}

int validar_senha(const char *senha)
{
    int tamanho = strlen(senha);
    int tem_maiuscula = 0, tem_minuscula = 0, tem_digito = 0;
    int i;

    if (tamanho < 8) {
        return 0; 
    }

    for (i = 0; i < tamanho; i++) {
        char c = senha[i];

        if (c >= 'A' && c <= 'Z') {      
            tem_maiuscula = 1;
        } else if (c >= 'a' && c <= 'z') { 
            tem_minuscula = 1;
        } else if (c >= '0' && c <= '9') { 
            tem_digito = 1;
        }
    }

    return (tem_maiuscula && tem_minuscula && tem_digito);
}

