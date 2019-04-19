//biblitecas

//base allegro
#include <allegro5/allegro.h>
//imagens allegro
#include <allegro5/allegro_image.h>
//funcoes primitivas da allegro, como geracao de formas geometricas
#include <allegro5/allegro_primitives.h>
//audio allegro
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
//fontes allegro
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//janela de dialogo nativa allegro
#include <allegro5/allegro_native_dialog.h>

//C
#include <stdio.h>
#include <stdbool.h>

//constantes
const int FPS = 60;
const double LARGURA_JANELA = 600;
const double ALTURA_JANELA = 500;

//ponteiros
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *filaDeEvento = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *fundo = NULL;

//variaveis globais
ALLEGRO_TRANSFORM camera;
bool sair = false;
bool tecla[2] = {false,false};
double tempoInicial = 0;
double posicaoCamera = 0;

//tratamento de erros
void erroMsg(char *texto){
    if(janela){
        al_show_native_message_box(janela,"ERRO!","O seguinte erro ocorreu: ", texto, 0, ALLEGRO_MESSAGEBOX_ERROR);
    }
    else{
        al_show_native_message_box(0,"ERRO!","O seguinte erro ocorreu: ", texto, 0, ALLEGRO_MESSAGEBOX_ERROR);
    }
}

//destroi tudo que esta ocupando memoria
void destroi(){
    if(janela){
        al_destroy_display(janela);
    }
    if(fundo){
        al_destroy_bitmap(fundo);
    }
    if(filaDeEvento){
        al_destroy_event_queue(filaDeEvento);
    }
    if(timer){
        al_destroy_timer(timer);
    }
}

//inicializacao
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
    if(!al_init_primitives_addon()){
        erroMsg("Algo deu errado na inicializacao do do add-on de primitives");
        destroi();
        return -1;
    }
    if(!al_init_image_addon()){
        erroMsg("Algo deu errado na inicializacao do add-on de imagens");
        destroi();
        return -1;
    }
    if(!al_init_primitives_addon()){
        erroMsg("Algo deu errado na inicializacao do add-on de primitives");
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

    //atribuicao e criacao de componentes, como janela, imagens, fontes...
    janela = al_create_display(LARGURA_JANELA, ALTURA_JANELA);
    if(!janela){
        erroMsg("Algo deu errado na criacao da janela");
        destroi();
        return -1;
    }
    fundo = al_load_bitmap("fundoTeste.bmp");
    if(!fundo){
        erroMsg("Algo deu errado no carregamento do fundo");
        destroi();
        return -1;
    }
    filaDeEvento = al_create_event_queue();
    if(!filaDeEvento){
        erroMsg("Algo deu errado na criacao da fila de eventos");
        destroi();
        return -1;
    }
    timer = al_create_timer(1.0/FPS);
    if(!timer){
        erroMsg("Algo deu errado na criacao do timer");
        destroi();
        return -1;
    }

    //determinacao de quais eventos a fila de eventos vai guardar
    al_register_event_source(filaDeEvento, al_get_display_event_source(janela));
    al_register_event_source(filaDeEvento, al_get_keyboard_event_source());
    al_register_event_source(filaDeEvento, al_get_mouse_event_source());
    al_register_event_source(filaDeEvento, al_get_timer_event_source(timer));

    //inicio do timer
    al_start_timer(timer);

    return 1;
}

void atualizaCamera(double *camera, double x , double larguraSprite){
    *camera = -(LARGURA_JANELA / 2) + x;

    if(*camera>680.0){
        *camera = 680;
    }
    if(*camera<0.0){
        *camera = 0;
    }
}

void iniciaTimer(){
    tempoInicial = al_get_time();
}

double obterTempo(){
    return tempoInicial - al_get_time();
}

int main(){
    double px = 300, py = 410;
    init();

    while(!sair){
        iniciaTimer();
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch(evento.keyboard.keycode){
                    case ALLEGRO_KEY_LEFT:
                        tecla[0] = true;
                    break;
                    case ALLEGRO_KEY_RIGHT:
                        tecla[1] = true;
                    break;
                }
            }
            if(evento.type == ALLEGRO_EVENT_KEY_UP){
                switch(evento.keyboard.keycode){
                    case ALLEGRO_KEY_LEFT:
                        tecla[0] = false;
                    break;
                    case ALLEGRO_KEY_RIGHT:
                        tecla[1] = false;
                    break;
                }
            }
        }
        if(tecla[0]){
            px-=5;
        }
        if(tecla[1]){
            px+=5;
        }
        atualizaCamera(&posicaoCamera,px,100);

        al_identity_transform(&camera);
        al_translate_transform(&camera,-posicaoCamera, 0);
        al_use_transform(&camera);



        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo,0,0,0);
        if(posicaoCamera >= 300 && posicaoCamera <=350){
            al_draw_filled_circle(px,py,50,al_map_rgb(0,200,125));
        }
        else{
            al_draw_filled_circle(px,py,50,al_map_rgb(0,0,125));
        }
        al_flip_display();

        if(obterTempo() < 1.0 / FPS){
            al_rest((1.0/FPS)-obterTempo());
        }
    }

    destroi();
    return 1;
}
