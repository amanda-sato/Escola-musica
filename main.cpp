#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define criarPasta(pasta) _mkdir(pasta)
#else
#define criarPasta(pasta) mkdir(pasta, 0777)
#endif


#define MAX_NOME 100
#define MAX_HORARIO 50
#define MAX_ALUNOS 100
#define MAX_PROFESSORES 100
#define MAX_AULAS 100

#define DADOS_ALUNOS "dados/alunos/aluno_%d.txt"
#define DADOS_AULAS "dados/aulas/aula_%d.txt"
#define DADOS_PROFESSORES "dados/professores/professor_%d.txt"

typedef struct {
    int id;
    char nome[MAX_NOME];
    int idade;
    char instrumento_musical[MAX_NOME];
    int contador_aulas;
} Aluno;

typedef struct {
    int id;
    char nome[MAX_NOME];
    char instrumento_musical[MAX_NOME];
    char horario[MAX_HORARIO];
    int contador_aulas;
} Professor;

typedef struct {
    int id;
    char nome[MAX_NOME]; // Nome da aula
    char horario[MAX_HORARIO];
    int Professor_id;
    int id_aluno[MAX_ALUNOS];
    int contador_alunos;
} Aula;


void criarPastas() {
    if (criarPasta("dados") == 0) {
        printf("Diretório 'dados' criado com sucesso.\n");
    } else {
        printf("Erro ao criar diretório 'dados'.\n");
        return;
    }

    if (criarPasta("dados/alunos") == 0) {
        printf("Diretório 'dados/alunos' criado com sucesso.\n");
    } else {
        printf("Erro ao criar diretório 'dados/alunos'.\n");
        return;
    }

    if (criarPasta("dados/professores") == 0) {
        printf("Diretório 'dados/professores' criado com sucesso.\n");
    } else {
        printf("Erro ao criar diretório 'dados/professores'.\n");
        return;
    }

    if (criarPasta("dados/aulas") == 0) {
        printf("Diretório 'dados/aulas' criado com sucesso.\n");
    } else {
        printf("Erro ao criar diretório 'dados/aulas'.\n");
        return;
    }
}



void salvarDados(
    Aluno *alunos, 
    int contador_estudante, 
    Professor *professores, 
    int contador_professor, 
    Aula *aulas, 
    int contador_aulas
) {
    for (int i = 0; i < contador_estudante; i++) {
        char filename[MAX_NOME];
        sprintf(filename, DADOS_ALUNOS, alunos[i].id);
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "%d\n%s\n%d\n%s\n%d\n", alunos[i].id, alunos[i].nome, alunos[i].idade, alunos[i].instrumento_musical, alunos[i].contador_aulas);
            fclose(file);
        } else {
            printf("Erro ao salvar aluno %d\n", alunos[i].id);
        }
    }

    for (int i = 0; i < contador_professor; i++) {
        char filename[MAX_NOME];
        sprintf(filename, DADOS_PROFESSORES, professores[i].id);
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "%d\n%s\n%s\n%s\n%d\n", professores[i].id, professores[i].nome, professores[i].instrumento_musical, professores[i].horario, professores[i].contador_aulas);
            fclose(file);
        } else {
            printf("Erro ao salvar professor %d\n", professores[i].id);
        }
    }

    for (int i = 0; i < contador_aulas; i++) {
        char filename[MAX_NOME];
        sprintf(filename, DADOS_AULAS, aulas[i].id);
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "%d\n%d\n", aulas[i].id, aulas[i].Professor_id);
            for (int j = 0; j < aulas[i].contador_alunos; j++) {
                fprintf(file, "%d\n", aulas[i].id_aluno[j]);
            }
            fprintf(file, "%s\n", aulas[i].horario);
            fclose(file);
        } else {
            printf("Erro ao salvar aula %d\n", aulas[i].id);
        }
    }
}

void carregarDados(
    Aluno *alunos, 
    int *contador_estudante, 
    Professor *professores, 
    int *contador_professor, 
    Aula *aulas, 
    int *contador_aulas
) {
    FILE *file;
    char filename[MAX_NOME];
    int id;

    *contador_estudante = 0;
    *contador_professor = 0;
    *contador_aulas = 0;

    for (id = 1; id <= MAX_ALUNOS; id++) {
        sprintf(filename, DADOS_ALUNOS, id);
        file = fopen(filename, "r");
        if (file) {
            fscanf(file, "%d\n", &alunos[*contador_estudante].id);
            fgets(alunos[*contador_estudante].nome, MAX_NOME, file);
            alunos[*contador_estudante].nome[strcspn(alunos[*contador_estudante].nome, "\n")] = 0;  // remove newline
            fscanf(file, "%d\n", &alunos[*contador_estudante].idade);
            fgets(alunos[*contador_estudante].instrumento_musical, MAX_NOME, file);
            alunos[*contador_estudante].instrumento_musical[strcspn(alunos[*contador_estudante].instrumento_musical, "\n")] = 0;  // remove newline
            fscanf(file, "%d\n", &alunos[*contador_estudante].contador_aulas);
            fclose(file);
            (*contador_estudante)++;
        }
    }

    for (id = 1; id <= MAX_PROFESSORES; id++) {
        sprintf(filename, DADOS_PROFESSORES, id);
        file = fopen(filename, "r");
        if (file) {
            fscanf(file, "%d\n", &professores[*contador_professor].id);
            fgets(professores[*contador_professor].nome, MAX_NOME, file);
            professores[*contador_professor].nome[strcspn(professores[*contador_professor].nome, "\n")] = 0;  // remove newline
            fgets(professores[*contador_professor].instrumento_musical, MAX_NOME, file);
            professores[*contador_professor].instrumento_musical[strcspn(professores[*contador_professor].instrumento_musical, "\n")] = 0;  // remove newline
            fgets(professores[*contador_professor].horario, MAX_HORARIO, file);
            professores[*contador_professor].horario[strcspn(professores[*contador_professor].horario, "\n")] = 0;  // remove newline
            fscanf(file, "%d\n", &professores[*contador_professor].contador_aulas);
            fclose(file);
            (*contador_professor)++;
        }
    }

    for (id = 1; id <= MAX_AULAS; id++) {
        sprintf(filename, DADOS_AULAS, id);
        file = fopen(filename, "r");
        if (file) {
            fscanf(file, "%d\n", &aulas[*contador_aulas].id);
            fscanf(file, "%d\n", &aulas[*contador_aulas].Professor_id);
            aulas[*contador_aulas].contador_alunos = 0;
            while (fscanf(file, "%d\n", &aulas[*contador_aulas].id_aluno[aulas[*contador_aulas].contador_alunos]) == 1) {
                aulas[*contador_aulas].contador_alunos++;
            }
            fgets(aulas[*contador_aulas].horario, MAX_HORARIO, file);
            aulas[*contador_aulas].horario[strcspn(aulas[*contador_aulas].horario, "\n")] = 0;  // remove newline
            fclose(file);
            (*contador_aulas)++;
        }
    }
}

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

void addAula(Aula *aulas, int *contador_aulas) {
    if (*contador_aulas >= MAX_AULAS) {
        printf("Número máximo de aulas alcançado.\n");
        return;
    }
    aulas[*contador_aulas].id = *contador_aulas + 1;
    aulas[*contador_aulas].contador_alunos = 0;
    printf("Insira o nome da aula: ");
    scanf(" %[^\n]", aulas[*contador_aulas].nome);
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

void editarAula(Aula *aulas, int contador_aulas) {
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

void excluirAula(Aula *aulas, int *contador_aulas) {
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


int main() {
    Aluno alunos[MAX_ALUNOS];
    Professor professores[MAX_PROFESSORES];
    Aula aulas[MAX_AULAS];
    int contador_estudante = 0;
    int contador_professor = 0;
    int contador_aulas = 0;

    criarPastas();
    carregarDados(alunos, &contador_estudante, professores, &contador_professor, aulas, &contador_aulas);

    int escolha;

    while (1) {
        printf("\n1. Adicionar Aluno\n2. Listar Alunos\n3. Adicionar Professor\n4. Listar Professores\n5. Adicionar Aula\n6. Listar Aulas\n7. Adicionar Aluno a Aula\n8. Editar Aluno\n9. Editar Professor\n10. Editar Aula\n11. Excluir Aluno\n12. Excluir Professor\n13. Excluir Aula\n14. Listar Aulas aluno\n15. Listar Aulas Professor\n16. Salvar Dados\n17. Carregar Dados\n18. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                addAluno(alunos, &contador_estudante);
                break;
            case 2:
                listarAlunos(alunos, contador_estudante);
                break;
            case 3:
                addProfessor(professores, &contador_professor);
                break;
            case 4:
                listarProfessores(professores, contador_professor);
                break;
            case 5:
                addAula(aulas, &contador_aulas);
                break;
            case 6:
                listarAulas(aulas, contador_aulas, alunos, contador_estudante, professores, contador_professor);
                break;
            case 7:
                adicionarAlunoAula(aulas, contador_aulas, alunos, contador_estudante);
                break;
            case 8:
                editarAluno(alunos, contador_estudante);
                break;
            case 9:
                editarProfessor(professores, contador_professor);
                break;
            case 10:
                editarAula(aulas, contador_aulas);
                break;
            case 11:
                excluirAluno(alunos, &contador_estudante, aulas, contador_aulas);
                break;
            case 12:
                excluirProfessor(professores, &contador_professor, aulas, contador_aulas);
                break;
            case 13:
                excluirAula(aulas, &contador_aulas);
                break;
            case 14:
                listarAulasAlunos(aulas, contador_aulas, alunos, contador_estudante);
                break;
            case 15:
                listarAulasProfessor(aulas, contador_aulas, professores, contador_professor);
                break;   
            case 16:
                salvarDados(alunos, contador_estudante, professores, contador_professor, aulas, contador_aulas);
                break;
            case 17:
                carregarDados(alunos, &contador_estudante, professores, &contador_professor, aulas, &contador_aulas);
                break;
            case 18:
                salvarDados(alunos, contador_estudante, professores, contador_professor, aulas, contador_aulas);
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}

