//bibliotecas
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
//fim bibliotecas

//constantes
const int FPS = 60.0;
const int LARGURA_JANELA = 1200;
const int ALTURA_JANELA = 600;
//fim constantes

//variaveis e ponteiros
ALLEGRO_DISPLAY *janela = NULL;

ALLEGRO_EVENT_QUEUE *filaDeEvento = NULL;

ALLEGRO_TIMER *timer = NULL;

ALLEGRO_BITMAP *spriteRafa = NULL;
ALLEGRO_BITMAP *spriteIlan = NULL;
ALLEGRO_BITMAP *spriteLarissa = NULL;
ALLEGRO_BITMAP *spriteYuka = NULL;
ALLEGRO_BITMAP *icone = NULL;

ALLEGRO_SAMPLE *chuvaPadrao = NULL;
ALLEGRO_SAMPLE *yukaBackground = NULL;
ALLEGRO_SAMPLE *gritoMorte = NULL;
ALLEGRO_SAMPLE *dying1 = NULL;
ALLEGRO_SAMPLE *dying2 = NULL;
ALLEGRO_SAMPLE *dying3 = NULL;
ALLEGRO_SAMPLE *yukaScream = NULL;

ALLEGRO_SAMPLE_ID idYukaBackground;
ALLEGRO_SAMPLE_ID idChuva;

ALLEGRO_FONT *pixelFontPequena = NULL;
ALLEGRO_FONT *pixelFont = NULL;
ALLEGRO_FONT *pixelFontTitle = NULL;

bool cenaFim = false;
bool jogoFinalizado = false;
bool fimDeJogo = false;
bool sair = false;
bool trocarCena = false;
bool chuvaBaixa = false;
bool chuvaAlta = false;
bool yukaBackgroundSom = false;
bool yukaPerseguindo = false;
int timerYukaEntrar = 0;
int timerFugaYuka = 0;
int contadorDeFinal[3] = {0,0,0};
int cenaFinal = 0;

int eventosTerminados = 0;
int eventos[5] = {0,0,0,0,0};
int acao = 0;
int acaoAnterior = 0;

double tempoInicial = 0;

int spawnYukaValor = 0;
int spawnYukaTentativa = 0;
//fim variaveis e ponteiros

//funcoes
int init();
void destroi();

int Menu();
int HallAnim();
int EscritorioAnim();
int Hall(int veioDeOnde);
int Cozinha();
int BanheiroPrimeiroAndar();
int BanheiroSegundoAndar();
int CorredorSegundoAndar(int veioDeOnde);
int Biblioteca(int veioDeOnde);
int BibliotecaAnim();
int SalaDeJantar(int veioDeOnde);
int Varanda(int veioDeOnde);
int CorredorPrimeiroAndar(int veioDeOnde);
int Escritorio(int veioDeOnde);
int CorredorSegundoAndar1(int veioDeOnde);
int QuartoHospedes();
int QuartoHospedesAnim();
int QuartoHospedesAnim1();
int QuartoCasal(int veioDeOnde);
int QuartoYuka();
int banheiroQuartoCasal();
int QuartoYukaAnim();
int finalBom();
int finalVerdadeiro();
int finalRuim();
int finalNeutro();
int creditos();

void atualizaCamera(float *cameraPosition, float playerPosition, float playerWidth);

void iniciaRafa();
void iniciaIlan();
void iniciaLarissa();
void iniciaYuka();

void erroMsg(char *texto);

void iniciaTimer();
double obterTempo();
int temporizaDistancia(int pos1,int pos2);

int filaPadrao(bool teclas[]);
int movimentoPadrao();
int movimentoPadraoComEscondido();
//fim funcoes

//structs e funcoes de inicialização de personagem
struct personagem{
    ALLEGRO_BITMAP *spritesheet;
    int alturaSprite, larguraSprite;
    int regiaoXdaFolha, regiaoYdaFolha;
    int frames_sprite, cont_frames;
    int colunas_sprite, coluna_atual;
    int linhas_sprite, linha_atual;
    float pos_x, pos_y;
    float velocidade;
    bool andando;
    bool correndo;
    int inverte_sprite;
};
//fim structs

void iniciaRafa(struct personagem *h){
    h->spritesheet = spriteRafa;
    h->alturaSprite = 160;
    h->larguraSprite = 100;
    h->regiaoXdaFolha = 0;
    h->regiaoYdaFolha = 0;
    h->frames_sprite = 0;
    h->cont_frames = 0;
    h->colunas_sprite = 8;
    h->coluna_atual = 0;
    h->linhas_sprite = 3;
    h->linha_atual = 0;
    h->pos_x = 0;
    h->pos_y = 340;
    h->velocidade = 0;
    h->inverte_sprite = 0;
    h->andando = false;
    h->correndo = false;
}
void iniciaIlan(struct personagem *h){
    h->spritesheet = spriteIlan;
    h->alturaSprite = 160;
    h->larguraSprite = 100;
    h->regiaoXdaFolha = 0;
    h->regiaoYdaFolha = 0;
    h->frames_sprite = 0;
    h->cont_frames = 0;
    h->colunas_sprite = 8;
    h->coluna_atual = 0;
    h->linhas_sprite = 3;
    h->linha_atual = 0;
    h->pos_x = 0;
    h->pos_y = 340;
    h->velocidade = 0;
    h->inverte_sprite = 0;
    h->andando = false;
    h->correndo = false;
}
void iniciaLarissa(struct personagem *h){
    h->spritesheet = spriteLarissa;
    h->alturaSprite = 160;
    h->larguraSprite = 100;
    h->regiaoXdaFolha = 0;
    h->regiaoYdaFolha = 0;
    h->frames_sprite = 0;
    h->cont_frames = 0;
    h->colunas_sprite = 8;
    h->coluna_atual = 0;
    h->linhas_sprite = 3;
    h->linha_atual = 0;
    h->pos_x = 0;
    h->pos_y = 340;
    h->velocidade = 0;
    h->inverte_sprite = 0;
    h->andando = false;
    h->correndo = false;
}
void iniciaYuka(struct personagem *h){
    h->spritesheet = spriteYuka;
    h->alturaSprite = 100;
    h->larguraSprite = 160;
    h->regiaoXdaFolha = 0;
    h->regiaoYdaFolha = 0;
    h->frames_sprite = 4;
    h->cont_frames = 0;
    h->colunas_sprite = 8;
    h->coluna_atual = 0;
    h->linhas_sprite = 1;
    h->linha_atual = 0;
    h->pos_x = 0;
    h->pos_y = 400;
    h->velocidade = 4;
    h->inverte_sprite = 0;
    h->andando = true;
    h->correndo = false;
}
//fim inicialização de personagem

struct personagem yukaGlobal;

int main(){
    init();
    while(!sair){
        system("cls");
        printf("eventos terminados: %d\n", eventosTerminados);
        for(int i = 0; i < 5; i++){
            printf("evento %d: %d\n", i + 1, eventos[i]);
        }
        printf("acao: %d\n", acao);
        printf("acao anterior: %d\n", acaoAnterior);
        if(acao == 1 || acao == 7 || acao == 18 || acao == 19 || acao == 20 || acao == 21){
            yukaPerseguindo = false;
            timerYukaEntrar = 0;
            timerFugaYuka = 0;
        }
        if(fimDeJogo){
            al_play_sample(dying1,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
            al_play_sample(dying2,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
            al_play_sample(dying3,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
            acao = 0;
            acaoAnterior = 0;
            cenaFinal = 0;
            yukaPerseguindo = false;
            chuvaAlta = false;
            chuvaBaixa = false;
            cenaFim = false;
            eventos[0] = 0;
            eventos[1] = 0;
            eventos[2] = 0;
            eventos[3] = 0;
            eventos[4] = 0;
            contadorDeFinal[0] = 0;
            contadorDeFinal[1] = 0;
            contadorDeFinal[2] = 0;
            timerYukaEntrar = 0;
            timerFugaYuka =0;
            eventosTerminados = 0;
            fimDeJogo = false;
            al_rest(7);
        }
        if(jogoFinalizado){
            acao = 0;
            acaoAnterior = 0;
            yukaPerseguindo = false;
            chuvaAlta = false;
            chuvaBaixa = false;
            eventos[0] = 0;
            eventos[1] = 0;
            eventos[2] = 0;
            eventos[3] = 0;
            eventos[4] = 0;
            timerYukaEntrar = 0;
            timerFugaYuka =0;
            eventosTerminados = 0;
            cenaFinal = 0;
            cenaFim = false;
            contadorDeFinal[0] = 0;
            contadorDeFinal[1] = 0;
            contadorDeFinal[2] = 0;
        }
        if(eventosTerminados>=2 && (acao == 2 || acao == 5 || acao == 11)){
            srand(time(NULL));
            if(eventosTerminados == 2){
                spawnYukaValor = rand() % 6;
                spawnYukaTentativa = rand() % 6;
            }
            else if(eventosTerminados == 3){
                spawnYukaValor = rand() % 5;
                spawnYukaTentativa = rand() % 5;
            }
            else if(eventosTerminados == 4){
                spawnYukaValor = rand() % 4;
                spawnYukaTentativa = rand() % 4;
            }
            else if(eventosTerminados == 5){
                spawnYukaValor = rand() % 3;
                spawnYukaTentativa = rand() % 3;
            }
            if(spawnYukaTentativa == spawnYukaValor){
                yukaPerseguindo = true;
                timerYukaEntrar = 150;
                timerFugaYuka = 1500;
            }
        }
        if(yukaPerseguindo && timerFugaYuka <= 0)yukaPerseguindo = false;
        if(acao!=0&&acao!=14&&!chuvaBaixa){
            chuvaBaixa = true;
            if(chuvaAlta){
                chuvaAlta = false;
            }
            al_stop_sample(&idChuva);
            al_play_sample(chuvaPadrao,0.4,0.5,1,ALLEGRO_PLAYMODE_LOOP,&idChuva);
        }
        else if((acao == 0 || acao == 14) && !chuvaAlta){
            chuvaAlta = true;
            if(chuvaBaixa){
                chuvaBaixa = false;
            }
            al_stop_sample(&idChuva);
            al_play_sample(chuvaPadrao,0.9,0.5,1,ALLEGRO_PLAYMODE_LOOP,&idChuva);
        }
        if(yukaPerseguindo){
            if(!yukaBackgroundSom){
                al_play_sample(yukaBackground,1,0.5,1,ALLEGRO_PLAYMODE_LOOP,&idYukaBackground);
                yukaBackgroundSom = true;
            }
        }
        else{
            if(yukaBackgroundSom){
                al_stop_sample(&idYukaBackground);
                yukaBackgroundSom = false;
            }
        }
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
        }
        if(cenaFim){
            yukaPerseguindo = false;
            timerYukaEntrar = 0;
            timerFugaYuka =0;
            if(chuvaAlta){
                chuvaAlta = false;
                al_stop_sample(&idChuva);
            }
            if(chuvaBaixa){
                chuvaBaixa = false;
                al_stop_sample(&idChuva);
            }
        }
        switch(acao){
            case 0:
                Menu();
            break;
            case 1:
                HallAnim();
            break;
            case 2:
                Hall(acaoAnterior);
            break;
            case 3:
                Cozinha();
            break;
            case 4:
                BanheiroPrimeiroAndar(acaoAnterior);
            break;
            case 5:
                CorredorSegundoAndar(acaoAnterior);
            break;
            case 6:
                Biblioteca(acaoAnterior);
            break;
            case 7:
                BibliotecaAnim();
            break;
            case 8:
                Escritorio(acaoAnterior);
            break;
            case 9:
                CorredorPrimeiroAndar(acaoAnterior);
            break;
            case 10:
                SalaDeJantar(acaoAnterior);
            break;
            case 11:
                CorredorSegundoAndar1(acaoAnterior);
            break;
            case 12:
                BanheiroSegundoAndar();
            break;
            case 13:
                QuartoHospedes(acaoAnterior);
            break;
            case 14:
                Varanda(acaoAnterior);
            break;
            case 15:
                QuartoCasal(acaoAnterior);
            break;
            case 16:
                banheiroQuartoCasal();
            break;
            case 17:
                QuartoYuka();
            break;
            case 18:
                QuartoHospedesAnim();
            break;
            case 19:
                QuartoHospedesAnim1();
            break;
            case 20:
                EscritorioAnim();
            break;
            case 21:
                QuartoYukaAnim();
            break;
            case 22:
                finalBom();
            break;
            case 23:
                finalVerdadeiro();
            break;
            case 24:
                finalRuim();
            break;
            case 25:
                finalNeutro();
            break;
        }
        trocarCena = false;
    }
    destroi();
    return 1;
}

int finalBom(){
    ALLEGRO_BITMAP *fade = NULL;
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    char textos[7][100];
    strcpy(textos[0], "Final bom");
    strcpy(textos[1], "                ");
    strcpy(textos[2], "Após a aparição da Yuka");
    strcpy(textos[3], "todos os personagens conseguiram passar por ela");
    strcpy(textos[4], "correram desesperadamente para o hall");
    strcpy(textos[5], "onde encontraram a porta da frente aberta");
    strcpy(textos[6], "todos saíram vivos");

    bool fim = false;
    int fadeTextos[7];
    int fadeFinalOpacidade = 0;
    int fadeAtual = 0;
    int timerFinal = 0;
    for(int i = 0; i < 7; i++){
        fadeTextos[i] = 0;
    }
    while(!sair && !jogoFinalizado){
        iniciaTimer();
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        for(int i = 0; i < 7; i++){
            al_draw_text(pixelFont, al_map_rgb(fadeTextos[i], fadeTextos[i],fadeTextos[i]), LARGURA_JANELA/2, 150 + i*20, ALLEGRO_ALIGN_CENTER,textos[i]);
        }
        if(fadeTextos[fadeAtual] < 255){
            fadeTextos[fadeAtual] += 1;
            if(fadeTextos[fadeAtual]>255) fadeTextos[fadeAtual] = 255;
        }
        else if (fadeAtual < 7){
            fadeAtual++;
        }
        else if(timerFinal == 0){
            timerFinal = 60;
        }
        else if(timerFinal > 1){
            timerFinal--;
        }
        else{
            fim = true;
        }

        if(fim){
            if(fadeFinalOpacidade<255){
                if(fadeFinalOpacidade > 255){
                    fadeFinalOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeFinalOpacidade),0,0,0);
                fadeFinalOpacidade += 5;
            }
            else{
                fim = false;
                jogoFinalizado = true;
            }
        }
        if(jogoFinalizado){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }

    }
    al_destroy_bitmap(fade);
    return 1;
}
int finalVerdadeiro(){
    ALLEGRO_BITMAP *fade = NULL;
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    char textos[9][100];
    strcpy(textos[0], "Final Verdadeiro");
    strcpy(textos[1], "                ");
    strcpy(textos[2], "Após a aparição da Yuka");
    strcpy(textos[3], "o Ilan foi pego e brutalmente assassinado");
    strcpy(textos[4], "enquanto Rafael e Larissa corriam para o hall");
    strcpy(textos[5], "a Yuka apareceu e derrubou a Larissa");
    strcpy(textos[6], "o Rafael à salvou, mas logo em seguida foi pego");
    strcpy(textos[7], "a porta do hall estava aberta e a Larissa conseguiu sair");
    strcpy(textos[8], "sozinha...");

    bool fim = false;
    int fadeTextos[9];
    int fadeFinalOpacidade = 0;
    int fadeAtual = 0;
    int timerFinal = 0;
    for(int i = 0; i < 9; i++){
        fadeTextos[i] = 0;
    }
    while(!sair && !jogoFinalizado){
        iniciaTimer();
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        for(int i = 0; i < 9; i++){
            al_draw_text(pixelFont, al_map_rgb(fadeTextos[i], fadeTextos[i],fadeTextos[i]), LARGURA_JANELA/2, 150 + i*20, ALLEGRO_ALIGN_CENTER,textos[i]);
        }
        if(fadeTextos[fadeAtual] < 255){
            fadeTextos[fadeAtual] += 1;
            if(fadeTextos[fadeAtual]>255) fadeTextos[fadeAtual] = 255;
        }
        else if (fadeAtual < 9){
            fadeAtual++;
        }
        else if(timerFinal == 0){
            timerFinal = 60;
        }
        else if(timerFinal > 1){
            timerFinal--;
        }
        else{
            fim = true;
        }

        if(fim){
            if(fadeFinalOpacidade<255){
                if(fadeFinalOpacidade > 255){
                    fadeFinalOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeFinalOpacidade),0,0,0);
                fadeFinalOpacidade += 5;
            }
            else{
                fim = false;
                jogoFinalizado = true;
            }
        }
        if(jogoFinalizado){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fade);
    return 1;
}
int finalRuim(){
    ALLEGRO_BITMAP *fade = NULL;
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    char textos[10][100];
    strcpy(textos[0], "Final Ruim");
    strcpy(textos[1], "                ");
    strcpy(textos[2], "Após a aparição da Yuka");
    strcpy(textos[3], "Rafael derruba o Ilan enquanto tenta escapar");
    strcpy(textos[4], "fazendo com que a Yuka o mate logo em seguida");
    strcpy(textos[5], "Larissa tropeça na escada enquanto tenta alcançar o Rafael");
    strcpy(textos[6], "é seriamente ferida na queda, Rafael prefere deixa-la pra trás e tentar escapar");
    strcpy(textos[7], "ao chegar a saída a porta está trancada");
    strcpy(textos[8], "Yuka aparece logo em seguida e estraçalha seu corpo");
    strcpy(textos[9], "Todos Morreram...");

    bool fim = false;
    int fadeTextos[10];
    int fadeFinalOpacidade = 0;
    int fadeAtual = 0;
    int timerFinal = 0;
    for(int i = 0; i < 10; i++){
        fadeTextos[i] = 0;
    }
    while(!sair && !jogoFinalizado){
        iniciaTimer();
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        for(int i = 0; i < 10; i++){
            al_draw_text(pixelFont, al_map_rgb(fadeTextos[i], fadeTextos[i],fadeTextos[i]), LARGURA_JANELA/2, 150 + i*20, ALLEGRO_ALIGN_CENTER,textos[i]);
        }
        if(fadeTextos[fadeAtual] < 255){
            fadeTextos[fadeAtual] += 1;
            if(fadeTextos[fadeAtual]>255) fadeTextos[fadeAtual] = 255;
        }
        else if (fadeAtual < 10){
            fadeAtual++;
        }
        else if(timerFinal == 0){
            timerFinal = 60;
        }
        else if(timerFinal > 1){
            timerFinal--;
        }
        else{
            fim = true;
        }

        if(fim){
            if(fadeFinalOpacidade<255){
                if(fadeFinalOpacidade > 255){
                    fadeFinalOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeFinalOpacidade),0,0,0);
                fadeFinalOpacidade += 5;
            }
            else{
                fim = false;
                jogoFinalizado = true;
            }
        }
        if(jogoFinalizado){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }

    }
    al_destroy_bitmap(fade);
    return 1;
}
int finalNeutro(){
    ALLEGRO_BITMAP *fade = NULL;
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    char textos[8][100];
    strcpy(textos[0], "Final Neutro");
    strcpy(textos[1], "                ");
    strcpy(textos[2], "Após a aparição da Yuka");
    strcpy(textos[3], "todos conseguem passar por ela e chegar no hall");
    strcpy(textos[4], "Rafael é pego enquanto desce as escadas");
    strcpy(textos[5], "Ilan se atira contra a Yuka e manda o Rafael ir embora");
    strcpy(textos[6], "Rafael obedece mesmo sabendo que não deveria");
    strcpy(textos[7], "Larissa e Rafael conseguiram escapar");

    bool fim = false;
    int fadeTextos[8];
    int fadeFinalOpacidade = 0;
    int fadeAtual = 0;
    int timerFinal = 0;
    for(int i = 0; i < 8; i++){
        fadeTextos[i] = 0;
    }
    while(!sair && !jogoFinalizado){
        iniciaTimer();
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        for(int i = 0; i < 8; i++){
            al_draw_text(pixelFont, al_map_rgb(fadeTextos[i], fadeTextos[i],fadeTextos[i]), LARGURA_JANELA/2, 150 + i*20, ALLEGRO_ALIGN_CENTER,textos[i]);
        }
        if(fadeTextos[fadeAtual] < 255){
            fadeTextos[fadeAtual] += 1;
            if(fadeTextos[fadeAtual]>255) fadeTextos[fadeAtual] = 255;
        }
        else if (fadeAtual < 8){
            fadeAtual++;
        }
        else if(timerFinal == 0){
            timerFinal = 60;
        }
        else if(timerFinal > 1){
            timerFinal--;
        }
        else{
            fim = true;
        }

        if(fim){
            if(fadeFinalOpacidade<255){
                if(fadeFinalOpacidade > 255){
                    fadeFinalOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeFinalOpacidade),0,0,0);
                fadeFinalOpacidade += 5;
            }
            else{
                fim = false;
                jogoFinalizado = true;
            }
        }
        if(jogoFinalizado){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }

    }
    al_destroy_bitmap(fade);
    return 1;
}
int creditos(){
    return 1;
}
int QuartoYukaAnim(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *dialogBox = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_BITMAP *detalheEscolhaDialogo = NULL;
    dialogBox = al_load_bitmap("imgs/dialogBox/DialogBox.png");
    fundo = al_load_bitmap("imgs/quartoYuka/QuartoYukaFundo.png");
    frente = al_load_bitmap("imgs/quartoYuka/QuartoYukaFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    detalheEscolhaDialogo = al_load_bitmap("imgs/efeitos/detalheEscolhaDialogo.png");
    struct personagem rafa;
    struct personagem ilan;
    struct personagem larissa;

    iniciaLarissa(&larissa);
    iniciaRafa(&rafa);
    iniciaIlan(&ilan);
    char dialogos[10][100];
    strcpy(dialogos[0], "Ilan: ei Rafa, achei a Larissa");
    strcpy(dialogos[1], "Rafael: percebi...");
    strcpy(dialogos[2], "Larissa: é bom estar com vocês, aquela coisa apareceu no quarto");
    strcpy(dialogos[3], "Larissa: eu corri e me escondi aqui, ai o Ilan apareceu");
    strcpy(dialogos[4], "Larissa: enfim, a gente precisa sair daqui, ela pode aparecer de novo");

    strcpy(dialogos[5], "Escolha 1: vamos sim, fico feliz eu ver você bem, fiquei muito preocupado");
    strcpy(dialogos[6], "Escolha 2: vamos lá, temos que dar um jeito de fugir");
    strcpy(dialogos[7], "Escolha 3: a culpa de estarmos aqui é sua, espero que consigamos sair pelo menos");

    enum posicoes {RIGHT, LEFT};
    int escolha = 1;
    int detalheEscolhaOpacidade = 50;
    bool aumentaOpacidadeEscolha = true;
    bool escolhaFeita = false;
    int dialogoAtual = -1;
    int tempoPularDialogo = 60;
    int opacidadedb = 0;
    int fadeOpacidade = 255;
    float timerEvento = 0;
    int timerDialogo = 0;
    int timerTrocarEscolha = 0;
    int timerEscolha = 0;
    bool inicio = true;
    bool fim = false;
    bool teclas[3] = {false, false, false};
    bool pausarDialogo = false;
    bool dialogBoxAtiva = false;
    bool yukaNoComodo = false;
    ilan.pos_x = 200;
    ilan.inverte_sprite = LEFT;
    larissa.pos_x = 150;
    larissa.inverte_sprite = RIGHT;
    rafa.pos_x = 550;
    rafa.inverte_sprite = LEFT;

    while(!trocarCena && !sair){
        iniciaTimer();
        timerEvento += 1.0/60;
        if(timerTrocarEscolha>0){
            timerTrocarEscolha--;
        }
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_UP){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = false;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = true;
                }
            }
        }
        if(rafa.andando || rafa.correndo){
            rafa.linha_atual = rafa.andando?1:2;
            rafa.velocidade = rafa.andando?3:6;
            rafa.colunas_sprite = 8;
            rafa.frames_sprite = 6;
        }
        else{
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.colunas_sprite = 5;
            rafa.frames_sprite = 25;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(ilan.andando || ilan.correndo){
            ilan.linha_atual = ilan.andando?1:2;
            ilan.velocidade = ilan.andando?3:6;
            ilan.colunas_sprite = 8;
            ilan.frames_sprite = 6;
        }
        else{
            ilan.velocidade = 0;
            ilan.linha_atual = 0;
            ilan.colunas_sprite = 5;
            ilan.frames_sprite = 25;
            if(ilan.coluna_atual>4){
                ilan.coluna_atual = 0;
            }
        }
        if(larissa.andando || larissa.correndo){
            larissa.linha_atual = larissa.andando?1:2;
            larissa.velocidade = larissa.andando?3:6;
            larissa.colunas_sprite = 8;
            larissa.frames_sprite = 6;
        }
        else{
            larissa.velocidade = 0;
            larissa.linha_atual = 0;
            larissa.colunas_sprite = 5;
            larissa.frames_sprite = 25;
            if(larissa.coluna_atual>4){
                larissa.coluna_atual = 0;
            }
        }
        if(larissa.cont_frames > larissa.frames_sprite){
            larissa.cont_frames = 0;
            larissa.coluna_atual = (larissa.coluna_atual+1)%larissa.colunas_sprite;
        }
        else{
            larissa.cont_frames++;
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1)%rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(ilan.cont_frames > ilan.frames_sprite){
            ilan.cont_frames = 0;
            ilan.coluna_atual = (ilan.coluna_atual+1)%ilan.colunas_sprite;
        }
        else{
            ilan.cont_frames++;
        }

        if(timerTrocarEscolha <= 0){
            if(teclas[1]){
                if(escolha > 1){
                    escolha--;
                }
                timerTrocarEscolha = 10;
            }
            else if(teclas[2]){
                if(escolha < 3){
                    escolha++;
                }
                timerTrocarEscolha = 10;
            }
        }

        rafa.regiaoXdaFolha = rafa.coluna_atual*rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual*rafa.alturaSprite;

        ilan.regiaoXdaFolha = ilan.coluna_atual*ilan.larguraSprite;
        ilan.regiaoYdaFolha = ilan.linha_atual*ilan.alturaSprite;

        larissa.regiaoXdaFolha = larissa.coluna_atual*larissa.larguraSprite;
        larissa.regiaoYdaFolha = larissa.linha_atual*larissa.alturaSprite;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo,0,0,0);
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                              rafa.larguraSprite,rafa.alturaSprite,
                              rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        al_draw_bitmap_region(ilan.spritesheet,ilan.regiaoXdaFolha,ilan.regiaoYdaFolha,
                              ilan.larguraSprite,ilan.alturaSprite,
                              ilan.pos_x,ilan.pos_y,ilan.inverte_sprite);
        al_draw_bitmap_region(larissa.spritesheet,larissa.regiaoXdaFolha,larissa.regiaoYdaFolha,
                              larissa.larguraSprite,larissa.alturaSprite,
                              larissa.pos_x,larissa.pos_y,larissa.inverte_sprite);
        if(yukaNoComodo && !fim){
            yukaGlobal.frames_sprite = 8;
            yukaGlobal.velocidade = 2;
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap(frente,0,0,0);
        if(dialogBoxAtiva){
            if(opacidadedb<255){
                opacidadedb+=5;
            }
            al_draw_tinted_bitmap(dialogBox,al_map_rgb(opacidadedb,opacidadedb,opacidadedb),0,500,0);
        }
        if(!inicio && timerEvento>1){
            if(dialogoAtual == -1) ilan.inverte_sprite = RIGHT;
            dialogBoxAtiva = true;
            if(opacidadedb>= 255)
            {
                timerDialogo = timerDialogo>0?timerDialogo-1:0;
                if((dialogoAtual != 4 && dialogoAtual != -1) || timerDialogo > 0 ){
                    al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[dialogoAtual]);
                }

                if(!pausarDialogo){
                    if(tempoPularDialogo>0){
                        tempoPularDialogo--;
                    }
                    if(tempoPularDialogo <= 0 && dialogoAtual != 9){
                        if(dialogoAtual != 4 && dialogoAtual != -1){
                            al_draw_text(pixelFontPequena,al_map_rgb(200,200,200),1000,580,ALLEGRO_ALIGN_CENTER,"pressione espaço para pular o dialogo");
                        }
                        if(teclas[0]){
                            tempoPularDialogo = 60;
                            if(dialogoAtual == 8) tempoPularDialogo = 200;
                            if(dialogoAtual != -1){
                                dialogoAtual++;
                            }
                        }
                    }
                    if(dialogoAtual == -1){
                        pausarDialogo = true;
                    }
                    if(dialogoAtual == 4){
                        timerDialogo = 240;
                        timerEscolha = 30;
                        pausarDialogo = true;
                    }

                    if(dialogoAtual == 9 && tempoPularDialogo <= 0){
                        pausarDialogo = true;
                        rafa.inverte_sprite = RIGHT;
                        iniciaYuka(&yukaGlobal);
                        yukaGlobal.pos_x = 550;
                        yukaNoComodo = true;
                        al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        al_play_sample(yukaBackground,1,0.5,1,ALLEGRO_PLAYMODE_LOOP,&idYukaBackground);
                        yukaBackgroundSom = true;
                        fim = true;
                        cenaFim = true;
                        for(int i = 0; i<5; i++){
                            if(eventos[i] == 1)contadorDeFinal[0]++;
                            if(eventos[i] == 2)contadorDeFinal[1]++;
                            if(eventos[i] == 3)contadorDeFinal[2]++;
                        }
                        if(contadorDeFinal[0]>2) cenaFinal = 1;
                        else if(contadorDeFinal[1]>2) cenaFinal = 2;
                        else if(contadorDeFinal[2]>2) cenaFinal = 3;
                        else cenaFinal = 4;

                        switch(cenaFinal){
                            case 1: acao = 22; break;
                            case 2: acao = 23; break;
                            case 3: acao = 24; break;
                            case 4: acao = 25; break;
                        }
                    }
                }
                else if(dialogoAtual == -1){
                    if(rafa.pos_x > 250){
                        rafa.andando = true;
                        rafa.pos_x -= rafa.velocidade;
                    }
                    else{
                        rafa.andando = false;
                        pausarDialogo = false;
                        dialogoAtual++;
                    }
                }
                else if(dialogoAtual == 4){
                    if(timerDialogo <= 0){
                        if(!escolhaFeita){
                            if(detalheEscolhaOpacidade <= 50){
                                aumentaOpacidadeEscolha = true;
                            }
                            else if(detalheEscolhaOpacidade >= 150){
                                aumentaOpacidadeEscolha = false;
                            }
                            if(aumentaOpacidadeEscolha){
                                detalheEscolhaOpacidade++;
                            }
                            else{
                                detalheEscolhaOpacidade--;
                            }
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[5]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,540,ALLEGRO_ALIGN_LEFT,dialogos[6]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,560,ALLEGRO_ALIGN_LEFT,dialogos[7]);
                            switch(escolha){
                                case 1:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,516,0);
                                break;
                                case 2:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,536,0);
                                break;
                                case 3:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,556,0);
                                break;
                            }
                            if(timerEscolha<=0){
                                if(teclas[0]){
                                    escolhaFeita = true;
                                    eventos[4] = escolha;
                                    eventosTerminados = 5;
                                }
                            }
                            else{
                                timerEscolha--;
                            }

                        }
                        else{
                            pausarDialogo = false;
                            dialogoAtual = 8;
                            tempoPularDialogo = 60;
                            switch(escolha){
                                case 1:
                                    strcpy(dialogos[8], "Larissa: eu também fiquei preocupada com você, devia ter te acompanhado");
                                    strcpy(dialogos[9], "Rafael: concordo, mas oque importa é que você está bem");
                                break;
                                case 2:
                                    strcpy(dialogos[8], "Larissa: temos sim, vamos logo");
                                    strcpy(dialogos[9], "Ilan: é bora lá pra porta da frente");
                                break;
                                case 3:
                                    strcpy(dialogos[8], "Larissa: eu nunca devia ter pedido ajuda pra você...");
                                    strcpy(dialogos[9], "Rafael: agora é tarde, só vamos sair daqui logo");
                                break;
                            }
                        }
                    }
                }
            }
        }

        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(dialogBox);
    al_destroy_bitmap(fade);
    al_destroy_bitmap(detalheEscolhaDialogo);
    acaoAnterior = 21;
    return 1;
}
int EscritorioAnim(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *dialogBox = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_BITMAP *detalheEscolhaDialogo = NULL;
    dialogBox = al_load_bitmap("imgs/dialogBox/DialogBox.png");
    fundo = al_load_bitmap("imgs/escritorio/EscritorioFundo.png");
    frente = al_load_bitmap("imgs/escritorio/EscritorioFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    detalheEscolhaDialogo = al_load_bitmap("imgs/efeitos/detalheEscolhaDialogo.png");
    struct personagem rafa;
    struct personagem ilan;

    iniciaRafa(&rafa);
    iniciaIlan(&ilan);
    char dialogos[9][100];
    strcpy(dialogos[0], "Ilan: Rafael ? é você cara ?");
    strcpy(dialogos[1], "Rafael: sim, bom te ver mano");
    strcpy(dialogos[2], "Ilan: fico feliz que você esteja bem");
    strcpy(dialogos[3], "Ilan: queria me desculpar pela discussão sobre o fantasma...");

    strcpy(dialogos[4], "Escolha 1: precisa se desculpar não, nem eu to acreditando no que aconteceu");
    strcpy(dialogos[5], "Escolha 2: tudo bem, não se preocupa com isso, eu to de boas");
    strcpy(dialogos[6], "Escolha 3: eu avisei...");

    enum posicoes {RIGHT, LEFT};
    int escolha = 1;
    int detalheEscolhaOpacidade = 50;
    bool aumentaOpacidadeEscolha = true;
    bool escolhaFeita = false;
    int dialogoAtual = 0;
    int tempoPularDialogo = 60;
    int opacidadedb = 0;
    int fadeOpacidade = 255;
    int timerDialogo = 0;
    int timerTrocarEscolha = 0;
    int timerEscolha = 0;
    bool inicio = true;
    bool fim = false;
    bool teclas[3] = {false, false, false};
    bool pausarDialogo = false;
    bool dialogBoxAtiva = false;
    ilan.pos_x = 560;
    ilan.inverte_sprite = RIGHT;
    rafa.pos_x = 1120;
    rafa.inverte_sprite = LEFT;

    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerTrocarEscolha>0){
            timerTrocarEscolha--;
        }
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_UP){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = false;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = true;
                }
            }
        }
        if(rafa.andando || rafa.correndo){
            rafa.linha_atual = rafa.andando?1:2;
            rafa.velocidade = rafa.andando?3:6;
            rafa.colunas_sprite = 8;
            rafa.frames_sprite = 6;
        }
        else{
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.colunas_sprite = 5;
            rafa.frames_sprite = 25;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(ilan.andando || ilan.correndo){
            ilan.linha_atual = ilan.andando?1:2;
            ilan.velocidade = ilan.andando?3:6;
            ilan.colunas_sprite = 8;
            ilan.frames_sprite = 6;
        }
        else{
            ilan.velocidade = 0;
            ilan.linha_atual = 0;
            ilan.colunas_sprite = 5;
            ilan.frames_sprite = 25;
            if(ilan.coluna_atual>4){
                ilan.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1)%rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(ilan.cont_frames > ilan.frames_sprite){
            ilan.cont_frames = 0;
            ilan.coluna_atual = (ilan.coluna_atual+1)%ilan.colunas_sprite;
        }
        else{
            ilan.cont_frames++;
        }

        if(timerTrocarEscolha <= 0){
            if(teclas[1]){
                if(escolha > 1){
                    escolha--;
                }
                timerTrocarEscolha = 10;
            }
            else if(teclas[2]){
                if(escolha < 3){
                    escolha++;
                }
                timerTrocarEscolha = 10;
            }
        }

        rafa.regiaoXdaFolha = rafa.coluna_atual*rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual*rafa.alturaSprite;

        ilan.regiaoXdaFolha = ilan.coluna_atual*ilan.larguraSprite;
        ilan.regiaoYdaFolha = ilan.linha_atual*ilan.alturaSprite;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo,0,0,0);
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                              rafa.larguraSprite,rafa.alturaSprite,
                              rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        al_draw_bitmap_region(ilan.spritesheet,ilan.regiaoXdaFolha,ilan.regiaoYdaFolha,
                              ilan.larguraSprite,ilan.alturaSprite,
                              ilan.pos_x,ilan.pos_y,ilan.inverte_sprite);
        al_draw_bitmap(frente,0,0,0);
        if(dialogBoxAtiva){
            if(opacidadedb<255){
                opacidadedb+=5;
            }
            al_draw_tinted_bitmap(dialogBox,al_map_rgb(opacidadedb,opacidadedb,opacidadedb),0,500,0);
        }
        if(!inicio){
            dialogBoxAtiva = true;
            if(opacidadedb>= 255)
            {
                timerDialogo = timerDialogo>0?timerDialogo-1:0;
                if(dialogoAtual != 3 || timerDialogo > 0){
                    al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[dialogoAtual]);
                }

                if(!pausarDialogo){
                    if(tempoPularDialogo>0){
                        tempoPularDialogo--;
                    }
                    if(tempoPularDialogo <= 0){
                        if(dialogoAtual != 3 && dialogoAtual != 8){
                            al_draw_text(pixelFontPequena,al_map_rgb(200,200,200),1000,580,ALLEGRO_ALIGN_CENTER,"pressione espaço para pular o dialogo");
                        }
                        if(teclas[0]){
                            tempoPularDialogo = 60;
                            if(dialogoAtual != 6){
                                dialogoAtual++;
                            }
                        }
                    }
                    if(dialogoAtual == 0){
                        pausarDialogo = true;
                    }
                    if(dialogoAtual == 3){
                        timerDialogo = 240;
                        timerEscolha = 30;
                        pausarDialogo = true;
                    }
                    if(dialogoAtual == 8 && tempoPularDialogo <= 0){
                        pausarDialogo = true;
                        al_rest(1);
                        fim = true;
                        acao = 8;
                    }
                }
                else if(dialogoAtual == 0){
                    if(rafa.pos_x > 610){
                        rafa.andando = true;
                        rafa.pos_x -= rafa.velocidade;
                    }
                    else{
                        rafa.andando = false;
                        pausarDialogo = false;
                        dialogoAtual++;
                    }
                }
                else if(dialogoAtual == 3){
                    if(timerDialogo <= 0){
                        if(!escolhaFeita){
                            if(detalheEscolhaOpacidade <= 50){
                                aumentaOpacidadeEscolha = true;
                            }
                            else if(detalheEscolhaOpacidade >= 150){
                                aumentaOpacidadeEscolha = false;
                            }
                            if(aumentaOpacidadeEscolha){
                                detalheEscolhaOpacidade++;
                            }
                            else{
                                detalheEscolhaOpacidade--;
                            }
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[4]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,540,ALLEGRO_ALIGN_LEFT,dialogos[5]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,560,ALLEGRO_ALIGN_LEFT,dialogos[6]);
                            switch(escolha){
                                case 1:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,516,0);
                                break;
                                case 2:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,536,0);
                                break;
                                case 3:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,556,0);
                                break;
                            }
                            if(timerEscolha<=0){
                                if(teclas[0]){
                                    escolhaFeita = true;
                                    eventos[3] = escolha;
                                    eventosTerminados = 4;
                                }
                            }
                            else{
                                timerEscolha--;
                            }

                        }
                        else{
                            pausarDialogo = false;
                            dialogoAtual = 7;
                            tempoPularDialogo = 60;
                            switch(escolha){
                                case 1:
                                    strcpy(dialogos[7], "Ilan: é macho, aquilo foi muito bizarro, a gente precisa sair daqui");
                                    strcpy(dialogos[8], "Rafael: sim, vamos voltar pra buscar a Larissa");
                                break;
                                case 2:
                                    strcpy(dialogos[7], "Ilan: então beleza, vamos sair daqui");
                                    strcpy(dialogos[8], "Rafael: vamos lá");
                                break;
                                case 3:
                                    strcpy(dialogos[7], "Ilan: legal Rafa, legal ...");
                                    strcpy(dialogos[8], "Rafael: ...");
                                break;
                            }
                        }
                    }
                }
            }
        }

        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(dialogBox);
    al_destroy_bitmap(fade);
    al_destroy_bitmap(detalheEscolhaDialogo);
    acaoAnterior = 20;
    return 1;
}
int QuartoYuka(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    fundo = al_load_bitmap("imgs/quartoYuka/QuartoYukaFundo.png");
    frente = al_load_bitmap("imgs/quartoYuka/QuartoYukaFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int opacidadeEmUmaEntradaS = 0;
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaI = 0;
    int timerEscondido = 0;
    char salaDaPortaI[50];
    char salaDaPortaS[50];
    bool escondido = false;
    bool visto = false;
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaI = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = LEFT;
    rafa.pos_x = 550;
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        else if(escondido && timerFugaYuka <= 0 && yukaNoComodo && yukaPerseguindo && !visto){
            yukaPerseguindo = false;
            yukaNoComodo = false;
            al_stop_sample(&idYukaBackground);
            yukaBackgroundSom = false;
        }
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        if(timerEscondido>0){
            timerEscondido--;
        }
        emUmaEntradaS = false;
        emUmaEntradaI = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadraoComEscondido(&rafa,-20,1120,teclas,&escondido);
        if(rafa.pos_x>500 && rafa.pos_x<600){
            if(teclas[3]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 11;
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Corredor");
        }
        if(rafa.pos_x>950 && rafa.pos_x<1250){
            if(teclas[2]){
                if(!escondido && timerEscondido <= 0){
                    if(yukaNoComodo)visto=true;
                    escondido = true;
                    timerEscondido = 240;
                    rafa.pos_x = 1050;
                }
                else if(escondido && timerEscondido <= 0){
                    escondido = false;
                    timerEscondido = 240;
                }
            }
            emUmaEntradaS = true;
            if(!escondido){
                strcpy(salaDaPortaS, "esconder embaixo da cama");
            }
            else{
                strcpy(salaDaPortaS, "sair de baixo da cama");
            }
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if(!escondido){
                if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
                   (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                        al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        fimDeJogo = true;
                        fim = true;
                }
            }
            else if(visto){
                if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
                   (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                        al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        fimDeJogo = true;
                        fim = true;
                }
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        if(!escondido){
            al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                rafa.larguraSprite,rafa.alturaSprite,
                rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        }

        al_draw_bitmap(frente,0,0,0);
        if(escondido)al_draw_bitmap(fade,0,0,0);
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            if(strcmp(salaDaPortaS, "esconder embaixo da cama")!=0 && strcmp(salaDaPortaS, "sair de baixo da cama")!=0){
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
            else if(timerEscondido>0){
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,30,30),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
            else{
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    acaoAnterior = 17;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int banheiroQuartoCasal(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *cortinaBanheiro = NULL;
    fundo = al_load_bitmap("imgs/banheiroQuartoCasal/BanheiroQuartoCasalFundo.png");
    frente = al_load_bitmap("imgs/banheiroQuartoCasal/BanheiroQuartoCasalFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    cortinaBanheiro = al_load_sample("sons/showerCurtain.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int timerEscondido = 0;
    char salaDaPortaS[50];
    bool yukaNoComodo = false;
    bool escondido = false;
    bool visto = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 20;
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        else if(escondido && timerFugaYuka <= 0 && yukaNoComodo && yukaPerseguindo && !visto){
            yukaPerseguindo = false;
            yukaNoComodo = false;
            al_stop_sample(&idYukaBackground);
            yukaBackgroundSom = false;
        }
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        if(timerEscondido>0){
            timerEscondido--;
        }
        filaPadrao(teclas);
        if(!fim)
        movimentoPadraoComEscondido(&rafa,-10,400,teclas,&escondido);
        if(rafa.pos_x>360 && rafa.pos_x<500){
            if(teclas[2]){
                if(!escondido && timerEscondido <= 0){
                    if(yukaNoComodo)visto = true;
                    escondido = true;
                    timerEscondido = 200;
                    rafa.pos_x = 470;
                    rafa.inverte_sprite = LEFT;
                    al_play_sample(cortinaBanheiro,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                else if(escondido && timerEscondido <= 0){
                    escondido = false;
                    timerEscondido = 200;
                    rafa.pos_x = 400;
                    al_play_sample(cortinaBanheiro,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
            }
            emUmaEntradaS = true;
            if(!escondido){
                strcpy(salaDaPortaS, "esconder no box");
            }
            else{
                strcpy(salaDaPortaS, "sair do box");
            }
        }
        else if(rafa.pos_x>-20 && rafa.pos_x<30){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 15;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Quarto de Casal");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if(!escondido){
                if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
                   (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                        al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        fimDeJogo = true;
                        fim = true;
                }
            }
            else if(visto){
                if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
                   (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                        al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        fimDeJogo = true;
                        fim = true;
                }
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        al_draw_bitmap(frente,0,0,0);
        if(escondido)al_draw_bitmap(fade,0,0,0);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            if(strcmp(salaDaPortaS, "esconder no box")!=0 && strcmp(salaDaPortaS, "sair do box")!=0){
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
            else if(timerEscondido>0){
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,30,30),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
            else{
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    al_destroy_sample(cortinaBanheiro);
    acaoAnterior = 16;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int QuartoCasal(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    fundo = al_load_bitmap("imgs/quartoDeCasal/QuartoCasalFundo.png");
    frente = al_load_bitmap("imgs/quartoDeCasal/QuartoCasalFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    char salaDaPortaI[50];
    char salaDaPortaS[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 1000;
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    if(veioDeOnde == 11){
        rafa.pos_x = 1100;
    }
    if(veioDeOnde == 16){
        rafa.pos_x = 805;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        emUmaEntradaI = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadrao(&rafa,-20,1120,teclas);
        if(rafa.pos_x>970 && rafa.pos_x<1090){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 5;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Corredor");
        }
        if(rafa.pos_x>740 && rafa.pos_x<870){
            if(teclas[3]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 16;
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Banheiro");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    acaoAnterior = 15;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int QuartoHospedes(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *macaneta = NULL;
    fundo = al_load_bitmap("imgs/quartoHospedes/quartoHospedesFundo.png");
    frente = al_load_bitmap("imgs/quartoHospedes/quartoHospedesFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    macaneta = al_load_sample("sons/doorHandle.wav");
    enum posicoes {RIGHT, LEFT};
    struct personagem rafa;
    struct personagem larissa;
    iniciaRafa(&rafa);
    if(eventos[0] != 0){
        iniciaLarissa(&larissa);
        larissa.pos_x = 50;
        larissa.inverte_sprite = RIGHT;
    }
    int timerFala = 0;
    int timerMacaneta = 0;
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    int fadeFala = 0;
    char salaDaPortaS[50];
    char salaDaPortaI[50];
    char falaRafa[50];
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = LEFT;
    if(veioDeOnde == 18 || veioDeOnde == 19){
        rafa.pos_x = 100;
    }
    else{
        rafa.pos_x = 1120;
    }
    while(!trocarCena && !sair){
        if(timerFugaYuka >= 0)timerFugaYuka--;
        iniciaTimer();
        if(timerMacaneta>0){
            timerMacaneta--;
        }
        emUmaEntradaI = false;
        emUmaEntradaS = false;
        filaPadrao(teclas);
        if(!fim)
            movimentoPadrao(&rafa,-20,1120,teclas);
        if(eventos[0] != 0){
            if(larissa.andando || larissa.correndo){
                larissa.linha_atual = larissa.andando?1:2;
                larissa.velocidade = larissa.andando?3:6;
                larissa.colunas_sprite = 8;
                larissa.frames_sprite = 6;
            }
            else{
                larissa.velocidade = 0;
                larissa.linha_atual = 0;
                larissa.colunas_sprite = 5;
                larissa.frames_sprite = 25;
                if(larissa.coluna_atual>4){
                    larissa.coluna_atual = 0;
                }
            }
            if(larissa.cont_frames > larissa.frames_sprite){
                larissa.cont_frames = 0;
                larissa.coluna_atual = (larissa.coluna_atual+1)%larissa.colunas_sprite;
            }
            else{
                larissa.cont_frames++;
            }
            larissa.regiaoXdaFolha = larissa.coluna_atual*larissa.larguraSprite;
            larissa.regiaoYdaFolha = larissa.linha_atual*larissa.alturaSprite;
        }
        if(rafa.pos_x>480 && rafa.pos_x<610){
            if(teclas[3]){
                if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                }
                if(timerFala <= 0){
                    timerFala = 240;
                    strcpy(falaRafa, "trancado...");
                }
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Corredor");
        }
        if(rafa.pos_x>1100 && rafa.pos_x<1200){
            if(teclas[2]){
                fim = true;
                acao = 14;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Varanda");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(eventos[0] != 0){
            al_draw_bitmap_region(larissa.spritesheet,larissa.regiaoXdaFolha,larissa.regiaoYdaFolha,
                larissa.larguraSprite,larissa.alturaSprite,
                larissa.pos_x,larissa.pos_y,larissa.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        al_draw_bitmap(frente,0,0,0);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                    rafa.pos_x + 50, rafa.pos_y -40,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        if(timerFala>0){
            if(fadeFala<255){
                fadeFala+=5;
            }
            timerFala--;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else if(fadeFala > 100){
            fadeFala-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else{
            fadeFala = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(macaneta);
    acaoAnterior = 13;
    return 1;
}
int QuartoHospedesAnim(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *dialogBox = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_BITMAP *detalheEscolhaDialogo = NULL;
    dialogBox = al_load_bitmap("imgs/dialogBox/DialogBox.png");
    fundo = al_load_bitmap("imgs/quartoHospedes/QuartoHospedesFundo.png");
    frente = al_load_bitmap("imgs/quartoHospedes/QuartoHospedesFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    detalheEscolhaDialogo = al_load_bitmap("imgs/efeitos/detalheEscolhaDialogo.png");
    struct personagem rafa;
    struct personagem larissa;

    iniciaRafa(&rafa);
    iniciaLarissa(&larissa);
    char dialogos[26][100];
    strcpy(dialogos[0], "Rafael: Larissa ?");
    strcpy(dialogos[1], "Larissa: RAFA !?");
    strcpy(dialogos[2], "Rafael: sim, legal a gente se encontrar aqui né, coincidência");
    strcpy(dialogos[3], "Larissa: idiota...");
    strcpy(dialogos[4], "Rafael: mas oque você veio fazer aqui ? Nós estávamos preocupados");
    strcpy(dialogos[5], "Larissa: a eu vim investigar a mansão");
    strcpy(dialogos[6], "Larissa: estão comentando sobre coisas estranhas acontecendo aqui");
    strcpy(dialogos[7], "Rafael: é ouvi falar, esse é um bom motivo pra você não estar aqui");
    strcpy(dialogos[8], "Rafael: enfim, porquê você enviou aquela mensagem ?");
    strcpy(dialogos[9], "Larissa: eu fiquei presa aqui, comecei a ouvir sons estranhos");
    strcpy(dialogos[10], "Larissa: as portas se trancaram sozinhas");
    strcpy(dialogos[11], "Larissa: e tinha alguma coisa me observando");
    strcpy(dialogos[12], "Larissa: pra piorar a bateria do meu celular estava acabando");
    strcpy(dialogos[13], "Larissa: então te enviei a mensagem antes da bateria acabar e vim pra ca");
    strcpy(dialogos[14], "Larissa: nada estranho aconteceu nesse quarto até agora");
    strcpy(dialogos[15], "Rafael: agora fiquei preocupado, espero que não seja zueira");
    strcpy(dialogos[16], "Larissa: Olha, eu to aqui a dois dias");
    strcpy(dialogos[17], "Larissa: você acha que eu ia ficar aqui dois dias só pra te zuar ?");
    strcpy(dialogos[18], "Rafael: talvez...");
    strcpy(dialogos[19], "Rafael: enfim, vamos procurar o Ilan e sair logo daqui");
    strcpy(dialogos[20], "Larissa: na verdade prefiro ficar aqui, encontra ele e vem me chamar por favor");

    strcpy(dialogos[21], "Escolha 1 - Larissa vem comigo, por favor eu insisto, não é seguro aqui");
    strcpy(dialogos[22], "Escolha 2 - beleza, fique ai e não saia até voltarmos");
    strcpy(dialogos[23], "Escolha 3 - a então se vira ae !");

    enum posicoes {RIGHT, LEFT};
    int escolha = 1;
    int detalheEscolhaOpacidade = 50;
    bool aumentaOpacidadeEscolha = true;
    bool escolhaFeita = false;
    int dialogoAtual = 0;
    int tempoPularDialogo = 60;
    int opacidadedb = 0;
    int fadeOpacidade = 255;
    int timerDialogo = 0;
    int timerTrocarEscolha = 0;
    int timerEscolha = 0;
    bool inicio = true;
    bool fim = false;
    bool teclas[3] = {false, false, false};
    bool pausarDialogo = false;
    bool dialogBoxAtiva = false;
    larissa.pos_x = 50;
    larissa.inverte_sprite = RIGHT;
    rafa.pos_x = 1120;
    rafa.inverte_sprite = LEFT;

    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerTrocarEscolha>0){
            timerTrocarEscolha--;
        }
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_UP){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = false;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = true;
                }
            }
        }
        if(rafa.andando || rafa.correndo){
            rafa.linha_atual = rafa.andando?1:2;
            rafa.velocidade = rafa.andando?3:6;
            rafa.colunas_sprite = 8;
            rafa.frames_sprite = 6;
        }
        else{
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.colunas_sprite = 5;
            rafa.frames_sprite = 25;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(larissa.andando || larissa.correndo){
            larissa.linha_atual = larissa.andando?1:2;
            larissa.velocidade = larissa.andando?3:6;
            larissa.colunas_sprite = 8;
            larissa.frames_sprite = 6;
        }
        else{
            larissa.velocidade = 0;
            larissa.linha_atual = 0;
            larissa.colunas_sprite = 5;
            larissa.frames_sprite = 25;
            if(larissa.coluna_atual>4){
                larissa.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1)%rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(larissa.cont_frames > larissa.frames_sprite){
            larissa.cont_frames = 0;
            larissa.coluna_atual = (larissa.coluna_atual+1)%larissa.colunas_sprite;
        }
        else{
            larissa.cont_frames++;
        }

        if(timerTrocarEscolha <= 0){
            if(teclas[1]){
                if(escolha > 1){
                    escolha--;
                }
                timerTrocarEscolha = 10;
            }
            else if(teclas[2]){
                if(escolha < 3){
                    escolha++;
                }
                timerTrocarEscolha = 10;
            }
        }

        rafa.regiaoXdaFolha = rafa.coluna_atual*rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual*rafa.alturaSprite;

        larissa.regiaoXdaFolha = larissa.coluna_atual*larissa.larguraSprite;
        larissa.regiaoYdaFolha = larissa.linha_atual*larissa.alturaSprite;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo,0,0,0);
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                              rafa.larguraSprite,rafa.alturaSprite,
                              rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        al_draw_bitmap_region(larissa.spritesheet,larissa.regiaoXdaFolha,larissa.regiaoYdaFolha,
                              larissa.larguraSprite,larissa.alturaSprite,
                              larissa.pos_x,larissa.pos_y,larissa.inverte_sprite);
        al_draw_bitmap(frente,0,0,0);
        if(dialogBoxAtiva){
            if(opacidadedb<255){
                opacidadedb+=5;
            }
            al_draw_tinted_bitmap(dialogBox,al_map_rgb(opacidadedb,opacidadedb,opacidadedb),0,500,0);
        }
        if(!inicio){
            dialogBoxAtiva = true;
            if(opacidadedb>= 255)
            {
                timerDialogo = timerDialogo>0?timerDialogo-1:0;
                if(dialogoAtual != 20 || timerDialogo > 0){
                    al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[dialogoAtual]);
                }

                if(!pausarDialogo){
                    if(tempoPularDialogo>0){
                        tempoPularDialogo--;
                    }
                    if(tempoPularDialogo <= 0){
                        if(dialogoAtual != 25){
                            al_draw_text(pixelFontPequena,al_map_rgb(200,200,200),1000,580,ALLEGRO_ALIGN_CENTER,"pressione espaço para pular o dialogo");
                        }
                        if(teclas[0]){
                            tempoPularDialogo = 60;
                            if(dialogoAtual != 25){
                                dialogoAtual++;
                            }
                        }
                    }
                    if(dialogoAtual == 3){
                        pausarDialogo = true;
                    }
                    if(dialogoAtual == 20){
                        timerDialogo = 240;
                        timerEscolha = 30;
                        pausarDialogo = true;
                    }
                    if(dialogoAtual == 25 && tempoPularDialogo <= 0){
                        pausarDialogo = true;
                        fim = true;
                        acao = 13;
                    }
                }
                else if(dialogoAtual == 3){
                    if(rafa.pos_x > 100){
                        rafa.andando = true;
                        rafa.pos_x -= rafa.velocidade;
                    }
                    else{
                        rafa.andando = false;
                        pausarDialogo = false;
                        dialogoAtual++;
                    }
                }
                else if(dialogoAtual == 20){
                    if(timerDialogo <= 0){
                        if(!escolhaFeita){
                            if(detalheEscolhaOpacidade <= 50){
                                aumentaOpacidadeEscolha = true;
                            }
                            else if(detalheEscolhaOpacidade >= 150){
                                aumentaOpacidadeEscolha = false;
                            }
                            if(aumentaOpacidadeEscolha){
                                detalheEscolhaOpacidade++;
                            }
                            else{
                                detalheEscolhaOpacidade--;
                            }
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[21]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,540,ALLEGRO_ALIGN_LEFT,dialogos[22]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,560,ALLEGRO_ALIGN_LEFT,dialogos[23]);
                            switch(escolha){
                                case 1:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,516,0);
                                break;
                                case 2:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,536,0);
                                break;
                                case 3:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,556,0);
                                break;
                            }
                            if(timerEscolha<=0){
                                if(teclas[0]){
                                    escolhaFeita = true;
                                    eventos[0] = escolha;
                                    eventosTerminados = 1;
                                }
                            }
                            else{
                                timerEscolha--;
                            }

                        }
                        else{
                            pausarDialogo = false;
                            dialogoAtual = 24;
                            tempoPularDialogo = 60;
                            switch(escolha){
                                case 1:
                                    strcpy(dialogos[24], "Larissa: não se preocupe seu fofo, vou ficar bem, pode ir lá");
                                    strcpy(dialogos[25], "Rafael: okay, to indo então");
                                break;
                                case 2:
                                    strcpy(dialogos[24], "Larissa: pode deixar, vou me esconder");
                                    strcpy(dialogos[25], "Rafael: se cuida");
                                break;
                                case 3:
                                    strcpy(dialogos[24], "Larissa: a Rafa vai $@#@!#$%@");
                                    strcpy(dialogos[25], "Rafael: só to tentando ajudar...");
                                break;
                            }
                        }
                    }
                }
            }
        }

        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(dialogBox);
    al_destroy_bitmap(fade);
    al_destroy_bitmap(detalheEscolhaDialogo);
    acaoAnterior = 18;
    return 1;
}
int QuartoHospedesAnim1(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *dialogBox = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_BITMAP *detalheEscolhaDialogo = NULL;
    dialogBox = al_load_bitmap("imgs/dialogBox/DialogBox.png");
    fundo = al_load_bitmap("imgs/quartoHospedes/QuartoHospedesFundo.png");
    frente = al_load_bitmap("imgs/quartoHospedes/QuartoHospedesFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    detalheEscolhaDialogo = al_load_bitmap("imgs/efeitos/detalheEscolhaDialogo.png");
    struct personagem rafa;
    struct personagem larissa;

    iniciaRafa(&rafa);
    iniciaLarissa(&larissa);
    char dialogos[26][100];
    strcpy(dialogos[0], "Larissa: que gritaria foi essa ? Ta tudo bem ?");
    strcpy(dialogos[1], "Rafael: eu estava conversando com o Ilan");
    strcpy(dialogos[2], "Rafael: de repente surgiu uma mulher se arrastando toda ensanguentada");
    strcpy(dialogos[3], "Larissa: meu deus... Então a história do fantasma é verdade !");
    strcpy(dialogos[4], "Rafael: fantasma?");
    strcpy(dialogos[5], "Larissa: sim, uns 20 anos atrás uma menina cometeu suicídio aqui");
    strcpy(dialogos[6], "Larissa: depois disso ninguém mais conseguiu morar nessa casa");
    strcpy(dialogos[7], "Larissa: e muita gente sumiu depois de ter vindo para cá");
    strcpy(dialogos[8], "Rafael: massa, então vamo tentar ir embora daqui logo");

    strcpy(dialogos[9], "Escolha 1 - vou atrás do Ilan, continua escondida tá, volto logo");
    strcpy(dialogos[10], "Escolha 2 - você vai continuar aqui ?");
    strcpy(dialogos[11], "Escolha 3 - você vai continuar aqui escondida ? Deixa de ser covarde !");
    enum posicoes {RIGHT, LEFT};
    int escolha = 1;
    int detalheEscolhaOpacidade = 50;
    bool aumentaOpacidadeEscolha = true;
    bool escolhaFeita = false;
    int dialogoAtual = 0;
    int tempoPularDialogo = 60;
    int opacidadedb = 0;
    int fadeOpacidade = 255;
    int timerDialogo = 0;
    int timerTrocarEscolha = 0;
    int timerEscolha = 0;
    bool inicio = true;
    bool fim = false;
    bool teclas[3] = {false, false, false};
    bool pausarDialogo = false;
    bool dialogBoxAtiva = false;
    larissa.pos_x = 50;
    larissa.inverte_sprite = RIGHT;
    rafa.pos_x = 1120;
    rafa.inverte_sprite = LEFT;

    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerTrocarEscolha>0){
            timerTrocarEscolha--;
        }
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_UP){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = false;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = true;
                }
            }
        }
        if(rafa.andando || rafa.correndo){
            rafa.linha_atual = rafa.andando?1:2;
            rafa.velocidade = rafa.andando?3:6;
            rafa.colunas_sprite = 8;
            rafa.frames_sprite = 6;
        }
        else{
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.colunas_sprite = 5;
            rafa.frames_sprite = 25;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(larissa.andando || larissa.correndo){
            larissa.linha_atual = larissa.andando?1:2;
            larissa.velocidade = larissa.andando?3:6;
            larissa.colunas_sprite = 8;
            larissa.frames_sprite = 6;
        }
        else{
            larissa.velocidade = 0;
            larissa.linha_atual = 0;
            larissa.colunas_sprite = 5;
            larissa.frames_sprite = 25;
            if(larissa.coluna_atual>4){
                larissa.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1)%rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(larissa.cont_frames > larissa.frames_sprite){
            larissa.cont_frames = 0;
            larissa.coluna_atual = (larissa.coluna_atual+1)%larissa.colunas_sprite;
        }
        else{
            larissa.cont_frames++;
        }

        if(timerTrocarEscolha <= 0){
            if(teclas[1]){
                if(escolha > 1){
                    escolha--;
                }
                timerTrocarEscolha = 10;
            }
            else if(teclas[2]){
                if(escolha < 3){
                    escolha++;
                }
                timerTrocarEscolha = 10;
            }
        }

        rafa.regiaoXdaFolha = rafa.coluna_atual*rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual*rafa.alturaSprite;

        larissa.regiaoXdaFolha = larissa.coluna_atual*larissa.larguraSprite;
        larissa.regiaoYdaFolha = larissa.linha_atual*larissa.alturaSprite;

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo,0,0,0);
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                              rafa.larguraSprite,rafa.alturaSprite,
                              rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        al_draw_bitmap_region(larissa.spritesheet,larissa.regiaoXdaFolha,larissa.regiaoYdaFolha,
                              larissa.larguraSprite,larissa.alturaSprite,
                              larissa.pos_x,larissa.pos_y,larissa.inverte_sprite);
        al_draw_bitmap(frente,0,0,0);
        if(dialogBoxAtiva){
            if(opacidadedb<255){
                opacidadedb+=5;
            }
            al_draw_tinted_bitmap(dialogBox,al_map_rgb(opacidadedb,opacidadedb,opacidadedb),0,500,0);
        }
        if(!inicio){
            if(rafa.pos_x > 100){
                rafa.andando = true;
                rafa.pos_x-=rafa.velocidade;
            }
            else if(rafa.andando){
                rafa.andando = false;
                dialogBoxAtiva = true;
            }
            if(opacidadedb>= 255)
            {
                timerDialogo = timerDialogo>0?timerDialogo-1:0;
                if(dialogoAtual != 8 || timerDialogo > 0){
                    al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[dialogoAtual]);
                }

                if(!pausarDialogo){
                    if(tempoPularDialogo>0){
                        tempoPularDialogo--;
                    }
                    if(tempoPularDialogo <= 0){
                        if(dialogoAtual != 8 && dialogoAtual != 13){
                            al_draw_text(pixelFontPequena,al_map_rgb(200,200,200),1000,580,ALLEGRO_ALIGN_CENTER,"pressione espaço para pular o dialogo");
                        }
                        if(teclas[0]){
                            tempoPularDialogo = 60;
                            if(dialogoAtual != 8 && dialogoAtual != 13){
                                dialogoAtual++;
                            }
                        }
                        if(dialogoAtual == 13 && tempoPularDialogo <= 0){
                            fim = true;
                            acao = 13;
                        }
                    }
                    if(dialogoAtual == 8){
                        timerDialogo = 240;
                        timerEscolha = 30;
                        pausarDialogo = true;
                    }
                }
                else if(dialogoAtual == 8){
                    if(timerDialogo <= 0){
                        if(!escolhaFeita){
                            if(detalheEscolhaOpacidade <= 50){
                                aumentaOpacidadeEscolha = true;
                            }
                            else if(detalheEscolhaOpacidade >= 150){
                                aumentaOpacidadeEscolha = false;
                            }
                            if(aumentaOpacidadeEscolha){
                                detalheEscolhaOpacidade++;
                            }
                            else{
                                detalheEscolhaOpacidade--;
                            }
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[9]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,540,ALLEGRO_ALIGN_LEFT,dialogos[10]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,560,ALLEGRO_ALIGN_LEFT,dialogos[11]);
                            switch(escolha){
                                case 1:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,516,0);
                                break;
                                case 2:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,536,0);
                                break;
                                case 3:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,556,0);
                                break;
                            }
                            if(timerEscolha<=0){
                                if(teclas[0]){
                                    escolhaFeita = true;
                                    eventos[2] = escolha;
                                    eventosTerminados = 3;
                                }
                            }
                            else{
                                timerEscolha--;
                            }
                        }
                        else{
                            pausarDialogo = false;
                            dialogoAtual = 12;
                            tempoPularDialogo = 60;
                            switch(escolha){
                                case 1:
                                    strcpy(dialogos[12], "Larissa: Pode deixar, volta logo tá");
                                    strcpy(dialogos[13], "Rafael: beleza, vou tentar voltar inteiro");
                                break;
                                case 2:
                                    strcpy(dialogos[12], "Larissa: vou, acho que é mais seguro");
                                    strcpy(dialogos[13], "Rafael: beleza, volto logo então");
                                break;
                                case 3:
                                    strcpy(dialogos[12], "Larissa: mano, some daqui, me deixa em paz");
                                    strcpy(dialogos[13], "Rafael: ...");
                                break;
                            }
                        }
                    }
                }
            }
        }

        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(dialogBox);
    al_destroy_bitmap(fade);
    al_destroy_bitmap(detalheEscolhaDialogo);
    acaoAnterior = 19;
    return 1;
}
int Varanda(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente1 = NULL;
    ALLEGRO_BITMAP *frente2 = NULL;
    ALLEGRO_BITMAP *frente3 = NULL;
    ALLEGRO_BITMAP *frente4 = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    fundo = al_load_bitmap("imgs/varanda/varandaFundo.png");
    frente1 = al_load_bitmap("imgs/varanda/VarandaFrente1.png");
    frente2 = al_load_bitmap("imgs/varanda/VarandaFrente2.png");
    frente3 = al_load_bitmap("imgs/varanda/VarandaFrente3.png");
    frente4 = al_load_bitmap("imgs/varanda/VarandaFrente4.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int frames = 0;
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    char salaDaPortaS[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    if(veioDeOnde == 5){
        rafa.pos_x = 500;
    }
    else if(veioDeOnde == 13){
        rafa.pos_x = 830;
    }
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadrao(&rafa,145,959,teclas);
        if(rafa.pos_x>450 && rafa.pos_x<650){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 5;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Corredor do segundo andar");
        }
        else if(rafa.pos_x>800 && rafa.pos_x<900){
            if(teclas[2]){
                if(eventos[0] == 0){
                    acao = 18;
                }
                else if(eventos[1] != 0 && eventos[2] == 0){
                    acao = 19;
                }
                else{
                    acao = 13;
                }
                fim = true;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Quarto de hospedes");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;

        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(frames > 12){
            frames = 0;
        }
        if(frames>=0 && frames <=3){
            al_draw_bitmap(frente1,0,0,0);
        }
        else if(frames <=6){
            al_draw_bitmap(frente2,0,0,0);
        }
        else if(frames <= 9){
            al_draw_bitmap(frente3,0,0,0);
        }
        else if (frames <= 12){
            al_draw_bitmap(frente4,0,0,0);
        }
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        frames++;
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente1);
    al_destroy_bitmap(frente2);
    al_destroy_bitmap(frente3);
    al_destroy_bitmap(frente4);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    acaoAnterior = 14;
    return 1;
}
int BanheiroSegundoAndar(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    fundo = al_load_bitmap("imgs/banheiro2Andar/Banheiro2AndarFundo.png");
    frente = al_load_bitmap("imgs/banheiro2Andar/Banheiro2AndarFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    char salaDaPortaS[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 20;
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadrao(&rafa,0,347,teclas);
        if(rafa.pos_x>-50 && rafa.pos_x<10){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 5;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Corredor");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    acaoAnterior = 12;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int Cozinha(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    fundo = al_load_bitmap("imgs/cozinha/CozinhaFundo.png");
    frente = al_load_bitmap("imgs/cozinha/CozinhaFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    char salaDaPortaS[50];
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int timerEscondido = 0;
    bool escondido = false;
    bool visto = false;
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = LEFT;
    rafa.pos_x = 1100;
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        else if(escondido && timerFugaYuka <= 0 && yukaNoComodo && yukaPerseguindo && !visto){
            yukaPerseguindo = false;
            yukaNoComodo = false;
            al_stop_sample(&idYukaBackground);
            yukaBackgroundSom = false;
        }
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        if(timerEscondido>0){
            timerEscondido--;
        }
        filaPadrao(teclas);
        if(!fim)
        movimentoPadraoComEscondido(&rafa,-20,1120,teclas,&escondido);
        if(rafa.pos_x>170 && rafa.pos_x<300){
            if(teclas[2]){
                if(!escondido && timerEscondido <= 0){
                    if(yukaNoComodo)visto=true;
                    escondido = true;
                    timerEscondido = 240;
                    rafa.pos_x = 235;
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                else if(escondido && timerEscondido <= 0){
                    escondido = false;
                    timerEscondido = 240;
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
            }
            emUmaEntradaS = true;
            if(!escondido){
                strcpy(salaDaPortaS, "esconder na despensa");
            }
            else{
                strcpy(salaDaPortaS, "sair da despensa");
            }
        }
        else if(rafa.pos_x>1100 && rafa.pos_x<1200){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 2;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Hall");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if(!escondido){
                if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
                   (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                        al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        fimDeJogo = true;
                        fim = true;
                }
            }
            else if(visto){
                if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
                   (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                        al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        fimDeJogo = true;
                        fim = true;
                }
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        if(!escondido){
            al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                rafa.larguraSprite,rafa.alturaSprite,
                rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        }
        al_draw_bitmap(frente,0,0,0);
        if(escondido)al_draw_bitmap(fade,0,0,0);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            if(strcmp(salaDaPortaS, "esconder na despensa")!=0 && strcmp(salaDaPortaS, "sair da despensa")!=0){
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
            else if(timerEscondido>0){
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,30,30),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
            else{
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    acaoAnterior = 3;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int BanheiroPrimeiroAndar(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *cortinaBanheiro = NULL;
    fundo = al_load_bitmap("imgs/banheiro1Andar/Banheiro1AndarFundo.png");
    frente = al_load_bitmap("imgs/banheiro1Andar/Banheiro1AndarFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    cortinaBanheiro = al_load_sample("sons/showerCurtain.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int timerEscondido = 0;
    char salaDaPortaS[50];
    bool yukaNoComodo = false;
    bool visto = false;
    bool escondido = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 20;
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        else if(escondido && timerFugaYuka <= 0 && yukaNoComodo && yukaPerseguindo && !visto){
            yukaPerseguindo = false;
            yukaNoComodo = false;
            al_stop_sample(&idYukaBackground);
            yukaBackgroundSom = false;
        }
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        if(timerEscondido>0){
            timerEscondido--;
        }
        filaPadrao(teclas);
        if(!fim)
        movimentoPadraoComEscondido(&rafa,-10,170,teclas,&escondido);
        if(rafa.pos_x>150 && rafa.pos_x<251){
            if(teclas[2]){
                if(!escondido && timerEscondido <= 0){
                    if(yukaNoComodo)visto=true;
                    escondido = true;
                    timerEscondido = 240;
                    rafa.pos_x = 250;
                    rafa.inverte_sprite = LEFT;
                    al_play_sample(cortinaBanheiro,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                else if(escondido && timerEscondido <= 0){
                    escondido = false;
                    timerEscondido = 240;
                    rafa.pos_x = 170;
                    al_play_sample(cortinaBanheiro,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
            }
            emUmaEntradaS = true;
            if(!escondido){
                strcpy(salaDaPortaS, "esconder no box");
            }
            else{
                strcpy(salaDaPortaS, "sair do box");
            }
        }
        else if(rafa.pos_x>-20 && rafa.pos_x<30){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 2;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Hall");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if(!escondido){
                if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
                   (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                        al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        fimDeJogo = true;
                        fim = true;
                }
            }
            else if(visto){
                if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
                   (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                        al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        fimDeJogo = true;
                        fim = true;
                }
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        al_draw_bitmap(frente,0,0,0);
        if(escondido)al_draw_bitmap(fade,0,0,0);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            if(strcmp(salaDaPortaS, "esconder no box")!=0 && strcmp(salaDaPortaS, "sair do box")!=0){
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
            else if(timerEscondido>0){
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,30,30),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
            else{
                al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
            }
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }

        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    al_destroy_sample(cortinaBanheiro);
    acaoAnterior = 4;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int CorredorSegundoAndar1(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *passosEscada = NULL;
    ALLEGRO_SAMPLE *macaneta = NULL;
    ALLEGRO_TRANSFORM camera;
    fundo = al_load_bitmap("imgs/corredor2Andar1/Corredor2Andar1Fundo.png");
    frente = al_load_bitmap("imgs/corredor2Andar1/Corredor2Andar1Frente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    passosEscada = al_load_sample("sons/footstepInStairs.wav");
    macaneta = al_load_sample("sons/doorHandle.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);

    enum posicoes {RIGHT, LEFT};

    int fadeOpacidade = 255;
    int fadeFala = 0;
    int timerFala = 0;
    int opacidadeEmUmaEntradaS = 0;
    int timerMacaneta = 0;
    float cameraPosition = 0;
    char salaDaPortaS[50];
    char falaRafa[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    if(veioDeOnde == 5){
        rafa.pos_x = 10;
    }
    else if(veioDeOnde == 17){
        rafa.pos_x = 2480;
        rafa.inverte_sprite = LEFT;
    }
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        if(timerMacaneta>0){
            timerMacaneta--;
        }
        emUmaEntradaS = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadrao(&rafa,2,2908,teclas);
        if(rafa.pos_x>-50 && rafa.pos_x<30){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(passosEscada,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 5;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Corredor");
        }
        else if(rafa.pos_x>320 && rafa.pos_x<445){
            if(teclas[2]){
                if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                }
                if(timerFala <= 0){
                    timerFala = 240;
                    strcpy(falaRafa, "trancado...");
                }
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "-");
        }
        else if(rafa.pos_x>1705 && rafa.pos_x<1834){
            if(teclas[2]){
                if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                }
                if(timerFala <= 0){
                    timerFala = 240;
                    strcpy(falaRafa, "trancado...");
                }
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "-");
        }
        else if(rafa.pos_x>2407 && rafa.pos_x<2536){
            if(teclas[2]){
                if(eventos[3] != 0){
                    if(!fim){
                        al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 21;
                }
                else{
                    if(!fim){
                        al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 17;
                }

            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Quarto Yuka");
        }

        atualizaCamera(&cameraPosition, rafa.pos_x,rafa.larguraSprite);
        al_identity_transform(&camera);
        al_translate_transform(&camera, -cameraPosition,0);
        al_use_transform(&camera);

        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);

        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(timerFala>0){
            if(fadeFala<255){
                fadeFala+=5;
            }
            timerFala--;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else if(fadeFala > 100){
            fadeFala-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else{
            fadeFala = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    atualizaCamera(&cameraPosition, 0,rafa.larguraSprite);
    al_identity_transform(&camera);
    al_translate_transform(&camera, -cameraPosition,0);
    al_use_transform(&camera);

    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    al_destroy_sample(passosEscada);
    al_destroy_sample(macaneta);
    acaoAnterior = 11;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int CorredorSegundoAndar(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *passosEscada = NULL;
    ALLEGRO_SAMPLE *macaneta = NULL;
    ALLEGRO_TRANSFORM camera;
    fundo = al_load_bitmap("imgs/corredor2Andar/Corredor2AndarFundo.png");
    frente = al_load_bitmap("imgs/corredor2Andar/Corredor2AndarFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    passosEscada = al_load_sample("sons/footstepInStairs.wav");
    macaneta = al_load_sample("sons/doorHandle.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);

    enum posicoes {RIGHT, LEFT};

    int fadeOpacidade = 255;
    int fadeFala = 0;
    int timerFala = 0;
    int timerMacaneta = 0;
    char falaRafa[50];
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    float cameraPosition = 0;
    char salaDaPortaS[50];
    char salaDaPortaI[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    if(veioDeOnde == 2){
        rafa.pos_x = 10;
    }
    else if(veioDeOnde == 12){
        rafa.pos_x = 1910;
    }
    else if(veioDeOnde == 14){
        rafa.pos_x = 2900;
    }
    else if(veioDeOnde == 11){
        rafa.pos_x = 400;
    }
    else if(veioDeOnde == 15){
        rafa.pos_x = 2215;
    }
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        if(timerMacaneta>0){
            timerMacaneta--;
        }
        emUmaEntradaS = false;
        emUmaEntradaI = false;
        filaPadrao(teclas);
        if(!fim){
            movimentoPadrao(&rafa,2,2908,teclas);
        }
        if(rafa.pos_x>0 && rafa.pos_x<100){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(passosEscada,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 2;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Hall");
        }
        else if(rafa.pos_x>270 && rafa.pos_x<530){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(passosEscada,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 11;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Corredor");
        }
        else if(rafa.pos_x>700 && rafa.pos_x<830){
            if(teclas[2]){
                if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                }
                if(timerFala <= 0){
                    timerFala = 240;
                    strcpy(falaRafa, "trancado...");
                }
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "-");
        }
        else if(rafa.pos_x>1840 && rafa.pos_x<1972){
            if(teclas[2]){
                if(eventos[3]!= 0){
                    if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 12;
                }
                else{
                    if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                    }
                    if(timerFala <= 0){
                        timerFala = 240;
                        strcpy(falaRafa, "trancado...");
                    }
                }
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Banheiro");
        }
        else if(rafa.pos_x>2500 && rafa.pos_x <2640){
            if(teclas[2]){
                if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                }
                if(timerFala <= 0){
                    timerFala = 240;
                    strcpy(falaRafa, "trancado...");
                }
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Quarto de hóspedes");
        }
        else if(rafa.pos_x>2900 && rafa.pos_x <3000){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 14;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Varanda");
        }
        if(rafa.pos_x>1170 && rafa.pos_x<1300){
            if(teclas[3]){
                if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                }
                if(timerFala <= 0){
                    timerFala = 240;
                    strcpy(falaRafa, "trancado...");
                }
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "-");
        }
        else if(rafa.pos_x>2150 && rafa.pos_x<2280){
            if(teclas[3]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 15;
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Quarto de Casal");
        }

        atualizaCamera(&cameraPosition, rafa.pos_x,rafa.larguraSprite);
        al_identity_transform(&camera);
        al_translate_transform(&camera, -cameraPosition,0);
        al_use_transform(&camera);

        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);

        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                         rafa.pos_x + 50, rafa.pos_y -40,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        if(timerFala>0){
            if(fadeFala<255){
                fadeFala+=5;
            }
            timerFala--;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else if(fadeFala > 100){
            fadeFala-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else{
            fadeFala = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    atualizaCamera(&cameraPosition, 0,rafa.larguraSprite);
    al_identity_transform(&camera);
    al_translate_transform(&camera, -cameraPosition,0);
    al_use_transform(&camera);

    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    al_destroy_sample(passosEscada);
    al_destroy_sample(macaneta);
    acaoAnterior = 5;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int CorredorPrimeiroAndar(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *macaneta = NULL;
    fundo = al_load_bitmap("imgs/corredor1Andar/Corredor1AndarFundo.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    macaneta = al_load_sample("sons/doorHandle.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int fadeOpacidade = 255;
    int fadeFala = 0;
    int timerFala = 0;
    int timerMacaneta = 0;
    char falaRafa[50];
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    char salaDaPortaI[50];
    char salaDaPortaS[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 1000;
    if(veioDeOnde == 8){
        rafa.pos_x = -20;
    }
    else if(veioDeOnde == 10){
        rafa.pos_x = 1120;
        rafa.inverte_sprite = LEFT;
    }
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        emUmaEntradaI = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadrao(&rafa,-20,1120,teclas);
        if(rafa.pos_x>-50 && rafa.pos_x<20){
            if(teclas[2]){
                if(eventos[2]!= 0 && eventos[3] == 0){
                    if(!fim){
                        al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 20;
                }
                else if(eventos[3] != 0){
                    if(!fim){
                        al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 8;
                }
                else{
                    if(timerMacaneta<=0){
                        al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        timerMacaneta = 120;
                    }
                    if(timerFala <= 0){
                        timerFala = 240;
                        strcpy(falaRafa, "trancado...");
                    }
                }
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Escritório");
        }
        if(rafa.pos_x>1080 && rafa.pos_x<1200){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 10;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Sala de Jantar");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        if(timerFala>0){
            if(fadeFala<255){
                fadeFala+=5;
            }
            timerFala--;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else if(fadeFala > 100){
            fadeFala-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }

        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }

        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    al_destroy_sample(macaneta);
    acaoAnterior = 9;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int Biblioteca(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *macaneta = NULL;
    fundo = al_load_bitmap("imgs/biblioteca/BibliotecaFundo.png");
    frente = al_load_bitmap("imgs/biblioteca/BibliotecaFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    macaneta = al_load_sample("sons/doorHandle.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int fadeOpacidade = 255;
    int fadeFala = 0;
    int timerFala = 0;
    int timerMacaneta = 0;
    char falaRafa[50];
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    char salaDaPortaI[50];
    char salaDaPortaS[50];
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    bool yukaNoComodo = false;
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 550;
    if(veioDeOnde == 2){
        rafa.pos_x = 550;
    }
    else if(veioDeOnde == 8){
        rafa.pos_x = 1120;
        rafa.inverte_sprite = LEFT;
    }
    else if(veioDeOnde == 7){
        iniciaYuka(&yukaGlobal);
        yukaPerseguindo = true;
        yukaBackgroundSom = true;
        al_play_sample(yukaBackground,1,0.5,1,ALLEGRO_PLAYMODE_LOOP,&idYukaBackground);
        yukaNoComodo = true;
        yukaGlobal.inverte_sprite = 0;
        yukaGlobal.pos_x = 1000;
        timerFugaYuka = 700;
        timerYukaEntrar = 0;
        rafa.pos_x = 650;
        rafa.inverte_sprite = RIGHT;
    }
    if(veioDeOnde != 7){
        if(yukaPerseguindo){
            iniciaYuka(&yukaGlobal);
            yukaGlobal.pos_x = rafa.pos_x;
        }
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        if(timerMacaneta>0){
            timerMacaneta--;
        }
        emUmaEntradaS = false;
        emUmaEntradaI = false;
        filaPadrao(teclas);
        if(!fim){
            movimentoPadrao(&rafa,-20,1120,teclas);
        }
        if(rafa.pos_x>480 && rafa.pos_x<610){
            if(teclas[3]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 2;
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Corredor");
        }
        if(rafa.pos_x>1080 && rafa.pos_x<1200){
            if(teclas[2]){
                if(eventos[3]!= 0){
                    if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 8;
                }
                else{
                    if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                    }
                    if(timerFala <= 0){
                        timerFala = 240;
                        strcpy(falaRafa, "trancado...");
                    }
                }
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Escritório");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                            rafa.larguraSprite,rafa.alturaSprite,
                            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        if(timerFala>0){
            if(fadeFala<255){
                fadeFala+=5;
            }
            timerFala--;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else if(fadeFala > 100){
            fadeFala-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else{
            fadeFala = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }

        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    al_destroy_sample(macaneta);
    acaoAnterior = 6;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int BibliotecaAnim(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *dialogBox = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_BITMAP *detalheEscolhaDialogo = NULL;
    ALLEGRO_SAMPLE *horrorSound = NULL;
    ALLEGRO_SAMPLE *portaAbrindo = NULL;
    dialogBox = al_load_bitmap("imgs/dialogBox/DialogBox.png");
    fundo = al_load_bitmap("imgs/biblioteca/BibliotecaFundo.png");
    frente = al_load_bitmap("imgs/biblioteca/BibliotecaFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    detalheEscolhaDialogo = al_load_bitmap("imgs/efeitos/detalheEscolhaDialogo.png");
    horrorSound = al_load_sample("sons/horrorSounds/Bam.wav");
    portaAbrindo = al_load_sample("sons/horrorSounds/horrorDoor.wav");
    struct personagem rafa;
    struct personagem ilan;
    struct personagem yuka;

    iniciaYuka(&yuka);
    iniciaRafa(&rafa);
    iniciaIlan(&ilan);
    char dialogos[16][100];
    strcpy(dialogos[0], "Rafael: eae Ilan, achei a Larissa");
    strcpy(dialogos[1], "Ilan: cadê ela ?");
    strcpy(dialogos[2], "Rafael: ta no segundo andar, vamo lá chamar ela pra irmos embora");
    strcpy(dialogos[3], "Ilan: vamo lá, mas porque ela não desceu com você ?");
    strcpy(dialogos[4], "Rafael: sei lá, só vamo logo, esse lugar ta me deixando desconfortável");
    strcpy(dialogos[5], "Ilan: MEU DEUS RAFA ATRÁS DE TU!!!!");
    strcpy(dialogos[6], "Rafael: OQUE !?? ONDE !!????");
    strcpy(dialogos[7], "Ilan: GELOOOOOOU");
    strcpy(dialogos[8], "Rafael: se é bobo ? Vamo sair logo daqui !");
    strcpy(dialogos[9], "Ilan: macho tu ta muito tenso, tu acredita mesmo nesse negócio de fantasma ?");

    strcpy(dialogos[10], "Escolha 1: não é que eu acredite, mas esse lugar é muito bizarro");
    strcpy(dialogos[11], "Escolha 2: acredito sim, além disso, você não ta sentindo um frio estranho ?");
    strcpy(dialogos[12], "Escolha 3: não enche cara, acredito no que eu quiser...");

    strcpy(dialogos[15], "Ilan: MEU DEUS OQUE É ISSO ?? CORRE RAFA !!");

    enum posicoes {RIGHT, LEFT};
    int escolha = 1;
    int detalheEscolhaOpacidade = 50;
    bool aumentaOpacidadeEscolha = true;
    bool escolhaFeita = false;
    int dialogoAtual = 0;
    int tempoPularDialogo = 60;
    int opacidadedb = 0;
    int fadeOpacidade = 255;
    int timerDialogo = 0;
    int timerTrocarEscolha = 0;
    int timerEscolha = 0;
    int timerSomPorta = 0;
    int timerFalaFinalIlan = 0;
    bool inicio = true;
    bool fim = false;
    bool teclas[3] = {false, false, false};
    bool pausarDialogo = false;
    bool dialogBoxAtiva = false;
    bool dialogoAcabou = false;
    bool somPortaTocou = false;
    bool ilanFalaFinal = false;
    bool yukaApareceu = false;
    bool ilanSaiu = false;
    ilan.pos_x = 700;
    ilan.inverte_sprite = LEFT;
    rafa.pos_x = 550;
    rafa.inverte_sprite = RIGHT;
    yuka.pos_x = 1050;
    yuka.inverte_sprite = 0;
    yuka.frames_sprite = 10;

    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerTrocarEscolha>0){
            timerTrocarEscolha--;
        }
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_UP){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = false;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = false;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    teclas[0] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                    teclas[1] = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                    teclas[2] = true;
                }
            }
        }
        if(rafa.andando || rafa.correndo){
            rafa.linha_atual = rafa.andando?1:2;
            rafa.velocidade = rafa.andando?3:6;
            rafa.colunas_sprite = 8;
            rafa.frames_sprite = 6;
        }
        else{
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.colunas_sprite = 5;
            rafa.frames_sprite = 25;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(!ilanSaiu){
            if(ilan.andando || ilan.correndo){
                ilan.linha_atual = ilan.andando?1:2;
                ilan.velocidade = ilan.andando?3:6;
                ilan.colunas_sprite = 8;
                ilan.frames_sprite = 6;
            }
            else{
                ilan.velocidade = 0;
                ilan.linha_atual = 0;
                ilan.colunas_sprite = 5;
                ilan.frames_sprite = 25;
                if(ilan.coluna_atual>4){
                    ilan.coluna_atual = 0;
                }
            }
        }

        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1)%rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(!ilanSaiu){
            if(ilan.cont_frames > ilan.frames_sprite){
                ilan.cont_frames = 0;
                ilan.coluna_atual = (ilan.coluna_atual+1)%ilan.colunas_sprite;
            }
            else{
                ilan.cont_frames++;
            }
        }
        if(yukaApareceu){
            yuka.pos_x-= 0.2;
            if(yuka.cont_frames > yuka.frames_sprite){
                yuka.cont_frames = 0;
                yuka.coluna_atual = (yuka.coluna_atual+1)%yuka.colunas_sprite;
            }
            else{
                yuka.cont_frames++;
            }
        }
        if(timerTrocarEscolha <= 0){
            if(teclas[1]){
                if(escolha > 1){
                    escolha--;
                }
                timerTrocarEscolha = 10;
            }
            else if(teclas[2]){
                if(escolha < 3){
                    escolha++;
                }
                timerTrocarEscolha = 10;
            }
        }

        rafa.regiaoXdaFolha = rafa.coluna_atual*rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual*rafa.alturaSprite;
        if(!ilanSaiu){
            ilan.regiaoXdaFolha = ilan.coluna_atual*ilan.larguraSprite;
            ilan.regiaoYdaFolha = ilan.linha_atual*ilan.alturaSprite;
        }
        if(yukaApareceu){
            yuka.regiaoXdaFolha = yuka.coluna_atual*yuka.larguraSprite;
            yuka.regiaoYdaFolha = yuka.linha_atual*yuka.alturaSprite;
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo,0,0,0);

        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                              rafa.larguraSprite,rafa.alturaSprite,
                              rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(!ilanSaiu){
            al_draw_bitmap_region(ilan.spritesheet,ilan.regiaoXdaFolha,ilan.regiaoYdaFolha,
                                ilan.larguraSprite,ilan.alturaSprite,
                                ilan.pos_x,ilan.pos_y,ilan.inverte_sprite);
        }

        if(yukaApareceu){
            al_draw_bitmap_region(yuka.spritesheet,yuka.regiaoXdaFolha,yuka.regiaoYdaFolha,
                                yuka.larguraSprite,yuka.alturaSprite,
                                yuka.pos_x,yuka.pos_y,yuka.inverte_sprite);
        }
        al_draw_bitmap(frente,0,0,0);
        if(dialogBoxAtiva){
            if(opacidadedb<255){
                opacidadedb+=5;
            }
            al_draw_tinted_bitmap(dialogBox,al_map_rgb(opacidadedb,opacidadedb,opacidadedb),0,500,0);
        }
        if(!inicio){
            if(rafa.pos_x < 650){
                rafa.andando = true;
                rafa.pos_x += rafa.velocidade;
            }
            else if(!dialogBoxAtiva){
                rafa.andando = false;
                dialogBoxAtiva = true;
            }
            if(opacidadedb>= 255)
            {
                timerDialogo = timerDialogo>0?timerDialogo-1:0;
                if((dialogoAtual != 9 || timerDialogo > 0) && !dialogoAcabou){
                    al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[dialogoAtual]);
                }
                if(tempoPularDialogo>0){
                    tempoPularDialogo--;
                }
                if(dialogoAtual == 14 && timerDialogo <= 0){
                    dialogoAcabou = true;
                }
                if(!pausarDialogo){
                    if(tempoPularDialogo <= 0){
                        if(dialogoAtual != 9 && dialogoAtual != 4){
                            timerEscolha = 30;
                            al_draw_text(pixelFontPequena,al_map_rgb(200,200,200),1000,580,ALLEGRO_ALIGN_CENTER,"pressione espaço para pular o dialogo");
                        }
                        if(dialogoAtual == 4){
                            pausarDialogo = true;
                            tempoPularDialogo = 120;
                        }
                        if(teclas[0]){
                            if(dialogoAtual != 9 && dialogoAtual != 4){
                                tempoPularDialogo = 60;
                                dialogoAtual++;
                            }
                        }
                        if(dialogoAtual == 9){
                            pausarDialogo = true;
                            timerDialogo = 200;
                        }
                        if(dialogoAtual == 14){
                            timerDialogo = 150;
                            pausarDialogo = true;
                        }
                    }
                }
                else if(dialogoAtual == 4){
                    if(tempoPularDialogo <= 0){
                        al_play_sample(horrorSound,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                        dialogoAtual++;
                        pausarDialogo = false;
                        tempoPularDialogo = 60;
                    }
                }
                else if(dialogoAtual == 9){
                    if(timerDialogo <= 0){
                        if(!escolhaFeita){
                            if(detalheEscolhaOpacidade <= 50){
                                aumentaOpacidadeEscolha = true;
                            }
                            else if(detalheEscolhaOpacidade >= 150){
                                aumentaOpacidadeEscolha = false;
                            }
                            if(aumentaOpacidadeEscolha){
                                detalheEscolhaOpacidade++;
                            }
                            else{
                                detalheEscolhaOpacidade--;
                            }
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[10]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,540,ALLEGRO_ALIGN_LEFT,dialogos[11]);
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,560,ALLEGRO_ALIGN_LEFT,dialogos[12]);
                            switch(escolha){
                                case 1:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,516,0);
                                break;
                                case 2:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,536,0);
                                break;
                                case 3:
                                    al_draw_tinted_bitmap(detalheEscolhaDialogo,al_map_rgba(0,0,0,detalheEscolhaOpacidade),0,556,0);
                                break;
                            }
                            if(timerEscolha<=0){
                                if(teclas[0]){
                                    escolhaFeita = true;
                                    eventos[1] = escolha;
                                    eventosTerminados = 2;
                                }
                            }
                            else{
                                timerEscolha--;
                            }
                        }
                        else{
                            pausarDialogo = false;
                            dialogoAtual = 13;
                            tempoPularDialogo = 60;
                            switch(escolha){
                                case 1:
                                    strcpy(dialogos[13], "Ilan: eu sei, o lugar parece estar mexendo com a sua cabeça");
                                    strcpy(dialogos[14], "Rafael: pois é, eu não me sinto muito bem aqui");
                                break;
                                case 2:
                                    strcpy(dialogos[13], "Ilan: macho, 35 graus pra mim é frio, claro que eu to com frio agora");
                                    strcpy(dialogos[14], "Rafael: mas não era pra estar tão frio quanto está agora");
                                break;
                                case 3:
                                    strcpy(dialogos[13], "Ilan: credo Rafa, não falo mais nisso ...");
                                    strcpy(dialogos[14], "Rafael: beleza...");
                                break;
                            }
                        }
                    }
                }
                else if(dialogoAtual == 14){
                    if(timerDialogo <= 0){
                        if(timerFalaFinalIlan>0){
                            timerFalaFinalIlan--;
                        }
                        if(ilanFalaFinal){
                            al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[15]);
                        }
                        if(!yukaApareceu){
                            if(timerSomPorta>0){
                                timerSomPorta--;
                            }
                            if(!somPortaTocou){
                                timerSomPorta = 300;
                                somPortaTocou = true;
                                al_play_sample(portaAbrindo,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                                ilan.inverte_sprite = RIGHT;
                            }
                            else if(timerSomPorta <= 0){
                                yukaApareceu = true;
                                al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                            }
                        }
                        else if(!ilanFalaFinal){
                            ilanFalaFinal = true;
                            timerFalaFinalIlan = 60;
                        }
                        else if(timerFalaFinalIlan == 0){
                            if(ilan.pos_x>550){
                                ilan.inverte_sprite = LEFT;
                                ilan.correndo=true;
                                ilan.pos_x-=ilan.velocidade;
                            }
                            else if(!ilanSaiu){
                                ilan.andando = false;
                                ilanSaiu = true;
                            }
                            else{
                                fim = true;
                                acao = 6;
                            }
                        }
                    }
                }
            }
        }
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(dialogBox);
    al_destroy_bitmap(fade);
    al_destroy_bitmap(detalheEscolhaDialogo);
    al_destroy_sample(horrorSound);
    acaoAnterior = 7;
    return 1;
}
int Escritorio(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    fundo = al_load_bitmap("imgs/escritorio/EscritorioFundo.png");
    frente = al_load_bitmap("imgs/escritorio/EscritorioFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    enum posicoes {RIGHT, LEFT};

    struct personagem rafa;
    struct personagem ilan;
    iniciaRafa(&rafa);
    if(eventos[3] != 0){
        iniciaIlan(&ilan);
        ilan.pos_x = 550;
        ilan.inverte_sprite = RIGHT;
    }
    int fadeOpacidade = 255;
    int fadeFala = 0;
    int timerFala = 0;
    char falaRafa[100];
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    char salaDaPortaI[50];
    char salaDaPortaS[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 1000;
    if(veioDeOnde == 6){
        rafa.pos_x = 290;
    }
    else  if(veioDeOnde == 9){
        rafa.pos_x = 1100;
        rafa.inverte_sprite = LEFT;
    }
    else if(veioDeOnde == 20){
        rafa.inverte_sprite = LEFT;
        rafa.pos_x = 610;
    }
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        emUmaEntradaI = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadrao(&rafa,-20,1120,teclas);
        if(eventos[3] != 0){
            if(ilan.andando || ilan.correndo){
                ilan.linha_atual = ilan.andando?1:2;
                ilan.velocidade = ilan.andando?3:6;
                ilan.colunas_sprite = 8;
                ilan.frames_sprite = 6;
            }
            else{
                ilan.velocidade = 0;
                ilan.linha_atual = 0;
                ilan.colunas_sprite = 5;
                ilan.frames_sprite = 25;
                if(ilan.coluna_atual>4){
                    ilan.coluna_atual = 0;
                }
            }
            if(ilan.cont_frames > ilan.frames_sprite){
                ilan.cont_frames = 0;
                ilan.coluna_atual = (ilan.coluna_atual+1)%ilan.colunas_sprite;
            }
            else{
                ilan.cont_frames++;
            }
            ilan.regiaoXdaFolha = ilan.coluna_atual*ilan.larguraSprite;
            ilan.regiaoYdaFolha = ilan.linha_atual*ilan.alturaSprite;
        }
        if(rafa.pos_x>225 && rafa.pos_x<355){
            if(teclas[3]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 6;
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Biblioteca");
        }
        if(rafa.pos_x>1080 && rafa.pos_x<1200){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 9;
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Corredor");
        }

        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        if(eventos[3] != 0){
        al_draw_bitmap_region(ilan.spritesheet,ilan.regiaoXdaFolha,ilan.regiaoYdaFolha,
                ilan.larguraSprite,ilan.alturaSprite,
                ilan.pos_x,ilan.pos_y,ilan.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);

        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        if(timerFala>0){
            if(fadeFala<255){
                fadeFala+=5;
            }
            timerFala--;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else if(fadeFala > 100){
            fadeFala-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else{
            fadeFala = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }

        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    acaoAnterior = 8;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int SalaDeJantar(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    fundo = al_load_bitmap("imgs/salaDeJantar/SalaDeJantarFundo.png");
    frente = al_load_bitmap("imgs/salaDeJantar/SalaDeJantarFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);
    enum posicoes {RIGHT, LEFT};
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    char salaDaPortaI[50];
    char salaDaPortaS[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 1000;
    if(veioDeOnde == 2){
        rafa.pos_x = -20;
    } else  if(veioDeOnde == 9){
        rafa.pos_x = 130;
    }
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        emUmaEntradaS = false;
        emUmaEntradaI = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadrao(&rafa,-20,1120,teclas);
        if(rafa.pos_x>-50 && rafa.pos_x<20){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 2;
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Hall");
        }
         if(rafa.pos_x>65 && rafa.pos_x<195){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 9;
            }
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Corredor");
        }

        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }

        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    acaoAnterior = 10;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int Hall(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *passosEscada = NULL;
    ALLEGRO_SAMPLE *macaneta = NULL;
    ALLEGRO_TRANSFORM camera;
    fundo = al_load_bitmap("imgs/hall/HallFundo.png");
    frente = al_load_bitmap("imgs/hall/HallFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    passosEscada = al_load_sample("sons/footstepInStairs.wav");
    macaneta = al_load_sample("sons/doorHandle.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);

    enum posicoes {RIGHT, LEFT};

    int fadeOpacidade = 255;
    int fadeFala = 0;
    int timerFala = 0;
    int timerMacaneta = 0;
    char falaRafa[100];
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    float cameraPosition = 0;
    char salaDaPortaS[50];
    char salaDaPortaI[50];
    bool yukaNoComodo = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    if(veioDeOnde == 1){
        rafa.pos_x = 1400;
    }
    else if(veioDeOnde == 3){
        rafa.pos_x = 10;
    }
    else if(veioDeOnde == 4){
        rafa.pos_x = 545;
    }
    else if(veioDeOnde == 5){
        rafa.pos_x = 1450;
    }
    else if(veioDeOnde == 6){
        rafa.pos_x = 2335;
    }
    else if(veioDeOnde == 10){
        rafa.pos_x = 2910;
        rafa.inverte_sprite = LEFT;
    }
    if(yukaPerseguindo){
        iniciaYuka(&yukaGlobal);
        yukaGlobal.pos_x = rafa.pos_x;
    }
    while(!trocarCena && !sair){
        iniciaTimer();
        if(timerFugaYuka >= 0)timerFugaYuka--;
        if(yukaPerseguindo && !yukaNoComodo && timerYukaEntrar <= 0){
            yukaNoComodo = true;
            al_play_sample(yukaScream,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
        }
        else if(yukaPerseguindo && !yukaNoComodo){
            timerYukaEntrar--;
        }
        if(timerMacaneta>0){
            timerMacaneta--;
        }
        emUmaEntradaS = false;
        emUmaEntradaI = false;
        filaPadrao(teclas);
        if(!fim)
        movimentoPadrao(&rafa,2,2908,teclas);
        if(rafa.pos_x>-10 && rafa.pos_x<10){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 3;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Cozinha");
        }
        else if(rafa.pos_x>480 && rafa.pos_x<610){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 4;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Banheiro");
        }
        else if(rafa.pos_x>1300 && rafa.pos_x<1600){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(passosEscada,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 5;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Corredor do segundo andar");
        }

        else if(rafa.pos_x>2270 && rafa.pos_x<2400){
            if(teclas[2]){
                if(eventos[1]==0 && eventos[0]!=0){
                    if(!fim){
                        al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 7;
                }
                else if(eventos[1]!=0){
                    if(!fim){
                        al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 6;
                }
                else{
                    timerFala = 150;
                    strcpy(falaRafa, "O Ilan acabou de entrar ai, melhor eu ir procurar em outro lugar");
                }
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Biblioteca");
        }
        else if(rafa.pos_x>2900 && rafa.pos_x<3000){
            if(teclas[2]){
                if(eventos[2]!= 0){
                    if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    fim = true;
                    acao = 10;
                }
                else{
                    if(timerMacaneta<=0){
                    al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    timerMacaneta = 120;
                    }
                    if(timerFala <= 0){
                        timerFala = 240;
                        strcpy(falaRafa, "trancado...");
                    }
                }
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Sala de jantar");
        }

        if(rafa.pos_x>1350 && rafa.pos_x <1550){
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "Saida");
        }

        atualizaCamera(&cameraPosition, rafa.pos_x,rafa.larguraSprite);
        al_identity_transform(&camera);
        al_translate_transform(&camera, -cameraPosition,0);
        al_use_transform(&camera);

        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        if(yukaNoComodo && !fim){
            yukaGlobal.inverte_sprite = yukaGlobal.pos_x > rafa.pos_x?0:1;
            yukaGlobal.pos_x = yukaGlobal.pos_x > rafa.pos_x?
                yukaGlobal.pos_x-yukaGlobal.velocidade:
                yukaGlobal.pos_x+yukaGlobal.velocidade;
            if(yukaGlobal.cont_frames > yukaGlobal.frames_sprite){
                yukaGlobal.cont_frames = 0;
                yukaGlobal.coluna_atual = (yukaGlobal.coluna_atual+1)%yukaGlobal.colunas_sprite;
            }
            else{
                yukaGlobal.cont_frames++;
            }
            yukaGlobal.regiaoXdaFolha = yukaGlobal.coluna_atual*yukaGlobal.larguraSprite;
            yukaGlobal.regiaoYdaFolha = yukaGlobal.linha_atual*yukaGlobal.alturaSprite;
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
            if((yukaGlobal.pos_x + 70 >= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 <= rafa.pos_x - 30)||
               (yukaGlobal.pos_x + 70 <= rafa.pos_x + 30 && yukaGlobal.pos_x - 70 >= rafa.pos_x - 30)){
                    al_play_sample(gritoMorte,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                    fimDeJogo = true;
                    fim = true;
            }
        }
        else if(yukaNoComodo && fim){
            al_draw_bitmap_region(yukaGlobal.spritesheet,yukaGlobal.regiaoXdaFolha,yukaGlobal.regiaoYdaFolha,
                                yukaGlobal.larguraSprite,yukaGlobal.alturaSprite,
                                yukaGlobal.pos_x,yukaGlobal.pos_y,yukaGlobal.inverte_sprite);
        }
        if(emUmaEntradaS){
            if(opacidadeEmUmaEntradaS<255){
                opacidadeEmUmaEntradaS+=5;
            }
            if(opacidadeEmUmaEntradaS>255){
                opacidadeEmUmaEntradaS = 255;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                    rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);

        }
        else if(opacidadeEmUmaEntradaS > 100){
            opacidadeEmUmaEntradaS-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS,opacidadeEmUmaEntradaS),
                         rafa.pos_x + 50, rafa.pos_y -50,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaS);
        }
        else{
            opacidadeEmUmaEntradaS = 0;
        }
        if(emUmaEntradaI){
            if(opacidadeEmUmaEntradaI<255){
                opacidadeEmUmaEntradaI+=5;
            }
            if(opacidadeEmUmaEntradaI>255){
                opacidadeEmUmaEntradaI = 255;
            }
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                         rafa.pos_x + 50, rafa.pos_y -40,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else if(opacidadeEmUmaEntradaI > 100){
            opacidadeEmUmaEntradaI-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI,opacidadeEmUmaEntradaI),
                         rafa.pos_x + 50, rafa.pos_y -40,ALLEGRO_ALIGN_CENTER, "%s", salaDaPortaI);
        }
        else{
            opacidadeEmUmaEntradaI = 0;
        }
        if(timerFala>0){
            if(fadeFala<255){
                fadeFala+=5;
            }
            timerFala--;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else if(fadeFala > 100){
            fadeFala-=5;
            al_draw_textf(pixelFontPequena,al_map_rgb(fadeFala,fadeFala,fadeFala),rafa.pos_x+50,rafa.pos_y -20,ALLEGRO_ALIGN_CENTER,"%s",falaRafa);
        }
        else{
            fadeFala = 0;
        }
        al_draw_bitmap(frente,0,0,0);
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
            al_rest(3);
        }
        al_flip_display();
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    atualizaCamera(&cameraPosition, 0,rafa.larguraSprite);
    al_identity_transform(&camera);
    al_translate_transform(&camera, -cameraPosition,0);
    al_use_transform(&camera);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    al_destroy_sample(passosEscada);
    al_destroy_sample(macaneta);
    acaoAnterior = 2;
    if(yukaPerseguindo)timerYukaEntrar = temporizaDistancia(rafa.pos_x, yukaGlobal.pos_x);
    return 1;
}
int HallAnim(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *dialogBox = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *portaTrancando = NULL;
    ALLEGRO_SAMPLE *chuva = NULL;
    ALLEGRO_SAMPLE *macaneta = NULL;
    ALLEGRO_SAMPLE *vasoQuebrando = NULL;
    dialogBox = al_load_bitmap("imgs/dialogBox/DialogBox.png");
    fundo = al_load_bitmap("imgs/hall/HallFundo.png");
    frente = al_load_bitmap("imgs/hall/HallFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    portaTrancando = al_load_sample("sons/doorLock.wav");
    chuva = al_load_sample("sons/rainBackground.wav");
    macaneta = al_load_sample("sons/doorHandle.wav");
    vasoQuebrando = al_load_sample("sons/vasoQuebrando.wav");
    struct personagem rafa;
    struct personagem ilan;

    iniciaRafa(&rafa);
    iniciaIlan(&ilan);
    int dialogoAtual = 0;
    char dialogos[13][100];
    int tempoPularDialogo = 0;
    strcpy(dialogos[0], "Ilan: ae Rafa, que mansão mais estranha, tu não acha ?");
    strcpy(dialogos[1], "Rafael: pois é, tem algo de errado, tá muito frio aqui dentro!");
    strcpy(dialogos[2], "Ilan: sim, ae que que tu acha da gente se separar pra procurarmos a Larissa ?");
    strcpy(dialogos[3], "Rafael: sei não em, é ai que a galera morre nos filmes");
    strcpy(dialogos[4], "Ilan: ta é doido Rafa, tem nada aqui não ma");
    strcpy(dialogos[5], "Rafael: a Larissa tava falando que tinha uns negócios estranhos aqui");
    strcpy(dialogos[6], "Ilan: me deixa de bobagem pô, você sabe que fantasmas não existem");
    strcpy(dialogos[7], "Rafael: mano impressão minha ou a porta trancou ?");
    strcpy(dialogos[8], "Ilan: eu ouvi também, vê ai macho");
    strcpy(dialogos[9], "Rafael: trancada...");
    strcpy(dialogos[10], "Rafael: que foi isso ?");
    strcpy(dialogos[11], "Ilan: alguma coisa caiu no outro cômodo, vou lá dar uma olhada");
    strcpy(dialogos[12], "Rafael: toma cuidado Ilan e vê se não demora");
    int ato = 0;
    int opacidadedb = 0;
    int fadeOpacidade = 255;
    int timer = 0;
    bool inicio = true;
    bool fim = false;
    bool pressionado = false;
    bool pausarDialogo = false;
    bool tocando = false;
    bool ato2okay = false;
    rafa.pos_x = 500;
    ilan.pos_x = 600;


    al_play_sample(chuva,0.7,0.5,1,ALLEGRO_PLAYMODE_LOOP,NULL);
    while(!trocarCena && !sair){
        iniciaTimer();
        pressionado = false;
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    pressionado = true;
                }
            }
        }
        if(ato == 1){
            rafa.andando = true;
            rafa.inverte_sprite = 1;
            ilan.andando = true;
            ilan.inverte_sprite = 0;
        }
        if(ato == 2 && !ato2okay){
            ato2okay = true;
            rafa.andando = false;
            ilan.andando = false;
            rafa.inverte_sprite = 0;
            ilan.inverte_sprite = 1;
        }
        if(rafa.andando || rafa.correndo){
            rafa.linha_atual = rafa.andando?1:2;
            rafa.velocidade = rafa.andando?3:6;
            rafa.colunas_sprite = 8;
            rafa.frames_sprite = 6;
        }
        else{
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.colunas_sprite = 5;
            rafa.frames_sprite = 25;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(ilan.andando || ilan.correndo){
            ilan.linha_atual = ilan.andando?1:2;
            ilan.velocidade = ilan.andando?3:6;
            ilan.colunas_sprite = 8;
            ilan.frames_sprite = 6;
        }
        else{
            ilan.velocidade = 0;
            ilan.linha_atual = 0;
            ilan.colunas_sprite = 5;
            ilan.frames_sprite = 25;
            if(ilan.coluna_atual>4){
                ilan.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1)%rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(ilan.cont_frames > ilan.frames_sprite){
            ilan.cont_frames = 0;
            ilan.coluna_atual = (ilan.coluna_atual+1)%ilan.colunas_sprite;
        }
        else{
            ilan.cont_frames++;
        }

        if(ato == 1){
            if(rafa.pos_x>350)rafa.pos_x -= rafa.velocidade;
            else{
                ato = 2;
            }
            if(ilan.pos_x<750)ilan.pos_x += ilan.velocidade;
            else{
                ato = 2;
            }
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual*rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual*rafa.alturaSprite;

        ilan.regiaoXdaFolha = ilan.coluna_atual*ilan.larguraSprite;
        ilan.regiaoYdaFolha = ilan.linha_atual*ilan.alturaSprite;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo,-900,0,0);
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                              rafa.larguraSprite,rafa.alturaSprite,
                              rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        al_draw_bitmap_region(ilan.spritesheet,ilan.regiaoXdaFolha,ilan.regiaoYdaFolha,
                              ilan.larguraSprite,ilan.alturaSprite,
                              ilan.pos_x,ilan.pos_y,ilan.inverte_sprite);
        al_draw_bitmap(frente,-900,0,0);
        if(ato == 2){
            if(opacidadedb <255){
                opacidadedb+=5;
            }
            al_draw_tinted_bitmap(dialogBox,al_map_rgb(opacidadedb,opacidadedb,opacidadedb),0,500,0);
            if(opacidadedb >=255){
                al_draw_text(pixelFont,al_map_rgb(200,200,200),50,520,ALLEGRO_ALIGN_LEFT,dialogos[dialogoAtual]);

                if(!pausarDialogo){
                    tempoPularDialogo ++;
                    if(tempoPularDialogo>= 60){
                        al_draw_text(pixelFontPequena,al_map_rgb(200,200,200),1000,580,ALLEGRO_ALIGN_CENTER,"pressione espaço para pular o dialogo");
                        if(pressionado){
                            tempoPularDialogo = 0;
                            dialogoAtual++;
                        }
                    }
                    if(dialogoAtual == 6){
                        pausarDialogo = true;
                    }
                    else if(dialogoAtual == 8){
                        pausarDialogo = true;
                    }
                    else if (dialogoAtual == 9){
                        pausarDialogo = true;
                    }
                    else if (dialogoAtual>=12){
                        pausarDialogo = true;
                    }
                }
                else{
                    if(dialogoAtual == 6){
                        if(!tocando){
                            al_play_sample(portaTrancando,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                            tocando = true;
                        }
                        timer++;
                        if(timer >= 150){
                            dialogoAtual++;
                            timer = 0;
                            pausarDialogo = false;
                            tocando = false;
                        }
                    }
                    else if(dialogoAtual == 8){
                        if(rafa.pos_x < 500 && timer == 0){
                            rafa.andando = true;
                            rafa.pos_x += rafa.velocidade;
                        }
                        else{
                            rafa.andando = false;
                            if(timer == 0){
                                al_play_sample(macaneta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,NULL);
                            }
                            timer++;
                            if(timer >= 80){
                                pausarDialogo = false;
                                dialogoAtual++;
                                timer = 0;
                            }
                        }
                    }
                    else if(dialogoAtual == 9){
                        if(timer == 40){
                            al_play_sample(vasoQuebrando,0.7,0.8,1,ALLEGRO_PLAYMODE_ONCE,NULL);
                        }
                        timer++;
                        if(timer >= 160){
                            pausarDialogo = false;
                            dialogoAtual++;
                            timer = 0;
                        }
                    }
                    else if(dialogoAtual >= 12){
                        if(ilan.pos_x < 1300 && timer == 0){
                            ilan.inverte_sprite = 0;
                            ilan.andando = true;
                            ilan.pos_x += ilan.velocidade;
                        }
                        else{
                            ilan.andando = false;
                            fim = true;
                            acao = 2;
                        }
                    }
                }
            }
        }
        if(inicio){
            if(fadeOpacidade>0){
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade -= 5;
            }
            else{
                inicio = false;
                fadeOpacidade = 0;
            }
        }
        else if(fim){
            if(fadeOpacidade<255){
                if(fadeOpacidade > 255){
                    fadeOpacidade = 255;
                }
                al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
                fadeOpacidade += 5;
            }
            else{
                trocarCena = true;
                fim = false;
            }
        }
        if(trocarCena){
            al_draw_bitmap(fade,0,0,0);
        }
        al_flip_display();
        ato = ato==0?1:ato;
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_sample(chuva);
    al_destroy_sample(vasoQuebrando);
    al_destroy_bitmap(dialogBox);
    al_destroy_sample(macaneta);
    al_destroy_sample(portaTrancando);
    al_destroy_bitmap(fade);
    acaoAnterior = 1;
    return 1;
}
int Menu(){
    ALLEGRO_BITMAP *fundoMenu1_1 = NULL;
    ALLEGRO_BITMAP *fundoMenu1_2 = NULL;
    ALLEGRO_BITMAP *fundoMenu1_3 = NULL;
    ALLEGRO_BITMAP *fundoMenu1_4 = NULL;

    ALLEGRO_BITMAP *fundoMenu2_1 = NULL;
    ALLEGRO_BITMAP *fundoMenu2_2 = NULL;
    ALLEGRO_BITMAP *fundoMenu2_3 = NULL;
    ALLEGRO_BITMAP *fundoMenu2_4 = NULL;

    ALLEGRO_BITMAP *fundoMenu3_1 = NULL;
    ALLEGRO_BITMAP *fundoMenu3_2 = NULL;
    ALLEGRO_BITMAP *fundoMenu3_3 = NULL;
    ALLEGRO_BITMAP *fundoMenu3_4 = NULL;

    ALLEGRO_BITMAP *fundoMenu4_1 = NULL;
    ALLEGRO_BITMAP *fundoMenu4_2 = NULL;
    ALLEGRO_BITMAP *fundoMenu4_3 = NULL;
    ALLEGRO_BITMAP *fundoMenu4_4 = NULL;

    ALLEGRO_BITMAP *fundoMenu5_1 = NULL;
    ALLEGRO_BITMAP *fundoMenu5_2 = NULL;
    ALLEGRO_BITMAP *fundoMenu5_3 = NULL;
    ALLEGRO_BITMAP *fundoMenu5_4 = NULL;

    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_AUDIO_STREAM *musicaMenu = NULL;
    ALLEGRO_SAMPLE *porta = NULL;

    fundoMenu1_1 = al_load_bitmap("imgs/menuPrincipal/normal/MenuPrincipal1.png");
    fundoMenu1_2 = al_load_bitmap("imgs/menuPrincipal/normal/MenuPrincipal2.png");
    fundoMenu1_3 = al_load_bitmap("imgs/menuPrincipal/normal/MenuPrincipal3.png");
    fundoMenu1_4 = al_load_bitmap("imgs/menuPrincipal/normal/MenuPrincipal4.png");

    fundoMenu2_1 = al_load_bitmap("imgs/menuPrincipal/comecar/MenuPrincipal1.png");
    fundoMenu2_2 = al_load_bitmap("imgs/menuPrincipal/comecar/MenuPrincipal2.png");
    fundoMenu2_3 = al_load_bitmap("imgs/menuPrincipal/comecar/MenuPrincipal3.png");
    fundoMenu2_4 = al_load_bitmap("imgs/menuPrincipal/comecar/MenuPrincipal4.png");

    fundoMenu3_1 = al_load_bitmap("imgs/menuPrincipal/continuar/MenuPrincipal1.png");
    fundoMenu3_2 = al_load_bitmap("imgs/menuPrincipal/continuar/MenuPrincipal2.png");
    fundoMenu3_3 = al_load_bitmap("imgs/menuPrincipal/continuar/MenuPrincipal3.png");
    fundoMenu3_4 = al_load_bitmap("imgs/menuPrincipal/continuar/MenuPrincipal4.png");

    fundoMenu4_1 = al_load_bitmap("imgs/menuPrincipal/configurar/MenuPrincipal1.png");
    fundoMenu4_2 = al_load_bitmap("imgs/menuPrincipal/configurar/MenuPrincipal2.png");
    fundoMenu4_3 = al_load_bitmap("imgs/menuPrincipal/configurar/MenuPrincipal3.png");
    fundoMenu4_4 = al_load_bitmap("imgs/menuPrincipal/configurar/MenuPrincipal4.png");

    fundoMenu5_1 = al_load_bitmap("imgs/menuPrincipal/sair/MenuPrincipal1.png");
    fundoMenu5_2 = al_load_bitmap("imgs/menuPrincipal/sair/MenuPrincipal2.png");
    fundoMenu5_3 = al_load_bitmap("imgs/menuPrincipal/sair/MenuPrincipal3.png");
    fundoMenu5_4 = al_load_bitmap("imgs/menuPrincipal/sair/MenuPrincipal4.png");

    musicaMenu = al_load_audio_stream("musicas/RascalMenu.ogg",4,1024);
    porta = al_load_sample("sons/doorMenu.wav");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    al_attach_audio_stream_to_mixer(musicaMenu,al_get_default_mixer());
    al_set_audio_stream_playmode(musicaMenu, ALLEGRO_PLAYMODE_LOOP);

    bool tocando = false;
    bool entrando = false;
    int tocandoCount = 0;
    int frames = 0;
    int selecionado = 0;
    int fadeOpacidade = 255;
    while(!trocarCena && !sair){
        iniciaTimer();
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
            else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                if(evento.mouse.x >500 && evento.mouse.x < 700 && evento.mouse.y > 200 && evento.mouse.y < 300){
                    selecionado = 1;
                    if(tocandoCount >=240){
                        tocandoCount = 0;
                        tocando = false;
                    }
                    else if(!tocando){
                        al_play_sample(porta,0.5,0.5,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        tocando = true;
                    }
                }
                else if(evento.mouse.x >45 && evento.mouse.x < 230 && evento.mouse.y > 200 && evento.mouse.y < 300){
                    selecionado = 2;
                }
                else if(evento.mouse.x >520 && evento.mouse.x < 550 && evento.mouse.y > 500 && evento.mouse.y < 550){
                    selecionado = 3;
                }
                else if(evento.mouse.x >1000 && evento.mouse.x < 1110 && evento.mouse.y > 190 && evento.mouse.y < 280){
                    selecionado = 4;
                }
                else{
                    selecionado = 0;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if(selecionado!=0){
                    entrando = true;
                    if(selecionado == 1){
                        acao = 1;
                    }
                    else if(selecionado == 4){
                        sair = true;
                    }
                }
            }
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        if(selecionado == 0){
            if(frames >=0 && frames <=3){
                al_draw_bitmap(fundoMenu1_1,0,0,0);
            }
            else if(frames<=6){
                al_draw_bitmap(fundoMenu1_2,0,0,0);
            }
            else if(frames<=9){
                al_draw_bitmap(fundoMenu1_3,0,0,0);
            }
            else if(frames<=12){
                al_draw_bitmap(fundoMenu1_4,0,0,0);
            }
        }
        else if(selecionado == 1){
            if(frames >=0 && frames <=3){
                al_draw_bitmap(fundoMenu2_1,0,0,0);
            }
            else if(frames<=6){
                al_draw_bitmap(fundoMenu2_2,0,0,0);
            }
            else if(frames<=9){
                al_draw_bitmap(fundoMenu2_3,0,0,0);
            }
            else if(frames<=12){
                al_draw_bitmap(fundoMenu2_4,0,0,0);
            }
        }
        else if(selecionado == 2){
            if(frames >=0 && frames <=3){
                al_draw_bitmap(fundoMenu3_1,0,0,0);
            }
            else if(frames<=6){
                al_draw_bitmap(fundoMenu3_2,0,0,0);
            }
            else if(frames<=9){
                al_draw_bitmap(fundoMenu3_3,0,0,0);
            }
            else if(frames<=12){
                al_draw_bitmap(fundoMenu3_4,0,0,0);
            }
        }
        else if(selecionado == 3){
            if(frames >=0 && frames <=3){
                al_draw_bitmap(fundoMenu4_1,0,0,0);
            }
            else if(frames<=6){
                al_draw_bitmap(fundoMenu4_2,0,0,0);
            }
            else if(frames<=9){
                al_draw_bitmap(fundoMenu4_3,0,0,0);
            }
            else if(frames<=12){
                al_draw_bitmap(fundoMenu4_4,0,0,0);
            }
        }
        else if(selecionado == 4){
            if(frames >=0 && frames <=3){
                al_draw_bitmap(fundoMenu5_1,0,0,0);
            }
            else if(frames<=6){
                al_draw_bitmap(fundoMenu5_2,0,0,0);
            }
            else if(frames<=9){
                al_draw_bitmap(fundoMenu5_3,0,0,0);
            }
            else if(frames<=12){
                al_draw_bitmap(fundoMenu5_4,0,0,0);
            }
        }
        al_draw_text(pixelFontTitle,al_map_rgb(0,0,0),600,30,ALLEGRO_ALIGN_CENTER,"EIJ Escape");
        if(fadeOpacidade>0&&entrando == false){
            al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
            fadeOpacidade -= 5;
        }
        else if(fadeOpacidade<255&&entrando == true){
            al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
            fadeOpacidade += 5;
        }
        else if(entrando == true){
            al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
            trocarCena = true;
        }
        al_flip_display();
        if(tocando == true && tocandoCount<240){
            tocandoCount++;
        }
        if(frames<12){
            frames++;
        }
        else{
            frames=0;
        }
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }
    al_destroy_bitmap(fundoMenu1_1);
    al_destroy_bitmap(fundoMenu1_2);
    al_destroy_bitmap(fundoMenu1_3);
    al_destroy_bitmap(fundoMenu1_4);

    al_destroy_bitmap(fundoMenu2_1);
    al_destroy_bitmap(fundoMenu2_2);
    al_destroy_bitmap(fundoMenu2_3);
    al_destroy_bitmap(fundoMenu2_4);

    al_destroy_bitmap(fundoMenu3_1);
    al_destroy_bitmap(fundoMenu3_2);
    al_destroy_bitmap(fundoMenu3_3);
    al_destroy_bitmap(fundoMenu3_4);

    al_destroy_bitmap(fundoMenu4_1);
    al_destroy_bitmap(fundoMenu4_2);
    al_destroy_bitmap(fundoMenu4_3);
    al_destroy_bitmap(fundoMenu4_4);

    al_destroy_bitmap(fundoMenu5_1);
    al_destroy_bitmap(fundoMenu5_2);
    al_destroy_bitmap(fundoMenu5_3);
    al_destroy_bitmap(fundoMenu5_4);

    al_destroy_bitmap(fade);
    al_destroy_audio_stream(musicaMenu);
    return 1;
}
int gameOver(){
    return 1;
}
void atualizaCamera(float *posicaoCamera, float playerPosition, float playerWidth){
        *posicaoCamera = -(LARGURA_JANELA/2) + (playerPosition+playerWidth/2);
    if(*posicaoCamera<= 0)
        *posicaoCamera = 0;
    if(*posicaoCamera>= 3000-LARGURA_JANELA)
        *posicaoCamera = 3000-LARGURA_JANELA;
}
void iniciaTimer(){
    tempoInicial = al_get_time();
}
double obterTempo(){
    return al_get_time() - tempoInicial;
}
void erroMsg(char *texto){
    if(janela){
        al_show_native_message_box(janela,"ERRO!","O seguinte erro ocorreu: ", texto, 0, ALLEGRO_MESSAGEBOX_ERROR);
    }
    else{
        al_show_native_message_box(0,"ERRO!","O seguinte erro ocorreu: ", texto, 0, ALLEGRO_MESSAGEBOX_ERROR);
    }
}
void destroi(){
    if(janela){
        al_destroy_display(janela);
    }
    if(filaDeEvento){
        al_destroy_event_queue(filaDeEvento);
    }
    if(timer){
        al_destroy_timer(timer);
    }
    if(spriteRafa){
        al_destroy_bitmap(spriteRafa);
    }
    if(spriteIlan){
        al_destroy_bitmap(spriteIlan);
    }
    if(spriteLarissa){
        al_destroy_bitmap(spriteLarissa);
    }
    if(spriteYuka){
        al_destroy_bitmap(spriteYuka);
    }
    if(icone){
        al_destroy_bitmap(icone);
    }
    if(pixelFont){
        al_destroy_font(pixelFont);
    }
    if(pixelFontTitle){
        al_destroy_font(pixelFontTitle);
    }
    if(pixelFontPequena){
        al_destroy_font(pixelFontPequena);
    }
    if(chuvaPadrao){
        al_destroy_sample(chuvaPadrao);
    }
    if(yukaBackground){
        al_destroy_sample(yukaBackground);
    }
    if(gritoMorte){
        al_destroy_sample(gritoMorte);
    }
    if(dying1){
        al_destroy_sample(dying1);
    }
    if(dying2){
        al_destroy_sample(dying2);
    }
    if(dying3){
        al_destroy_sample(dying3);
    }
    if(yukaScream){
        al_destroy_sample(yukaScream);
    }
}
int init(){
    //inicializacao das bibliotecas e add-ons
    if(!al_init()){
        erroMsg("Algo deu errado na inicializacao da Allegro");
        return -1;
    }
    if(!al_init_native_dialog_addon()){
        destroi();
        return -1;
    }
    if(!al_install_keyboard()){
        erroMsg("Algo deu errado na inicializacao do teclado");
        destroi();
        return -1;
    }
    if(!al_install_audio()){
        erroMsg("Algo deu errado na inicializacao do audio");
        destroi();
        return -1;
    }
    if(!al_install_mouse()){
        erroMsg("Algo deu errado na inicializacao do mouse");
        destroi();
        return -1;
    }
    if(!al_init_image_addon()){
        erroMsg("Algo deu errado na inicializacao do add-on de imagens");
        destroi();
        return -1;
    }
    if(!al_init_primitives_addon()){
        erroMsg("Algo deu errado na inicializacao do primitives add-on");
        destroi();
        return -1;
    }
    if(!al_init_acodec_addon()){
        erroMsg("Algo deu errado na inicializacao do codec de som");
        destroi();
        return -1;
    }
    al_init_font_addon();
    if(!al_init_ttf_addon()){
        erroMsg("Algo deu errado na integracao de fontes true type");
        destroi();
        return -1;
    }
    if(!al_reserve_samples(10)){
        erroMsg("Algo deu errado na geracao do mixer");
        destroi();
        return -1;
    }

    janela = al_create_display(LARGURA_JANELA, ALTURA_JANELA);
    if(!janela){
        erroMsg("Algo deu errado na criacao da janela");
        destroi();
        return -1;
    }
    al_set_window_title(janela, "EIJ Escape");
    filaDeEvento = al_create_event_queue();
    if(!filaDeEvento){
        erroMsg("Algo deu errado na criacao da fila de eventos");
        destroi();
        return -1;
    }
    spriteRafa = al_load_bitmap("imgs/personagens/SpriteSheetRafa.png");
    if(!spriteRafa){
        erroMsg("Algo deu errado ao carregar a spritesheet do Rafa");
        destroi();
        return -1;
    }
    spriteIlan = al_load_bitmap("imgs/personagens/SpriteSheetIlan.png");
    if(!spriteIlan){
        erroMsg("Algo deu errado ao carregar a spritesheet do Ilan");
        destroi();
        return -1;
    }
    spriteLarissa = al_load_bitmap("imgs/personagens/SpriteSheetLarissa.png");
    if(!spriteLarissa){
        erroMsg("Algo deu errado ao carregar a spritesheet da Larissa");
        destroi();
        return -1;
    }
    spriteYuka = al_load_bitmap("imgs/personagens/SpriteSheetYuka.png");
    if(!spriteYuka){
        erroMsg("Algo deu errado ao carregar a spritesheet da Yuka");
        destroi();
        return -1;
    }
    icone = al_load_bitmap("imgs/icone/iconeJogo.png");
    if(!icone){
        erroMsg("Algo deu errado ao carregar o icone do jogo");
        destroi();
        return -1;
    }
    al_set_display_icon(janela,icone);

    pixelFont = al_load_font("fontes/pixelFont.ttf",14,0);
    if(!pixelFont){
        erroMsg("Algo deu errado ao carregar a fonte");
        destroi();
        return -1;
    }
    pixelFontTitle = al_load_font("fontes/pixelFont.ttf",40,0);
    if(!pixelFontTitle){
        erroMsg("Algo deu errado ao carregar a fonte");
        destroi();
        return -1;
    }
    pixelFontPequena = al_load_font("fontes/pixelFont.ttf",8,0);
    if(!pixelFontPequena){
        erroMsg("Algo deu errado ao carregar a fonte");
        destroi();
        return -1;
    }
    chuvaPadrao = al_load_sample("sons/rain.wav");
    if(!chuvaPadrao){
        erroMsg("Algo deu errado ao carregar um sample");
        destroi();
        return -1;
    }
    yukaBackground = al_load_sample("sons/horrorSounds/yukaBackground.wav");
    if(!yukaBackground){
        erroMsg("Algo deu errado ao carregar um sample");
        destroi();
        return -1;
    }
    gritoMorte = al_load_sample("sons/horrorSounds/death.wav");
    if(!gritoMorte){
        erroMsg("Algo deu errado ao carregar um sample");
        destroi();
        return -1;
    }
    dying1 = al_load_sample("sons/horrorSounds/dying.wav");
    if(!dying1){
        erroMsg("Algo deu errado ao carregar um sample");
        destroi();
        return -1;
    }
    dying2 = al_load_sample("sons/horrorSounds/boneCrushing.wav");
        if(!dying2){
        erroMsg("Algo deu errado ao carregar um sample");
        destroi();
        return -1;
    }
    dying3 = al_load_sample("sons/horrorSounds/BloodSquirt.wav");
    if(!dying3){
        erroMsg("Algo deu errado ao carregar um sample");
        destroi();
        return -1;
    }
    yukaScream = al_load_sample("sons/horrorSounds/femaleScream.wav");
    if(!yukaBackground){
        erroMsg("Algo deu errado ao carregar um sample");
        destroi();
        return -1;
    }

    al_register_event_source(filaDeEvento, al_get_display_event_source(janela));
    al_register_event_source(filaDeEvento, al_get_keyboard_event_source());
    al_register_event_source(filaDeEvento, al_get_mouse_event_source());
    return 1;
}
int filaPadrao(bool teclas[]){
    while(!al_event_queue_is_empty(filaDeEvento)){
        ALLEGRO_EVENT evento;
        al_wait_for_event(filaDeEvento, &evento);

        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            sair = true;
        }
        else if(evento.type == ALLEGRO_EVENT_KEY_UP){
            if(evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A){
                teclas[0] = false;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D){
                teclas[1] = false;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                teclas[2] = false;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                teclas[3] = false;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_LSHIFT){
                teclas[4] = false;
            }
        }
        else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A){
                teclas[0] = true;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D){
                teclas[1] = true;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W){
                teclas[2] = true;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S){
                teclas[3] = true;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_LSHIFT){
                teclas[4] = true;
            }
        }
    }
    return 1;
}
int movimentoPadrao(struct personagem *rafa,int comodoLimMin,int comodoLimMax, bool teclas[]){
    enum posicoes {RIGHT, LEFT};
    if(!teclas[0] && !teclas[1]){
        rafa->andando = false;
        rafa->correndo = false;
    }
    else if(teclas[0] && teclas[1]){
        rafa->andando = false;
        rafa->correndo = false;
    }
    else if(((teclas[0] && teclas [4] && rafa->pos_x > comodoLimMin) || (teclas[1] && teclas[4] && rafa->pos_x < comodoLimMax))){
        rafa->andando = false;
        rafa->correndo = true;
        rafa->inverte_sprite = teclas[0]?LEFT:RIGHT;
    }
    else if(((teclas[0] && rafa->pos_x > comodoLimMin) || (teclas[1] && rafa->pos_x < comodoLimMax))){
        rafa->andando = true;
        rafa->correndo = false;
        rafa->inverte_sprite = teclas[0]?LEFT:RIGHT;
    }
    else{
        rafa->andando = false;
        rafa->correndo = false;
    }
    if(rafa->correndo || rafa->andando){
        rafa->velocidade = rafa->correndo?6:3;
        rafa->linha_atual = rafa->correndo?2:1;
        rafa->frames_sprite = 6;
        rafa->colunas_sprite = 8;
        rafa->pos_x = rafa->inverte_sprite == LEFT?rafa->pos_x-rafa->velocidade:rafa->pos_x + rafa->velocidade;
    }
    else {
        rafa->velocidade = 0;
        rafa->linha_atual = 0;
        rafa->frames_sprite = 25;
        rafa->colunas_sprite = 5;
        if(rafa->coluna_atual>4){
            rafa->coluna_atual = 0;
        }
    }
    if(rafa->cont_frames > rafa->frames_sprite){
        rafa->cont_frames = 0;
        rafa->coluna_atual = (rafa->coluna_atual+1) % rafa->colunas_sprite;
    }
    else{
        rafa->cont_frames++;
    }
    return 1;
}
int movimentoPadraoComEscondido(struct personagem *rafa,int comodoLimMin,int comodoLimMax, bool teclas[], bool *escondido){
    enum posicoes {RIGHT, LEFT};
    if(!teclas[0] && !teclas[1]){
        rafa->andando = false;
        rafa->correndo = false;
    }
    else if(teclas[0] && teclas[1]){
        rafa->andando = false;
        rafa->correndo = false;
    }
    else if(((teclas[0] && teclas [4] && rafa->pos_x > comodoLimMin) || (teclas[1] && teclas[4] && rafa->pos_x < comodoLimMax))&&!*escondido){
        rafa->andando = false;
        rafa->correndo = true;
        rafa->inverte_sprite = teclas[0]?LEFT:RIGHT;
    }
    else if(((teclas[0] && rafa->pos_x > comodoLimMin) || (teclas[1] && rafa->pos_x < comodoLimMax))&&!*escondido){
        rafa->andando = true;
        rafa->correndo = false;
        rafa->inverte_sprite = teclas[0]?LEFT:RIGHT;
    }
    else{
        rafa->andando = false;
        rafa->correndo = false;
    }
    if(rafa->correndo || rafa->andando){
        rafa->velocidade = rafa->correndo?6:3;
        rafa->linha_atual = rafa->correndo?2:1;
        rafa->frames_sprite = 6;
        rafa->colunas_sprite = 8;
        rafa->pos_x = rafa->inverte_sprite == LEFT?rafa->pos_x-rafa->velocidade:rafa->pos_x + rafa->velocidade;
    }
    else {
        rafa->velocidade = 0;
        rafa->linha_atual = 0;
        rafa->frames_sprite = 25;
        rafa->colunas_sprite = 5;
        if(rafa->coluna_atual>4){
            rafa->coluna_atual = 0;
        }
    }
    if(rafa->cont_frames > rafa->frames_sprite){
        rafa->cont_frames = 0;
        rafa->coluna_atual = (rafa->coluna_atual+1) % rafa->colunas_sprite;
    }
    else{
        rafa->cont_frames++;
    }
    return 1;
}
int temporizaDistancia(int pos1, int pos2){
    int distancia = pos1-pos2;
    return distancia>0?(distancia/4) + timerYukaEntrar:((-(distancia))/4)+timerYukaEntrar;
}



