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
ALLEGRO_FONT *pixelFontPequena = NULL;
ALLEGRO_FONT *pixelFont = NULL;
ALLEGRO_FONT *pixelFontTitle = NULL;
bool sair = false;
bool trocarCena = false;
int acao = 0;
int acaoAnterior = 0;
double tempoInicial = 0;

int init();
void destroi();
int Menu();
int HallAnim();
int Hall(int veioDeOnde);
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
                HallAnim();
            break;
            case 2:
                Hall(acaoAnterior);
            break;
        }
        trocarCena = false;
    }

    destroi();
    return 1;
}
int Hall(int veioDeOnde){
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *frente = NULL;
    ALLEGRO_SAMPLE *chuva = NULL;
    fundo = al_load_bitmap("imgs/hall/HallFundo.png");
    frente = al_load_bitmap("imgs/hall/HallFrente.png");
    chuva = al_load_sample("sons/rainBackground.wav");
    struct personagem rafa;
    iniciaRafa(&rafa);

    enum posicoes {RIGHT, LEFT};

    bool trocarCena = false;
    bool teclas[5] = {false,false,false,false,false};
    rafa.inverte_sprite = LEFT;
    if(veioDeOnde == 1){
        while(!trocarCena && !sair){
            iniciaTimer();
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
            else if(teclas[0] && teclas [4] || teclas[1] && teclas[4]){
                rafa.andando = false;
                rafa.correndo = true;
                rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
            }
            else if(teclas[0] || teclas[1]){
                rafa.andando = true;
                rafa.correndo = false;
                rafa.inverte_sprite = teclas[0]?LEFT:RIGHT;
            }
            if(rafa.correndo || rafa.andando){
                rafa.velocidade = rafa.correndo?4:2;
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

            rafa.regiaoXdaFolha = rafa.coluna_atual * rafa.larguraSprite;
            rafa.regiaoYdaFolha = rafa.linha_atual * rafa.alturaSprite;
            al_draw_bitmap(fundo,0,0,0);
            al_draw_bitmap_region(rafa.spritesheet,rafa.regiaoXdaFolha,rafa.regiaoYdaFolha,
                              rafa.larguraSprite,rafa.alturaSprite,
                              rafa.pos_x,rafa.pos_y,rafa.inverte_sprite);
            al_draw_bitmap(frente,0,0,0);
            al_flip_display();
            if(obterTempo()< 1.0/FPS){
                al_rest((1.0/FPS)-obterTempo());
            }
        }
    }
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(frente);
    al_destroy_sample(chuva);
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
    strcpy(dialogos[1], "Rafa: Pois é, tem algo de errado, tá muito frio aqui dentro!");
    strcpy(dialogos[2], "Ilan: Sim, ae que que se acha da gente se separar pra procurarmos a Larissa ?");
    strcpy(dialogos[3], "Rafa: Sei não em, é ai que a galera morre nos filmes.");
    strcpy(dialogos[4], "Ilan: Ta é doido Rafa, tem nada aqui não ma.");
    strcpy(dialogos[5], "Rafa: A Larissa tava falando que tinha uns negócios estranhos aqui.");
    strcpy(dialogos[6], "Ilan: Me deixa de bobagem pô, você sabe que fantasmas não existem.");
    strcpy(dialogos[7], "Rafa: Mano impressão minha ou a porta trancou ?");
    strcpy(dialogos[8], "Ilan: Eu ouvi também, vê ai macho.");
    strcpy(dialogos[9], "Rafa: Trancada...");
    strcpy(dialogos[10], "Rafa: Que foi isso ?");
    strcpy(dialogos[11], "Ilan: Alguma coisa caiu no outro cômodo, vou lá dar uma olhada.");
    strcpy(dialogos[12], "Rafa: Toma cuidado Ilan e vê se não demora.");
    int ato = 0;
    int opacidadedb = 0;
    int fadeOpacidade = 255;
    int timer = 0;
    bool cenaTerminou = false;
    bool pressionado = false;
    bool pausarDialogo = false;
    bool tocando = false;
    bool ato2okay = false;
    rafa.pos_x = 500;
    ilan.pos_x = 600;


    al_play_sample(chuva,0.7,0.5,1,ALLEGRO_PLAYMODE_LOOP,NULL);
    while(!cenaTerminou && !sair){
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
            rafa.velocidade = rafa.andando?2:4;
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
            ilan.velocidade = ilan.andando?2:4;
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
                            cenaTerminou = true;
                            acao = 2;
                        }
                    }
                }
            }
        }
        if(fadeOpacidade > 0){
            al_draw_tinted_bitmap(fade,al_map_rgba(255,255,255,fadeOpacidade),0,0,0);
            fadeOpacidade -= 5;
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
    if(pixelFont){
        al_destroy_font(pixelFont);
    }
    if(pixelFontTitle){
        al_destroy_font(pixelFontTitle);
    }
    if(pixelFontPequena){
        al_destroy_font(pixelFontPequena);
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

    al_register_event_source(filaDeEvento, al_get_display_event_source(janela));
    al_register_event_source(filaDeEvento, al_get_keyboard_event_source());
    al_register_event_source(filaDeEvento, al_get_mouse_event_source());

    return 1;
}
