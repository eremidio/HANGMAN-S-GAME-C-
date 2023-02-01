//ESTE ARQUIVO CONTÉM A CLASSE DO APLICATIVO DO JOGO

/*CABEÇALHO*/
#include"jogodaforca_ajuda.h"
#include<gtkmm.h>
#include<vector>
#include<string>
#include<fstream>
using namespace Glib;
using namespace Gtk;
using namespace std;

class Game: public Window{
public:
//CONTRUTOR E DESTRUIDOR DA CLASSE
Game();
virtual ~Game();
//VARIÁVEIS DE BACK-END
ustring chosen_word, coded_word, guess, line, user_attempts;
vector<ustring> current_dictionary;
vector<ustring> user_attempts_vector;
ifstream dictionary_portuguese, dictionary_spanish, dictionary_english;
size_t pos;
int key, errors, i
;

//WIDGETS
//JANELA DE AJUDA
HelpWindow* help_window=new HelpWindow;

//JANELA DE SELEÇÃO
Window* selector_window = new Window;
Box selector_box, portuguese_box, english_box, spanish_box, selector_label_box;
Frame selector_label_frame, portuguese_frame, english_frame, spanish_frame;
Separator selector_separator1, selector_separator2, selector_separator3;
CheckButton portuguese_checkbutton, english_checkbutton, spanish_checkbutton;
Label selector_label;

//BASE PARA OS DEMAIS WIDGETS
Box base;
//CRÉDITOS
AboutDialog game_aboutdialog;

//BARRA DE FERRAMENTAS
Box toolbar_box;
Toolbar game_toolbar;

//ÁREA DE SÁIDA DE DADOS
Box output_box, label_box, label_box1, label_box2, draw_box;
Frame draw_frame, label_frame1, label_frame2;
Separator label_separator;
ScrolledWindow draw_scrolledwindow;
Label label1, label2;
Image image0, image1, image2, image3, image4, image5, image6, image7, image8;

//ÁREA DE ENTRADA DE DADOS
Box input_box, keyboard_box, guess_entry_box;
Frame keyboard_frame, guess_entry_frame, guess_entry_button_frame;
Grid keyboard_grid, guess_entry_grid;
Button a_button, b_button, c_button, d_button, e_button, f_button, g_button, h_button, i_button, j_button, k_button, l_button, m_button, n_button, o_button, p_button, q_button, r_button, s_button, t_button, u_button, v_button, w_button, x_button, y_button, z_button, a1_button, a2_button, a3_button, e1_button, e2_button, i1_button, i2_button, o1_button, o2_button, o3_button, u1_button, u2_button, c1_button, n1_button, guess_entry_button;
Entry guess_entry;

//ÁREA INFERIOR DO APP
Box lower_box, info_box, chooser_box;
Frame info_frame, buttonbox_frame;
Label info_label;
ButtonBox chooser_buttonbox;
Button chooser_button;


//MÉTODOS DA CLASSE

//FUNÇÕES DE SELEÇÃO DA PALAVRA ESCOLHIDA E DE CRIAÇÃO DA PALAVRA CIFRADA
void show_selector();
void load_english();
void load_portuguese();
void load_spanish();
void choose_word();
void reset_app();

//FUNÇÃO PRINCIPAL DO APLICATIVO (EXIBE A PALAVRA CIFRADA E CONTROLA O FLUXO DO JOGO)
void main_function();

//FUNÇÕES AUXILIARES QUE SÃO INVOCADAS A PARTIR DA FUNÇÃO PRINCIPAL
void count_error();
void warning_repetition();
void warning_game_over();
void warning_win();

//FUNÇÕES DE ENTRADA DE DADOS
void attempt();
void input_a();
void input_a1();
void input_a2();
void input_a3();
void input_b();
void input_c();
void input_c1();
void input_d();
void input_e();
void input_e1();
void input_e2();
void input_f();
void input_g();
void input_h();
void input_i();
void input_i1();
void input_i2();
void input_j();
void input_k();
void input_l();
void input_m();
void input_n();
void input_n1();
void input_o();
void input_o1();
void input_o2();
void input_o3();
void input_p();
void input_q();
void input_r();
void input_s();
void input_t();
void input_u();
void input_u1();
void input_u2();
void input_v();
void input_w();
void input_x();
void input_y();
void input_z();

//AJUDA E CRÉDITOS
void about();
void close_credits(int response_id);
void help();
void quit();
};
