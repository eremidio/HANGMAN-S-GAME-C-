//ESTE ARQUIVO CONTÉM A JANELA DE INSTRUÇÕES PARA O USO DO APLICATIVO

/*CABEÇALHO*/
#include<gtkmm.h>
#include<iostream>

using namespace std;
using namespace Glib;
using namespace Gtk;

/*CLASSE DE MENU DE AJUDA LABEL+SCROLLEDWINDOW*/
class HelpWindow: public Window{
public:

//CONSTRUTOR E DESTRUIDOR DA CLASSE
HelpWindow();
virtual ~HelpWindow();
//WIDGETS
ScrolledWindow help_scrolledwindow;
Label help_label;
Box help_box;

};

//DESTRUIDOR DA CLASSE
HelpWindow::~HelpWindow(){
};

//CONSTRUTOR DA CLASSE
HelpWindow::HelpWindow(){

//LAYOUT
set_border_width(5);
add(help_scrolledwindow);
help_scrolledwindow.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);
help_scrolledwindow.add(help_label);
help_label.set_justify(JUSTIFY_FILL);
help_label.set_line_wrap();
//AJUSTE DA FONTE A SER USADA
Pango::FontDescription help_font;
help_font.set_family("Times");
help_font.set_size(12*PANGO_SCALE);
help_font.set_weight(Pango::Weight::WEIGHT_BOLD);
help_label.override_font(help_font);
//TEXTO DE AJUDA A SER EXIBIDO NA JANELA SECUNDÁRIA DE AJUDA
help_label.set_text("JOGO DA FORCA - Versão 1.0\n"
"----------------------------------------------------------------\n\n"
"1.0 - LAYOUT GERAL E FUNCIONALIDADE\n"
"----------------------------------------------------------------\n\n"
"Este programa consiste em um jogo da forca. Neste jogo você deve adivinhar uma palavra secreta sorteada aleatoriamente.\n" "Você pode tanto inserir letra por letra até formar a palavra secreta, ou você pode tentar arriscar uma palavra inteira.\n"
"Este aplicativo dispõe de um teclado contendo os caractéres que formam as palavras secretas. Ao clicar num destes botões o aplicativo automaticamente checa se o caractére correspondente compõe a palavra secreta.\nEm caso de sucesso o caractére é revelado na palavra secreta e em caso de falha um erro é computado.\n"
"O programa também dispõe de um campo no qual o usuário pode arriscar uma palavra inteira, basta inserir uma palavra (ou somente um trecho) que se supõe ser a palavra secreta e clicar no botão 'Arriscar uma palavra' que o aplicativo irá vericar se o palpite corresponde a palavra secreta ou não.\nEm caso de sucesso a palavra secreta é revelada e em caso de falha um erro é computado.\n\n"
"2.0 - OBSERVAÇÕES IMPORTANTES\n"
"----------------------------------------------------------------\n\n"
"Tentativas repetidas são proibidas no jogo. Palavras ou letras testadas em cada rodada são exibidos na tela do aplicativo. Uma tentativa repetida, porém não é computada como erro.\n"
"Antes de usar o aplicativo você deve clicar na guia idioma e selecionar um dicionário de palavras que conterá palavras selecionadas no respectivo idioma. Nesta versão atual três idiomas estão disponíveis: espanhol, inglês e português.\n"
"Quando uma palavra é cifrada as letras com acento gráfico são computadas como dois caractéres. Por exemplo a palavra paz (p-a-z) é cifrada como '* * *', já a palavra pé (p-é) é cifrada como '* * * ' (1 caractére extra devido ao acento agudo), ação é cifrada como (a-ç-ã-o) é cifrada como '* * * * * *'(2 caractéres extras devido à cedilha e ao acento circunflexo), etc. Infelizmente, isto é devido ao fato da linguagem de programação em que o jogo foi escrito originalmente ser projetada para operar com a língua inglesa. Isto poderá ser corrigido em versões futuras. Para a maioria das palavras isto porém não acarreta dificuldades adicionais.\n\n"
"3.0 - AGRADECIMENTOS\n"
"----------------------------------------------------------------\n\n"
"Obrigado pela preferência. Sugestões de melhorias entrar em contato com: e.r.emidio@yandex.com.\n\n"

);



};
