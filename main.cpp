//Vamo criar aqueles arquivos pra guardar funçoes e bibliotecas

//pq o ev escolheu esse trabalho mds 🤡


#include <stdio.h>
#include <stdlib.h>


struct tipoCurso
{
	int codigoCurso;
	char nomeCurso[50];
	int red, mat, lin, hum, nat;
};

//Struct que contém as vagas de cada cota
struct Vagas
{
  int codigoCurso,
  AC, L1, L3, L4, L5, L7, L8, L9, L11, L13, L15;
};

int main()
{
	//Abertura cursos e pesos----------------------------------------------------------
	FILE *arq;
	arq = fopen("cursos_e_pesos.txt", "r");

	if(!arq) //Testar se a abertura funcionou
		printf("Erro na abertura do arquivo.\n\n");
	else printf("Abriu!\n\n");
	


	//Structs dos cursos e pesos-------------------------------------------------------
  
	FILE *ptCursoPeso = arq;
	tipoCurso *pesos;
	int nCursos;

  //Leitura da quantidade de pesos
	fscanf(ptCursoPeso, "%d", &nCursos);
  
	pesos = (tipoCurso*) calloc(nCursos, sizeof(tipoCurso));

	if(!pesos)
		printf("Erro na leitura dos pesos.\n\n");
	else
	{
    //Armazenando informacoes nos structs
		for(int i = 0; i < nCursos; i++) 
		{
			fscanf(ptCursoPeso, "%d", &pesos[i].codigoCurso);
			fscanf(ptCursoPeso, "%[^0-9]", pesos[i].nomeCurso);
			fscanf(ptCursoPeso, "%d %d %d %d %d", &pesos[i].red, &pesos[i].mat, &pesos[i].lin, &pesos[i].hum, &pesos[i].nat);	
	}

		for(int i = 0; i < nCursos; i++)//Print pra testar se os structs estao certos
			printf("%d %s %d %d %d %d %d\n", pesos[i].codigoCurso, pesos[i].nomeCurso, pesos[i].red, pesos[i].mat, pesos[i].lin, pesos[i].hum, pesos[i].mat);
	}




  
  //Vou tentar ler as vagas de cada cota -------------------------------------------------

  FILE *arqVagas;
  arqVagas = fopen("cursos_e_vagas.txt", "r");
  int nVagas;
  int indice = 0;

  fscanf(arqVagas, "%d", &nVagas);

  // Declaro um vetor de struct Vagas do tamanho nVagas;
  Vagas vagas[nVagas];

  while ((fscanf(arqVagas, "%d %d %d %d %d %d %d %d %d %d %d %d ", &vagas[indice].codigoCurso, &vagas[indice].AC, &vagas[indice].L1, &vagas[indice].L3, &vagas[indice].L4, &vagas[indice].L5, &vagas[indice].L7, &vagas[indice].L8, &vagas[indice].L9, &vagas[indice].L11, &vagas[indice].L13, &vagas[indice].L15) != EOF))
  {
    indice++;
  }// mds nao sei se isso da certo (aparentemente nao)
  //atualizações: deu certo e eu nao sei como

  // só para testar se ta lende certinho
  printf("\n\nLeitura das structs Vagas:\n\n");
  for (int i = 0; i < nVagas; i++) 
  {
    printf("%d %d %d %d %d %d %d %d %d %d %d %d\n", vagas[i].codigoCurso,
           vagas[i].AC, vagas[i].L1, vagas[i].L3, vagas[i].L4, vagas[i].L5,
           vagas[i].L7, vagas[i].L8, vagas[i].L9, vagas[i].L11, vagas[i].L13,
           vagas[i].L15);
  }
  fclose(arqVagas);
  
//-------------------------------------------------------------------------------------------------
//agr tentar ler 




  
	return 0;
}