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

const int FPS = 60.0;
const int LARGURA_JANELA = 1200;
const int ALTURA_JANELA = 600;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *filaDeEvento = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *spriteRafa = NULL;
ALLEGRO_BITMAP *spriteIlan = NULL;
ALLEGRO_BITMAP *spriteLarissa = NULL;
ALLEGRO_BITMAP *spriteYuka = NULL;

bool sair = false;
bool trocarCena = false;
int acao = 0;
double tempoInicial = 0;

int init();
void destroi();
int Menu();
int entradaHall();
void iniciaRafa();
void iniciaIlan();
void iniciaLarissa();
void iniciaYuka();
void erroMsg(char *texto);
void iniciaTimer();
double obterTempo();

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
                entradaHall();
            break;
        }
        trocarCena = false;
    }

    destroi();
    return 1;
}

int entradaHall(){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_SAMPLE *passos = NULL;
    ALLEGRO_SAMPLE *portaTrancando = NULL;
    ALLEGRO_SAMPLE *chuva = NULL;
    fundo = al_load_bitmap("imgs/hall/HallFundo.png");
    frente = al_load_bitmap("imgs/hall/HallFrente.png");
    struct personagem rafa;
    struct personagem ilan;

    iniciaRafa(&rafa);
    iniciaIlan(&ilan);
    int texto = 0;
    int ato = 0;
    int opacidadedb = 5;
    bool cenaTerminou = false;
    rafa.pos_x = 500;
    ilan.pos_x = 600;

    while(!cenaTerminou && !sair){
        iniciaTimer();
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
        }
        if(ato == 1){
            rafa.andando = true;
            rafa.inverte_sprite = 1;
            ilan.andando = true;
            ilan.inverte_sprite = 0;
        }
        if(ato == 2){
            rafa.andando = false;
            ilan.andando = false;
            rafa.inverte_sprite = 0;
            ilan.inverte_sprite = 1;
        }
        if(rafa.andando || rafa.correndo){
            rafa.linha_atual = rafa.andando?1:2;
            rafa.velocidade = rafa.andando?2:4;
            rafa.colunas_sprite = 8;
            rafa.frames_sprite = 6;
        }
        else{
            rafa.velocidade = 0;
            rafa.linha_atual = 0;
            rafa.colunas_sprite = 5;
            rafa.frames_sprite = 25;
        }
        if(ilan.andando || ilan.correndo){
            ilan.linha_atual = ilan.andando?1:2;
            ilan.velocidade = ilan.andando?2:4;
            ilan.colunas_sprite = 8;
            ilan.frames_sprite = 6;
        }
        else{
            ilan.linha_atual = 0;
            ilan.colunas_sprite = 5;
            ilan.frames_sprite = 25;
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
                opacidadedb+=2;
            }
            al_draw_filled_rectangle(0,500,1200,600,al_map_rgba(61, 23, 1,opacidadedb));
            if(opacidadedb >=255){

            }
        }
        al_flip_display();
        ato = ato==0?1:ato;
        if(obterTempo()< 1.0/FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }

    return 1;
}

int Menu(){
    ALLEGRO_BITMAP *fundoMenu = NULL;
    ALLEGRO_AUDIO_STREAM *musicaMenu = NULL;
    ALLEGRO_SAMPLE *chuva = NULL;
    ALLEGRO_SAMPLE *porta = NULL;
    musicaMenu = al_load_audio_stream("musicas/RascalMenu.ogg",4,1024);
    porta = al_load_sample("sons/doorMenu.wav");
    chuva = al_load_sample("sons/rainMenu.wav");
    al_play_sample(chuva,0.5,0.5,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    al_attach_audio_stream_to_mixer(musicaMenu,al_get_default_mixer());
    al_set_audio_stream_playmode(musicaMenu, ALLEGRO_PLAYMODE_LOOP);

    bool tocando = false;
    int tocandoCount = 0;
    int frames = 0;
    int selecionado = 0;
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
                    trocarCena = true;
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
        al_draw_bitmap(fundoMenu,0,0,0);
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
    if(musicaMenu){
        al_destroy_audio_stream(musicaMenu);
    }
    if(chuva){
        al_destroy_sample(chuva);
    }
    if(porta){
        al_destroy_sample(porta);
    }
    return 1;
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

    al_register_event_source(filaDeEvento, al_get_display_event_source(janela));
    al_register_event_source(filaDeEvento, al_get_keyboard_event_source());
    al_register_event_source(filaDeEvento, al_get_mouse_event_source());

    return 1;
}
