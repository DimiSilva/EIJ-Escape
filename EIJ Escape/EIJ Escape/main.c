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
ALLEGRO_SAMPLE_ID idChuva;
ALLEGRO_FONT *pixelFontPequena = NULL;
ALLEGRO_FONT *pixelFont = NULL;
ALLEGRO_FONT *pixelFontTitle = NULL;

bool sair = false;
bool trocarCena = false;
int acao = 6;
int acaoAnterior = 1;

bool chuvaPadraoAtiva = false;

double tempoInicial = 0;
//fim variaveis e ponteiros

//funcoes
int init();
void destroi();

int Menu();
int HallAnim();
int Hall(int veioDeOnde);
int Cozinha();
int BanheiroPrimeiroAndar();
int BanheiroSegundoAndar();
int CorredorSegundoAndar(int veioDeOnde);
int Biblioteca(int veioDeOnde);
int SalaDeJantar(int veioDeOnde);

void atualizaCamera(float *cameraPosition, float playerPosition, float playerWidth);

void iniciaRafa();
void iniciaIlan();
void iniciaLarissa();
void iniciaYuka();

void erroMsg(char *texto);

void iniciaTimer();
double obterTempo();
//fim funcoes

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
    h->frames_sprite = 0;
    h->cont_frames = 0;
    h->colunas_sprite = 8;
    h->coluna_atual = 0;
    h->linhas_sprite = 1;
    h->linha_atual = 0;
    h->pos_x = 0;
    h->pos_y = 500;
    h->velocidade = 0;
    h->inverte_sprite = 0;
    h->andando = true;
    h->correndo = false;
}

int main(){
    init();
    while(!sair){
        if(acao>0&&!chuvaPadraoAtiva){
            al_play_sample(chuvaPadrao,1,0.5,1,ALLEGRO_PLAYMODE_LOOP,&idChuva);
            chuvaPadraoAtiva = true;
        }
        else if(acao == 0){
            chuvaPadraoAtiva = false;
            al_stop_sample(&idChuva);
        }
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
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
                BanheiroSegundoAndar(acaoAnterior);
            break;
        }
        trocarCena = false;
    }
    destroi();
    return 1;
}
int BanheiroSegundoAndar(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *cortinaBanheiro = NULL;
    fundo = al_load_bitmap("imgs/banheiro2Andar/Banheiro2AndarFundo.png");
    frente = al_load_bitmap("imgs/banheiro2Andar/Banheiro2AndarFrente.png");
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
    bool escondido = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 20;
    while(!trocarCena && !sair){
        iniciaTimer();
        emUmaEntradaS = false;
        if(timerEscondido>0){
            timerEscondido--;
        }
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
        if(!teclas[0] && !teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if(teclas[0] && teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if(((teclas[0] && teclas [4] && rafa.pos_x > -10) || (teclas[1] && teclas[4] && rafa.pos_x < 170))&& !escondido){
            rafa.andando = false;
            rafa.correndo = true;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else if(((teclas[0] && rafa.pos_x > -10) || (teclas[1] && rafa.pos_x < 170)) && !escondido){
            rafa.andando = true;
            rafa.correndo = false;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else{
            rafa.andando = false;
            rafa.correndo = false;
        }
        if(rafa.correndo || rafa.andando){
            rafa.velocidade = rafa.correndo?6:3;
            rafa.linha_atual = rafa.correndo?2:1;
            rafa.frames_sprite = 6;
            rafa.colunas_sprite = 8;
            rafa.pos_x = rafa.inverte_sprite == LEFT?rafa.pos_x-rafa.velocidade:rafa.pos_x + rafa.velocidade;
        }
        else {
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.frames_sprite = 25;
            rafa.colunas_sprite = 5;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1) % rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(rafa.pos_x>150 && rafa.pos_x<251){
            if(teclas[2]){
                if(!escondido && timerEscondido <= 0){
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
                acao = 5;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Corredor do segundo andar");
        }
        rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
        rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
        al_draw_bitmap(fundo,0,0,0);
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
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
    al_destroy_sample(cortinaBanheiro);
    acaoAnterior = 6;
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
    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int timerEscondido = 0;
    char salaDaPortaS[50];
    bool escondido = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = LEFT;
    rafa.pos_x = 1100;
    while(!trocarCena && !sair){
        iniciaTimer();
        emUmaEntradaS = false;
        if(timerEscondido>0){
            timerEscondido--;
        }
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
        if(!teclas[0] && !teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if(teclas[0] && teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if(((teclas[0] && teclas [4] && rafa.pos_x > -10) || (teclas[1] && teclas[4] && rafa.pos_x < 1110))&& !escondido){
            rafa.andando = false;
            rafa.correndo = true;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else if(((teclas[0] && rafa.pos_x > -10) || (teclas[1] && rafa.pos_x < 1110)) && !escondido){
            rafa.andando = true;
            rafa.correndo = false;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else{
            rafa.andando = false;
            rafa.correndo = false;
        }
        if(rafa.correndo || rafa.andando){
            rafa.velocidade = rafa.correndo?6:3;
            rafa.linha_atual = rafa.correndo?2:1;
            rafa.frames_sprite = 6;
            rafa.colunas_sprite = 8;
            rafa.pos_x = rafa.inverte_sprite == LEFT?rafa.pos_x-rafa.velocidade:rafa.pos_x + rafa.velocidade;
        }
        else {
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.frames_sprite = 25;
            rafa.colunas_sprite = 5;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1) % rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(rafa.pos_x>170 && rafa.pos_x<300){
            if(teclas[2]){
                if(!escondido && timerEscondido <= 0){
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
        if(!escondido){
            al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                rafa.larguraSprite,rafa.alturaSprite,
                rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
        }
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
    acaoAnterior = 3;
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
    bool escondido = false;
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    rafa.pos_x = 20;
    while(!trocarCena && !sair){
        iniciaTimer();
        emUmaEntradaS = false;
        if(timerEscondido>0){
            timerEscondido--;
        }
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
        if(!teclas[0] && !teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if(teclas[0] && teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if(((teclas[0] && teclas [4] && rafa.pos_x > -10) || (teclas[1] && teclas[4] && rafa.pos_x < 170))&& !escondido){
            rafa.andando = false;
            rafa.correndo = true;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else if(((teclas[0] && rafa.pos_x > -10) || (teclas[1] && rafa.pos_x < 170)) && !escondido){
            rafa.andando = true;
            rafa.correndo = false;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else{
            rafa.andando = false;
            rafa.correndo = false;
        }
        if(rafa.correndo || rafa.andando){
            rafa.velocidade = rafa.correndo?6:3;
            rafa.linha_atual = rafa.correndo?2:1;
            rafa.frames_sprite = 6;
            rafa.colunas_sprite = 8;
            rafa.pos_x = rafa.inverte_sprite == LEFT?rafa.pos_x-rafa.velocidade:rafa.pos_x + rafa.velocidade;
        }
        else {
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.frames_sprite = 25;
            rafa.colunas_sprite = 5;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1) % rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(rafa.pos_x>150 && rafa.pos_x<251){
            if(teclas[2]){
                if(!escondido && timerEscondido <= 0){
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
        al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
            rafa.larguraSprite,rafa.alturaSprite,
            rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
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
    al_destroy_sample(cortinaBanheiro);
    acaoAnterior = 4;
    return 1;
}
int CorredorSegundoAndar(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *passosEscada = NULL;
    ALLEGRO_TRANSFORM camera;
    fundo = al_load_bitmap("imgs/corredor2Andar/Corredor2AndarFundo.png");
    frente = al_load_bitmap("imgs/corredor2Andar/Corredor2AndarFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    passosEscada = al_load_sample("sons/footstepInStairs.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);

    enum posicoes {RIGHT, LEFT};

    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    float cameraPosition = 0;
    char salaDaPortaS[50];
    char salaDaPortaI[50];
    bool inicio = true;
    bool fim = false;
    bool emUmaEntradaS = false;
    bool emUmaEntradaI = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = RIGHT;
    if(veioDeOnde == 2){
        rafa.pos_x = 10;
    }
    else if(veioDeOnde == 6){
        rafa.pos_x = 740;
    }

    while(!trocarCena && !sair){
        iniciaTimer();
        emUmaEntradaS = false;
        emUmaEntradaI = false;
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
        if(!teclas[0] && !teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if(teclas[0] && teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if((teclas[0] && teclas [4] && rafa.pos_x > 2) || (teclas[1] && teclas[4] && rafa.pos_x < 2908)){
            rafa.andando = false;
            rafa.correndo = true;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else if((teclas[0] && rafa.pos_x > 2) || (teclas[1] && rafa.pos_x < 2908)){
            rafa.andando = true;
            rafa.correndo = false;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else{
            rafa.andando = false;
            rafa.correndo = false;
        }
        if(rafa.correndo || rafa.andando){
            rafa.velocidade = rafa.correndo?6:3;
            rafa.linha_atual = rafa.correndo?2:1;
            rafa.frames_sprite = 6;
            rafa.colunas_sprite = 8;
            rafa.pos_x = rafa.inverte_sprite == LEFT?rafa.pos_x-rafa.velocidade:rafa.pos_x + rafa.velocidade;
        }
        else {
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.frames_sprite = 25;
            rafa.colunas_sprite = 5;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1) % rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
        if(rafa.pos_x>0 && rafa.pos_x<200){
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
        else if(rafa.pos_x>700 && rafa.pos_x<810){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 6;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Banheiro do segundo andar");
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
            strcpy(salaDaPortaS, "-------");
        }
        else if(rafa.pos_x>2270 && rafa.pos_x<2400){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 6;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "--------");
        }
        else if(rafa.pos_x>2900 && rafa.pos_x<3000){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 7;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "--------");
        }

        if(rafa.pos_x>1350 && rafa.pos_x <1550){
            emUmaEntradaI = true;
            strcpy(salaDaPortaI, "--------");
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
    atualizaCamera(&cameraPosition, rafa.pos_x,rafa.larguraSprite);
    al_identity_transform(&camera);
    al_translate_transform(&camera, -cameraPosition,0);
    al_use_transform(&camera);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_bitmap(fade);
    al_destroy_sample(abrirPorta);
    al_destroy_sample(passosEscada);
    acaoAnterior = 5;
    return 1;
}
int Biblioteca(int veioDeOnde){
    return 1;
}
int SalaDeJantar(int veioDeOnde){
    return 1;
}
int Hall(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_SAMPLE *abrirPorta = NULL;
    ALLEGRO_SAMPLE *passosEscada = NULL;
    ALLEGRO_TRANSFORM camera;
    fundo = al_load_bitmap("imgs/hall/HallFundo.png");
    frente = al_load_bitmap("imgs/hall/HallFrente.png");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    abrirPorta = al_load_sample("sons/portaAbrindoFechando.wav");
    passosEscada = al_load_sample("sons/footstepInStairs.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);

    enum posicoes {RIGHT, LEFT};

    int fadeOpacidade = 255;
    int opacidadeEmUmaEntradaS = 0;
    int opacidadeEmUmaEntradaI = 0;
    float cameraPosition = 0;
    char salaDaPortaS[50];
    char salaDaPortaI[50];
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
    while(!trocarCena && !sair){
        iniciaTimer();
        emUmaEntradaS = false;
        emUmaEntradaI = false;
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
        if(!teclas[0] && !teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if(teclas[0] && teclas[1]){
            rafa.andando = false;
            rafa.correndo = false;
        }
        else if((teclas[0] && teclas [4] && rafa.pos_x > 2) || (teclas[1] && teclas[4] && rafa.pos_x < 2908)){
            rafa.andando = false;
            rafa.correndo = true;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else if((teclas[0] && rafa.pos_x > 2) || (teclas[1] && rafa.pos_x < 2908)){
            rafa.andando = true;
            rafa.correndo = false;
            rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
        }
        else{
            rafa.andando = false;
            rafa.correndo = false;
        }
        if(rafa.correndo || rafa.andando){
            rafa.velocidade = rafa.correndo?6:3;
            rafa.linha_atual = rafa.correndo?2:1;
            rafa.frames_sprite = 6;
            rafa.colunas_sprite = 8;
            rafa.pos_x = rafa.inverte_sprite == LEFT?rafa.pos_x-rafa.velocidade:rafa.pos_x + rafa.velocidade;
        }
        else {
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.frames_sprite = 25;
            rafa.colunas_sprite = 5;
            if(rafa.coluna_atual>4){
                rafa.coluna_atual = 0;
            }
        }
        if(rafa.cont_frames > rafa.frames_sprite){
            rafa.cont_frames = 0;
            rafa.coluna_atual = (rafa.coluna_atual+1) % rafa.colunas_sprite;
        }
        else{
            rafa.cont_frames++;
        }
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
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 6;
            }
            emUmaEntradaS = true;
            strcpy(salaDaPortaS, "Biblioteca");
        }
        else if(rafa.pos_x>2900 && rafa.pos_x<3000){
            if(teclas[2]){
                if(!fim){
                    al_play_sample(abrirPorta,1,0.5,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                fim = true;
                acao = 7;
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
    acaoAnterior = 2;
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
    strcpy(dialogos[0], "Ilan: Ae Rafa, que mansão mais estranha, tu não acha ?");
    strcpy(dialogos[1], "Rafael: Pois é, tem algo de errado, tá muito frio aqui dentro!");
    strcpy(dialogos[2], "Ilan: Sim, ae que que se acha da gente se separar pra procurarmos a Larissa ?");
    strcpy(dialogos[3], "Rafael: Sei não em, é ai que a galera morre nos filmes.");
    strcpy(dialogos[4], "Ilan: Ta é doido Rafa, tem nada aqui não ma.");
    strcpy(dialogos[5], "Rafael: A Larissa tava falando que tinha uns negócios estranhos aqui.");
    strcpy(dialogos[6], "Ilan: Me deixa de bobagem pô, você sabe que fantasmas não existem.");
    strcpy(dialogos[7], "Rafael: Mano impressão minha ou a porta trancou ?");
    strcpy(dialogos[8], "Ilan: Eu ouvi também, vê ai macho.");
    strcpy(dialogos[9], "Rafael: Trancada...");
    strcpy(dialogos[10], "Rafael: Que foi isso ?");
    strcpy(dialogos[11], "Ilan: Alguma coisa caiu no outro cômodo, vou lá dar uma olhada.");
    strcpy(dialogos[12], "Rafael: Toma cuidado Ilan e vê se não demora.");
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
    ALLEGRO_BITMAP *fundoMenu = NULL;
    ALLEGRO_BITMAP *fade = NULL;
    ALLEGRO_AUDIO_STREAM *musicaMenu = NULL;
    ALLEGRO_SAMPLE *chuva = NULL;
    ALLEGRO_SAMPLE *porta = NULL;
    musicaMenu = al_load_audio_stream("musicas/RascalMenu.ogg",4,1024);
    porta = al_load_sample("sons/doorMenu.wav");
    chuva = al_load_sample("sons/rainMenu.wav");
    fade = al_load_bitmap("imgs/efeitos/fade.png");
    al_play_sample(chuva,0.5,0.5,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
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
                    if(tocandoCount >=120){
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
        if(selecionado == 0){
            if(frames >=0 && frames <3){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/normal/MenuPrincipal1.png");
            }
            else if(frames<6){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/normal/MenuPrincipal2.png");
            }
            else if(frames<9){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/normal/MenuPrincipal3.png");
            }
            else if(frames<12){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/normal/MenuPrincipal4.png");
            }
        }
        else if(selecionado == 1){
            if(frames >=0 && frames <3){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/comecar/MenuPrincipal1.png");
            }
            else if(frames<6){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/comecar/MenuPrincipal2.png");
            }
            else if(frames<9){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/comecar/MenuPrincipal3.png");
            }
            else if(frames<12){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/comecar/MenuPrincipal4.png");
            }
        }
        else if(selecionado == 2){
            if(frames >=0 && frames <3){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/continuar/MenuPrincipal1.png");
            }
            else if(frames<6){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/continuar/MenuPrincipal2.png");
            }
            else if(frames<9){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/continuar/MenuPrincipal3.png");
            }
            else if(frames<12){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/continuar/MenuPrincipal4.png");
            }
        }
        else if(selecionado == 3){
            if(frames >=0 && frames <3){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/configurar/MenuPrincipal1.png");
            }
            else if(frames<6){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/configurar/MenuPrincipal2.png");
            }
            else if(frames<9){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/configurar/MenuPrincipal3.png");
            }
            else if(frames<12){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/configurar/MenuPrincipal4.png");
            }
        }
        else if(selecionado == 4){
            if(frames >=0 && frames <3){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/sair/MenuPrincipal1.png");
            }
            else if(frames<6){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/sair/MenuPrincipal2.png");
            }
            else if(frames<9){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/sair/MenuPrincipal3.png");
            }
            else if(frames<12){
                fundoMenu = al_load_bitmap("imgs/menuPrincipal/sair/MenuPrincipal4.png");
            }
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundoMenu,0,0,0);
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
        if(tocando == true && tocandoCount<120){
            tocandoCount++;
        }
        if(frames<11){
            frames++;
        }
        else{
            frames = 0;
        }
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
        al_destroy_bitmap(fundoMenu);
    }
    al_destroy_bitmap(fade);
    al_destroy_sample(chuva);
    al_destroy_audio_stream(musicaMenu);
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
    chuvaPadrao = al_load_sample("sons/rainBackground.wav");
    if(!chuvaPadrao){
        erroMsg("Algo deu errado ao carregar um sample");
        destroi();
        return -1;
    }
    al_register_event_source(filaDeEvento, al_get_display_event_source(janela));
    al_register_event_source(filaDeEvento, al_get_keyboard_event_source());
    al_register_event_source(filaDeEvento, al_get_mouse_event_source());
    return 1;
}
