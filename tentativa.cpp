#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_HORARIO 50
#define MAX_ALUNOS 100
#define MAX_PROFESSORES 100
#define MAX_AULAS 100

typedef struct {
    int id;
    char name[MAX_NOME];
    int idade;
    char instrumento_musical[MAX_NOME];
    int contador_aulas; // Contador de aulas para o aluno
} Aluno;

typedef struct {
    int id;
    char name[MAX_NOME];
    char instrumento_musical[MAX_NOME];
    char horario[MAX_HORARIO];
    int contador_aulas; // Contador de aulas para o professor
} Professor;

typedef struct {
    int id;
    int id_aluno;
    int Professor_id;
    char horario[MAX_HORARIO];
} Aulas;


void addAluno(Aluno *alunos, int *contador_estudante);
void Listaralunos(Aluno *alunos, int contador_estudante);
void addProfessor(Professor *professores, int *contador_professor);
void Listarprofessores(Professor *professores, int contador_professor);
void addAulas(Aulas *aulas, int *contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor);
void Listaraulas(Aulas *aulas, int contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor);
void ListarAlunoaulas(Aulas *aulas, int contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor, int id_aluno);
void ListarProfessoraulas(Aulas *aulas, int contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor, int Professor_id);


void addAluno(Aluno *alunos, int *contador_estudante) {
    if (*contador_estudante >= MAX_ALUNOS) {
        printf("Número máximo de alunos alcançado.\n");
        return;
    }
    alunos[*contador_estudante].id = *contador_estudante + 1; 
    printf("Enter Aluno name: ");
    scanf(" %[^\n]", alunos[*contador_estudante].name);
    printf("Enter Aluno idade: ");
    scanf("%d", &alunos[*contador_estudante].idade);
    printf("Enter Aluno instrumento_musical: ");
    scanf(" %[^\n]", alunos[*contador_estudante].instrumento_musical);
    alunos[*contador_estudante].contador_aulas = 0;
    (*contador_estudante)++;
}

void Listaralunos(Aluno *alunos, int contador_estudante) {
    for (int i = 0; i < contador_estudante; i++) {
        printf("ID: %d, Name: %s, idade: %d, instrumento_musical: %s, aulas: %d\n",
               alunos[i].id, alunos[i].name, alunos[i].idade, alunos[i].instrumento_musical, alunos[i].contador_aulas);
    }
}

void addProfessor(Professor *professores, int *contador_professor) {
    if (*contador_professor >= MAX_PROFESSORES) {
        printf("Número máximo de professores alcançado.\n");
        return;
    }
    professores[*contador_professor].id = *contador_professor + 1; 
    printf("Enter Professor name: ");
    scanf(" %[^\n]", professores[*contador_professor].name);
    printf("Enter instrumento_musical: ");
    scanf(" %[^\n]", professores[*contador_professor].instrumento_musical);
    printf("Enter horario: ");
    scanf(" %[^\n]", professores[*contador_professor].horario);
    professores[*contador_professor].contador_aulas = 0;
    (*contador_professor)++;
}

void Listarprofessores(Professor *professores, int contador_professor) {
    for (int i = 0; i < contador_professor; i++) {
        printf("ID: %d, Name: %s, instrumento_musical: %s, horario: %s, aulas: %d\n",
               professores[i].id, professores[i].name, professores[i].instrumento_musical, professores[i].horario, professores[i].contador_aulas);
    }
}

void addAulas(Aulas *aulas, int *contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor) {
    if (*contador_aulas >= MAX_AULAS) {
        printf("Número máximo de aulas alcançado.\n");
        return;
    }
    int id_aluno, Professor_id;

    aulas[*contador_aulas].id = *contador_aulas + 1; 

    printf("Aluno ID: ");
    scanf("%d", &id_aluno);
    int alunoExists = 0;
    for (int i = 0; i < contador_estudante; i++) {
        if (alunos[i].id == id_aluno) {
            alunoExists = 1;
            alunos[i].contador_aulas++;
            break;
        }
    }
    if (!alunoExists) {
        printf("O ID do aluno não foi encontrado.\n");
        return;
    }

    printf("Professor ID: ");
    scanf("%d", &Professor_id);
    int ProfessorExists = 0;
    for (int i = 0; i < contador_professor; i++) {
        if (professores[i].id == Professor_id) {
            ProfessorExists = 1;
            professores[i].contador_aulas++;
            break;
        }
    }
    if (!ProfessorExists) {
        printf("O ID do professor não foi encontrado.\n");
        return;
    }

    aulas[*contador_aulas].id_aluno = id_aluno;
    aulas[*contador_aulas].Professor_id = Professor_id;
    printf("Enter horario: ");
    scanf(" %[^\n]", aulas[*contador_aulas].horario);
    (*contador_aulas)++;
}

void Listaraulas(Aulas *aulas, int contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor) {
    for (int i = 0; i < contador_aulas; i++) {
        char nome_aluno[MAX_NOME] = "Unknown";
        char nome_professor[MAX_NOME] = "Unknown";

        for (int j = 0; j < contador_estudante; j++) {
            if (alunos[j].id == aulas[i].id_aluno) {
                strcpy(nome_aluno, alunos[j].name);
                break;
            }
        }

        for (int j = 0; j < contador_professor; j++) {
            if (professores[j].id == aulas[i].Professor_id) {
                strcpy(nome_professor, professores[j].name);
                break;
            }
        }

        printf("Aulas ID: %d, Aluno: %s, Professor: %s, horario: %s\n",
               aulas[i].id, nome_aluno, nome_professor, aulas[i].horario);
    }
}

void ListarAlunoaulas(Aulas *aulas, int contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor, int id_aluno) {
    printf("aulas for Aluno ID %d:\n", id_aluno);
    for (int i = 0; i < contador_aulas; i++) {
        if (aulas[i].id_aluno == id_aluno) {
            char nome_professor[MAX_NOME] = "Unknown";
            for (int j = 0; j < contador_professor; j++) {
                if (professores[j].id == aulas[i].Professor_id) {
                    strcpy(nome_professor, professores[j].name);
                    break;
                }
            }
            printf("Aulas ID: %d, Professor: %s, horario: %s\n",
                   aulas[i].id, nome_professor, aulas[i].horario);
        }
    }
}

void ListarProfessoraulas(Aulas *aulas, int contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor, int Professor_id) {
    printf("aulas for Professor ID %d:\n", Professor_id);
    for (int i = 0; i < contador_aulas; i++) {
        if (aulas[i].Professor_id == Professor_id) {
            char nome_aluno[MAX_NOME] = "Unknown";
            for (int j = 0; j < contador_estudante; j++) {
                if (alunos[j].id == aulas[i].id_aluno) {
                    strcpy(nome_aluno, alunos[j].name);
                    break;
                }
            }
            printf("Aulas ID: %d, Aluno: %s, horario: %s\n",
                   aulas[i].id, nome_aluno, aulas[i].horario);
        }
    }
}

int main() {
    Aluno alunos[MAX_ALUNOS];
    Professor professores[MAX_PROFESSORES];
    Aulas aulas[MAX_AULAS];
    int contador_estudante = 0;
    int contador_professor = 0;
    int contador_aulas = 0;

    int escolha;

    while (1) {
        printf("\n1. Adcionar Aluno\n2. Listar alunos\n3. Adcionar Professor\n4. Listar professores\n5. Adcionar Aulas\n6. Listar aulas\n7. Listar Aluno aulas\n8. Listar Professor aulas\n9. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                addAluno(alunos, &contador_estudante);
                break;
            case 2:
                Listaralunos(alunos, contador_estudante);
                break;
            case 3:
                addProfessor(professores, &contador_professor);
                break;
            case 4:
                Listarprofessores(professores, contador_professor);
                break;
            case 5:
                addAulas(aulas, &contador_aulas, alunos, contador_estudante, professores, contador_professor);
                break;
            case 6:
                Listaraulas(aulas, contador_aulas, alunos, contador_estudante, professores, contador_professor);
                break;
            case 7:
                printf("Enter Aluno ID: ");
                int id_aluno;
                scanf("%d", &id_aluno);
                ListarAlunoaulas(aulas, contador_aulas, alunos, contador_estudante, professores, contador_professor, id_aluno);
                break;
            case 8:
                printf("Enter Professor ID: ");
                int Professor_id;
                scanf("%d", &Professor_id);
                ListarProfessoraulas(aulas, contador_aulas, alunos, contador_estudante, professores, contador_professor, Professor_id);
                break;
            case 9:
                exit(0);
            default:
                printf("Escolha inválida. Tente de novo.\n");
        }
    }
    return 0;
}

