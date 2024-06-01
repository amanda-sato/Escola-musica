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
    printf("Insira o horário preferencial de aula (manhã, tarde ou noite): ");
    scanf(" %[^\n]", professores[*contador_professor].horario);
    professores[*contador_professor].contador_aulas = 0;
    (*contador_professor)++;
}

void listarProfessores(Professor *professores, int contador_professor) {
    for (int i = 0; i < contador_professor; i++) {
        printf("-------------------\n");
        printf("ID: %d\n", professores[i].id);
        printf("Nome: %s\n", professores[i].nome);
        printf("Instumento musical: %s\n", professores[i].instrumento_musical);
        printf("Horário de preferencia: %s\n", professores[i].horario);
        printf("Aulas: %d\n", professores[i].contador_aulas);
        printf("-------------------\n");
    }
}

void editarProfessor(Professor *professores, int contador_professor) {
    for (int i = 0; i < contador_professor; i++) {
        printf("-------------------\n");
        printf("ID: %d\n", professores[i].id);
        printf("Nome: %s\n", professores[i].nome);
        printf("Instumento musical: %s\n", professores[i].instrumento_musical);
        printf("Horário de preferencia: %s\n", professores[i].horario);
        printf("Aulas: %d\n", professores[i].contador_aulas);
        printf("-------------------\n");
    }
    int id;
    printf("Insira o ID do professor a editar: ");
    scanf("%d", &id);
    for (int i = 0; i < contador_professor; i++) {
        if (professores[i].id == id) {
            printf("Editar nome (atual: %s): ", professores[i].nome);
            scanf(" %[^\n]", professores[i].nome);
            printf("Editar instrumento musical (atual: %s): ", professores[i].instrumento_musical);
            scanf(" %[^\n]", professores[i].instrumento_musical);
            printf("Editar horário de preferencia (atual: %s): ", professores[i].horario);
            scanf(" %[^\n]", professores[i].horario);
            return;
        }
    }
    printf("Professor não encontrado.\n");
}

void excluirProfessor(Professor *professores, int *contador_professor, Aula *aulas, int contador_aulas) {
    for (int i = 0; i < *contador_professor; i++) {
        printf("-------------------\n");
        printf("ID: %d\n", professores[i].id);
        printf("Nome: %s\n", professores[i].nome);
        printf("Instumento musical: %s\n", professores[i].instrumento_musical);
        printf("Horário de preferencia: %s\n", professores[i].horario);
        printf("Aulas: %d\n", professores[i].contador_aulas);
        printf("-------------------\n");
    }
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
    for (int i = 0; i < contador_professor; i++) {
        printf("-------------------\n");
        printf("ID: %d\n", professores[i].id);
        printf("Nome: %s\n", professores[i].nome);
        printf("Instumento musical: %s\n", professores[i].instrumento_musical);
        printf("Horário de preferencia: %s\n", professores[i].horario);
        printf("Aulas: %d\n", professores[i].contador_aulas);
        printf("-------------------\n");
    }
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
                    printf("Horário de preferencia: %s\n", aulas[j].horario);
                }
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Professor não encontrado.\n");
    }
}