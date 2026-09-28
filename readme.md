# SafeConsole C - Sistema de Cifragem, Sanitização e Logs de Auditoria

O **SafeConsole** é uma ferramenta de linha de comando desenvolvida em Linguagem C voltada para a área de **Segurança da Informação**[cite: 1]. O projeto consolida conceitos fundamentais de desenvolvimento seguro, aplicando leitura protegida de buffers, algoritmos de cifragem simétrica, sanitização de dados sensíveis e gerenciamento de logs de auditoria em memória e em arquivo[cite: 1].

Projeto desenvolvido para a disciplina de **Algoritmos e Estrutura de Dados** do curso de **Segurança da Informação** da **CÉSAR SCHOOL**[cite: 1].

---

## Integrantes do Projeto

* **Bernardo Acioli**[cite: 1]
* **Alexandre Miranda**[cite: 1]

---

## Sumário
1. [Visão Geral e Arquitetura](#visão-geral-e-arquitetura)
2. [Estrutura de Dados Globais](#estrutura-de-dados-globais)
3. [Documentação das Funções](#documentação-das-funções)
   - [Módulo de Sanitização e Validação (Etapa 1)](#1-módulo-de-sanitização-e-validação-etapa-1)
   - [Módulo de Cifragem Simétrica (Etapa 2)](#2-módulo-de-cifragem-simétrica-etapa-2)
   - [Módulo de Auditoria e Logs (Etapa 3)](#3-módulo-de-auditoria-e-logs-etapa-3)
   - [Módulo Extra](#4-módulo-extra)
4. [Como Compilar e Executar](#como-compilar-e-executar)
5. [Exemplo de Uso](#exemplo-de-uso)

---

## Visão Geral e Arquitetura

O sistema funciona por meio de um menu interativo construído com um laço `do-while` e diretivas `switch/case`[cite: 1]. O fluxo do programa garante que todas as operações realizadas pelo operador registrem automaticamente um log de auditoria na memória, permitindo rastreabilidade dos dados manipulados[cite: 1].

---

## Estrutura de Dados Globais

### `typedef struct LogAuditoria`
Estrutura utilizada para armazenar os metadados de cada operação executada no sistema:
* `int id`: Identificador único e sequencial do log.
* `char operacao[30]`: Nome da funcionalidade ou algoritmo executado (ex: "Data Masking", "Cifra Cesar").
* `int tamanho_payload`: Tamanho da string processada em bytes/caracteres (obtido via `strlen`).
* `char payload[TAM_BUFFER]`: Conteúdo textual processado pela operação.

### Variáveis de Estado Global
* `LogAuditoria historico_logs[MAX_LOGS]`: Vetor de estruturas que atua como vetor de auditoria em memória (capacidade máxima definida pela constante `MAX_LOGS`).
* `int total_logs`: Contador global do número de registros armazenados no histórico.

---

## Documentação das Funções

### 1. Módulo de Sanitização e Validação (Etapa 1)

* **`void limpar_buffer_entrada(void)`**
  * **Descrição:** Descarta os caracteres remanescentes no buffer de entrada (`stdin`) após leituras com `scanf()`. Previne comportamentos inesperados em leituras subsequentes de texto.

* **`void ler_string_segura(char *buffer, int tamanho)`**
  * **Descrição:** Realiza a leitura segura de strings utilizando `fgets()`, respeitando o limite máximo do buffer para evitar *Buffer Overflow*[cite: 1]. Trata e remove o caractere de quebra de linha (`\n`) do final da string[cite: 1].

* **`void mascarar_dados(char *dado)`**
  * **Descrição:** Aplica técnica de *Data Masking* em strings sensíveis (ex: CPF, cartão de crédito)[cite: 1]. Mantém visíveis apenas os 4 últimos dígitos e substitui todos os caracteres anteriores por asteriscos (`*`)[cite: 1].

* **`int validar_senha(const char *senha)`**
  * **Descrição:** Avalia os critérios de complexidade de credenciais[cite: 1]. Retorna `1` (verdadeiro) se a senha contiver no mínimo 8 caracteres, com pelo menos uma letra maiúscula, uma minúscula e um dígito numérico (consultando a Tabela ASCII)[cite: 1]. Caso contrário, retorna `0`[cite: 1].

---

### 2. Módulo de Cifragem Simétrica (Etapa 2)

* **`void cifrar_cesar(char *texto, int deslocamento)`**
  * **Descrição:** Implementa o algoritmo clássico de Cifra de César com deslocamento modular alfabético[cite: 1]. Preserva maiúsculas e minúsculas dentro dos limites de 'A'-'Z' e 'a'-'z'.

* **`void descifrar_cesar(char *texto, int deslocamento)`**
  * **Descrição:** Reverte a cifragem de César aplicando a função `cifrar_cesar()` com o valor inverso do deslocamento informada pelo usuário[cite: 1].

* **`void cifrar_xor(unsigned char *dado, int tamanho, char chave)`**
  * **Descrição:** Aplica uma cifra de fluxo (*Stream Cipher*) executando a operação bit-a-bit XOR (`^`) em cada byte do dado contra um caractere chave fornecido[cite: 1].

* **`void exibir_hexadecimal(const unsigned char *dado, int tamanho)`**
  * **Descrição:** Formata e exibe no terminal os bytes de um buffer em formato hexadecimal utilizando o especificador `%02X`[cite: 1].

---

### 3. Módulo de Auditoria e Logs (Etapa 3)

* **`void registrar_log(const char *operacao, const char *payload)`**
  * **Descrição:** Salva na matriz de histórico em memória os dados da operação realizada[cite: 1]. Define o ID, nome da operação, calcula o tamanho com `strlen()` e armazena o payload[cite: 1].

* **`void exibir_relatorio_logs(void)`**
  * **Descrição:** Formata e exibe uma tabela detalhada no terminal listando todos os registros contidos na auditoria (ID, Algoritmo/Operação, Tamanho do Payload e Payload Processado)[cite: 1].

* **`void buscar_no_historico(const char *termo)`**
  * **Descrição:** Realiza buscas por substrings dentro do histórico de auditoria utilizando a função `strstr()` da biblioteca padrão[cite: 1]. Retorna as ocorrências encontradas no payload ou na identificação da operação[cite: 1].

---

### 4. Módulo Extra

* **`void exportar_logs_arquivo(void)`**
  * **Descrição:** Persiste os registros presentes na memória em um arquivo físico de texto chamado `logs_auditoria.txt` utilizando rotinas de manipulação de arquivo (`fopen`, `fprintf`, `fclose`).

---

## Como Compilar e Executar

### Pré-requisitos
* Compilador **GCC** instalado no ambiente (Linux, macOS ou Windows via MinGW/WSL).

### Instruções

1. Clone o repositório para a sua máquina local:
   ```bash
   git clone [https://github.com/SEU_USUARIO/safe-console-c.git](https://github.com/SEU_USUARIO/safe-console-c.git)
   cd safe-console-c
