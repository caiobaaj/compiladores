// CTCO06 - Compiladores
// Caio Teodoro Portela - 2020004501
// Trabalho 2 - 04/09/2025

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int pertence(char c, const char* conjunto);
void analisadorH(const char* cadeia);

int main() {
    char cadeia[100];

    while (true) {
        printf("Digite uma cadeia para análise (ou 'sair' para terminar):\n\n> ");
        fgets(cadeia, sizeof(cadeia), stdin);
        cadeia[strcspn(cadeia, "\n")] = 0;

        if (strcmp(cadeia, "sair") == 0) {
            break;
        }

        if (strlen(cadeia) != 11) {
            printf("A cadeia deve conter exatamente 11 simbolos.\n");
            continue;
        }

        analisadorH(cadeia);
    }

    printf("Programa encerrado.\n");
    return 0;
}

int pertence(char c, const char* conjunto) {
    for (int i = 0; conjunto[i] != '\0'; i++) {
        if (c == conjunto[i]) {
            return 1;
        }
    }
    return 0;
}

void analisadorH(const char* cadeia) {
    char prefixo[4], corpo[6], sufixo[4];
    char token_prefixo, token_corpo, token_sufixo;

    if (cadeia[0] != 'a') {
        printf("Erro no prefixo: Código deve iniciar com 'a'. Lido: '%c'\n", cadeia[0]);
        return;
    }

    if (cadeia[1] == 'b') token_prefixo = 'B';
    else if (cadeia[1] == 'c') token_prefixo = 'C';
    else if (cadeia[1] == 'd') token_prefixo = 'D';
    else {
        printf("Erro no prefixo: Segundo caractere inválido. Lido: '%c'\n", cadeia[1]);
        return;
    }

    if (cadeia[1] == 'b' && !pertence(cadeia[2], "cd")) {
        printf("Erro no prefixo: Terceiro caractere inválido após 'ab'. Lido: '%c'\n", cadeia[2]);
        return;
    }
    if (cadeia[1] == 'c' && !pertence(cadeia[2], "bd")) {
        printf("Erro no prefixo: Terceiro caractere inválido após 'ac'. Lido: '%c'\n", cadeia[2]);
        return;
    }
    if (cadeia[1] == 'd' && !pertence(cadeia[2], "bc")) {
        printf("Erro no prefixo: Terceiro caractere inválido após 'ad'. Lido: '%c'\n", cadeia[2]);
        return;
    }
    if (cadeia[1] == cadeia[2]) {
        printf("Erro no prefixo: Segunda e terceira letras devem ser distintas.\n");
        return;
    }
    strncpy(prefixo, &cadeia[0], 3);
    prefixo[3] = '\0';

    if (cadeia[3] != 'i') {
        printf("Erro no corpo: Deve iniciar com 'i'. Lido: '%c'\n", cadeia[3]);
        return;
    }

    if (cadeia[4] == 'j') token_corpo = 'J';
    else if (cadeia[4] == 'k') token_corpo = 'K';
    else if (cadeia[4] == 'm') token_corpo = 'M';
    else {
        printf("Erro no corpo: Quinto caractere inválido. Lido: '%c'\n", cadeia[4]);
        return;
    }
    
    if (!pertence(cadeia[5], "jkm") || !pertence(cadeia[6], "jkm") || 
        cadeia[4] == cadeia[5] || cadeia[4] == cadeia[6] || cadeia[5] == cadeia[6]) {
        printf("Erro no corpo: A combinação de 'j', 'k', 'm' é inválida ou tem letras repetidas.\n");
        return;
    }

    if (cadeia[7] != 'n') {
        printf("Erro no corpo: Deve terminar com 'n'. Lido: '%c'\n", cadeia[7]);
        return;
    }
    strncpy(corpo, &cadeia[3], 5);
    corpo[5] = '\0';

    if (cadeia[8] == 'w') token_sufixo = 'W';
    else if (cadeia[8] == 'x') token_sufixo = 'X';
    else if (cadeia[8] == 'y') token_sufixo = 'Y';
    else {
        printf("Erro no sufixo: Nono caractere inválido. Lido: '%c'\n", cadeia[8]);
        return;
    }

    if (cadeia[8] == 'w' && !pertence(cadeia[9], "xy")) {
        printf("Erro no sufixo: Décimo caractere inválido após 'w'. Lido: '%c'\n", cadeia[9]);
        return;
    }
    if (cadeia[8] == 'x' && !pertence(cadeia[9], "wy")) {
        printf("Erro no sufixo: Décimo caractere inválido após 'x'. Lido: '%c'\n", cadeia[9]);
        return;
    }
    if (cadeia[8] == 'y' && !pertence(cadeia[9], "wx")) {
        printf("Erro no sufixo: Décimo caractere inválido após 'y'. Lido: '%c'\n", cadeia[9]);
        return;
    }

    if (cadeia[10] != 'z') {
        printf("Erro no sufixo: Código deve terminar com 'z'. Lido: '%c'\n", cadeia[10]);
        return;
    }
    strncpy(sufixo, &cadeia[8], 3);
    sufixo[3] = '\0';

    printf("Cadeia válida. Tokens reconhecidos:\n");
    printf("<%c, %s>\n", token_prefixo, prefixo);
    printf("<%c, %s>\n", token_corpo, corpo);
    printf("<%c, %s>\n", token_sufixo, sufixo);
}