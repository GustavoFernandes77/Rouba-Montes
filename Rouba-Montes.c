#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

typedef struct pilha_cartas {
    int valor_carta;
    int valor_naipe;
    struct pilha_cartas* anterior;
} pilha_cartas;

typedef struct carta_topo {
    pilha_cartas* topo;
} carta_topo;

typedef struct player{
   char nome[10];
   int pontos;
   pilha_cartas* topo;
   struct player* proximo;
}player;

typedef struct player_list{
    player* primeiro;

}player_list;

typedef struct throwout{
    pilha_cartas* inicio;
}throwout;

carta_topo* cria_pilha();//cria pilha de compra
player_list* CriaListaJogadores();//inicializa a lista de jogadores
throwout* CriaListaDescarte();//inicializa a lista para descarte ou pegar cartas
void insere_lista(int carta ,int naipe ,throwout* l);
void cria_jogador(int num_p , player_list* p);//cria junto a quantidade de jogadores
void cria_listadescarte(throwout* l);//cria a lista de descarte
int criapilha_compra(int v, carta_topo* c);//insere a quantidade de baralhos a pilha de compra
void embaralha_pilhaC(carta_topo* c, int num_baralhos);//embaralha a pilha de compra 
void printlista(throwout* l);
void retira_pilhacartasPlayer(carta_topo* c , player* p);//Será utilizada para dar uma carta da pilha de compra ao jogador 
void retira_pilhacartasListaDiscarte(carta_topo* c , throwout* l, int num_p);// |INUTILIZADA |Todo incio de rodada ira recebere na pilha de descarta um numero total de cartas relacionado ao numero de jogadores
void verifica_cartas_jogador(player* p , int nump , int *acao );//verifica as cartas entre jogadores para roubar seus montes
void verifica_lista(player* p , throwout* l , int *acao);//verifica a pilha de cartas do jogador e da lista de descarte  adicionando um a pilha ou a lista
int retira_da_lista(throwout* l,int *carta, int *naipe, int pos);//remove da lista de descarte
void imprime_carta(int v);// printa a carta que for intruduzida 
void empilha_player(player* p , int carta , int naipe);//funçoes para dar a carta ao jogador seja da lista ou de outro jogador
void desempilha_player (player *p , int *carta , int *naipe );//função para retirar a carta do jogador seja para lista ou outro jogador
int remover(throwout* l , int *carta,int *naipe, int pos);//Remove da lista de descarte
void imprime_carta(int v);//Printa o valor e naipe da carta
void desempilha_compra (int* carta,int* naipe ,carta_topo* p );//remove uma carta da pilha de compras
int quant_lista(throwout* l);//ve quantos items tem na lista
void contapts(player* p);//conta os pontos do jogador
void insert_playerpts(player vetor[] ,int num_p);//funçao para inserção
void insert_playercard (pilha_cartas vetor[] ,int num_c);
void libera_carta(pilha_cartas* p); //libera a memoria das cartas
void libera_player(player_list* pl); //libera a memoria dos players
void libera_lista(throwout* l); //libera a lista de descarte
void libera_baralhocompra( carta_topo* c); //libera o baralho de compras

int main() {
    
    int num_p;//quantidade de players
    int num_b;//quantidade de baralho
    int acao;//caso o jogador roubo 
    
    carta_topo* baralho = cria_pilha();
    player_list* jogador = CriaListaJogadores();
    throwout* lista = CriaListaDescarte();
    
    printf(" ________________________________________\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|             ROUBA  MONTES              |\n");
    printf("|     Por: Gustavo Fernandes Oliveira    |\n");
    printf("|                                        |\n");
    printf("|               BOM JOGO                 |\n");
    printf("|________________________________________|\n\n");
    
    printf("Insira o numero de baralhos que se deseja jogar:");
    scanf("%d",&num_b);
    printf("\n");
    printf("JOGO SELECIONADO PARA %d DE BARALHO(S)\n\n",num_b);

    criapilha_compra(num_b, baralho);

    
    printf("\t|PARA DAR CONTINUACAO AO JOGO|\n\n");
    printf("Insira a quantidade de jogadores:");
    scanf("%d", &num_p);
    printf("\n");
    
    cria_jogador(num_p , jogador);
    printf("\n");
   
   for(int i = 0 ; i < 4 ; i++){
    
    printf("Loading");
    Sleep(150);
    
    printf(".");
    Sleep(150);
    
    printf(".");
    Sleep(150);
    
    printf(".");
    Sleep(150);
    
    system("cls");
   }
    player* aux = jogador->primeiro;
   
   while(baralho->topo != NULL){
        
        //if(lista->inicio == NULL){
            
            //retira_pilhacartasListaDiscarte(baralho , lista , num_p);
            
        //}
        acao = 0;
        printf("CARTAS NA MESA\n");
        printlista(lista);
        
        printf("VEZ DO PLAYER : %s\n", aux->nome);
        Sleep(500);
        printf("Carta retirada por %s\n",aux->nome);
        
        retira_pilhacartasPlayer(baralho , aux);
        
        imprime_carta(aux->topo->valor_carta);
        imprime_carta(aux->topo->valor_naipe);
        printf("\n");
        
        printf("\tENTER PARA DAR CONTINUIDADE\n\n");
        
        setbuf(stdin,NULL);
        getchar();

        verifica_lista(aux , lista , &acao);
        verifica_cartas_jogador(aux , num_p , &acao);
        contapts(aux);

        printf("\tNUMERO DE PTS %d\n\n", aux->pontos);
        
        if(acao == 0){
            printf("\tJOGADOR NAO ROUBOU NENHUMA CARTA | PASSA A VEZ\n\n");
            aux = aux->proximo;
        
        }else{
            printf("\tJOGADOR %s REPETE A JOGADA \n", aux->nome);

        }

        printf("\tENTER PARA DAR CONTINUIDADE\n\n");
        
        setbuf(stdin,NULL);
        getchar();
        
        printf("<-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->\n");
        
        
    }
    printf("Fim de game\n");
    printf("Ranking do jogadores\n");

    player* vetorpts = (player*) malloc(num_p*sizeof(player));
    
    for(int i = 0 ; i < num_p ; i++){
        
        vetorpts[i] = (*aux);
        aux = aux->proximo;
    }
   
    insert_playerpts(vetorpts , num_p );

     for(int i = 0 ; i < num_p ; i++){
        
        printf("%d - Jogador : %s  %d \n\n" , i+1 , vetorpts[i].nome , vetorpts[i].pontos);
    }

    pilha_cartas* vetorcard = (pilha_cartas*)malloc(vetorpts[0].pontos*sizeof(pilha_cartas));

    pilha_cartas* temp = vetorpts[0].topo;

    for(int i = 0 ; i< vetorpts[0].pontos ; i++){
        
        vetorcard[i].valor_carta = temp->valor_carta;
        vetorcard[i].valor_naipe = temp->valor_naipe;

        temp = temp -> anterior;
    }
    insert_playercard(vetorcard , vetorpts[0].pontos);
    printf("Ordem das cartas do(a) %s \n", vetorpts[0].nome);
    
     for(int i = 0 ; i< vetorpts[0].pontos ; i++){
        
        imprime_carta(vetorcard[i].valor_carta);
        imprime_carta(vetorcard[i].valor_naipe);
       
       printf("\n");
     }
    
    free(vetorcard);
    free(vetorpts);

    libera_baralhocompra(baralho);
    libera_lista(lista);
    libera_player(jogador);

    printf("\tmemoria liberada\t");
    printf(" \tOBRIGADO POR JOGAR\t");
    
    return 0;
}

carta_topo* cria_pilha() {
    
    carta_topo* c = (carta_topo*) malloc (1 * sizeof(carta_topo));
    c->topo = NULL;
    return c;
}

player_list* CriaListaJogadores(){
    
    player_list* p = (player_list*) malloc (sizeof(player_list));
    p->primeiro =  NULL;
    return p;
}

throwout* CriaListaDescarte(){
    
    throwout* l = (throwout*) malloc (sizeof(throwout));
    l->inicio = NULL;
    return l;
}

void cria_jogador(int num_p, player_list* p) {
    
    player* novo_jogador;
    player* aux;
    
    for (int i = 1; i <= num_p; i++) {
        novo_jogador = (player*)malloc(sizeof(player));

        printf("Insira o nome do jogador %d: ", i);
        setbuf(stdin, NULL);
        gets(novo_jogador->nome);

        novo_jogador->topo = NULL;
        novo_jogador->proximo = NULL;
        
        printf("\n");

        if (p->primeiro == NULL) {
            p->primeiro = novo_jogador;
            novo_jogador->proximo = novo_jogador;
        } else {
            aux = p->primeiro;  // reseta o aux pro inicio da lista

            while (aux->proximo != p->primeiro) {
                aux = aux->proximo;
            }

            aux->proximo = novo_jogador;
            novo_jogador->proximo = p->primeiro;
        }
    }
}

int criapilha_compra(int v, carta_topo* c) {
    
    int vetor_carta[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int vetor_naipe[4] = {14, 15, 16, 17};
    int count = 0;
    
    for(int k =  0 ; k < v ; k++){ 
        
        for (int j = 0; j < 4; j++){
            
            for (int i = 0; i < 13 ; i++){
                
                pilha_cartas* novo = (pilha_cartas*)malloc(1 * sizeof(pilha_cartas));
                
                novo->valor_carta = vetor_carta[i];
                novo->valor_naipe = vetor_naipe[j];
                novo->anterior = c->topo;
                
                c->topo = novo;
                count ++;
            }
        }
    }
    embaralha_pilhaC(c , v);
    return 1;
    
}

void embaralha_pilhaC(carta_topo* c, int num_baralhos ) {
    srand(time(NULL));
    int total_cartas = 52 * num_baralhos;

    pilha_cartas* cartas[total_cartas];
    pilha_cartas* temp = c->topo;

    // Coloca todas as cartas em um array
    for (int i = 0; i < total_cartas; i++) {
        cartas[i] = temp;
        temp = temp->anterior;
    }

    // Embaralha as cartas usando o algoritmo de Fisher-Yates
    for (int i = total_cartas - 1; i >= 0; i--) {
        int j = rand() % (i + 1);

        int tempValorCarta = cartas[i]->valor_carta;
        cartas[i]->valor_carta = cartas[j]->valor_carta;
        cartas[j]->valor_carta = tempValorCarta;

        int tempValorNaipe = cartas[i]->valor_naipe;
        cartas[i]->valor_naipe = cartas[j]->valor_naipe;
        cartas[j]->valor_naipe = tempValorNaipe;
    }
}

void printlista(throwout* l) {
    pilha_cartas* atual = l->inicio;
    int i = 1;
    
    if(atual == NULL){
        printf("Sem cartas na mesa\n\n");
    }
    else{ 
    
        while(atual != NULL){
            printf("%d - " , i);
            
            imprime_carta(atual->valor_carta);
            imprime_carta(atual->valor_naipe);
           
            printf("\n");
            atual = atual->anterior;
            i++;
        }
    }
}

void insere_lista(int carta , int naipe, throwout *l){
    
    pilha_cartas* novo = (pilha_cartas*) malloc(sizeof(pilha_cartas));
    pilha_cartas* aux;
    aux = l->inicio;
    
    if(l->inicio == NULL){
        
        novo->valor_carta = carta;
        novo->valor_naipe = naipe;
        novo->anterior = NULL;
        
        l->inicio = novo;
    }
    else{
        
        while(aux->anterior != NULL){
            aux = aux->anterior;
        }
        novo->valor_carta = carta;
        novo->valor_naipe = naipe;

        aux->anterior = novo;
        novo->anterior = NULL;
    }

}

void retira_pilhacartasPlayer(carta_topo* c , player* p){
    int carta , naipe;
    desempilha_compra(&carta , &naipe , c);
    empilha_player(p , carta , naipe);
}

void retira_pilhacartasListaDiscarte(carta_topo* c , throwout* l, int num_p){
    int carta , naipe; //utiliza funções padrões de empilha e desempilhar de um pilha dinmaica para desempilhar a pilha de comprar e entregar ao jogador
   for(int i = 0 ; i <= num_p ; i++){ 
        
        desempilha_compra(&carta ,&naipe ,c);
        insere_lista (carta , naipe, l);
        
   }
   
}

void empilha_player(player* p , int carta , int naipe){
    pilha_cartas* novo = (pilha_cartas*) malloc (sizeof(pilha_cartas));
    
    if(novo == NULL){
       printf("ERRO");

    }
    else{
        novo->valor_carta = carta;
        novo->valor_naipe = naipe;
        novo -> anterior = p -> topo;
        p->topo = novo;

    }

}

void desempilha_player (player *p , int *carta , int *naipe  ){
    pilha_cartas* aux;
    
    *carta = p->topo->valor_carta;
    *naipe = p->topo->valor_naipe;

    aux = p->topo;
    p->topo = aux->anterior;
    free(aux);

}

void verifica_cartas_jogador(player* p, int nump , int* acao) {
    player* aux = p->proximo;  // Assumindo que p->proximo foi inicializado corretamente
    int confirma = 0;
    int carta, naipe;
    int save1, save2;

    for (int i = 0; i < nump - 1; i++) {
        
        if (p->topo != NULL && aux->topo != NULL && p->topo->valor_carta == aux->topo->valor_carta) {
            
            confirma = 1;
            desempilha_player(aux, &save1, &save2);
            printf("O JOGADOR %s PERDEU SEU MONTE\n", aux->nome );

            *acao = 1;
            
            while (aux->topo != NULL) {
                
                desempilha_player(aux, &carta, &naipe);
                empilha_player(p, carta, naipe);
            }

            empilha_player(p, save1, save2);
        }
        aux = aux->proximo;
    }

    if (confirma == 0) {
        printf("\tJOGADOR NAO ROUBOU MONTES\n");
    }
}

void verifica_lista(player* p , throwout* l , int *acao){
    int posicao = 1;
    int confirma = 0;
    int confirma2 = 0;
    int carta, naipe;
    pilha_cartas* aux = l->inicio;

    while (aux != NULL && confirma2 != 1) {  // Corrigido para verificar se aux é diferente de NULL

        if (p->topo->valor_carta == aux->valor_carta) {
            
            confirma = remover(l, &carta, &naipe, posicao);
            empilha_player(p, carta, naipe);

            printf("CARTA REMOVIDA DA LISTA\n");
            
            imprime_carta(p->topo->valor_carta);
            imprime_carta(p->topo->valor_naipe);
            printf("\n");
            
            confirma2++;

        } else {
            posicao++;
        }

        aux = aux->anterior;
    }

    if (p->topo != NULL && p->topo->anterior != NULL &&
        
        p->topo->valor_carta == p->topo->anterior->valor_carta) {
        
        printf("A CARTA RETIRADA DA LISTA ENTROU NO MONTE DO JOGADOR \n ");
        imprime_carta(p->topo->valor_carta);
        imprime_carta(p->topo->valor_naipe);
        printf("\n");
        
        confirma = 1;
        *acao = 1;
    }

    if (confirma != 1) {
        
        if (p->topo != NULL) {
            
            printf("A CARTA RETIRADA PELO JOGADOR FOI INSERIDA A LISTA \n ");//caso jogador nao encontre carta na lista
            printf("\t");
            
            imprime_carta(p->topo->valor_carta);
            imprime_carta(p->topo->valor_naipe);

            desempilha_player(p, &carta, &naipe);
            insere_lista(carta, naipe, l);

            printf("\n");
        }
    }
}
   
int remover(throwout* l , int *carta,int *naipe, int pos){

   pilha_cartas* novo = l->inicio;
   pilha_cartas* aux = l->inicio;
   int quantidade = quant_lista(l);
   

   if(pos <= 0 || pos > quantidade){
        return 0;
   }
   
   for( int i = 1; i < pos ; i++){
        aux = novo;
        novo = novo->anterior;
   }
    *carta = novo->valor_carta;
    *naipe = novo->valor_naipe;

    if(novo == l->inicio){
        l->inicio = novo ->anterior;
    }
    else{
        aux->anterior = novo ->anterior;
    }
    free(novo);
    return 1;

}

void imprime_carta(int v){
    switch (v){ //valor inteiro que entrar vai printar ou carta ou naipe
        case 1:
            printf("As de ");
            break;
        case 11:
            printf("Valete de  ");
            break;
        case 12:
            printf("Rainha de  ");
            break;
        case 13:
            printf("Rei de ");
            break;
        case 14:
            printf("Paus \n");
            break;
        case 15:
            printf("Copas \n");
            break;
        case 16:
            printf("Ouros \n");
            break;
        case 17:
            printf("Espadas \n");
            break;
        default:
            if(v == NULL){
                printf("vazio \n");
            }
            else{ 
                printf("%d de ", v);
            }
            break;
    }
        
}

void desempilha_compra (int* carta , int* naipe ,carta_topo* p ){
    pilha_cartas* aux;// função de desempilhar padrão
   
    *carta = p->topo->valor_carta;
    *naipe = p->topo->valor_naipe;
    
    aux = p->topo;
    p->topo = aux->anterior;
    
    free(aux);
   
}       

int quant_lista(throwout* l){
    pilha_cartas* aux = l->inicio; //conta a quantidade de cartas na lista
    int i = 0;

    if(l->inicio == NULL){
        return 0;
    }
    else{
        i++;
    }

    while(aux->anterior != NULL){
        aux = aux->anterior;
        i++;
    }
    return i;
}

void contapts(player* p){
    pilha_cartas* aux = p->topo; //conta o numero de pts em cada rodada do jogador inserido
    int ponto = 0;
    
    while(aux != NULL){
        aux = aux->anterior;
        ponto++;
    }
    p->pontos = ponto;
}

void insert_playerpts(player vetor[] ,int num_p){
   int i, j , min; //utiliza o metodo de inserçao para ordenar os pontos e fazer o ranking
   player temp;
    for (i = 0; i < num_p - 1; i++) {
        min = i;
        for (j = i + 1; j < num_p; j++) {
            if (vetor[j].pontos < vetor[min].pontos) {
                min = j;
            }
        }
        temp = vetor[min];
        vetor[min] = vetor[i];
        vetor[i] = temp;
    }

   
   //Inverte o vetor
        int inicio = 0;
        int fim = num_p - 1;

        while (inicio < fim) {

            player temp = vetor[inicio];
            vetor[inicio] = vetor[fim];
            vetor[fim] = temp;

            inicio++;
            fim--;
    
   }
}

void insert_playercard (pilha_cartas vetor[] ,int num_c){

    int i, j , min;
   pilha_cartas temp;
    
    for (i = 0; i < num_c - 1; i++) {
        min = i;
        
        for (j = i + 1; j < num_c; j++) {
            
            if (vetor[j].valor_carta < vetor[min].valor_carta) {
                min = j;
            }
        }
       
       temp = vetor[min];
        vetor[min] = vetor[i];
        vetor[i] = temp;
    }
}

void libera_carta(pilha_cartas* p){
    
    while(p != NULL){
        pilha_cartas* aux = p;
        p = aux->anterior;
        
        free(aux);
    }
}

void libera_player (player_list* pl){
    
    while(pl->primeiro != NULL){
        player* aux = pl->primeiro;
        
        libera_carta(aux->topo);
        pl->primeiro = aux->proximo;
        
        free(aux);
    }
}

void libera_lista(throwout* l){

    while(l->inicio != NULL){
        pilha_cartas* aux = l->inicio;
        
        l->inicio = aux->anterior;

        free(aux);
    }
}

void libera_baralhocompra(carta_topo* c){
    
    while(c->topo != NULL){
        pilha_cartas * aux = c->topo; 
        
        c->topo = aux->anterior;
        free(aux);
    }
}