#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 100
#define MAX_LOGS 10

// Estrutura para armazenar metadados dos logs de auditoria
typedef struct {
    int id;
    char operacao[30];
    int tamanho_payload;
    char payload[TAM_BUFFER];
} LogAuditoria;

// Variáveis globais para controle do histórico
LogAuditoria historico_logs[MAX_LOGS];
int total_logs = 0;

// Protótipos das funções
void limpar_buffer_entrada(void);
void ler_string_segura(char *buffer, int tamanho);
void mascarar_dados(char *dado);
int validar_senha(const char *senha);

void cifrar_cesar(char *texto, int deslocamento);
void descifrar_cesar(char *texto, int deslocamento);
void cifrar_xor(unsigned char *dado, int tamanho, char chave);
void exibir_hexadecimal(const unsigned char *dado, int tamanho);

void registrar_log(const char *operacao, const char *payload);
void exibir_relatorio_logs(void);
void buscar_no_historico(const char *termo);
void exportar_logs_arquivo(void); // Funcionalidade Extra
int main(void)
{
    int opcao;
    char buffer[TAM_BUFFER];

    do {
        printf("\n========================================\n");
        printf("              SafeConsole               \n");
        printf("========================================\n");
        printf("1 - Mascarar dado sensivel\n");
        printf("2 - Validar senha\n");
        printf("3 - Cifrar/Descifrar Cesar\n");
        printf("4 - Cifrar XOR (exibir em Hexadecimal)\n");
        printf("5 - Exibir Relatorio de Auditoria (Logs)\n");
        printf("6 - Buscar Termo no Historico de Logs\n");
        printf("7 - Exportar Logs para Arquivo (Extra)\n");
        printf("0 - Sair\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limpar_buffer_entrada();

        switch (opcao) {
            case 1: {
                printf("\n--- Sanitizacao de Dados ---\n");
                printf("Digite o dado sensivel (ex: CPF, cartao, token): ");
                ler_string_segura(buffer, TAM_BUFFER);
                
                char buffer_origem[TAM_BUFFER];
                strcpy(buffer_origem, buffer);

                mascarar_dados(buffer);
                printf("Dado mascarado: %s\n", buffer);

                registrar_log("Data Masking", buffer);
                break;
            }

            case 2: {
                printf("\n--- Validador de Senha ---\n");
                printf("Digite a senha para validar: ");
                ler_string_segura(buffer, TAM_BUFFER);

                if (validar_senha(buffer)) {
                    printf("Status: Senha FORTE! Atende aos criterios minimos.\n");
                    registrar_log("Validador Senha (Forte)", buffer);
                } else {
                    printf("Status: Senha FRACA. Minimo 8 caracteres, com maiuscula, minuscula e digito.\n");
                    registrar_log("Validador Senha (Fraca)", buffer);
                }
                break;
            }

            case 3: {
                int op_cesar, deslocamento;
                printf("\n--- Cifra de Cesar ---\n");
                printf("1 - Cifrar\n");
                printf("2 - Descifrar\n");
                printf("Escolha uma opcao: ");
                if (scanf("%d", &op_cesar) != 1) {
                    op_cesar = -1;
                }
                limpar_buffer_entrada();

                if (op_cesar != 1 && op_cesar != 2) {
                    printf("Opcao invalida!\n");
                    break;
                }

                printf("Digite o texto: ");
                ler_string_segura(buffer, TAM_BUFFER);

                printf("Digite o deslocamento (chave numerica): ");
                scanf("%d", &deslocamento);
                limpar_buffer_entrada();

                if (op_cesar == 1) {
                    cifrar_cesar(buffer, deslocamento);
                    printf("Texto cifrado: %s\n", buffer);
                    registrar_log("Cifra Cesar (Cifrar)", buffer);
                } else {
                    descifrar_cesar(buffer, deslocamento);
                    printf("Texto descifrado: %s\n", buffer);
                    registrar_log("Cifra Cesar (Descifrar)", buffer);
                }
                break;
            }

            case 4: {
                char chave;
                printf("\n--- Cifra XOR ---\n");
                printf("Digite o texto/dado: ");
                ler_string_segura(buffer, TAM_BUFFER);

                printf("Digite um caractere como chave: ");
                scanf(" %c", &chave);
                limpar_buffer_entrada();

                int tamanho = strlen(buffer);
                cifrar_xor((unsigned char *)buffer, tamanho, chave);

                printf("Payload cifrado (Hexadecimal): ");
                exibir_hexadecimal((unsigned char *)buffer, tamanho);

                // Converte bytes hex para representação string no log
                char hex_str[TAM_BUFFER] = "";
                for (int i = 0; i < tamanho && (i * 3) < TAM_BUFFER - 4; i++) {
                    char temp[4];
                    snprintf(temp, sizeof(temp), "%02X ", (unsigned char)buffer[i]);
                    strcat(hex_str, temp);
                }

                registrar_log("Cifra XOR (Hex)", hex_str);
                break;
            }

            case 5:
                exibir_relatorio_logs();
                break;

            case 6: {
                printf("\n--- Busca de Logs ---\n");
                printf("Digite o termo que deseja pesquisar: ");
                ler_string_segura(buffer, TAM_BUFFER);
                buscar_no_historico(buffer);
                break;
            }

            case 7:
                exportar_logs_arquivo();
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
