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
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>

//constantes
const int FPS = 60;
const int LARGURA_JANELA = 1200;
const int ALTURA_JANELA = 600;
enum teclas {IDDLE = 1, LEFT, RIGHT};

//ponteiros
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *filaDeEvento = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *fundo = NULL;
ALLEGRO_BITMAP *link = NULL;
ALLEGRO_FONT *fonte = NULL;

//variaveis globais
bool sair = false,acao = false;
double tempoInicial = 0;
int pos = IDDLE, score = 0;
float cameraPositionX = 0;
bool teclas[2] = {false,false};
ALLEGRO_TRANSFORM camera;

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
    if(filaDeEvento){
        al_destroy_event_queue(filaDeEvento);
    }
    if(timer){
        al_destroy_timer(timer);
    }
    if(fundo){
        al_destroy_bitmap(fundo);
    }
    if(link){
        al_destroy_bitmap(link);
    }
    if(fonte){
        al_destroy_font(fonte);
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
    fundo = al_load_bitmap("fundoTeste.png");
    if(!fundo){
        erroMsg("Algo deu errado no carregamento do fundo");
        destroi();
        return -1;
    }
    link = al_load_bitmap("link.png");
    if(!link){
        erroMsg("Algo deu errado no carregamento do personagem");
        destroi();
        return -1;
    }
    fonte = al_load_ttf_font("pixelFont.ttf",14,ALLEGRO_ALIGN_CENTER);
    if(!fonte){
        erroMsg("Algo deu errado no carregamento da fonte");
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

void inicioTimer(){
    tempoInicial = al_get_time();
}
double tempo(){
    return al_get_time() - tempoInicial;
}

void atualizaCamera(float *posicaoCamera, float playerPositionX, float playerWidth){
    *posicaoCamera = -(LARGURA_JANELA/2) + (playerPositionX+playerWidth/2) ;
    if(*posicaoCamera<= 0)
        *posicaoCamera = 0;
    if(*posicaoCamera>=2000-LARGURA_JANELA)
        *posicaoCamera = 2000-LARGURA_JANELA;
}

int main(){
    float px = 300, py = 470;
    float sx = 0, sy = 0;
    float sw = 96, sh = 104;
    int frame = 0,alfa = 0;
    init();
    while(!sair){
        inicioTimer();
        acao = false;
        while(!al_event_queue_is_empty(filaDeEvento)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaDeEvento, &evento);
            if(evento.type == ALLEGRO_EVENT_KEY_UP){
                if(evento.keyboard.keycode == ALLEGRO_KEY_LEFT){
                    teclas[0] = false;
                    pos = pos==LEFT?IDDLE:pos;
                }
                if(evento.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                    teclas[1] = false;
                    pos = pos==RIGHT?IDDLE:pos;
                }
            }
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_LEFT){
                    teclas[0] = true;
                    pos = LEFT;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                    teclas[1] = true;
                    pos = RIGHT;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    acao = true;
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    score++;
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true;
            }
        }
        frame++;
        if(pos == LEFT){
            if(frame >= 6){
                frame = 0;
                sy = 5 * sh;
                sx += 96;
            }
            px -= 5;
        }
        else if(pos == RIGHT){
            if(frame >= 6){
                frame = 0;
                sy = 7 * sh;
                sx += 96;
            }
            px += 5;
        }
        else if(pos == IDDLE){
            sy = 0;
            sx = 0;
        }
        if(sx >= 10*96){
            sx = 0;
        }


        atualizaCamera(&cameraPositionX,px,sw);

        al_identity_transform(&camera);
        al_translate_transform(&camera,-cameraPositionX,0);
        al_use_transform(&camera);



        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fundo,0,0,0);
        al_draw_bitmap_region(link,sx,sy,sw,sh,px,py,0);
        al_draw_textf(fonte,al_map_rgb(0,0,0),LARGURA_JANELA/2, 100,0,"score: %d",score);
        if(px>= 30 && px<= 140){
            if(alfa<255){
                alfa += 5;
            }else{
                alfa = 255;
            }
            al_draw_text(fonte,al_map_rgba(0,0,0,alfa),px,py-100,0,"pressione espaco para salvar");
            if(acao){
                DIR *pastaSave = mkdir("save");
                FILE *save = fopen("save/save.txt","w");
                fprintf(save,"%d",score);
                fclose(save);
            }
        }
        else{
            alfa = 0;
        }
        al_flip_display();

        if(tempo()<1.0/FPS){
            al_rest((1.0/FPS) - tempo());
        }
    }

    destroi();
    return 1;
}
