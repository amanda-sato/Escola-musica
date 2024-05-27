#include <stdio.h>
#include "library.h"

#define MAX_PROFESSORES 100

void addProfessor(Professor *professores, int *contador_professor) {
    if (*contador_professor >= MAX_PROFESSORES) {
        printf("Número máximo de professores alcançado.\n");
        return;
    }
    professores[*contador_professor].id = *contador_professor + 1; 
    printf("Insira o nome do professor: ");
    scanf(" %[^\n]", professores[*contador_professor].nome);
    printf("Insira o instrumento musical do professor: ");
    scanf(" %[^\n]", professores[*contador_professor].instrumento_musical);
    printf("Insira o horário de aula (manhã, tarde ou noite): ");
    scanf(" %[^\n]", professores[*contador_professor].horario);
    professores[*contador_professor].contador_aulas = 0;
    (*contador_professor)++;
}

void listarProfessores(Professor *professores, int contador_professor) {
    for (int i = 0; i < contador_professor; i++) {
        printf("ID: %d, nome: %s, instrumento musical: %s, horário: %s, aulas: %d\n",
               professores[i].id, professores[i].nome, professores[i].instrumento_musical, professores[i].horario, professores[i].contador_aulas);
    }
}

void editarProfessor(Professor *professores, int contador_professor) {
    int id;
    printf("Insira o ID do professor a editar: ");
    scanf("%d", &id);
    for (int i = 0; i < contador_professor; i++) {
        if (professores[i].id == id) {
            printf("Editar nome (atual: %s): ", professores[i].nome);
            scanf(" %[^\n]", professores[i].nome);
            printf("Editar instrumento musical (atual: %s): ", professores[i].instrumento_musical);
            scanf(" %[^\n]", professores[i].instrumento_musical);
            printf("Editar horário (atual: %s): ", professores[i].horario);
            scanf(" %[^\n]", professores[i].horario);
            return;
        }
    }
    printf("Professor não encontrado.\n");
}

void excluirProfessor(Professor *professores, int *contador_professor, Aula *aulas, int contador_aulas) {
    int id;
    printf("Insira o ID do professor a excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < *contador_professor; i++) {
        if (professores[i].id == id) {
            for (int j = 0; j < contador_aulas; j++) {
                if (aulas[j].Professor_id == id) {
                    printf("O professor ID %d está associado a uma aula e não pode ser excluído.\n", id);
                    return;
                }
            }
            for (int j = i; j < *contador_professor - 1; j++) {
                professores[j] = professores[j + 1];
            }
            (*contador_professor)--;
            return;
        }
    }
    printf("Professor não encontrado.\n");
}

void listarAulasProfessor(Aula *aulas, int contador_aulas, Professor *professores, int contador_professor) {
    int id_professor;
    printf("Insira o ID do professor para listar suas aulas: ");
    scanf("%d", &id_professor);

    int encontrado = 0;
    for (int i = 0; i < contador_professor; i++) {
        if (professores[i].id == id_professor) {
            encontrado = 1;
            printf("Aulas do professor %s (ID: %d):\n", professores[i].nome, professores[i].id);
            for (int j = 0; j < contador_aulas; j++) {
                if (aulas[j].Professor_id == id_professor) {
                    printf("ID da aula: %d\n", aulas[j].id);
                    printf("Horário: %s\n", aulas[j].horario);
                }
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Professor não encontrado.\n");
    }
}