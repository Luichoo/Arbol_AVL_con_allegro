// Proyecto Arbol.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "arbol.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
void imprime_arbol(A* inicio, ALLEGRO_FONT* titulo, int cont, int cont2);
int main()
{
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();//los dos son para escribir textos;
    al_init_ttf_addon();
    
    bool siono = false;// para el loop del while
    bool siono2 = false;// 
    A* inicio, * aux;
    int opc = 0, num, x = 1, y = 1, b = 1, b2 = 0, checa2 = 0, balanceos[2][50] = { 0 }, i = 0, j = 0, cont1= 0, band = 0;
    short int checa=0;
    inicio = NULL;

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();//no entiendo pero es como para checar eventos
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);//los fps
    ALLEGRO_DISPLAY* display = al_create_display(1540, 980);//Esto es el tamaño de la pantalla, display es como una variable tipo allegro
    ALLEGRO_FONT * f1 = al_load_font("GODOFWAR.TTF", 20, 0);//asignas el nombre a la variable para usarla
    ALLEGRO_FONT * fnum = al_load_font("uwch.ttf", 20, 0);//asignas el nombre a la variable para usarla
    ALLEGRO_FONT* titulo = al_load_font("Arcade.ttf", 30, 0);
    al_set_window_title(display, "Arbol AVL");//titulo de la pantalla
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//como para registrar el evento o algo asi
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    while (!siono) {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

 
        if (opc == 0) {
            num = 0;
            b = 1;
            b2 = 0;
            if (events.type == ALLEGRO_EVENT_TIMER); {

                if (x > 20 && x < 190 && y>70 && y < 139)
                {
                    al_draw_rectangle(20, 70, 190, 139, al_map_rgb(255, 255, 255), 6);
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)// al hacer click entra al juego
                    {
                        b = 0;
                        opc = 1;
                    }
                }
                else
                    al_draw_rectangle(20, 70, 190, 139, al_map_rgb(169, 161, 157), 4);//visual del menu
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                if (x > 20 && x < 190 && y>170 && y < 239)
                {
                    al_draw_rectangle(20, 170, 190, 239, al_map_rgb(255, 255, 255), 6);//visual del menu
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) { // al hacer click borra un elemento
                        b = 0;
                        opc = 2;                   
                    }
                }
                else
                    al_draw_rectangle(20, 170, 190, 239, al_map_rgb(169, 161, 157), 4);//visual del menu
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                if (x > 20 && x < 190 && y>270 && y < 339)
                {
                    
                    al_draw_rectangle(20, 270, 190, 339, al_map_rgb(255, 255, 255), 6);//visual del menu
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)// al hacer click en salir sale del juego
                    {   
                         siono = true;
                    }
                       
                }
                else
                    al_draw_rectangle(20, 270, 190, 339, al_map_rgb(169, 161, 157), 4);//visual del menu
           //////////////////////////////////////////////////////////////////////////////////////////////////////////////    
             
                if (!inicio) {
                    al_draw_rectangle(420, 70, 990, 339, al_map_rgb(169, 161, 157),4);//visual del menu
                    al_draw_filled_rectangle(420, 70, 990, 339, al_map_rgb(64, 45, 60));//visual del menu
                    al_draw_text(titulo, al_map_rgb(255, 255, 255), 620, 109, 0, "BIENVENID@");
                    }
                else {
                    imprime_arbol(inicio, titulo, 0, 0);
                }
                al_draw_filled_rectangle(20, 70, 190, 139, al_map_rgb(64, 45, 60));//visual del menu
                al_draw_filled_rectangle(20, 170, 190, 239, al_map_rgb(64, 45, 60));//visual del menu

                al_draw_filled_rectangle(20, 270, 190, 339, al_map_rgb(64, 45, 60));//visual del menu
                al_draw_text(f1, al_map_rgb(255, 255, 255), 62, 95, 0, "Inserta");
                al_draw_text(f1, al_map_rgb(255, 255, 255), 73, 195, 0, "Borra");
                al_draw_text(f1, al_map_rgb(255, 255, 255), 74, 295, 0, "Salir"); 
            }
            
        }
al_draw_rectangle(20, 10, 190, 50, al_map_rgb(169, 161, 157), 4);//titulo
                al_draw_filled_rectangle(20, 10, 190, 50, al_map_rgb(64, 45, 60));//visual del menu
al_draw_text(titulo, al_map_rgb(255, 255, 255), 30, 20, 0, "ARBOL AVL");
if (opc != 0) {
    if (events.type == ALLEGRO_EVENT_TIMER); {
        if (x > 20 && x < 190 && y > 10 && y <50) {
            al_draw_rectangle(20, 10, 190, 50, al_map_rgb(255, 255, 255), 6);
            if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
              b = 0;
              opc = 0;
              al_draw_filled_rectangle(0, 0, 1540, 980, al_map_rgb(0, 0, 0));
            }
        }
        else {
            al_draw_rectangle(620, 180, 700, 140, al_map_rgb(169, 161, 157), 4);
        }
    }
}
if (i != 0) {
    for (j = 0, cont1 = 0; j < i; j++) {
        al_draw_rectangle(420, 100 + cont1, 990, 180 + cont1, al_map_rgb(169, 161, 157), 4);//visual del menu
        al_draw_filled_rectangle(420, 100 + cont1, 990, 180 + cont1, al_map_rgb(64, 45, 60));//visual del menu
        al_draw_textf(titulo, al_map_rgb(255, 255, 255), 520, 109 + cont1, 0, "desbalanceo en el nodo %d", balanceos[1][j]);
        switch (balanceos[0][j]) {
        case 3:
            al_draw_text(titulo, al_map_rgb(255, 255, 255), 430, 139 + cont1, 0, "se aplico un balanceo hacia la derecha");
            break;
        case 4:
            al_draw_text(titulo, al_map_rgb(255, 255, 255), 430, 139 + cont1, 0, "se hizo un balanceo derecha-izquierda");
            break;
        case 1:
            al_draw_text(titulo, al_map_rgb(255, 255, 255), 430, 139 + cont1, 0, "se aplico un balanceo hacia la izquierda");
            break;
        case 2:
            al_draw_text(titulo, al_map_rgb(255, 255, 255), 430, 139 + cont1, 0, "se hizo un balanceo izquierda-derecha");
            break;
        default:
            break;
        }
        cont1 = cont1 + 100;
    }
    if (events.type == ALLEGRO_EVENT_TIMER); {
        if (x > 1100 && x < 1300 && y > 110 + cont1 && y < 170 + cont1) {
            al_draw_rectangle(1300, 110 + cont1, 1100, 170 + cont1, al_map_rgb(255, 255, 255), 6);//Boton de confirmar
            if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                b = 0;
                opc = 0;
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 50; j++) {
                        balanceos[i][j] = 0;
                    }
                }

                i = 0;
            }
        }
        else {
            al_draw_rectangle(1300, 110 + cont1, 1100, 170 + cont1, al_map_rgb(169, 161, 157), 4);//Boton de confirmar
        }
    }

    al_draw_filled_rectangle(1300, 110 + cont1, 1100, 170 + cont1, al_map_rgb(64, 45, 60));//Boton de confirmar
    al_draw_text(titulo, al_map_rgb(255, 255, 255), 1140, 130 + cont1, 0, "Continuar");
    if (i == 0) {
        al_draw_filled_rectangle(0, 0, 1540, 980, al_map_rgb(0, 0, 0));
    }
}
        if (opc == 1) {//insercion de dato
            checa2 = 0;

            if (events.type == ALLEGRO_EVENT_TIMER); {
                if (x > 620 && x < 700 && y < 180 && y >140) {
                    al_draw_rectangle(620, 180, 700, 140, al_map_rgb(255, 255, 255), 6);
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                        num = num + 1;
                        b2 = 0;
                    }
                }
                else {
                    al_draw_rectangle(620, 180, 700, 140, al_map_rgb(169, 161, 157), 4);
                }
                  if (x > 620 && x < 700 && y < 380 && y >340) {
                      al_draw_rectangle(620, 380, 700, 340, al_map_rgb(255, 255, 255), 6);
                       if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                           num = num - 1;
                           b2 = 0;
                       }
                   }
                   else {
                   al_draw_rectangle(620, 380, 700, 340, al_map_rgb(169, 161, 157), 4);
                   }
                    if (x > 420 && x < 500 && y < 180 && y >140) {
                        al_draw_rectangle(420, 180, 500, 140, al_map_rgb(255, 255, 255), 6);
                       if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                           num = num + 10;
                           b2 = 0;
                       }
                   }
                   else {
                        al_draw_rectangle(420, 180, 500, 140, al_map_rgb(169, 161, 157), 4);
                   }
                   if (x > 420 && x < 500 && y < 380 && y >340) {
                       al_draw_rectangle(420, 380, 500, 340, al_map_rgb(255, 255, 255), 6);
                       if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                           num = num - 10;
                           b2 = 0;
                       }
                   }
                   else {
                       al_draw_rectangle(420, 380, 500, 340, al_map_rgb(169, 161, 157), 4);
                   }
                   if (x < 900 && x > 700 && y < 270 && y >230) {//aceptar numero
                       al_draw_rectangle(900, 270, 700, 230, al_map_rgb(255, 255, 255), 6);
                       if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                         checa = 0;
                         system("cls");
                         checa2 = 1;
                           if (inicio) {
                               checa2 = 1;
                               if (num == inicio->numero) {
                                   checa2 = 0;
                               }
                               else {
                                     checa_repetidos(&checa2,num,inicio);
                               }

                           }
                           else {
                               checa2 = 1;
                           }
                           if (checa2 == 0) {
                               b2 = 1;
                           }
                           else {
                               checa = inserta_dato(&inicio,num);
                               if (checa == 1) {
                                i = 0;
                                if (inicio->hijo_derecha || inicio->hijo_izquierda) {
                                    aux = inicio;
                                    band = 1;
                                    system("cls");
                                    while (band == 1)
                                    {
                                        band = 0;
                                    Checa_Balanceo(&inicio, balanceos,&i,&band);
                                     revalida_altura(inicio, 0);
                                    }
                                }
                                    b = 0;
                                    opc = -1;
                                    if(i==0)
                                    opc = 0;
                               }
                               
                           }
                       }
                   }
                   else {
                        al_draw_rectangle(900, 270, 700, 230, al_map_rgb(169, 161, 157), 4);
                   }
             /*      if (i != 0) {
                       for (j = 0,cont1 = 0; j < i; j++,cont1+100) {
                           al_draw_rectangle(420, 100 + cont1, 990, 180 + cont1, al_map_rgb(169, 161, 157), 4);//visual del menu
                           al_draw_filled_rectangle(420, 100 + cont1, 990, 180 + cont1, al_map_rgb(64, 45, 60));//visual del menu
                           al_draw_textf(titulo, al_map_rgb(255, 255, 255), 520, 109 + cont1, 0, "desbalanceo en el nodo %d",balanceos[1][i]);
                           switch (balanceos[0][i]) {
                           case 1:
                            al_draw_text(titulo, al_map_rgb(255, 255, 255), 430, 139 + cont1, 0, "se aplico un balanceo hacia la derecha");
                               break;
                           case 2:
                               al_draw_text(titulo, al_map_rgb(255, 255, 255), 430, 139 + cont1, 0, "se hizo un balanceo derecha-izquierda");
                               break;
                           case 3:
                               al_draw_text(titulo, al_map_rgb(255, 255, 255), 430, 139 + cont1, 0, "se aplico un balanceo hacia la izquierda");
                               break;
                           case 4:
                               al_draw_text(titulo, al_map_rgb(255, 255, 255), 430, 139 + cont1, 0, "se hizo un balanceo izquierda-derecha");
                               break;
                           default:
                               break;
                           }      
                       }
                       if (events.type == ALLEGRO_EVENT_TIMER); {
                           if (x > 1100 && x < 1300 && y > 110 + cont1 && y < 170 + cont1) {
                               al_draw_rectangle(1300, 110 + cont1, 1100, 170 + cont1, al_map_rgb(255, 255, 255), 6);//Boton de confirmar
                               if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                                   b = 0;
                                   opc = 0;
                                   for (i = 0; i < 2; i++) {
                                       for (j = 0; j < 50; i++) {
                                           balanceos[i][j] = 0;
                                       }
                                   }
                                   i = 0;
                               }
                           }
                           else {
                               al_draw_rectangle(1300, 110 + cont1, 1100, 170 + cont1, al_map_rgb(169, 161, 157), 4);//Boton de confirmar
                           }
                       }

                       al_draw_filled_rectangle(1300, 110 + cont1, 1100, 170 + cont1, al_map_rgb(64, 45, 60));//Boton de confirmar
                       al_draw_text(titulo, al_map_rgb(255, 255, 255), 1140, 130 + cont1, 0, "Continuar");
                   }*/
                   if (b2 == 1) {
al_draw_rectangle(20, 170, 300, 320, al_map_rgb(169, 161, 157), 4);//titulo
al_draw_filled_rectangle(20, 170, 300, 320, al_map_rgb(64, 45, 60));//visual del menu
al_draw_text(titulo, al_map_rgb(255, 255, 255), 55, 200, 0, "Ese numero ya ");
al_draw_text(titulo, al_map_rgb(255, 255, 255), 105, 230, 0, " existe");
al_draw_text(titulo, al_map_rgb(255, 255, 255), 25, 260, 0, " intentelo con otro");                       
                   }
                   al_draw_rectangle(420, 10, 700, 120, al_map_rgb(169, 161, 157), 4);//titulo
                   al_draw_filled_rectangle(420, 10, 700, 120, al_map_rgb(64, 45, 60));//visual del menu
                al_draw_filled_rectangle(620, 180, 700, 140, al_map_rgb(64, 45, 60)); //+1
                al_draw_filled_rectangle(620, 380, 700, 340, al_map_rgb(64, 45, 60));// -1
                al_draw_filled_rectangle(420, 180, 500, 140, al_map_rgb(64, 45, 60)); //+10
                al_draw_filled_rectangle(420, 380, 500, 340, al_map_rgb(64, 45, 60));// -10
                al_draw_rectangle(600, 270, 530, 230, al_map_rgb(169, 161, 157), 4);//Valor del num
                
                al_draw_filled_rectangle(900, 270, 700, 230, al_map_rgb(64, 45, 60));//Boton de confirmar
                al_draw_filled_rectangle(600, 270, 530, 230, al_map_rgb(64, 45, 60));//visual del num
               // al_draw_rectangle(700, 200, 470, 50, al_map_rgb(169, 161, 157), 4);//titulo
               // checa = inserta_dato(&inicio);
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 645, 350, 0, "-1");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 645, 150, 0, "+1");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 440, 350, 0, "-10");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 440, 150, 0, "+10");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 425, 35, 0, "Ingrese numero que");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 465, 65, 0, "desee agregar");
                al_draw_textf(titulo, al_map_rgb(255, 255, 255), 540, 240, 0, "%d",num);
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 740, 240, 0, "Confirmar");
            }

        }
        if (opc == 2) {//borrado
            if (events.type == ALLEGRO_EVENT_TIMER); {
                if (x > 620 && x < 700 && y < 180 && y >140) {
                    al_draw_rectangle(620, 180, 700, 140, al_map_rgb(255, 255, 255), 6);
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                        num = num + 1;
                        b2 = 0;
                    }
                }
                else {
                    al_draw_rectangle(620, 180, 700, 140, al_map_rgb(169, 161, 157), 4);
                }
                if (x > 620 && x < 700 && y < 380 && y >340) {
                    al_draw_rectangle(620, 380, 700, 340, al_map_rgb(255, 255, 255), 6);
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                        num = num - 1;
                        b2 = 0;
                    }
                }
                else {
                    al_draw_rectangle(620, 380, 700, 340, al_map_rgb(169, 161, 157), 4);
                }
                if (x > 420 && x < 500 && y < 180 && y >140) {
                    al_draw_rectangle(420, 180, 500, 140, al_map_rgb(255, 255, 255), 6);
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                        num = num + 10;
                        b2 = 0;
                    }
                }
                else {
                    al_draw_rectangle(420, 180, 500, 140, al_map_rgb(169, 161, 157), 4);
                }
                if (x > 420 && x < 500 && y < 380 && y >340) {
                    al_draw_rectangle(420, 380, 500, 340, al_map_rgb(255, 255, 255), 6);
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                        num = num - 10;
                        b2 = 0;
                    }
                }
                else {
                    al_draw_rectangle(420, 380, 500, 340, al_map_rgb(169, 161, 157), 4);
                }
                if (x < 900 && x > 700 && y < 270 && y >230) {//aceptar numero
                    al_draw_rectangle(900, 270, 700, 230, al_map_rgb(255, 255, 255), 6);
                    if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                        checa = 0;
                        if (inicio) {
                           
                            aux = inicio;
                            checa = Busca_nodo(&aux, num);
                            if (checa == 1) {
                                b = 0;
                            }
                            else if (checa == 0) b2 = 1;
                            else if (checa == -1) {
                                inicio = NULL;
                                free(inicio);
                                b = 0;
                            }
                            else if (checa == -2) {

                                inicio = elimina_raiz(&inicio);
                                b = 0;
                            }
                            if (checa != 0) {
                                num = 0;
                                i = 0;
                                if (inicio->hijo_derecha || inicio->hijo_izquierda) {
                                    band = 1;
                                    while (band == 1)
                                    {
                                        band = 0;
                                        Checa_Balanceo(&inicio, balanceos, &i, &band);
                                        revalida_altura(inicio, 0);
                                    }
                                }
                                b = 0;
                                opc = -1;
                                if(i==0)
                                opc = 0;
                            }
                        }
                        else{
                            b2 = 2;
                        }
                    }
                }
                else {
                    al_draw_rectangle(900, 270, 700, 230, al_map_rgb(169, 161, 157), 4);
                }
                if (b2 == 1) {
                    al_draw_rectangle(20, 170, 300, 320, al_map_rgb(169, 161, 157), 4);//titulo
                    al_draw_filled_rectangle(20, 170, 300, 320, al_map_rgb(64, 45, 60));//visual del menu
                    al_draw_text(titulo, al_map_rgb(255, 255, 255), 55, 200, 0, "Ese numero no ");
                    al_draw_text(titulo, al_map_rgb(255, 255, 255), 105, 230, 0, " existe");
                    al_draw_text(titulo, al_map_rgb(255, 255, 255), 25, 260, 0, " intentelo con otro");
                }
                if (b2 == 2) {
                    al_draw_rectangle(20, 170, 300, 320, al_map_rgb(169, 161, 157), 4);//titulo
                    al_draw_filled_rectangle(20, 170, 300, 320, al_map_rgb(64, 45, 60));//visual del menu
                    al_draw_text(titulo, al_map_rgb(255, 255, 255), 55, 200, 0, "No hay datos ");
                    al_draw_text(titulo, al_map_rgb(255, 255, 255), 105, 230, 0, " para");
                    al_draw_text(titulo, al_map_rgb(255, 255, 255), 45, 260, 0, " eliminar");
                }
                al_draw_rectangle(420, 10, 700, 120, al_map_rgb(169, 161, 157), 4);//titulo
                al_draw_filled_rectangle(420, 10, 700, 120, al_map_rgb(64, 45, 60));//visual del menu
                al_draw_filled_rectangle(620, 180, 700, 140, al_map_rgb(64, 45, 60)); //+1
                al_draw_filled_rectangle(620, 380, 700, 340, al_map_rgb(64, 45, 60));// -1
                al_draw_filled_rectangle(420, 180, 500, 140, al_map_rgb(64, 45, 60)); //+10
                al_draw_filled_rectangle(420, 380, 500, 340, al_map_rgb(64, 45, 60));// -10
                al_draw_rectangle(600, 270, 530, 230, al_map_rgb(169, 161, 157), 4);//Valor del num

                al_draw_filled_rectangle(900, 270, 700, 230, al_map_rgb(64, 45, 60));//Boton de confirmar
                al_draw_filled_rectangle(600, 270, 530, 230, al_map_rgb(64, 45, 60));//visual del num
               // al_draw_rectangle(700, 200, 470, 50, al_map_rgb(169, 161, 157), 4);//titulo
               // checa = inserta_dato(&inicio);
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 645, 350, 0, "-1");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 645, 150, 0, "+1");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 440, 350, 0, "-10");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 440, 150, 0, "+10");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 425, 35, 0, "Ingrese numero que");
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 465, 65, 0, "desee borrar");
                al_draw_textf(titulo, al_map_rgb(255, 255, 255), 540, 240, 0, "%d", num);
                al_draw_text(titulo, al_map_rgb(255, 255, 255), 740, 240, 0, "Confirmar");
            }

    }
    if (b == 0) {
        b = 1;
        al_draw_filled_rectangle(0, 0, 1540, 980, al_map_rgb(0, 0, 0));
    }
        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            siono = true;
        }
        if (events.type == ALLEGRO_EVENT_MOUSE_AXES)// x y son las coordenadas del mouse 
        {
            x = events.mouse.x;
            y = events.mouse.y;
        }
        al_flip_display();
    }
    al_destroy_display(display);
    al_destroy_font(f1);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////
void imprime_arbol(A*inicio, ALLEGRO_FONT* titulo,int cont,int cont2){
    if (inicio) {
        int b = 0,aux=0,aux2=0;


        al_draw_filled_circle(700 - cont, 120 + cont2, 40, al_map_rgb(64, 45, 60));
        al_draw_circle(700 - cont, 120 + cont2, 40, al_map_rgb(169, 161, 157), 4);
        al_draw_textf(titulo, al_map_rgb(255, 255, 255), 690-cont, 109+cont2, 0, "%d",inicio->numero);
        if (inicio->hijo_izquierda) {
            if (inicio->padre) {
                 al_draw_line(600 - cont, 200 + cont2, 663 - cont, 140 + cont2, al_map_rgb(169, 161, 157), 4);

            }
            else {
                cont = 105;
                cont2 = 50;
                al_draw_line(530  , 250 , 663, 140, al_map_rgb(169, 161, 157), 4);
            }
           
            imprime_arbol(inicio->hijo_izquierda,titulo,cont+90,cont2+100);
        }
        if (inicio->hijo_derecha) {
            if (inicio->padre) {
                al_draw_line(735 - cont, 140 + cont2, 800 - cont , 200 + cont2, al_map_rgb(169, 161, 157), 4);
            }
            else {
               cont = -200;
               cont2 = 30;
                al_draw_line(740, 130, 1000, 230, al_map_rgb(169, 161, 157), 4);
            }
           
            imprime_arbol(inicio->hijo_derecha,titulo, cont -120, cont2 +  90);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////