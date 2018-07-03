//
//  main.c
//  Dominó
//
//  Created by Fellipe Thufik Costa Gomes Hoashi on 20/03/14.
//  Copyright (c) 2014 Fellipe Thufik Costa Gomes Hoashi. All rights reserved.
//

#include<stdio.h>
#include "string.h"

typedef struct _TAresta
{
    int v;
    int pos_vet;
    struct _TAresta *prox;

}TAresta;


void Adicionar(TAresta *vetor[7],int x,int y);
void Verificar_Jogo(TAresta *vetor[7]);
int verificar_vetor(TAresta *v[7],int v_aux[7]);
int verificar_existencia(TAresta *v[7],int x,int y);
void zerar_vetor(TAresta *v[7]);

int verificar_vetor(TAresta *v[7],int v_aux[7])
{
    int aux[7];
    int i;
    int verdadeiro = 0;
    memset(aux, 0, sizeof(aux));

    for (i=0; i<7; i++) {
        if (v[i] != NULL) {
            aux[i] = 1;
        }
        else
        {
            aux[i] = 0;
        }
    }

    for (i=0; i<7; i++) {
        if (aux[i] == v_aux[i]) {
            verdadeiro = 1;
        }
        else
        {
            verdadeiro = 0;
            break;
        }
    }

    if (verdadeiro == 1) {
        return verdadeiro;
    }
    else
        return 0;


}

int verificar_existencia(TAresta *v[7],int x,int y)
{
    TAresta *aux = v[x];
    while (aux != NULL) {
        if (aux->v == y) {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}






void Verificar_Jogo(TAresta *vetor[7])
{

    int vet_aux[7];
    int cont=0,menor=-1,maior=0,i;
    TAresta *salvador = (TAresta *) malloc(sizeof(TAresta));
    TAresta *aux = (TAresta *) malloc(sizeof(TAresta));


    for (i=0; i<7; i++) {
        if (menor == -1 && vetor[i] != NULL) {
            menor = i;
        }
        if (vetor[i] != NULL) {
            maior = i;
        }
        vet_aux[i] = 0;
    }


    aux = vetor[vetor[menor]->v];
    vet_aux[menor] = 1;
    vet_aux[aux->pos_vet] = 1;


    while(aux != NULL)
    {
        if(vet_aux[aux->v] == 1)
        {
            while(vet_aux[aux->v] == 1)
            {

                salvador = aux;
                aux = aux->prox;
                if (aux == NULL) {
                    break;
                }


            }

            if((aux == NULL) && verificar_vetor(vetor,vet_aux) == 1)
            {
                int verdadeiro=0,i=0;
                for (i=0; i<7; i++) {
                    if (vet_aux[i] == 1 && i!= menor && i != maior) {
                        verdadeiro = 1;
                    }
                }
                if (verdadeiro == 1) {
                    printf("Jogo existe\n");
                }
                else
                    printf("Jogo nao existe\n");

            }
            else if((aux == NULL) && (verificar_vetor(vetor,vet_aux) == 0))
            {
                aux = vetor[salvador->v];
                TAresta *aux2 = aux;
                while (aux2 != NULL) {
                    if (vet_aux[aux2->v] == 0) {
                        break;
                    }
                    else
                        aux2 = aux2->prox;
                }
                if (aux2 ==NULL) {
                    printf("O Jogo nao existe\n");

                    break;
                }

            }

            else if(vet_aux[aux->v] == 0)
            {
                vet_aux[aux->v] = 1;
                salvador = aux;
                aux = vetor[aux->v];
                if ((aux->prox == NULL) && (aux->v == salvador->pos_vet)) {
                    TAresta *auxiliar = vetor[salvador->pos_vet];
                    TAresta *auxiliar2 = vetor[auxiliar->v];
                    int encontrou = 0;
                    while (auxiliar != NULL) {
                        while (auxiliar2 != NULL) {
                            if (vet_aux[auxiliar2->v] == 0) {
                                aux = vetor[auxiliar2->v];
                                vet_aux[auxiliar2->v] = 1;
                                encontrou = 1;
                                break;
                            }
                            else
                            {
                                auxiliar2 = auxiliar2->prox;
                            }

                        }
                        if (encontrou == 0) {
                            auxiliar = auxiliar->prox;
                            if (auxiliar != NULL) {
                                auxiliar2 = vetor[auxiliar->v];
                            }

                        }
                        else
                        {
                            break;
                        }

                    }

                    if (encontrou ==0) {
                        if (verificar_vetor(vetor, vet_aux) == 0 )
                        {
                            printf("Jogo nao existe\n");
                            aux = NULL;
                        }
                        else
                        {
                            printf("Jogo existe\n");
                            aux = NULL;
                        }



                    }

                }

            }

        }
        else
        {
            vet_aux[aux->v] = 1;
            aux = vetor[aux->v];
        }


    }

}

void Adicionar(TAresta *vetor[7],int x,int y)
{
    TAresta *No = (TAresta *) malloc(sizeof(TAresta));
    TAresta *No2 = (TAresta *) malloc(sizeof(TAresta));

    if (verificar_existencia(vetor, x, y) != 1) {
        if(x == y)
        {

            if(vetor[x] == NULL)
            {

                No->v = x;
                No->pos_vet = x;
                No->prox = NULL;
                vetor[x] = No;
            }
            else
            {
                TAresta *No = (TAresta *) malloc(sizeof(TAresta *));
                TAresta *aux = vetor[x];
                while(aux->prox != NULL)
                {
                    aux = aux->prox;
                }
                aux->prox = No;
                No->v = y;
                No->pos_vet = y;
                No->prox = NULL;
            }

        }
        else
        {
            if(vetor[x] == NULL && vetor[y] == NULL)
            {

                No->v = y;
                No->pos_vet = x;
                No2->v = x;
                No2->pos_vet = y;
                No->prox = NULL;
                No2->prox = NULL;
                vetor[x] = No;
                vetor[y] = No2;


            }

            else if(vetor[x] != NULL && vetor[y] == NULL)
            {


                TAresta *aux = vetor[x];

                while(aux->prox != NULL)
                {
                    aux = aux->prox;
                }
                aux->prox = No;
                No->v = y;
                No->pos_vet = x;
                No->prox = NULL;
                No2->v = x;
                No2->pos_vet = y;
                No2->prox = NULL;


                vetor[y] = No2;

            }
            else if(vetor[x] == NULL && vetor[y] != NULL)
            {
                No = (TAresta *) malloc(sizeof(TAresta *));
                No2 =(TAresta *) malloc(sizeof(TAresta *));

                TAresta *aux = vetor[y];
                while(aux->prox != NULL)
                {
                    aux = aux->prox;
                }
                aux->prox = No;
                No->v = x;
                No->pos_vet = y;
                No->prox = NULL;
                vetor[x] = No2;
                No2->v = y;
                No2->pos_vet = x;
                No2->prox = NULL;


            }
            else
            {
                No = (TAresta *) malloc(sizeof(TAresta *));
                No2 =(TAresta *) malloc(sizeof(TAresta *));

                TAresta *aux  = vetor[x];
                TAresta *aux2 = vetor[y];
                while (aux->prox != NULL) {
                    aux = aux->prox;
                }
                while (aux2->prox != NULL) {
                    aux2 = aux2->prox;
                }

                aux->prox = No;
                No->v = y;
                No->pos_vet = x;
                No->prox = NULL;
                aux2->prox = No2;
                No2->v = x;
                No2->pos_vet = y;
                No2->prox = NULL;

            }

        }

    }

}

    void zerar_vetor(TAresta *v[7])
    {
        int i=0;
        for(i=0;i<7;i++)
        {
            v[i] = NULL;

        }

    }

int main()
{
    TAresta *vetor[7];
    int i,v=-1,x,y,cont=0;

    for(i=0;i<7;i++)
    {
        vetor[i] = (TAresta *) malloc(sizeof(TAresta *)) ;
        vetor[i] = NULL;
    }

    FILE *fp;
    fp = fopen("arquivo.txt","r");
    if( fp == NULL){
        printf("erro na abertura do arquivo.\n");
        return 1;
    }

     while(v != 0)
     {
        fscanf(fp,"%d",&v);
        if(v==0){
            //printf("teste");
            break;
        }

        else
        {
            while(cont < v)
            {
                fscanf(fp,"%d",&x);
                fscanf(fp,"%d",&y);
                Adicionar(vetor,x,y);
                cont++;
            }
        }
        Verificar_Jogo(vetor);

     }



    //printf("x= %d e y = %d",x,y);
    //printf("\n");
    //Adicionar(vetor,2 , 1);
    //Adicionar(vetor,2 , 1);
    //Adicionar(vetor,2 , 1);
   //Adicionar(vetor, 0, 2);
   // Adicionar(vetor, 2, 2);
   // Adicionar(vetor, 3, 3);
   // Adicionar(vetor, 3, 4);
   // Adicionar(vetor,4, 4);
   // Adicionar(vetor, 2, 5);
   // Adicionar(vetor, 5, 5);
    //printf("%d",vetor[2]->v);
    //printf("teste");
    //Verificar_Jogo(vetor);



    //   cont++;
    // }

    return 0;


}
