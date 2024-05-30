#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>
#include "library.h"

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define criarPasta(pasta) _mkdir(pasta)
#else
#define criarPasta(pasta) mkdir(pasta, 0777)
#endif


#define MAX_AULAS 100
#define MAX_PROFESSORES 100
#define MAX_ALUNOS 100

#define DADOS_ALUNOS "dados/alunos/aluno_%d.txt"
#define DADOS_AULAS "dados/aulas/aula_%d.txt"
#define DADOS_PROFESSORES "dados/professores/professor_%d.txt"


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

