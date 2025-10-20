// ============================================================================
//         SISTEMA DE CADASTRO DE TERRITÓRIOS - NÍVEL NOVATO
// ============================================================================
//
// OBJETIVOS:
// - Criar uma struct chamada Territorio
// - Usar vetor estático de 5 elementos para armazenar territórios
// - Cadastrar: Nome, Cor do Exército e Número de Tropas
// - Exibir o estado atual do mapa de forma organizada
//
// CONCEITOS ABORDADOS:
// - struct
// - Vetor estático
// - Entrada/saída com scanf, fgets e printf
// - Funções modulares
//
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <locale.h>

// --- Constantes Globais ---
#define NUM_TERRITORIOS 5
#define TAM_STRING 100

// --- Estrutura de Dados ---
typedef struct {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int numTropas;
} Territorio;

// --- Protótipos das Funções ---
void exibirCabecalho();
void cadastrarTerritorios(Territorio territorios[], int tamanho);
void exibirMapa(const Territorio territorios[], int tamanho);
void limparBufferEntrada();

// --- Função Principal (main) ---
int main() {
    // Configuração do locale para português
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    // Declaração do vetor estático de territórios
    Territorio mapa[NUM_TERRITORIOS];
    
    // Exibir cabeçalho do sistema
    exibirCabecalho();
    
    // Cadastrar os dados dos territórios
    cadastrarTerritorios(mapa, NUM_TERRITORIOS);
    
    // Exibir o mapa com todos os territórios cadastrados
    printf("\n");
    exibirMapa(mapa, NUM_TERRITORIOS);
    
    return 0;
}

// --- Implementação das Funções ---

// exibirCabecalho():
// Exibe o cabeçalho inicial do sistema com informações sobre o programa
void exibirCabecalho() {
    printf("============================================================================\n");
    printf("           SISTEMA DE CADASTRO DE TERRITÓRIOS - WAR\n");
    printf("============================================================================\n\n");
    printf("Você irá cadastrar %d territórios com as seguintes informações:\n", NUM_TERRITORIOS);
    printf("  - Nome do Território\n");
    printf("  - Cor do Exército Dominante\n");
    printf("  - Número de Tropas\n\n");
    printf("============================================================================\n\n");
}

// cadastrarTerritorios():
// Solicita ao usuário os dados de cada território e armazena no vetor
// Parâmetros:
//   - territorios[]: vetor de territórios a ser preenchido (passagem por referência)
//   - tamanho: número de territórios a cadastrar
void cadastrarTerritorios(Territorio territorios[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("📍 CADASTRO DO TERRITÓRIO %d/%d\n", i + 1, tamanho);
        printf("------------------------------------------------------------\n");
        
        // Leitura do nome do território
        printf("Nome do território: ");
        limparBufferEntrada();
        fgets(territorios[i].nome, TAM_STRING, stdin);
        // Remove o '\n' do final da string, se presente
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Leitura da cor do exército
        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, TAM_STRING, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';
        
        // Leitura do número de tropas
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        
        // Validação simples do número de tropas
        while (territorios[i].numTropas < 0) {
            printf("❌ Erro: O número de tropas não pode ser negativo!\n");
            printf("Número de tropas: ");
            scanf("%d", &territorios[i].numTropas);
        }
        
        printf("\n");
    }
}

// exibirMapa():
// Exibe o estado atual de todos os territórios em formato de tabela
// Parâmetros:
//   - territorios[]: vetor de territórios (passagem por referência constante - apenas leitura)
//   - tamanho: número de territórios no vetor
void exibirMapa(const Territorio territorios[], int tamanho) {
    printf("============================================================================\n");
    printf("                        🗺️  MAPA DOS TERRITÓRIOS\n");
    printf("============================================================================\n\n");
    
    // Cabeçalho da tabela
    printf("%-5s %-25s %-20s %-10s\n", "#", "TERRITÓRIO", "EXÉRCITO", "TROPAS");
    printf("----------------------------------------------------------------------------\n");
    
    // Dados de cada território
    for (int i = 0; i < tamanho; i++) {
        printf("%-5d %-25s %-20s %-10d\n", 
               i + 1,
               territorios[i].nome,
               territorios[i].corExercito,
               territorios[i].numTropas);
    }
    
    printf("============================================================================\n");
    
    // Estatísticas gerais
    int totalTropas = 0;
    for (int i = 0; i < tamanho; i++) {
        totalTropas += territorios[i].numTropas;
    }
    
    printf("\n📊 ESTATÍSTICAS:\n");
    printf("   - Total de territórios cadastrados: %d\n", tamanho);
    printf("   - Total de tropas no mapa: %d\n", totalTropas);
    printf("   - Média de tropas por território: %.2f\n", (float)totalTropas / tamanho);
    printf("\n============================================================================\n");
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada (stdin)
// Evita problemas com leituras consecutivas de scanf e fgets
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}