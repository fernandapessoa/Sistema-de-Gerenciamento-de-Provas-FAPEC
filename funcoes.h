struct Aluno {
  int codigoCurso;
  int codigoAluno;
  char nome[81];
  int dia, mes, ano;
  int nascimento; //concatenado de ano-mes-dia para ordenar no caso de empate e conferir se tem mais de 60 anos
  char tipoVaga[4]; // AC, L1, L11...

  int acertos_LIN, acertos_MAT, acertos_NAT, acertos_HUM;// acertos em cada materia
  float ep_LIN, ep_MAT, ep_NAT, ep_HUM;// a nota já calculada
  
  float RED_notaAnterior, RED_notaAtual; // redação pode ter a nota alterada
  bool alteracaoRed; //se a nota da redação foi alterada
  
  float nota_final;
  int classificacao;
    
  bool presente; //se fez a prova ou não
  bool aprovado; // se true = aprovado, se false = reprovado
};


struct tipoCurso {
  int codigoCurso;
  char nomeCurso[50];
  // Peso de cada matéria
  int red, mat, lin, hum, nat;
  // Quantidade de vagas para cada cota
  int AC, L1, L3, L4, L5, L7, L8, L9, L11, L13, L15;
};


struct Reprovados
{
  int codigoCurso;
  int codigoAluno;
  char nome[81];
  bool aprovado; 
};

//BUSCA----------------------------------------------------------------------------------------------------------------
int buscaIndiceAluno(int codigoAlunoAux, Aluno *alunos, int qntTotalInscritos);

int buscaIndiceCurso(int codigoCursoAux, tipoCurso *cursos, int nCursos);

//ORDENAÇÃO
void ordenaCursos (tipoCurso *&cursos, int nCursos);

//LEITURA----------------------------------------------------------------------------------------------------------------
int le_Cursos_e_Pesos (tipoCurso *&cursos);

void le_Cursos_e_Vagas (tipoCurso *&cursos, int nCursos);

int le_Dados(Aluno *&alunos);

void le_Acertos(Aluno *&alunos, int qntTotalInscritos);

//IMPRESSAO----------------------------------------------------------------------------------------------------------------
void imprimeCandidato(Aluno *alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos);

//CALCULO------------------------------------------------------------------------------------------------------------------
void calculaDesvioPadrao (Aluno *alunos, int qntTotalInscritos, float &media_lin, float &media_mat, float &media_nat, float &media_hum, float &desvio_lin, float &desvio_mat, float &desvio_nat, float &desvio_hum);

void calculaEP (Aluno *alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos, float media_lin, float media_mat, float media_nat, float media_hum, float desvio_lin, float desvio_mat, float desvio_nat, float desvio_hum);

void alterarNotaRed(Aluno *&alunos, int qntTotalInscritos);

void calculaNotaFinal(Aluno *&alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos);

//GERAR ARQUIVO ORDENADO ---------------------------------------------------------------------------------------------------
void geraArquivoCandidato(Aluno *&alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos);

void geraArquivoReprovados(Aluno *&alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos);

