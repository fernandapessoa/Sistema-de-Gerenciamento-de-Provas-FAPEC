# Sistema-de-Gerenciamento-de-Provas-FAPEC

Esse sistema foi desenvolvido para o trabalho de Algoritmos e Programação II na Universidade Federal do Mato Grosso do Sul.
Realizado em 28/11/2022

## Índice

1. [O que é?](#o-que-é)
2. [Arquivos de entrada](#arquivos-de-entrada)
3. [Como compilar](#como-compilar)
4. [O programa](#o-programa)
  


## O que é?
O Trabalho consiste em fazer um programa de avaliação dos candidatos que participaram do Vestibular, gerando a classificação, aprovados e reprovados. É um progarama de terminal que trabalho com arquivos .txt. 
Foi desenvolvido em C/C++, utilizando ponteiros e alocações dinâmicas de memória.
  
## Arquivos de entrada  
**cursos_e_pesos**: Arquivo txt que mostra o código do curso, seguido pelo o nome e os pesos de cada área. No início do arquivo está um número N que representa a quantidade de cursos nesse arquivo.    

![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/17f8b600-3ab1-49fa-8db7-3de6de5d0c1e)   
  
![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/a78f2c3b-66d2-47ed-a508-f78d1011b871)    


**cursos_e_vagas**: Arquivo txt que contém o código do curso seguido para quantas vagas tem em cada cota. No início do arquivo está um número N que representa a quantidade de cursos nesse arquivo.  

![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/0f767e27-79cb-42da-b34b-237bb39d01ad)    
  
![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/fbeba7ef-e444-4ebc-a25d-998f0d470972)  


**dados**: Arquivo txt que contém o código do vestibulando, seu nome, data de nascimento e sua cota.  No início do arquivo está um número N que representa a quantidade de vestibulandos nesse arquivo.  

![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/a2ce3ced-2cbc-4aa4-8de5-730a7dcb0ba5)  
  

**acertos**: Arquivo txt que contém o código do aluno e a quantidade de acertos em cada área de conhecimento e sua nota em redação.  No início do arquivo está um número N que representa a quantidade de vestibulandos nesse arquivo.   
  
![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/6f20536f-a6d5-41d5-9978-3ab2df6e4c4c)   

![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/ac60dff6-7e10-4937-ab59-793bd5d77a3e)  



**alteracaoNotaRedacao**: Arquivo txt que contém o código do vestibulando seguido de sua nota da redação antiga e nova (caso tenha sido corrigida novamente).  
  
![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/ef0e7d9c-f0d8-4eac-be61-6bf0cde6558b)  

## Como compilar
Dentro do seu diretório, o comando:  

```gcc *.cpp -o prg.exe -Wall -lm```  

gerará um executável chamado prg.exe. Que para executar:  

```./pgr```  

obs: É necessário ter o compilador gcc já em seu computador.  

   
## O programa  
Será gerado um menu no console:  
![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/be96470c-bd16-4be7-8d6d-59d71d09f36b)  

obs: Caso apareça caracteres estranhos, cole o seguinte comando no terminal para que reconheça os caracteres UFT8:   

```$OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding```


  
**0 - Carregar os arquivos de entrada:** Para iniciar o carregamento dos arquivos de entrada, é necessário digitar 0 e pressionar Enter no início do programa. Uma vez carregados, a opção 0 não aparecerá mais no menu.
Nesse momento:  
- Serão lidos os arquivos de entrada.
- Calculadas as médias, desvio padrão e EPs (escore padronizado da competência).
- Serão calculadas as Notas Finais.
- Os cursos serão ordenados.
![image](https://github.com/fernandapessoa/Sistema-de-Gerenciamento-de-Provas-FAPEC/assets/103967442/5e6903d2-0ad0-433d-a69f-830338b32e71)

**1 - Gerar arquivo de saída .txt:** Será gerado o Arquivo_candidato.txt, que mostra uma lista geral classificado por nota, levando em consideração as vagas para cada cota.  

**2 - Pesquisar candidatos .txt:** Ao ser informado a matrícula de um candidato, aparecerá as informações: Código, nome, data de nascimento e curso dele. Tecle 0 para voltar ao menu.  

**3 - Gerar arquivo candidatos não aprovados:** Gera um arquivo Reprovados.txt, separados por curso e em ordem alfabética.  

**4 - Alterar nota da redação de candidatos que entraram com recurso:** Lê o arquivo alteracaoNotaRedacao.txt, altera as notas de redações e recalcula as notas finais de todos os candidatos. Após isso, pode ser gerado novamente os aprovados ao clicar na opção 1 do menu.  

**5 - Encerra o programa**  
