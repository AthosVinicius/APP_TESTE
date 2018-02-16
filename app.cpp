#include <stdio.h>
#include <stdlib.h>

// Estrutura User
typedef struct User{
    char name[50];
    int registration;
    float T1;
    float T2;
    float T3;
    float media;
    User *proximo;
    User *anterior;
}User;

// Estrutura da lista
typedef struct Tipo_Lista{
    User *inicio = NULL;
    User *fim = NULL;
}Tipo_Lista;

// Função que inicia a lista
void iniciar_lista(Tipo_Lista *Lista){
    Lista->inicio = NULL;
    Lista->fim = NULL;
}

// Calcula a média ponderada
float calcular_media_ponderada(float T1, float T2, float T3){
    int peso1 = 1, peso2 = 2, peso3 = 3;
    return (T1*peso1 + T2*peso2 + T3*peso3)/(peso1+peso2+peso3);
}

// Cadastra um novo usuário
void inserir(Tipo_Lista *Lista){

    User *novo_usuario = new User;

    printf("\n [ CADASTRO DE USUARIO ] \n\n");

    printf("Digite o nome do usuario: \n");
    fflush(stdin);
    fgets(novo_usuario->name, 50, stdin);

    printf("Digite o numero de registro do usuario: \n");
    scanf("%d", &novo_usuario->registration);

    printf("Digite a nota do primeiro teste: \n");
    scanf("%f", &novo_usuario->T1);

    printf("Digite a nota do segundo teste: \n");
    scanf("%f", &novo_usuario->T2);

    printf("Digite a nota do terceiro teste: \n");
    scanf("%f", &novo_usuario->T3);

    novo_usuario->media = calcular_media_ponderada(novo_usuario->T1, novo_usuario->T2, novo_usuario->T3);

    novo_usuario->proximo = NULL;
    novo_usuario->anterior = NULL;

    //Se a lista estiver vazia ela aposta pro unico usuário que existe.
    if(Lista->inicio == NULL){
        Lista->inicio = novo_usuario;
        Lista->fim = novo_usuario;
    }else{
        Lista->fim->proximo = novo_usuario;
        novo_usuario->anterior = Lista->fim;
        Lista->fim = novo_usuario;
    }
}

//Exclui um usuário da lista, liberando o espaço na memória
int excluir_usuario(Tipo_Lista *Lista){
    User *usuario_atual, *proximo_usuario, *usuario_anterior;
    int registration;

    printf("Digite o numero de registro do usuario a ser excluido: \n");
    scanf("%d", &registration);

    if(Lista->inicio == NULL){
        printf("\n\n=====================================\n");
        printf("A lista esta vazia!");
        printf("\n=====================================\n");
        return 0;
    }else{
        usuario_atual = Lista->inicio;
        while(usuario_atual != NULL){
            proximo_usuario = usuario_atual->proximo;
            usuario_anterior = usuario_atual->anterior;
            if(usuario_atual->registration == registration){
                if(usuario_anterior != NULL){
                    if(proximo_usuario != NULL){
                        usuario_anterior->proximo = proximo_usuario;
                        proximo_usuario->anterior = usuario_anterior;
                        free(usuario_atual);
                    }else{
                        usuario_anterior->proximo = NULL;
                        Lista->fim = usuario_anterior;
                        free(usuario_atual);
                    }
                }else{
                    if(proximo_usuario != NULL){
                        proximo_usuario->anterior = NULL;
                        Lista->inicio = proximo_usuario;
                        free(usuario_atual);
                    }else{
                        free(usuario_atual);
                    }
                }

                printf("\n\n=====================================\n");
                printf("Usuario removido!");
                printf("\n=====================================\n");
                return 0;
            }else{
                usuario_atual = usuario_atual->proximo;
            }
        }
        printf("\n\n=====================================\n");
        printf("O usuario nao foi encontrado.");
        printf("\n=====================================\n");
    }
}

//Busca usuário pelo número de registro
int buscar_usuario(Tipo_Lista *Lista){
    User *usuario_atual, *proximo_usuario, *usuario_anterior;
    int registration;

    printf("Digite o numero de registro do usuario a ser consultar: \n");
    scanf("%d", &registration);

    if(Lista->inicio == NULL){

        printf("\n\n=====================================\n");
        printf("A lista esta vazia!");
        printf("\n=====================================\n");
        return 0;

    }else{
        usuario_atual = Lista->inicio;
        while(usuario_atual != NULL){
            if(usuario_atual->registration == registration){

                printf("\n\n========== DADOS DO USUARIO ==========\n");
                printf("Nome: %s\n", usuario_atual->name);
                printf("Numero de Registro: %d\n", usuario_atual->registration);
                printf("Nota Teste 1: %f\n", usuario_atual->T1);
                printf("Nota Teste 2: %f\n", usuario_atual->T2);
                printf("Nota Teste 3: %f\n", usuario_atual->T3);
                printf("Media: %f\n", usuario_atual->media);
                printf("\n=====================================\n\n");

                return 0;
            }else{
                usuario_atual = usuario_atual->proximo;
            }
        }

        printf("\n\n=====================================\n");
        printf("O usuario nao foi encontrado.");
        printf("\n=====================================\n");
    }
}

//Busca usuário pelo número de registro
int alterar_usuario(Tipo_Lista *Lista){
    User *usuario_atual, *proximo_usuario, *usuario_anterior;
    int registration;
    int menu_escolhido;

    printf("Digite o numero de registro do usuario a ser alterado: \n");
    scanf("%d", &registration);

    if(Lista->inicio == NULL){

        printf("\n\n=====================================\n");
        printf("A lista esta vazia!");
        printf("\n=====================================\n");
        return 0;

    }else{
        usuario_atual = Lista->inicio;
        while(usuario_atual != NULL){
            if(usuario_atual->registration == registration){

                printf("\n\n========== ESCOLHA A INFORMACAO QUE DESEJA ALTERAR ==========\n");
                printf("1 -  NOME \n");
                printf("2 -  T1 \n");
                printf("3 -  T2 \n");
                printf("4 -  T3 \n");
                printf("0 -  VOLTAR \n");

                printf("\nDigite o numero do menu que deseja acessar: \n");
                scanf("%d",&menu_escolhido);

                switch((int)menu_escolhido)
                {
                  case 1:
                        printf("Digite o nome do usuario: \n");
                        fflush(stdin);
                        fgets(usuario_atual->name, 50, stdin);

                        printf("\n\n=====================================\n");
                        printf("Nome alterado.");
                        printf("\n=====================================\n\n");
                      break;
                  case 2:
                        printf("Digite a nota do primeiro teste: \n");
                        scanf("%f", &usuario_atual->T1);
                        usuario_atual->media = calcular_media_ponderada(usuario_atual->T1, usuario_atual->T2, usuario_atual->T3);

                        printf("\n\n=====================================\n");
                        printf("T1 alterado.");
                        printf("\n=====================================\n\n");
                      break;
                  case 3:
                        printf("Digite a nota do segundo teste: \n");
                        scanf("%f", &usuario_atual->T2);
                        usuario_atual->media = calcular_media_ponderada(usuario_atual->T1, usuario_atual->T2, usuario_atual->T3);

                        printf("\n\n=====================================\n");
                        printf("T2 alterado.");
                        printf("\n=====================================\n\n");
                      break;
                  case 4:
                        printf("Digite a nota do terceiro teste: \n");
                        scanf("%f", &usuario_atual->T3);
                        usuario_atual->media = calcular_media_ponderada(usuario_atual->T1, usuario_atual->T2, usuario_atual->T3);

                        printf("\n\n=====================================\n");
                        printf("T3 alterado.");
                        printf("\n=====================================\n\n");
                      break;
                  case 0:
                        return 0;
                      break;
                  default:
                        printf("opcao invalida \n");
                        break;
                }
            }else{
                usuario_atual = usuario_atual->proximo;
            }
        }

        printf("\n\n=====================================\n");
        printf("O usuario nao foi encontrado.");
        printf("\n=====================================\n");
    }
}

int main(void)
{

      int menu_escolhido;

      Tipo_Lista lista_encadeada;

      iniciar_lista(&lista_encadeada);

      do
          {
             printf("\n [ MENU PRINCIPAL ] \n\n");

              printf("1 -  BUSCAR \n");
              printf("2 -  CADASTRAR \n");
              printf("3 -  ALTERAR \n");
              printf("4 -  EXCLUIR \n");
              printf("0 -  FECHAR \n");

              printf("\n");

              printf("Digite o numero do menu que deseja acessar: \n");
              scanf("%d",&menu_escolhido);

              switch((int)menu_escolhido)
              {
                  case 1:
                        buscar_usuario(&lista_encadeada);
                      break;
                  case 2:
                        inserir(&lista_encadeada);
                      break;
                  case 3:
                        alterar_usuario(&lista_encadeada);;
                      break;
                  case 4:
                        excluir_usuario(&lista_encadeada);
                      break;
                  case 0:
                    printf("\n\n=====================================\n");
                      printf("Fechando...\n");
                    printf("\n=====================================\n");
                    break;

                  default:
                    printf("\n\n=====================================\n");
                      printf("Numero de menu invalido, tente novamente...\n");
                    printf("\n=====================================\n");
              }
          } while(menu_escolhido);


    return 0;
}
