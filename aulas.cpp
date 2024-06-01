#include <stdio.h>
#include <string.h>
#include "library.h"

#define MAX_AULAS 100

void addAula(Aula *aulas, int *contador_aulas, Professor *professores, int contador_professor) {
    if (*contador_aulas >= MAX_AULAS) {
        printf("Número máximo de aulas alcançado.\n");
        return;
    }
    aulas[*contador_aulas].id = *contador_aulas + 1;
    aulas[*contador_aulas].contador_alunos = 0;
    printf("Insira o nome da aula: ");
    scanf(" %[^\n]", aulas[*contador_aulas].nome);
    listarProfessores(professores, contador_professor);
    printf("Insira o ID do professor: ");
    scanf("%d", &aulas[*contador_aulas].Professor_id);
    printf("Insira um horário (manhã, tarde ou noite): ");
    scanf(" %[^\n]", aulas[*contador_aulas].horario);
    (*contador_aulas)++;
}

void listarAulas(Aula *aulas, int contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor) {
    for (int i = 0; i < contador_aulas; i++) {
        char nome_professor[MAX_NOME] = "Desconhecido";
        for (int j = 0; j < contador_professor; j++) {
            if (professores[j].id == aulas[i].Professor_id) {
                strcpy(nome_professor, professores[j].nome);
                break;
            }
        }

        printf("Aula ID: %d, Nome: %s, Professor: %s, Horário: %s, Alunos:\n",
               aulas[i].id, aulas[i].nome, nome_professor, aulas[i].horario);

        for (int j = 0; j < aulas[i].contador_alunos; j++) {
            char nome_aluno[MAX_NOME] = "Desconhecido";
            for (int k = 0; k < contador_estudante; k++) {
                if (alunos[k].id == aulas[i].id_aluno[j]) {
                    strcpy(nome_aluno, alunos[k].nome);
                    break;
                }
            }
            printf("  Aluno ID: %d, Nome: %s\n", aulas[i].id_aluno[j], nome_aluno);
        }
    }
}

void editarAula(Aula *aulas, int contador_aulas) {
    for (int i = 0; i < contador_aulas; i++) {
        char nome_professor[MAX_NOME] = "Desconhecido";
        printf("-------------------------------\n");
        printf("Id - %d \n", aulas[i].id);
        printf("Nome: %s \n", aulas[i].nome);
        printf("Horario: %s \n", aulas[i].horario);
        printf("Professor Id: %d \n", aulas[i].Professor_id);
        printf("-------------------------------\n");
    }
    int id;
    printf("Insira o ID da aula a editar: ");
    scanf("%d", &id);
    for (int i = 0; i < contador_aulas; i++) {
        if (aulas[i].id == id) {
            printf("Editar nome da aula (atual: %s): ", aulas[i].nome);
            scanf(" %[^\n]", aulas[i].nome);
            printf("Editar ID do professor (atual: %d): ", aulas[i].Professor_id);
            scanf("%d", &aulas[i].Professor_id);
            printf("Editar horário (atual: %s): ", aulas[i].horario);
            scanf(" %[^\n]", aulas[i].horario);
            return;
        }
    }
     printf("Aula não encontrada.\n");
}

void excluirAula(Aula *aulas, int *contador_aulas) {
    for (int i = 0; i < *contador_aulas; i++) {
        char nome_professor[MAX_NOME] = "Desconhecido";
        printf("-------------------------------\n");
        printf("Id - %d \n", aulas[i].id);
        printf("Nome: %s \n", aulas[i].nome);
        printf("Horario: %s \n", aulas[i].horario);
        printf("Professor Id: %d \n", aulas[i].Professor_id);
        printf("-------------------------------\n");
    }
    int id;
    printf("Insira o ID da aula a excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < *contador_aulas; i++) {
        if (aulas[i].id == id) {
            for (int j = i; j < *contador_aulas - 1; j++) {
                aulas[j] = aulas[j + 1];
            }
            (*contador_aulas)--;
            return;
        }
    }
    printf("Aula não encontrada.\n");
}