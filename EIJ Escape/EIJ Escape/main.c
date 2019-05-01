#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

#include <stdio.h>
#include <stdbool.h>

const double FPS = 60.0;
const int LARGURA_JANELA = 1200;
const int ALTURA_JANELA = 600;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *filaDeEvento = NULL;
ALLEGRO_TIMER *timer = NULL;

bool sair = false;
bool trocarCena = false;
int acao = 0;
double tempoInicial = 0;

int init();
void destroi();
int Menu();
void erroMsg(char *texto);
void iniciaTimer();
double obterTempo();

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
        }
        trocarCena = false;
    }

    destroi();
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
                if(evento.mouse.x >500 && evento.mouse.x < 700 && evento.mouse.y > 200 && evento.mouse.y < 250){
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
    if(fundoMenu){
        al_destroy_bitmap(fundoMenu);
    }
    if(musicaMenu){
        al_destroy_audio_stream(musicaMenu);
    }
    if(chuva){
        al_destroy_sample(chuva);
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

    al_register_event_source(filaDeEvento, al_get_display_event_source(janela));
    al_register_event_source(filaDeEvento, al_get_keyboard_event_source());
    al_register_event_source(filaDeEvento, al_get_mouse_event_source());

    return 1;
}
