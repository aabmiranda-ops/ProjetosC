#include <stdio.h>
#include <string.h>

#define TAM_BUFFER 100

void limpar_buffer_entrada(void);
void ler_string_segura(char *buffer, int tamanho);

void mascarar_dados(char *dado);
int  validar_senha(char *senha);

void cifrar_cesar(char *texto, int deslocamento);
void descifrar_cesar(char *texto, int deslocamento);
void cifrar_xor(char *dado, char chave);
void exibir_hexadecimal(char *dado, int tamanho);


int main(void)
{
    int opcao;
    char buffer[TAM_BUFFER];

    do {
        printf("\n=== SafeConsole ===\n");
        printf("1 - Mascarar dado sensivel\n");
        printf("2 - Validar senha\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        limpar_buffer_entrada();

        switch (opcao) {

            case 1:
                printf("Digite o dado sensivel (ex: CPF, cartao, token): ");
                ler_string_segura(buffer, TAM_BUFFER);
                mascarar_dados(buffer);
                printf("Dado mascarado: %s\n", buffer);
                break;

            case 2:
                printf("Digite a senha para validar: ");
                ler_string_segura(buffer, TAM_BUFFER);
                if (validar_senha(buffer))
                    printf("Senha forte! Atende aos criterios minimos.\n");
                else
                    printf("Senha fraca. Minimo 8 caracteres, com maiuscula, minuscula e digito.\n");
                break;

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
    char c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


void ler_string_segura(char *buffer, int tamanho)
{
    int len;

    fgets(buffer, tamanho, stdin);

    len = strlen(buffer);
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


int validar_senha(char *senha)
{
    int tamanho = strlen(senha);
    int tem_maiuscula = 0;
    int tem_minuscula = 0;
    int tem_digito = 0;
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