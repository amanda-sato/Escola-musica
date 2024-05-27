#include <stdio.h>
#include "library.h"

#define MAX_ALUNOS 100

void addAluno(Aluno *alunos, int *contador_estudante) {
    if (*contador_estudante >= MAX_ALUNOS) {
        printf("Número máximo de alunos alcançado.\n");
        return;
    }
    alunos[*contador_estudante].id = *contador_estudante + 1; 
    printf("Insira o nome do aluno: ");
    scanf(" %[^\n]", alunos[*contador_estudante].nome);
    printf("Insira a idade do aluno: ");
    scanf("%d", &alunos[*contador_estudante].idade);
    printf("Insira o instrumento musical do aluno: ");
    scanf(" %[^\n]", alunos[*contador_estudante].instrumento_musical);
    alunos[*contador_estudante].contador_aulas = 0;
    (*contador_estudante)++;
}

void listarAlunos(Aluno *alunos, int contador_estudante) {
    for (int i = 0; i < contador_estudante; i++) {
        printf("ID: %d, nome: %s, idade: %d, instrumento musical: %s, aulas: %d\n",
               alunos[i].id, alunos[i].nome, alunos[i].idade, alunos[i].instrumento_musical, alunos[i].contador_aulas);
    }
}

void editarAluno(Aluno *alunos, int contador_estudante) {
    int id;
    printf("Insira o ID do aluno a editar: ");
    scanf("%d", &id);
    for (int i = 0; i < contador_estudante; i++) {
        if (alunos[i].id == id) {
            printf("Editar nome (atual: %s): ", alunos[i].nome);
            scanf(" %[^\n]", alunos[i].nome);
            printf("Editar idade (atual: %d): ", alunos[i].idade);
            scanf("%d", &alunos[i].idade);
            printf("Editar instrumento musical (atual: %s): ", alunos[i].instrumento_musical);
            scanf(" %[^\n]", alunos[i].instrumento_musical);
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}

void excluirAluno(Aluno *alunos, int *contador_estudante, Aula *aulas, int contador_aulas) {
    int id;
    printf("Insira o ID do aluno a excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < *contador_estudante; i++) {
        if (alunos[i].id == id) {
            for (int j = 0; j < contador_aulas; j++) {
                for (int k = 0; k < aulas[j].contador_alunos; k++) {
                    if (aulas[j].id_aluno[k] == id) {
                        for (int l = k; l < aulas[j].contador_alunos - 1; l++) {
                            aulas[j].id_aluno[l] = aulas[j].id_aluno[l + 1];
                        }
                        aulas[j].contador_alunos--;
                    }
                }
            }
            for (int j = i; j < *contador_estudante - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*contador_estudante)--;
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}

void adicionarAlunoAula(Aula *aulas, int contador_aulas, Aluno *alunos, int contador_estudante) {
    int id_aula, id_aluno;
    printf("Insira o ID da aula: ");
    scanf("%d", &id_aula);
    printf("Insira o ID do aluno: ");
    scanf("%d", &id_aluno);

    for (int i = 0; i < contador_aulas; i++) {
        if (aulas[i].id == id_aula) {
            if (aulas[i].contador_alunos >= MAX_ALUNOS) {
                printf("Número máximo de alunos nesta aula alcançado.\n");
                return;
            }
            for (int j = 0; j < contador_estudante; j++) {
                if (alunos[j].id == id_aluno) {
                    aulas[i].id_aluno[aulas[i].contador_alunos] = id_aluno;
                    aulas[i].contador_alunos++;
                    alunos[j].contador_aulas++;
                    return;
                }
            }
        }
    }
    printf("ID da aula ou aluno não encontrado.\n");
}

void listarAulasAlunos(Aula *aulas, int contador_aulas, Aluno *alunos, int contador_estudante) {
    int id_aluno;
    printf("Insira o ID do aluno para listar suas aulas: ");
    scanf("%d", &id_aluno);

    
    int encontrado = 0;
    for (int i = 0; i < contador_estudante; i++) {
        if (alunos[i].id == id_aluno) {
            encontrado = 1;
            printf("Aulas do aluno %s (ID: %d):\n", alunos[i].nome, alunos[i].id);
            for (int j = 0; j < contador_aulas; j++) {
                for (int k = 0; k < aulas[j].contador_alunos; k++) {
                    if (aulas[j].id_aluno[k] == id_aluno) {
                        printf("ID da aula: %d\n", aulas[j].id);
                        printf("Horário: %s\n", aulas[j].horario);
                        break;
                    }
                }
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno não encontrado.\n");
    }
}