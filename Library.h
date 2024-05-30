#ifndef LIBRARY_H
#define LIBRARY_H 

#define MAX_NOME 100
#define MAX_HORARIO 50
#define MAX_AULAS 100
#define MAX_ALUNOS 100

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
void addAluno(Aluno *alunos, int *contador_estudante);
void listarAlunos(Aluno *alunos, int contador_estudante);
void editarAluno(Aluno *alunos, int contador_estudante);
void excluirAluno(Aluno *alunos, int *contador_estudante, Aula *aulas, int contador_aulas);
void adicionarAlunoAula(Aula *aulas, int contador_aulas, Aluno *alunos, int contador_estudante);
void listarAulasAlunos(Aula *aulas, int contador_aulas, Aluno *alunos, int contador_estudante);



void addProfessor(Professor *professores, int *contador_professor);
void listarProfessores(Professor *professores, int contador_professor);
void editarProfessor(Professor *professores, int contador_professor);
void excluirProfessor(Professor *professores, int *contador_professor, Aula *aulas, int contador_aulas);
void listarAulasProfessor(Aula *aulas, int contador_aulas, Professor *professores, int contador_professor);



void addAula(Aula *aulas, int *contador_aulas);
void listarAulas(Aula *aulas, int contador_aulas, Aluno *alunos, int contador_estudante, Professor *professores, int contador_professor);
void editarAula(Aula *aulas, int contador_aulas);
void excluirAula(Aula *aulas, int *contador_aulas);
#endif