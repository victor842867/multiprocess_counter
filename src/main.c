
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

int verifica_primo(int x);

int main() {

  pid_t processo1;
  pid_t processo2;
  pid_t processo3;
  pid_t processo4;

  int i; /*contador*/
  int primo;
  int entrada_atual;
  char descarte;

  /*Definindo flags de protecao e visibilidade de memoria*/
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  int *quantidade_de_primos;

  quantidade_de_primos = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);

  *quantidade_de_primos = 0;


  for(i=0;descarte != '\n';i++){

    scanf("%d",&entrada_atual); /*Lendo o proximo numero que será verificado*/
    scanf("%c",&descarte);      /*Verificando se a entrada lida é final de linha*/

      processo1 = fork();
      if(processo1 == 0 ){
        primo = verifica_primo(entrada_atual);
        if(primo == 1){
          (*quantidade_de_primos)++;
        }
        exit(0);
      }else{ /*continua processo da main apos chamada do processo 1*/

        if(descarte != '\n'){
          scanf("%d",&entrada_atual); /*Lendo o proximo numero que será verificado*/
          scanf("%c",&descarte);      /*Verificando se a entrada lida é final de linha*/

          processo2 = fork();
          if(processo2 == 0 ){
            primo = verifica_primo(entrada_atual);
            if(primo == 1){
              (*quantidade_de_primos)++;
            }
            exit(0);
          }else{ /*continua processo da main apos chamada do processo 2*/

            if(descarte != '\n'){
            scanf("%d",&entrada_atual); /*Lendo o proximo numero que será verificado*/
            scanf("%c",&descarte);      /*Verificando se a entrada lida é final de linha*/

            processo3 = fork();
            if(processo3 == 0){
              primo = verifica_primo(entrada_atual);
                if(primo == 1){
                  (*quantidade_de_primos)++;
                }
                exit(0);
              }else{ /*continua processo da main apos chamada do processo 3*/
                if(descarte != '\n'){

                scanf("%d",&entrada_atual); /*Lendo o proximo numero que será verificado*/
                scanf("%c",&descarte);      /*Verificando se a entrada lida é final de linha*/

                  processo4 = fork();
                  if(processo4 == 0){
                    primo = verifica_primo(entrada_atual);
                    if(primo == 1){
                      (*quantidade_de_primos)++;
                    }
                    exit(0);
                  }else{
                    if(descarte != '\n'){
                  }
                }
              }
            }
          }
        }
      }
    }
    waitpid(processo1,NULL,0);
    waitpid(processo2,NULL,0);
    waitpid(processo3,NULL,0);
    waitpid(processo4,NULL,0);
  }

waitpid(processo1,NULL,0);
waitpid(processo2,NULL,0);
waitpid(processo3,NULL,0);
waitpid(processo4,NULL,0);

  /*PRINTAR A VARIAVEL COMPARTILHADA QUE POSSUI A QUANTIDADE DE NUMEROS PRIMOS*/
  printf("%d\n", *quantidade_de_primos);
  return 0;
}


int verifica_primo(int x){
  int i; /*contador*/
  int resto;
  int resto_zero = 0;

  for(i=1;i<=x;i++){
    resto = x%i;
    if(resto == 0){
      resto_zero++;
    }
  }

  if(resto_zero == 2){
    return 1;
  }

  return 0;
}
