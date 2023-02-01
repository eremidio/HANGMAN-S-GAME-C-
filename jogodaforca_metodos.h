//ESSE ARQUIVO CONTÉM OS MÉTODOS DA CLASSE DO APLICATIVO

/*CABEÇALHO*/
#include"jogodaforca.h"
#include<gtkmm.h>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<array> 
#include<cstdlib>
#include<ctime>
using namespace Glib;
using namespace Gtk;
using namespace std;

//DESTRUIDOR DA CLASSE
Game::~Game(){
delete help_window;
delete selector_window;
current_dictionary.clear();
             };

//CONSTRUTOR DA CLASSE
Game::Game():base(ORIENTATION_VERTICAL, 5), toolbar_box(ORIENTATION_VERTICAL, 5), output_box(ORIENTATION_HORIZONTAL, 5), label_box(ORIENTATION_VERTICAL, 5), label_box1(ORIENTATION_HORIZONTAL, 5), label_box2(ORIENTATION_HORIZONTAL, 5), draw_box(ORIENTATION_HORIZONTAL, 5), input_box(ORIENTATION_HORIZONTAL, 5), keyboard_box(ORIENTATION_HORIZONTAL, 5), guess_entry_box(ORIENTATION_VERTICAL, 5), lower_box(ORIENTATION_HORIZONTAL, 5), info_box(ORIENTATION_HORIZONTAL, 5), chooser_box(ORIENTATION_HORIZONTAL, 5), selector_box(ORIENTATION_VERTICAL, 5), selector_label_box(ORIENTATION_HORIZONTAL, 5), portuguese_box(ORIENTATION_HORIZONTAL, 5), english_box(ORIENTATION_HORIZONTAL, 5), spanish_box(ORIENTATION_HORIZONTAL, 5),chooser_buttonbox(ORIENTATION_HORIZONTAL), portuguese_checkbutton("Português"), english_checkbutton("Inglês"), spanish_checkbutton("Espanhol"), a_button("a"), b_button("b"), c_button("c"), d_button("d"), e_button("e"), f_button("f"), g_button("g"), h_button("h"), i_button("i"), j_button("j"), k_button("k"), l_button("l"), m_button("m"), n_button("n"), o_button("o"), p_button("p"), q_button("q"), r_button("r"), s_button("s"), t_button("t"), u_button("u"), v_button("v"), w_button("w"), x_button("x"), y_button("y"), z_button("z"), a1_button("á"), a2_button("â"), a3_button("ã"), e1_button("é"), e2_button("ê"), i1_button("í"), i2_button("î"), o1_button("ó"), o2_button("ô"), o3_button("õ"), u1_button("ú"), u2_button("û"), c1_button("ç"), n1_button("ñ"), guess_entry_button("Arriscar uma\npalavra"), chooser_button("Escolher\npalavra"), image0("0.png"), image1("1.png"), image2("2.png"), image3("3.png"), image4("4.png"), image5("5.png"), image6("6.png"), image7("7.png"), image8("8.png")
{
//BASE PARA LAYOUT DO APLICATIVO
add(base);
set_title("Jogo da forca");
set_border_width(10);
//AJUSTE DA JANELA DE CRÉDITOS
game_aboutdialog.set_transient_for(*this);
game_aboutdialog.set_logo_icon_name("mail-send");
game_aboutdialog.set_program_name("Jogo da forca");
game_aboutdialog.set_version("1.0");
game_aboutdialog.set_copyright("Elias Rodrigues Emídio");
game_aboutdialog.set_comments("Entre em contato com:\ne.r.emidio@yandex.com");
game_aboutdialog.set_license("LGPL");
vector<Glib::ustring> list_authors;
list_authors.push_back("Elias Rodrigues Emídio (Programação) e");
list_authors.push_back("Fernanda Mai Germana Silva (Vocabulário)");
game_aboutdialog.set_authors(list_authors);
game_aboutdialog.signal_response().connect(sigc::mem_fun(*this, &Game::close_credits));
//AJUSTANDO A BARRA DE FERRAMENTAS
base.pack_start(toolbar_box, PACK_SHRINK);
toolbar_box.pack_start(game_toolbar, PACK_SHRINK);
game_toolbar.set_toolbar_style(TOOLBAR_BOTH);
auto item1 = Gtk::make_managed<Gtk::ToolButton>("_Idioma");
item1->set_use_underline();
item1->set_icon_name("accessories-dictionary");
item1->set_homogeneous(true);
game_toolbar.append(*item1);
item1->signal_clicked().connect( sigc::mem_fun(*this,&Game::show_selector));
game_toolbar.append(*make_managed<Gtk::SeparatorToolItem>());
auto item2 = Gtk::make_managed<Gtk::ToolButton>("_Ajuda");
item2->set_use_underline();
item2->set_icon_name("help-faq");
item2->set_homogeneous(true);
game_toolbar.append(*item2);
item2->signal_clicked().connect( sigc::mem_fun(*this,&Game::help));
auto item3 = Gtk::make_managed<Gtk::ToolButton>("_Sobre");
item3->set_use_underline();
item3->set_icon_name("help-about");
item3->set_homogeneous(true);
game_toolbar.append(*item3);
item3->signal_clicked().connect( sigc::mem_fun(*this,&Game::about));
game_toolbar.append(*make_managed<Gtk::SeparatorToolItem>());
auto item4 = Gtk::make_managed<Gtk::ToolButton>("_Sair");
item4->set_use_underline();
item4->set_icon_name("application-exit");
item4->set_homogeneous(true);
game_toolbar.append(*item4);
item4->signal_clicked().connect( sigc::mem_fun(*this,&Game::quit));
//AJUSTANDO A ÁREA DE SAÍDA DE DADOS DO PROGRAMA
base.pack_start(output_box, PACK_EXPAND_WIDGET);
output_box.pack_start(draw_box);
draw_box.pack_start(draw_frame, PACK_EXPAND_WIDGET);
draw_frame.add(draw_scrolledwindow);
draw_scrolledwindow.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);
draw_scrolledwindow.add(image0);
image0.show();
output_box.pack_start(label_box);
label_box.pack_start(label_box1);
label_box1.pack_start(label_frame1, PACK_EXPAND_WIDGET);
label_frame1.set_shadow_type(SHADOW_NONE);
label_frame1.add(label1);
label_box.pack_start(label_separator, PACK_SHRINK);
label_box.pack_start(label_box2);
label_box2.pack_start(label_frame2, PACK_EXPAND_WIDGET);
label_frame2.set_shadow_type(SHADOW_NONE);
label_frame2.set_label("Tentativas:");
label_frame2.set_label_align(ALIGN_CENTER, ALIGN_END);
label_frame2.add(label2);
label2.set_line_wrap();
//AJUSTANDO A ÁREA DE ENTRADA DE DADOS
base.pack_start(input_box);
//TECLADO (CONTENDO BOTÕES COM AS LETRAS PARA ENTRADA DE UM CARACTÉRE POR VEZ)
input_box.pack_start(keyboard_box);
keyboard_box.pack_start(keyboard_frame, PACK_EXPAND_WIDGET);
keyboard_frame.set_shadow_type(SHADOW_NONE);
keyboard_frame.add(keyboard_grid);
keyboard_grid.set_row_homogeneous(true);
keyboard_grid.set_column_homogeneous(true);
//AJUSTANDO E ATIVANDO OS BOTÕES
keyboard_grid.attach(a_button, 0, 0, 1, 1);
a_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_a));
keyboard_grid.attach(b_button, 1, 0, 1, 1);
b_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_b));
keyboard_grid.attach(c_button, 2, 0, 1, 1);
c_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_c));
keyboard_grid.attach(d_button, 3, 0, 1, 1);
d_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_d));
keyboard_grid.attach(e_button, 4, 0, 1, 1);
e_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_e));
keyboard_grid.attach(f_button, 5, 0, 1, 1);
f_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_f));
keyboard_grid.attach(g_button, 6, 0, 1, 1);
g_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_g));
keyboard_grid.attach(h_button, 7, 0, 1, 1);
h_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_h));
keyboard_grid.attach(i_button, 8, 0, 1, 1);
i_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_i));
keyboard_grid.attach(j_button, 9, 0, 1, 1);
j_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_j));
keyboard_grid.attach(k_button, 10, 0, 1, 1);
k_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_k));
keyboard_grid.attach(l_button, 11, 0, 1, 1);
l_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_l));
keyboard_grid.attach(m_button, 12, 0, 1, 1);
m_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_m));
keyboard_grid.attach(n_button, 0, 1, 1, 1);
n_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_n));
keyboard_grid.attach(o_button, 1, 1, 1, 1);
o_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_o));
keyboard_grid.attach(p_button, 2, 1, 1, 1);
p_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_p));
keyboard_grid.attach(q_button, 3, 1, 1, 1);
q_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_q));
keyboard_grid.attach(r_button, 4, 1, 1, 1);
r_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_r));
keyboard_grid.attach(s_button, 5, 1, 1, 1);
s_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_s));
keyboard_grid.attach(t_button, 6, 1, 1, 1);
t_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_t));
keyboard_grid.attach(u_button, 7, 1, 1, 1);
u_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_u));
keyboard_grid.attach(v_button, 8, 1, 1, 1);
v_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_v));
keyboard_grid.attach(w_button, 9, 1, 1, 1);
w_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_w));
keyboard_grid.attach(x_button, 10, 1, 1, 1);
x_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_x));
keyboard_grid.attach(y_button, 11, 1, 1, 1);
y_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_y));
keyboard_grid.attach(z_button, 12, 1, 1, 1);
z_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_z));
keyboard_grid.attach(a1_button, 0, 3, 1, 1);
a1_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_a1));
keyboard_grid.attach(a2_button, 1, 3, 1, 1);
a2_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_a2));
keyboard_grid.attach(a3_button, 2, 3, 1, 1);
a3_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_a3));
keyboard_grid.attach(e1_button, 3, 3, 1, 1);
e1_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_e1));
keyboard_grid.attach(e2_button, 4, 3, 1, 1);
e2_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_e2));
keyboard_grid.attach(i1_button, 5, 3, 1, 1);
i1_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_i1));
keyboard_grid.attach(i2_button, 6, 3, 1, 1);
i2_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_i2));
keyboard_grid.attach(o1_button, 7, 3, 1, 1);
o1_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_o1));
keyboard_grid.attach(o2_button, 8, 3, 1, 1);
o2_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_o2));
keyboard_grid.attach(o3_button, 9, 3, 1, 1);
o3_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_o3));
keyboard_grid.attach(u1_button, 10, 3, 1, 1);
u1_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_u1));
keyboard_grid.attach(u2_button, 11, 3, 1, 1);
u2_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_u2));
keyboard_grid.attach(c1_button, 12, 3, 1, 1);
c1_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_c1));
keyboard_grid.attach(n1_button, 0, 4, 1, 1);
n1_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::input_n1));
//ENTRADA PARA CHUTE UMA PALAVRA INTEIRA
input_box.pack_start(guess_entry_box);
guess_entry_box.pack_start(guess_entry_grid, PACK_EXPAND_WIDGET);
guess_entry_grid.set_row_homogeneous(true);
guess_entry_grid.set_column_homogeneous(true);
guess_entry_grid.attach(guess_entry_frame, 0, 0, 1, 1);
guess_entry_frame.set_shadow_type(SHADOW_NONE);
guess_entry_frame.add(guess_entry);
guess_entry.set_visible(true);
guess_entry.set_visibility(true);
guess_entry.set_editable(true);
guess_entry_grid.attach(guess_entry_button_frame, 0, 1, 1, 1);
guess_entry_button_frame.set_shadow_type(SHADOW_NONE);
guess_entry_button_frame.add(guess_entry_button);
guess_entry_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::attempt));
//AJUSTE DA PARTE INFERIOR DA JANELA PRINCIPAL DO APLICATIVO
base.pack_start(lower_box, PACK_SHRINK);
lower_box.pack_start(info_box);
info_box.pack_start(info_frame);
info_frame.add(info_label);
info_label.set_text("PARA JOGAR O JOGO SELECIONE PRIMEIRO UM DICIONÁRIO DE PALAVRAS NA GUIA IDIOMA NO MENU ACIMA.");
info_label.set_line_wrap();
info_label.set_justify(JUSTIFY_FILL);
lower_box.pack_start(chooser_box);
chooser_box.pack_start(buttonbox_frame);
buttonbox_frame.set_shadow_type(SHADOW_NONE);
buttonbox_frame.add(chooser_buttonbox);
chooser_buttonbox.pack_start(chooser_button);
chooser_buttonbox.set_layout(BUTTONBOX_CENTER);
chooser_button.signal_clicked().connect(sigc::mem_fun(*this, &Game::choose_word));
//EXIBINDO TODOS OS WIDGETS
show_all_children();
//AJUSTE DA JANELA DE SELEÇÃO DE IDIOMAS
selector_window->set_title("Seleção de idiomas");
selector_window->set_default_size(400, 400);
selector_window->add(selector_box);
//RÓTULO
selector_box.pack_start(selector_label_box, PACK_EXPAND_WIDGET);
selector_label_box.pack_start(selector_label_frame, PACK_EXPAND_WIDGET);
selector_label_frame.set_shadow_type(SHADOW_NONE);
selector_label_frame.add(selector_label);
selector_label.set_text("ESCOLHA O IDIOMA DO QUAL PALAVRAS SERÃO SORTEADAS:");
selector_label.set_line_wrap();
//BOTÕES DE SELEÇÃO DE IDIOMAS
//PORTUGUÊS
selector_box.pack_start(selector_separator1, PACK_SHRINK);
selector_box.pack_start(portuguese_box, PACK_EXPAND_WIDGET);
portuguese_box.pack_start(portuguese_frame, PACK_EXPAND_WIDGET);
portuguese_frame.set_shadow_type(SHADOW_NONE);
portuguese_frame.add(portuguese_checkbutton);
portuguese_checkbutton.signal_toggled().connect(sigc::mem_fun(*this, &Game::load_portuguese));
//ESPANHOL
selector_box.pack_start(selector_separator2, PACK_SHRINK);
selector_box.pack_start(spanish_box, PACK_EXPAND_WIDGET);
spanish_box.pack_start(spanish_frame, PACK_EXPAND_WIDGET);
spanish_frame.set_shadow_type(SHADOW_NONE);
spanish_frame.add(spanish_checkbutton);
spanish_checkbutton.signal_toggled().connect(sigc::mem_fun(*this, &Game::load_spanish));
//INGLÊS
selector_box.pack_start(selector_separator3, PACK_SHRINK);
selector_box.pack_start(english_box, PACK_EXPAND_WIDGET);
english_box.pack_start(english_frame, PACK_EXPAND_WIDGET);
english_frame.set_shadow_type(SHADOW_NONE);
english_frame.add(english_checkbutton);
english_checkbutton.signal_toggled().connect(sigc::mem_fun(*this, &Game::load_english));
};

//MÉTODOS DA CLASSE
//FUNÇÕES DE USO GERAL
void Game::quit(){
hide();
                 };

void Game::about(){
game_aboutdialog.show();
game_aboutdialog.present();
                  };

void Game::close_credits(int response_id){
switch (response_id){
case Gtk::RESPONSE_CLOSE:
case Gtk::RESPONSE_CANCEL:
case Gtk::RESPONSE_DELETE_EVENT:
game_aboutdialog.hide();
break;

default:
break;
                    };
                                         };

void Game::help(){
help_window->set_default_size(550, 500);
help_window->show();
help_window->show_all_children();
help_window->set_title("Ajuda.");
                 };


//SELEÇÃO DE IDIOMAS DOS QUAIS AS PALAVRAS SERÃO SORTEADAS
void Game::show_selector(){
selector_window->show();
selector_window->show_all_children();
                          };

void Game::load_portuguese(){
current_dictionary.clear();
english_checkbutton.set_active(false);
spanish_checkbutton.set_active(false);
//CARREGANDO ARQUIVO
dictionary_portuguese.open("palavra.txt");

//EM CASO DE SUCESSO IMPORTAR PALAVRAS EM PORTUGUÊS
if(dictionary_portuguese.is_open()==true){
while(dictionary_portuguese.eof()==false){
dictionary_portuguese>>line;
current_dictionary.push_back(line);
                                         };
                                         }

//EM CASO DE ERRO AVISAR AO USUÁRIO
else if(dictionary_portuguese.is_open()==false){
MessageDialog dialog(*this, "ERRO FATAL:");
dialog.set_secondary_text("Impossível carregar o dicionário de palavras em português!!!");
dialog.run();
                                               };
dictionary_portuguese.close();
                            };

void Game::load_spanish(){
current_dictionary.clear();
english_checkbutton.set_active(false);
portuguese_checkbutton.set_active(false);
//CARREGANDO ARQUIVO
dictionary_spanish.open("palabra.txt");

//EM CASO DE SUCESSO IMPORTAR PALAVRAS EM ESPANHOL
if(dictionary_spanish.is_open()==true){
while(dictionary_spanish.eof()==false){
dictionary_spanish>>line;
current_dictionary.push_back(line);
                                         };
                                         }

//EM CASO DE ERRO AVISAR AO USUÁRIO
else if(dictionary_spanish.is_open()==false){
MessageDialog dialog(*this, "ERRO FATAL:");
dialog.set_secondary_text("Impossível carregar o dicionário de palavras em espanhol!!!");
dialog.run();
                                               };
dictionary_spanish.close();
                            };

void Game::load_english(){
current_dictionary.clear();
portuguese_checkbutton.set_active(false);
spanish_checkbutton.set_active(false);
//CARREGANDO ARQUIVO
dictionary_english.open("word.txt");

//EM CASO DE SUCESSO IMPORTAR PALAVRAS EM PORTUGUÊS
if(dictionary_english.is_open()==true){
while(dictionary_english.eof()==false){
dictionary_english>>line;
current_dictionary.push_back(line);
                                         };
                                         }

//EM CASO DE ERRO AVISAR AO USUÁRIO
else if(dictionary_english.is_open()==false){
MessageDialog dialog(*this, "ERRO FATAL:");
dialog.set_secondary_text("Impossível carregar o dicionário de palavras em inglês!!!");
dialog.run();
                                               };
dictionary_english.close();
                            };

//ESCOLHENDO UMA PALAVRA E AJUSTANDO O APP PARA INICIAR UMA RODADA
void Game::choose_word(){
//SEMENTE PARA GERAÇÃO DE NÚMEROS ALEATÓRIOS
srand(time(NULL));
//ESCOLHENDO UMA PALAVRA 
key=rand()%current_dictionary.size();
chosen_word=current_dictionary[key];
//GERANDO UMA STRING CIFRADA E ALOCANDO EM UMA VARIÁVEL GLOBAL
string coded_word_generator(chosen_word.length(), '*');
stringstream(coded_word_generator)>>coded_word;
//REMOVENDO HÍFENS E APÓSTROFOS DA PALAVRA SECRETA
//HÍFEN
guess="-";
pos=chosen_word.find(guess);
if(pos>chosen_word.length())
{pos=0;}
else
{coded_word.replace(pos, guess.length(), guess);
while(string::npos>(pos=chosen_word.find(guess, pos))){
coded_word.replace(pos, guess.length(), guess);
++pos;
                                                      };
};
//APÓSTROFO

guess="'";
pos=chosen_word.find(guess);
if(pos>chosen_word.length())
{pos=0;}
else
{coded_word.replace(pos, guess.length(), guess);
while(string::npos>(pos=chosen_word.find(guess, pos))){
coded_word.replace(pos, guess.length(), guess);
++pos;
                                                      };
};
//EXIBINDO A PALAVRA
label1.set_text(coded_word);
//ATUALIZANDO O APP
reset_app();
                        };

void Game::reset_app(){
//IMAGEM
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image0);
image0.show();
//TENTATIVAS JÁ TESTADAS
user_attempts_vector.clear();
user_attempts_vector.push_back("_0_");
user_attempts=" ";
label2.set_text(user_attempts);
//OUTROS AJUSTES
guess_entry.set_text("");
errors=0;
                      };

//FUNÇÕES DE ENTRADAS DE DADOS
//ENTRADA NA QUAL USUÁRIO TENTA ADIVINHAR UMA PALAVRA INTEIRA
void Game::attempt(){
guess=guess_entry.get_text();
main_function();
                    };

//BOTÕES DO TECLADO
void Game::input_a(){
guess="a";
main_function();
                    };

void Game::input_a1(){
guess="á";
main_function();
                     };

void Game::input_a2(){
guess="â";
main_function();
                    };

void Game::input_a3(){
guess="ã";
main_function();
                     };

void Game::input_b(){
guess="b";
main_function();
                    };

void Game::input_c(){
guess="c";
main_function();
                    };
void Game::input_c1(){
guess="ç";
main_function();
                     };

void Game::input_d(){
guess="d";
main_function();
                    };

void Game::input_e(){
guess="e";
main_function();
                    };

void Game::input_e1(){
guess="é";
main_function();
                     };

void Game::input_e2(){
guess="ê";
main_function();
                     };

void Game::input_f(){
guess="f";
main_function();
                    };

void Game::input_g(){
guess="g";
main_function();
                    };

void Game::input_h(){
guess="h";
main_function();
                    };
void Game::input_i(){
guess="i";
main_function();
                    };

void Game::input_i1(){
guess="í";
main_function();
                    };

void Game::input_i2(){
guess="î";
main_function();
                    };

void Game::input_j(){
guess="j";
main_function();
                    };

void Game::input_k(){
guess="k";
main_function();
                    };

void Game::input_l(){
guess="l";
main_function();
                    };

void Game::input_m(){
guess="m";
main_function();
                    };

void Game::input_n(){
guess="n";
main_function();
                    };

void Game::input_n1(){
guess="ñ";
main_function();
                    };

void Game::input_o(){
guess="o";
main_function();
                    };

void Game::input_o1(){
guess="ó";
main_function();
                    };

void Game::input_o2(){
guess="ô";
main_function();
                    };

void Game::input_o3(){
guess="õ";
main_function();
                    };

void Game::input_p(){
guess="p";
main_function();
                    };

void Game::input_q(){
guess="q";
main_function();
                    };

void Game::input_r(){
guess="r";
main_function();
                    };

void Game::input_s(){
guess="s";
main_function();
                    };

void Game::input_t(){
guess="t";
main_function();
                    };

void Game::input_u(){
guess="u";
main_function();
                    };

void Game::input_u1(){
guess="ú";
main_function();
                    };

void Game::input_u2(){
guess="û";
main_function();
                    };

void Game::input_v(){
guess="v";
main_function();
                    };

void Game::input_w(){
guess="w";
main_function();
                    };

void Game::input_x(){
guess="x";
main_function();
                    };

void Game::input_y(){
guess="y";
main_function();
                    };

void Game::input_z(){
guess="z";
main_function();
                    };

//FUNÇÕES AUXILÍARES
void Game::count_error(){
errors++;
if(errors==1){
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image1);
image1.show();
             };
if(errors==2){
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image2);
image2.show();
             };
if(errors==3){
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image3);
image3.show();
             };
if(errors==4){
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image4);
image4.show();
             };
if(errors==5){
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image5);
image5.show();
             };
if(errors==6){
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image6);
image6.show();
             };
if(errors==7){
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image7);
image7.show();
             };
if(errors==8){
draw_scrolledwindow.remove();
draw_scrolledwindow.add(image8);
image8.show();
warning_game_over();
             };


                        };

void Game::warning_game_over(){
MessageDialog dialog(*this,"GAME OVER!!!");
//VARIÁVEL TEMPORÁRIA
string dialog_text="Você cometeu oito erros\nA palavra secreta é:\n";
dialog_text+=chosen_word;
dialog_text+=".\nTente novamente.\n";
dialog.set_secondary_text(dialog_text);
dialog.run();
                        };

void Game::warning_repetition(){
MessageDialog dialog(*this,"Atenção!!!");
dialog.set_secondary_text("Tentativa repetida detectada.\nTente novamente!!");
dialog.run();
                        };

void Game::warning_win(){
MessageDialog dialog(*this,"PARABÉNS, VOCÊ GANHOU!!!");
//VARIÁVEL TEMPORÁRIA
string dialog_text="A palavra secreta é:\n";
dialog_text+=chosen_word;
dialog_text+=".\nObrigado por jogar.\nClique no botão 'Escolher palavra' para jogar novamente.";
dialog.set_secondary_text(dialog_text);
dialog.run();
                        };

//FUNÇÃO PRINCIPAL (ESTA FUNÇÃO ENTRE OUTRAS COISAS CHECA SE O PALPITE DO USUÁRIO É UM ACERTO OU NÃO, CONTABILIZA ERROS E TENTATIVAS REPETIDAS ALÉM DE  INFORMAR O STATUS DO JOGO AO USUÁRIO)
void Game::main_function(){
//CHECANDO SE O USUÁRIO COMETEU ALGUMA TENTATIVA REPETIDA E ATUALIZANDO A LISTA DE TENTATIVAS FEITAS
//INFORMANDO REPETIÇÕES
for(auto i:user_attempts_vector){
if(guess==i){
warning_repetition();
return;
            };
                                };
//ATUALIZANDO A LISTA DE TENTATIVAS  E EXIBINDO O RESULTADO PARA O USUÁRIO
user_attempts+="-";
user_attempts+=guess;
user_attempts_vector.push_back(guess);
label2.set_text(user_attempts);
                              
//CHECANDO SE A TENTATIVA DO USUÁRIO É UM ACERTO OU ERRO
pos=chosen_word.find(guess);
//COMPUTANDO ERROS
if(pos>chosen_word.length()){
pos=0;
count_error();
return;
                            }
//EM CASO DE ACERTO SUSBSTITUIR TODAS AS OCORRÊNCIAS DA TENTATIVA NA PALAVRA SECRETA
else
{
coded_word.replace(pos, guess.length(), guess);
while(string::npos>(pos=chosen_word.find(guess, pos))){
coded_word.replace(pos, guess.length(), guess);
++pos;
                                                      };
//EXIBINDO A PALAVRA
label1.set_text(coded_word);
};

//INFORMANDO O USUÁRIO DO SUCESSO AO ACERTAR A PALAVRA
if(coded_word==chosen_word)
warning_win();
                          };
