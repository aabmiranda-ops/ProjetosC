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
