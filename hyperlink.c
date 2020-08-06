#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#ifdef WIN32
	#define limpatela system("cls")
	#include <windows.h>
	#define sleep(x) Sleep(x*1000)
	#else
		#define limpatela system("clear")
		#endif
typedef struct No{
	int num;
	struct No* ant;
	struct No* prox;
}no;

typedef struct{
	no *atual;
}lista;

typedef struct Nof{
    int num;
    struct Nof* prox;
}nof;

typedef struct Fila{
    nof *inicio;
    nof *fim;
}fila;

void inicio(lista *l,fila *f);
void menu();
void abrirpagina(lista *l);
void avancar(lista *l);
void voltar(lista *l);
void desalocar(lista *l);
void historico(fila *f,int x);
void mostrarhistorico(fila *f);

int main(){
	setlocale(LC_ALL, "Portuguese");
	lista *l;
    l = (lista *) malloc(sizeof(lista));
      fila *f;
    f = (fila *) malloc(sizeof(fila));
    inicio(l,f);
    int opt;

     do{
        menu();
        printf("Digite uma opção:\n");
        scanf("%d",&opt);
        switch(opt){
            case 1:
                abrirpagina(l);
                historico(f,l->atual->num);
                break;
            case 2:
                avancar(l);
                if(l->atual!=NULL)
              	 historico(f,l->atual->num);
                break;
            case 3:
                voltar(l);
                if(l->atual!=NULL)
                historico(f,l->atual->num);
                break;
			case 4:
				mostrarhistorico(f);
				break;
            case 5:
                break;
            default:
                printf("Opcao Inválida!\n");
                break;
        }
        if(opt!=5){
        limpatela;
        if(l->atual!=NULL)
     	printf("Página atual: %d\n",l->atual->num);
     }
    }while(opt!=5);
    return 0;
}
void inicio(lista *l,fila *f){
    l->atual = NULL;
    f->inicio = NULL;
    f->fim = NULL;
}

void menu(){
    printf("                     Menu \n");
    printf("1-Abrir página;\n2-Avançar;\n3-Voltar;\n4-Mostrar histórico;\n5-Fechar programa;\n");
}

void abrirpagina(lista *l){
   no *aux = (no*)malloc(sizeof(struct No));
    printf("Digite o número da página:\n");
    scanf("%d",&aux->num);

    aux->prox = NULL;
    if(l->atual == NULL){
        l->atual = aux;
        l->atual->ant = NULL;
    }
    else {
    	if(l->atual->prox!=NULL)
    	   desalocar(l);
    	 	aux->ant = l->atual;
    	aux->ant->prox = aux;
        l->atual = aux;
    }
}

void avancar(lista *l){
    if(l->atual==NULL||l->atual->prox==NULL){
        printf("Não há páginas a frente\n");
        sleep(1);
        return ;
    }
   l->atual = l->atual->prox;
}

void voltar(lista *l){
    if(l->atual==NULL||l->atual->ant==NULL){
        printf("Não há páginas atrás\n");
        sleep(1);
        return ;
    }
   l->atual = l->atual->ant;
}

void desalocar(lista *l){
	no *aux = (no*)malloc(sizeof(struct No));
	for(aux=l->atual->prox; aux!=NULL; aux=l->atual->prox){
		l->atual->prox = aux->prox;
		free(aux);
	}	
}

void historico(fila *f,int x){
	static int tam = 0;
		
nof *aux = (nof*)malloc(sizeof(struct Nof));
			aux->num = x;
		aux->prox = NULL;
	if(f->inicio==NULL){
		f->inicio = aux;
        f->fim = aux;
        tam++;
        return;
	}
	else if(f->inicio->num==x){
			f->fim->prox = f->inicio;
			f->fim = f->inicio;
			f->inicio = f->inicio->prox;
			f->fim->prox = NULL;
			return;
		}
	else{
	for(aux=f->inicio ; aux->prox!=NULL ;aux = aux->prox){
		if(aux->prox->num == x){
			f->fim->prox = aux->prox;
			f->fim = aux->prox;
			aux->prox = aux->prox->prox;
			f->fim->prox = NULL;
			return;
		}
	}	
	}
	nof *aux1 = (nof*)malloc(sizeof(struct Nof));
	aux1->num = x;
		aux1->prox = NULL;
		f->fim->prox = aux1;
		f->fim = aux1;
	if(tam<5)
		tam++;
	else{
		nof *aux1 = f->inicio;
		f->inicio = f->inicio->prox;
		free(aux1);
	}
}
	
void mostrarhistorico(fila *f){
	nof *aux = (nof*)malloc(sizeof(struct Nof));
	for(aux = f->inicio ; aux!=NULL ; aux=aux->prox)
		printf("%d\n",aux->num);
	sleep(2);
}
