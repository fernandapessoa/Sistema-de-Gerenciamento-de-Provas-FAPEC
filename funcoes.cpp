#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int buscaIndiceCurso(int codigoCursoAux, tipoCurso *cursos, int nCursos) {
  for (int i = 0; i < nCursos; i++) {
    if (cursos[i].codigoCurso == codigoCursoAux)
      return i;
  }
  return -1;
};


int buscaIndiceAluno(int codigoAlunoAux, Aluno *alunos, int qntTotalInscritos) {
  for (int i = 0; i < qntTotalInscritos; i++) {
    if (alunos[i].codigoAluno == codigoAlunoAux)
      return i;
  }
  return -1;
};

//Ordena os cursos por ordem alfabética
void ordenaCursos (tipoCurso *&cursos, int nCursos)
{
    int vez;
    tipoCurso cursoAux;
    do
    {
        vez = 0;
        for(int i=1; i<nCursos; i++)
        {
            if(strcmp(cursos[i].nomeCurso, cursos[i-1].nomeCurso)<0)
            {
              cursoAux = cursos[i];
              cursos[i] = cursos[i-1];
              cursos[i-1] = cursoAux;
              vez = 1;
            }
        }

    }while(vez!=0);

    for(int i=0; i<nCursos; i++)
    {
      printf("%s\n", cursos[i].nomeCurso);
    }
    printf("Cursos ordenados\n");
}

int le_Cursos_e_Pesos (tipoCurso *&cursos)
{
  
  FILE *ptCursoPeso;
  ptCursoPeso = fopen("cursos_e_pesos.txt", "r");
  int nCursos;
  
  if (!ptCursoPeso)
    printf("Erro na abertura do arquivo.\n\n");
  else
  {

    // Leitura da quantidade de pesos
    fscanf(ptCursoPeso, "%d", &nCursos);
    
    //ALOCAÇÃO DINÂMICA NA MEMÓRIA
    cursos = (tipoCurso *) calloc(nCursos, sizeof(tipoCurso));

    if (!cursos)
      printf("Erro na leitura dos pesos.\n\n");
      
    else 
    {
      // Armazenando informacoes nos structs
      for (int i = 0; i < nCursos; i++) 
      {
        fscanf(ptCursoPeso, "%d", &cursos[i].codigoCurso);
        fscanf(ptCursoPeso, " %[^0-9]", cursos[i].nomeCurso);
        fscanf(ptCursoPeso, "%d %d %d %d %d", &cursos[i].red, &cursos[i].mat,
              &cursos[i].lin, &cursos[i].hum, &cursos[i].nat);
      }
      printf("\nCursos e pesos lidos\n");
    }
  }
  fclose(ptCursoPeso);
  return nCursos;
}



void le_Cursos_e_Vagas (tipoCurso *&cursos, int nCursos)
{
  
  FILE *arqVagas;
  arqVagas = fopen("cursos_e_vagas.txt", "r");
  int nVagas, indice = 0, codigoCursoAux;

  if (!arqVagas) // Testar se a abertura funcionou
    printf("\n\nErro na abertura do arquivo.\n\n");
  else
  {
    // leitura da quantidade de vagas
    fscanf(arqVagas, "%d", &nVagas);

    // Salvando na struct tipoCurso *pesos
    for (int i = 0; i < nVagas; i++) {
      // leitura do código do curso
      fscanf(arqVagas, "%d", &codigoCursoAux);

      // Acha o índice de tipoCurso *pesos que tem o mesmo codigoCurso que foi
      // lido
      indice = buscaIndiceCurso(codigoCursoAux, cursos, nCursos);

      if (indice == -1) {
        printf("Erro na procura do índice");
      }
      // Aqui salva todas as cotas nele
      else {
        fscanf(arqVagas, "%d %d %d %d %d %d %d %d %d %d %d ", &cursos[indice].AC,
              &cursos[indice].L1, &cursos[indice].L3, &cursos[indice].L4,
              &cursos[indice].L5, &cursos[indice].L7, &cursos[indice].L8,
              &cursos[indice].L9, &cursos[indice].L11, &cursos[indice].L13,
              &cursos[indice].L15);
      }
    }
    printf("Vagas lidas\n");
  }
  fclose(arqVagas);
}

int le_Dados(Aluno *&alunos)
{
  FILE *arqDados;
  arqDados = fopen("dados.txt", "r");
  int codCursoAux, qntInscritos, qntTotalInscritos = 0, indice = 0;

  if (!arqDados) // Testar se a abertura funcionou
    printf("\n\nErro na abertura do arquivo.\n\n");
  else
  {

    //ALOCAÇÃO DINÂMICA NA MEMÓRIA (precisa alocar primeiro com malloc para depois usar o realloc, por isso aqui só aloca um espaço)
    alunos = (Aluno *) malloc (1*sizeof(Aluno));

    //O while le os codigos do curso
    while ((fscanf(arqDados, "%d", &codCursoAux)) != EOF) {

      //então ve a quantidade de inscritos que vai limitar o for e atualizar a alocação dinâmica de memória
      fscanf(arqDados, "%d", &qntInscritos);
      qntTotalInscritos = qntTotalInscritos + qntInscritos;

      //ALOCAÇÃO DINÂMICA USANDO O REALLOC
      alunos = (Aluno *) realloc(alunos, qntTotalInscritos * sizeof(Aluno));
      
      //Aqui vai ler cada linha do arquivo que contém informação sobre os alunos
      for (int i = 0; i < qntInscritos; i++) {

        fscanf(arqDados, "%d", &alunos[indice].codigoAluno);
        fscanf(arqDados, " %[^0-9]", alunos[indice].nome);
        fscanf(arqDados, "%d/%d/%d", &alunos[indice].dia, &alunos[indice].mes, &alunos[indice].ano );
        fscanf(arqDados, "%s", alunos[indice].tipoVaga);
        alunos[indice].codigoCurso = codCursoAux;
        alunos[indice].nascimento = alunos[indice].ano*10000 + alunos[indice].mes*100 + alunos[indice].dia;

        //iSSO É PARA EVITAR QUE FIQUEM COM VALORES LIXO
        alunos[indice].acertos_HUM = 0;
        alunos[indice].acertos_LIN = 0;
        alunos[indice].acertos_MAT = 0;
        alunos[indice].acertos_NAT = 0;
        alunos[indice].ep_HUM = 0;
        alunos[indice].ep_LIN = 0;
        alunos[indice].ep_MAT = 0;
        alunos[indice].ep_NAT = 0;
        alunos[indice].RED_notaAnterior = 0;
        alunos[indice].RED_notaAtual = 0;
        alunos[indice].presente = false;
        alunos[indice].alteracaoRed = false;
        //Como cada hora aparece mais gente, o índice depende dessa variável aqui em vez do for
        indice++;
      }
    }  
    printf("Dados lidos\n");
  }
  fclose(arqDados);
  //como na função le_Acertos vai precisar usar essa variável aqui, ela é retornada para a main
  return qntTotalInscritos;
}


void le_Acertos(Aluno *&alunos, int qntTotalInscritos)
{
  FILE *arqAcertos;
  arqAcertos = fopen("acertos.txt", "r");
  int nAcertos, codigoAlunoAux, indice;
  Aluno alunoLixo; //serve para armazenar lixo e não ler os acertos do usuário não encontrado como se fosse um outro codAluno

  if (!arqAcertos) // Testar se a abertura funcionou
    printf("\n\nErro na abertura do arquivo.\n\n");
  else
  {

    fscanf(arqAcertos, "%d", &nAcertos);

    //le o código do aluno, em seguida procura o índice desse aluno para então salvar as próximas informações
    for (int i = 0; i < nAcertos; i++) {
      fscanf(arqAcertos, "%d", &codigoAlunoAux);
      indice = buscaIndiceAluno(codigoAlunoAux, alunos, qntTotalInscritos);
     
      if (indice == -1) 
      {
        printf("Código %d NÃO está registrado em dados.txt\n", codigoAlunoAux);
        fscanf(arqAcertos, "%d %d %d %d %f", &alunoLixo.acertos_LIN,
              &alunoLixo.acertos_MAT, &alunoLixo.acertos_NAT,
              &alunoLixo.acertos_HUM, &alunoLixo.RED_notaAtual);
        alunoLixo.presente = true;
      } else {
        fscanf(arqAcertos, "%d %d %d %d %f", &alunos[indice].acertos_LIN,
              &alunos[indice].acertos_MAT, &alunos[indice].acertos_NAT,
              &alunos[indice].acertos_HUM, &alunos[indice].RED_notaAtual);
        alunos[indice].presente = true;
      }
    }
    printf("Acertos lidos\n\n");
  }
  fclose(arqAcertos);
}

void imprimeCandidato(Aluno *alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos)
{
  int matriculaAux, indiceAluno, indiceCurso; 
  do{
    
    printf("\nINFORME A MATRICULA DO CANDIDATO PARA PESQUISAR OU 0 PARA ENCERRAR AS PESQUISA: ");
    scanf("%d", &matriculaAux);
    indiceAluno =  buscaIndiceAluno(matriculaAux , alunos, qntTotalInscritos);
      
    if(indiceAluno == -1){
      printf("Matrícula não encontrada.\n");
    }
    else{
      indiceCurso = buscaIndiceCurso(alunos[indiceAluno].codigoCurso, cursos, nCursos);
      printf("%d %s %d/%d/%d %d %s\n", alunos[indiceAluno].codigoAluno, alunos[indiceAluno].nome, 
      alunos[indiceAluno].dia, alunos[indiceAluno].mes, alunos[indiceAluno].ano, cursos[indiceCurso].codigoCurso, cursos[indiceCurso].nomeCurso);
    }
    
  }while (matriculaAux != 0);
  
};

void calculaDesvioPadrao (Aluno *alunos, int qntTotalInscritos, float &media_lin, float &media_mat, float &media_nat, float &media_hum, float &desvio_lin, float &desvio_mat, float &desvio_nat, float &desvio_hum)
{
  float somatorio_lin = 0, somatorio_mat = 0, somatorio_nat = 0, somatorio_hum = 0;
  double sigma_lin = 0, sigma_mat = 0, sigma_nat = 0, sigma_hum = 0;
  int quantidadeAlunosPresentes = 0;

  //Soma os acertos de cada área de todos os alunos PRESENTES 
  for(int i=0; i<qntTotalInscritos; i++)
  {
    if(alunos[i].presente){
      quantidadeAlunosPresentes++;
      somatorio_lin = somatorio_lin + alunos[i].acertos_LIN;
      somatorio_mat = somatorio_mat + alunos[i].acertos_MAT;
      somatorio_nat = somatorio_nat + alunos[i].acertos_NAT;
      somatorio_hum = somatorio_hum + alunos[i].acertos_HUM;
    }
  }

//Calcula a média de área levando em consideração apenas os alunos que estavam presentes
  media_lin = somatorio_lin/quantidadeAlunosPresentes;
  media_mat = somatorio_mat/quantidadeAlunosPresentes;
  media_nat = somatorio_nat/quantidadeAlunosPresentes;
  media_hum = somatorio_hum/quantidadeAlunosPresentes;

  for(int i=0; i<qntTotalInscritos; i++)
  {
    if(alunos[i].presente){
      sigma_lin = sigma_lin + pow((alunos[i].acertos_LIN - media_lin), 2);
      sigma_mat = sigma_mat + pow((alunos[i].acertos_MAT - media_mat), 2);
      sigma_nat = sigma_nat + pow((alunos[i].acertos_NAT - media_nat), 2);
      sigma_hum = sigma_hum + pow((alunos[i].acertos_HUM - media_hum), 2);
    }
  }

  desvio_lin = sqrt(sigma_lin/quantidadeAlunosPresentes);
  desvio_mat = sqrt(sigma_mat/quantidadeAlunosPresentes);
  desvio_nat = sqrt(sigma_nat/quantidadeAlunosPresentes);
  desvio_hum = sqrt(sigma_hum/quantidadeAlunosPresentes);

  //printf("desvio lin:%f\nmedia lin: %f\n", desvio_lin*2, media_lin*2);

  printf("Médias e desvio padrão calculados\n");
}

void calculaEP (Aluno *alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos, float media_lin, float media_mat, float media_nat, float media_hum, float desvio_lin, float desvio_mat, float desvio_nat, float desvio_hum)
{
  for(int i=0; i<qntTotalInscritos; i++)
  {
    if(alunos[i].presente)
    {
      //EP vem de escore padronizado da competência, é a nota oficial considerando a media e desvio
      alunos[i].ep_LIN = 500 + 100*((2*alunos[i].acertos_LIN - 2*media_lin)/(2*desvio_lin));
      alunos[i].ep_MAT = 500 + 100*((2*alunos[i].acertos_MAT - 2*media_mat)/(2*desvio_mat));
      alunos[i].ep_NAT = 500 + 100*((2*alunos[i].acertos_NAT - 2*media_nat)/(2*desvio_nat));
      alunos[i].ep_HUM = 500 + 100*((2*alunos[i].acertos_HUM - 2*media_hum)/(2*desvio_hum));
      
    }
  }
  printf("EPs calculadas\n");
}

void alterarNotaRed(Aluno *&alunos, int qntTotalInscritos)
{
  FILE *arqRed;
  //char nomeArqRed[50];
  // printf("\nDigite o nome do arquivo .txt que contém as alterações das notas da redação: ");
  // scanf(" %s", nomeArqRed);
  arqRed = fopen("alteracaoNotaRedacao.txt", "r");

  int quantidadeAlteracoes, codigoAlunoAux, indiceAluno;

  if(!arqRed)
    printf("Erro na abertura do arquivo\n");
  else
  {
    fscanf(arqRed, "%d", &quantidadeAlteracoes);

    for(int i=0; i<quantidadeAlteracoes; i++)
    {
      fscanf(arqRed, "%d", &codigoAlunoAux);

      indiceAluno = buscaIndiceAluno(codigoAlunoAux, alunos, qntTotalInscritos);

      if(indiceAluno == -1){
        printf("Não foi encontrado o aluno\n");
      }

      else
      {
        fscanf(arqRed, "%f %f", &alunos[indiceAluno].RED_notaAnterior,  &alunos[indiceAluno].RED_notaAtual );
        alunos[indiceAluno].alteracaoRed = true;
      }
    }
    
    printf("Notas de redação alteradas\n");
  }
  fclose(arqRed);
}


void calculaNotaFinal(Aluno *&alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos)
{
  int indiceCurso;
  for(int i=0; i<qntTotalInscritos; i++)
  {
    if(alunos[i].presente)
    {
      indiceCurso = buscaIndiceCurso(alunos[i].codigoCurso, cursos, nCursos);

      alunos[i].nota_final = (
      (alunos[i].ep_HUM * cursos[indiceCurso].hum) + 
      (alunos[i].ep_LIN * cursos[indiceCurso].lin) + 
      (alunos[i].ep_MAT * cursos[indiceCurso].mat) + 
      (alunos[i].ep_NAT * cursos[indiceCurso].nat) + 
      (alunos[i].RED_notaAtual * cursos[indiceCurso].red))/
      (cursos[indiceCurso].hum + cursos[indiceCurso].lin + 
      cursos[indiceCurso].mat + cursos[indiceCurso].nat +  cursos[indiceCurso].red);
    }
    else
    {
      alunos[i].nota_final = 0;
    }
  }
  printf("Notas finais calculadas\n");
};



void geraArquivoCandidato(Aluno *&alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos)
{
  FILE *arq;
  arq = fopen("Arquivo_candidato.txt", "w");
  Aluno *candidatos;

  char vaga[4];
  int vez = 0, posicao, quantidadeVaga;
  Aluno alunoAux;
  int indiceCandidatos = 0, data = 20221115;
  
  /*Cara pessoa que for tentar entender o que está acontecendo nessa função,
  desejo a você boa sorte.
  Eu tentaria comentar o que se passou na minha cabeça, mas são 4h da manhã,
  e talvez nem eu saiba o que eu fiz.
  Mas funciona!!*/

  //PS. Criei coragem e comentei o código do geraArquivoReprovados que é basicamente a mesma coisa que esse aqui


  fprintf(arq,"/*LISTA GERAL CLASSIFICADO POR NOTA*/	\n");	
  for(int i=0; i<nCursos; i++)
  {
    fprintf(arq,"\n%d %s\n", cursos[i].codigoCurso, cursos[i].nomeCurso);
    fprintf(arq,"INSC	V_LIN	V_MAT	V_NAT	V_HUM	RED     COTA NOTA FINAL	CLASSIFICAÇÃO\n");
    
    for(int vagas = 0; vagas<11; vagas++)
    {
      
    switch (vagas)
      {
        case 0: strcpy(vaga, "AC"); quantidadeVaga = cursos[i].AC; break;
        case 1: strcpy(vaga, "L1"); quantidadeVaga = cursos[i].L1; break;
        case 2:strcpy(vaga, "L3"); quantidadeVaga = cursos[i].L3;break;
        case 3:strcpy(vaga, "L4"); quantidadeVaga = cursos[i].L4;break;
        case 4:strcpy(vaga, "L5"); quantidadeVaga = cursos[i].L5;break;
        case 5:strcpy(vaga, "L7"); quantidadeVaga = cursos[i].L7;break;
        case 6:strcpy(vaga, "L8"); quantidadeVaga = cursos[i].L8;break;
        case 7:strcpy(vaga, "L9"); quantidadeVaga = cursos[i].L9;break;
        case 8:strcpy(vaga, "L11"); quantidadeVaga = cursos[i].L11;break;
        case 9:strcpy(vaga, "L13"); quantidadeVaga = cursos[i].L13;break;
        case 10:strcpy(vaga, "L15"); quantidadeVaga = cursos[i].L15;break;
        default: break;
      }
          
      indiceCandidatos = 0;
      candidatos = (Aluno *) malloc(1*sizeof(Aluno));

      for(int j=0; j<qntTotalInscritos; j++)
      {
        if(alunos[j].codigoCurso == cursos[i].codigoCurso && (strcmp(alunos[j].tipoVaga, vaga) == 0) && alunos[j].presente)
        {
          candidatos = (Aluno *) realloc(candidatos,(indiceCandidatos+1)*sizeof(Aluno));
          candidatos[indiceCandidatos] = alunos[j];
          indiceCandidatos++;
        }
      }
      
      do
      {
        vez = 0;
        for(int j=1; j<indiceCandidatos; j++)
        {
          //Essa parte aqui é pra caso empate
          if(candidatos[j].nota_final == candidatos[j-1].nota_final && candidatos[j].nota_final != 0)
          {
            //Eles tem além do dia mes e ano, uma variável nascimento que ta concatenada no formato ano-mes-dia
            //então eu comparo para ver qual tem 60 anos ou mais fazendo a conta
            // data - nascimento
            //sendo que data é 20221115, seguindo as mesma lógica de ano-mes-dia concatenaddo
            if((data - candidatos[j].nascimento) > 600000 || (data - candidatos[j-1].nascimento) > 600000)
            {
              if(candidatos[j].nascimento < candidatos[j-1].nascimento)
              {
                alunoAux = candidatos[j];
                candidatos[j] = candidatos[j-1];
                candidatos[j-1] = alunoAux;
                vez = 1;
              }
            }
            else if(candidatos[j].RED_notaAtual > candidatos[j-1].RED_notaAtual)
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
            else if (candidatos[j].ep_LIN > candidatos[j-1].ep_LIN )
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
            else if (candidatos[j].ep_MAT > candidatos[j-1].ep_MAT )
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
            else if (candidatos[j].ep_HUM > candidatos[j-1].ep_HUM )
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
            else if (candidatos[j].ep_NAT > candidatos[j-1].ep_NAT )
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
          }
          //essa aqui ordena normal
          else if(candidatos[j].nota_final > candidatos[j-1].nota_final)
          {
            alunoAux = candidatos[j];
            candidatos[j] = candidatos[j-1];
            candidatos[j-1] = alunoAux;
            vez = 1;
          }
        }
      }
      while (vez !=0 );

      posicao = 1;

      for(int j=0; j<indiceCandidatos; j++)
      {
          candidatos[j].classificacao = posicao;
          posicao++;
          if(candidatos[j].classificacao <= quantidadeVaga)
          {
              candidatos[j].aprovado = true;
          } else 
          {
              candidatos[j].aprovado = false;
          }
          fprintf(arq,"%d  %.2f  %.2f  %.2f  %.2f  %.2f   %s     %.2f        %d\n",
          candidatos[j].codigoAluno, candidatos[j].ep_LIN, candidatos[j].ep_MAT, candidatos[j].ep_NAT,
          candidatos[j].ep_HUM, candidatos[j].RED_notaAtual, candidatos[j].tipoVaga, candidatos[j].nota_final, candidatos[j].classificacao);
      }

      free(candidatos);

      Aluno *candidatos;
      indiceCandidatos = 0;
      candidatos = (Aluno *) malloc(1*sizeof(Aluno));

      for(int j=0; j<qntTotalInscritos; j++)
      {
        if(alunos[j].codigoCurso == cursos[i].codigoCurso && (strcmp(alunos[j].tipoVaga, vaga) == 0) && alunos[j].presente == false)
        {
          candidatos = (Aluno *) realloc(candidatos,(indiceCandidatos+1)*sizeof(Aluno));
          candidatos[indiceCandidatos++] = alunos[j];
        }
      }
      
      for(int j=0; j<indiceCandidatos; j++)
      {
        candidatos[j].classificacao = posicao;
        posicao++;
        if(candidatos[j].classificacao <= quantidadeVaga)
        {
          candidatos[j].aprovado = true;
        } 
        else 
        {
          candidatos[j].aprovado = false;
        }
        // fprintf(arq,"%d  %.2f  %.2f  %.2f  %.2f  %.2f   %s     %.2f        %d\n",
        // candidatos[j].codigoAluno, candidatos[j].ep_LIN, candidatos[j].ep_MAT, candidatos[j].ep_NAT,
        // candidatos[j].ep_HUM, candidatos[j].RED_notaAtual, candidatos[j].tipoVaga, candidatos[j].nota_final, candidatos[j].classificacao);
      }
      free(candidatos);
    }
  }
  fclose(arq);
  printf("Arquivo_candidato.txt gerado com sucesso!\n");
};



void geraArquivoReprovados(Aluno *&alunos, int qntTotalInscritos, tipoCurso *cursos, int nCursos)
{
FILE *arq;
arq = fopen("Reprovados.txt", "w");

fprintf(arq,".+*******+.NAO APROVADOS.+*******+.\n");  

Aluno *candidatos;
Reprovados *reprovados;
Reprovados reprovadoAux;
int indiceReprovados = 0;
candidatos = (Aluno *) malloc(1*sizeof(Aluno));

char vaga[4];
int vez = 0, posicao, quantidadeVaga;
Aluno alunoAux;
int indiceCandidatos = 0, data = 20221115;


  for(int i=0; i<nCursos; i++)
  {
    fprintf(arq,"\n%d %s\n", cursos[i].codigoCurso, cursos[i].nomeCurso);
    reprovados = (Reprovados *) malloc(1*sizeof(Reprovados));
    
    
    for(int vagas = 0; vagas<11; vagas++)
    {
      switch (vagas)
      {
        case 0: strcpy(vaga, "AC"); quantidadeVaga = cursos[i].AC; break;
        case 1: strcpy(vaga, "L1"); quantidadeVaga = cursos[i].L1; break;
        case 2:strcpy(vaga, "L3"); quantidadeVaga = cursos[i].L3;break;
        case 3:strcpy(vaga, "L4"); quantidadeVaga = cursos[i].L4;break;
        case 4:strcpy(vaga, "L5"); quantidadeVaga = cursos[i].L5;break;
        case 5:strcpy(vaga, "L7"); quantidadeVaga = cursos[i].L7;break;
        case 6:strcpy(vaga, "L8"); quantidadeVaga = cursos[i].L8;break;
        case 7:strcpy(vaga, "L9"); quantidadeVaga = cursos[i].L9;break;
        case 8:strcpy(vaga, "L11"); quantidadeVaga = cursos[i].L11;break;
        case 9:strcpy(vaga, "L13"); quantidadeVaga = cursos[i].L13;break;
        case 10:strcpy(vaga, "L15"); quantidadeVaga = cursos[i].L15;break;
        default: break;
      }

        //E lá vamos nós...
        indiceCandidatos = 0;

        //Então, candidatos é um vetor temporário que eu uso para ordenar quem tem uma cota espefíca de um curso esécífico
        //E para isso eu uso a bela alocação dinâmica.
        //Esse malloc inicial serve para não dar erro no futuro realloc.
        candidatos = (Aluno *) malloc(1*sizeof(Aluno));
        


        for(int j=0; j<qntTotalInscritos; j++)
        {
          if(alunos[j].codigoCurso == cursos[i].codigoCurso && (strcmp(alunos[j].tipoVaga, vaga) == 0) && alunos[j].presente)
          {
            candidatos = (Aluno *) realloc(candidatos,(indiceCandidatos+1)*sizeof(Aluno));
            candidatos[indiceCandidatos] = alunos[j];
            indiceCandidatos++;
          }
        }

        //E então eu ordeno esse vetor temporário com o belo, singelo e famoso bubble sort
        do
        {
          vez = 0;
          for(int j=1; j<indiceCandidatos; j++)
          {
              //Essa parte aqui é pra caso empate
          if(candidatos[j].nota_final == candidatos[j-1].nota_final && candidatos[j].nota_final != 0)
          {
            //Eles tem além do dia mes e ano, uma variável nascimento que ta concatenada no formato ano-mes-dia
            //então eu comparo para ver qual tem 60 anos ou mais fazendo a conta
            // data - nascimento
            //sendo que data é 20221115, seguindo as mesma lógica de ano-mes-dia concatenaddo
            if((data - candidatos[j].nascimento) > 600000 || (data - candidatos[j-1].nascimento) > 600000)
            {
              if(candidatos[j].nascimento < candidatos[j-1].nascimento)
              {
                alunoAux = candidatos[j];
                candidatos[j] = candidatos[j-1];
                candidatos[j-1] = alunoAux;
                vez = 1;
              }
            }
            else if(candidatos[j].RED_notaAtual > candidatos[j-1].RED_notaAtual)
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
            else if (candidatos[j].ep_LIN > candidatos[j-1].ep_LIN )
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
            else if (candidatos[j].ep_MAT > candidatos[j-1].ep_MAT )
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
            else if (candidatos[j].ep_HUM > candidatos[j-1].ep_HUM )
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
            else if (candidatos[j].ep_NAT > candidatos[j-1].ep_NAT )
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
          }

          //essa aqui ordena normal
          else if(candidatos[j].nota_final > candidatos[j-1].nota_final)
            {
              alunoAux = candidatos[j];
              candidatos[j] = candidatos[j-1];
              candidatos[j-1] = alunoAux;
              vez = 1;
            }
          }
        } while (vez !=0 );

        //Depois disso, eu percorro novamente o meu vetor temporário e faço a classificação dos participantes já ordenados pela nota final
        //E coloco no arquivo dos candidatos os que não foram aprovados
        posicao = 1;
        for(int j=0; j<indiceCandidatos; j++)
        {
          candidatos[j].classificacao = posicao;
          posicao++;
          if(candidatos[j].classificacao <= quantidadeVaga)
          {
              candidatos[j].aprovado = true;
          } else {
              candidatos[j].aprovado = false;
              //fprintf(arq,"%d %s\n", candidatos[j].codigoAluno, candidatos[j].nome);
              reprovados = (Reprovados *) realloc(reprovados, (indiceReprovados+1)*sizeof(Reprovados));
              reprovados[indiceReprovados].codigoAluno = candidatos[j].codigoAluno;
              reprovados[indiceReprovados].codigoCurso = candidatos[j].codigoCurso;
              reprovados[indiceReprovados].aprovado = false;
              strcpy(reprovados[indiceReprovados].nome, candidatos[j].nome);
              indiceReprovados++;
          }
        }

        //então eu libero o ponteiro do meu vetor temporário...
        free(candidatos);

        //e repito o processo... Porém, agora apenas para os candidatos que NÃO ESTAVAM PRESENTES
        Aluno *candidatos;
        indiceCandidatos = 0;
        candidatos = (Aluno *) malloc(1*sizeof(Aluno));

        for(int j=0; j<qntTotalInscritos; j++)
        {
            if(alunos[j].codigoCurso == cursos[i].codigoCurso && (strcmp(alunos[j].tipoVaga, vaga) == 0) && alunos[j].presente == false)
            {
                candidatos = (Aluno *) realloc(candidatos,(indiceCandidatos+1)*sizeof(Aluno));
                candidatos[indiceCandidatos++] = alunos[j];
            }
        }

        for(int j=0; j<indiceCandidatos; j++)
        {
            candidatos[j].classificacao = posicao;
            posicao++;
            candidatos[j].aprovado = false;
            //fprintf(arq,"%d %s\n", candidatos[j].codigoAluno, candidatos[j].nome);
            reprovados = (Reprovados *) realloc(reprovados, (indiceReprovados+1)*sizeof(Reprovados));
            reprovados[indiceReprovados].codigoAluno = candidatos[j].codigoAluno;
            reprovados[indiceReprovados].codigoCurso = candidatos[j].codigoCurso;
            reprovados[indiceReprovados].aprovado = false;
            strcpy(reprovados[indiceReprovados].nome, candidatos[j].nome);
            indiceReprovados++;

        }
        free(candidatos);
        
    }

    do
    {
      vez = 0;
      for(int i=1; i<indiceReprovados; i++)
      {
        if(strcmp(reprovados[i].nome, reprovados[i-1].nome)<0)
        {
          reprovadoAux = reprovados[i];
          reprovados[i] = reprovados[i-1];
          reprovados[i-1] = reprovadoAux;
          vez = 1;
        }
      }
    }while(vez!=0);

    for(int j=0; j<indiceReprovados; j++)
    {
      //printf("%d %s\n", reprovados[j].codigoAluno, reprovados[j].nome);
      fprintf(arq,"%d %s\n", reprovados[j].codigoAluno, reprovados[j].nome);
    }
    
    free(reprovados);
    
    indiceReprovados = 0;
  }
    //printf("Chegou aqui,rep: %d\n", indiceReprovados);
    // for(int j=0; j<qntTotalInscritos; j++)
    // {
    //   printf("%d\n", alunos[j].aprovado);
    // }


    fclose(arq);
    
    printf("Reprovados.txt gerado com sucesso!\n");
  };
