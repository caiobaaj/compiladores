#include <stdio.h>
#include <string.h>   
#include <ctype.h>    
#include <stdbool.h>  


// a) Cadeias de a’s e b’s com exatamente a mesma quantidade de a’s e b’s
// (ab|ba)*
typedef enum {
    A0, A1, A2, A_REJEITA
} estadoA;

// b) Cadeias de dígitos sem zeros à esquerda 
// [1-9][0-9]*
typedef enum {
    B0, B1, B_REJEITA
} estadoB;

// c) Cadeias de dígitos que representem números pares
// [0-9]*[02468]
typedef enum {
    C0, C1, C2, C_REJEITA
} estadoC;

// d) Cadeias de a’s e b’s com um numero par de a’s e um numero ímpar de b’s
// (aa|bb)b(aa|bb) -> (não consegui fazer uma expressão regular melhor do que essa, mas o autômato finito é bem mais claro)
typedef enum {
    D0, D1, D2, D3, D_REJEITA
} estadoD;

bool analisaCadeiaA(const char* in);
bool analisaCadeiaB(const char* in);
bool analisaCadeiaC(const char* in);
bool analisaCadeiaD(const char* in);


int main() {

    char cadeia[100];

    while (true) {
        printf("Digite uma cadeia para análise (ou 'sair' para terminar):\n\n> ");
        fgets(cadeia, sizeof(cadeia), stdin);
        cadeia[strcspn(cadeia, "\n")] = 0;

        if (strcmp(cadeia, "sair") == 0) {
            break;
        }

        bool a = analisaCadeiaA(cadeia);
        bool b = analisaCadeiaB(cadeia);
        bool c = analisaCadeiaC(cadeia);
        bool d = analisaCadeiaD(cadeia);

        printf("\n");

        if (a) printf("VÁLIDO PARA a) Cadeias de a’s e b’s com exatamente a mesma quantidade de a’s e b’s\n");
        if (b) printf("VÁLIDO PARA b) Cadeias de dígitos sem zeros à esquerda \n");
        if (c) printf("VÁLIDO PARA c) Cadeias de dígitos que representem números pares\n");
        if (d) printf("VÁLIDO PARA d) Cadeias de a’s e b’s com um numero par de a’s e um numero ímpar de b’s\n");
        if (!a && !b && !c && !d) printf("CADEIA INVÁLIDA\n");

        printf("\n");
    }

    return 0;
}


bool analisaCadeiaA(const char* in) {

    estadoA estado_atual = A0;
    int k = 0;

    while(in[k] != '\0') {
        char terminal = in[k];
        switch(estado_atual) {
            case A0: 
                if (terminal == 'a')      
                    estado_atual = A1;
                else if (terminal == 'b') 
                    estado_atual = A2;
                else               
                    estado_atual = A_REJEITA;
                break;
            case A1: 
                if (terminal == 'b')      
                    estado_atual = A0; 
                else               
                    estado_atual = A_REJEITA;
                break;
            case A2: 
                if (terminal == 'a')      
                    estado_atual = A0; 
                else               
                    estado_atual = A_REJEITA;
                break;
            case A_REJEITA:
                break;
        }
        k++;
    }

    return (estado_atual == A0);
}


bool analisaCadeiaB(const char* in) {

    estadoB estado_atual = B0;
    int k = 0;

    if (strlen(in) == 0) return false;

    while(in[k] != '\0') {
        char terminal = in[k];
        switch(estado_atual) {
            case B0:
                if (terminal >= '1' && terminal <= '9') 
                    estado_atual = B1;
                else                      
                    estado_atual = B_REJEITA;
                break;
            case B1:
                if (!isdigit(terminal))          
                    estado_atual = B_REJEITA;
                break;
            case B_REJEITA:
                break;
        }
        k++;
    }

    return (estado_atual == B1);
}


bool analisaCadeiaC(const char* in) {

    estadoC estado_atual = C0;
    int k = 0;

    if (strlen(in) == 0) return false;

    while(in[k] != '\0') {
        char terminal = in[k];
        switch(estado_atual) {
            case C0:
            case C1:
            case C2:
                if (!isdigit(terminal)) {
                    estado_atual = C_REJEITA;
                } else if ((terminal - '0') % 2 == 0) {
                    estado_atual = C1;
                } else {
                    estado_atual = C2;
                }
                break;
            case C_REJEITA:
                break;
        }
        k++;
    }

    return (estado_atual == C1);
}


bool analisaCadeiaD(const char* in) {

    estadoD estado_atual = D0;
    int k = 0;

    while(in[k] != '\0') {
        char terminal = in[k];
        switch(estado_atual) {
            case D0:
                if (terminal == 'a')      
                    estado_atual = D1;
                else if (terminal == 'b') 
                    estado_atual = D2;
                else               
                    estado_atual = D_REJEITA;
                break;
            case D1:
                if (terminal == 'a')      
                    estado_atual = D0;
                else if (terminal == 'b') 
                    estado_atual = D3;
                else               
                    estado_atual = D_REJEITA;
                break;
            case D2:
                if (terminal == 'a')      
                    estado_atual = D3;
                else if (terminal == 'b') 
                    estado_atual = D0;
                else               
                    estado_atual = D_REJEITA;
                break;
            case D3:
                if (terminal == 'a')      
                    estado_atual = D2;
                else if (terminal == 'b') 
                    estado_atual = D1;
                else               
                    estado_atual = D_REJEITA;
                break;
            case D_REJEITA:
                break;
        }
        k++;
    }

    return (estado_atual == D2);
}