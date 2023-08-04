
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"


int main(){
  tipoCurso *cursos; 
  Aluno *alunos;
  int quantidadetTotalInscritos, nCursos;
  int vez = 0, op;
  float media_lin, media_mat, media_nat, media_hum;
  float desvio_lin, desvio_mat, desvio_nat, desvio_hum;
  

  while (op != 5)
    {
      printf("\n\n.+*****+.MENU.+*****+.\n\n");
	  if (vez == 0) printf("0 - Carregar os arquivos de entrada\n");
      printf("1 - Gerar arquivo de saída .txt\n");
      printf("2 - Pesquisar candidatos .txt\n");
      printf("3 - Gerar arquivo dos candidados não aprovados\n");
      printf("4 - Alterar nota de redação dos candidatos que entraram com recurso\n");
      printf("5 - Encerrar programa\n");

      scanf("%d", &op);

	  if(op == 0 and vez == 0)
	  {
      vez++;
      nCursos = le_Cursos_e_Pesos(cursos);
      le_Cursos_e_Vagas(cursos, nCursos);
      quantidadetTotalInscritos = le_Dados(alunos);
      le_Acertos(alunos, quantidadetTotalInscritos);
      calculaDesvioPadrao (alunos, quantidadetTotalInscritos,  media_lin, media_mat, media_nat, media_hum, desvio_lin, desvio_mat, desvio_nat, desvio_hum);
      calculaEP (alunos, quantidadetTotalInscritos, cursos, nCursos, media_lin, media_mat, media_nat, media_hum, desvio_lin, desvio_mat, desvio_nat, desvio_hum);
      calculaNotaFinal(alunos, quantidadetTotalInscritos, cursos, nCursos);
      ordenaCursos (cursos, nCursos);
	  }

      if(op != 0 && vez == 0 && op!=5)
      {
        printf("Não foi possível realizar essa opção. Você não carregou os arquivos.\n");
      }

      else if(op == 1)
      {
        printf("Aguarde um momento, gerando arquivo Arquivo_candidato.txt...\n\n");
        geraArquivoCandidato(alunos, quantidadetTotalInscritos ,cursos, nCursos);
      }

      else if(op == 2)
      {
        imprimeCandidato(alunos, quantidadetTotalInscritos, cursos, nCursos);
      }

      else if(op == 3)
      {
        printf("Aguarde um momento, gerando arquivo Reprovados.txt...\n\n");
        geraArquivoReprovados(alunos, quantidadetTotalInscritos, cursos,nCursos);
      }

      else if(op == 4)
      {
        alterarNotaRed(alunos, quantidadetTotalInscritos);
        calculaNotaFinal(alunos, quantidadetTotalInscritos, cursos, nCursos);
      }

    }

    free(cursos);
    free(alunos);
    return 0;

    //É isso espero que tenha gostado. bjs

}