#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

string PALAVRA_SECRETA = "MELANCIA";
map<char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe(char chute)
{
    for (char letra : PALAVRA_SECRETA)
    {
        if (chute == letra)
        {
            return true;
        }
    }
    return false;
}

bool nao_acertou()
{
    for (char letra : PALAVRA_SECRETA)
    {
        if (!chutou[letra])
        {
            return true;
        }
    }

    return false;
}

bool nao_inforcou()
{
    return chutes_errados.size() < 5;
}

void imprime_cabecalho()
{
    cout << "*********************" << endl;
    cout << "*** Jogo da Forca ***" << endl;
    cout << "*********************" << endl;
    cout << endl;
}

void imprime_erros()
{
    if (!chutes_errados.empty())
    {
        cout << "Chutes errados: ";
        for (char letra : chutes_errados)
        {
            cout << letra << " ";
        }
        cout << endl;
        cout << endl;
    }
}

void imprime_palavra()
{
    for (char letra : PALAVRA_SECRETA)
    {
        if (chutou[letra])
        {
            cout << letra << " ";
        }
        else
        {
            cout << "_ ";
        }
    }
    cout << endl;
    cout << endl;
}

void chuta()
{
    cout << "Seu chute: ";
    char chute;
    cin >> chute;

    chute = toupper(chute);

    chutou[chute] = true;

    if (letra_existe(chute))
    {
        cout << "Você acertou! Seu chute está na palavra." << endl;
    }
    else
    {
        cout << "Você errou! Seu chute não está na palavra." << endl;
        chutes_errados.push_back(chute);
    }

    cout << endl;
}

vector<string> le_arquivo()
{
    ifstream arquivo;
    arquivo.open("palavras.txt");

    if (arquivo.is_open())
    {

        int quantidade_palavras;
        arquivo >> quantidade_palavras;

        vector<string> palavras_do_arquivo;

        for (int i = 0; i < quantidade_palavras; i++)
        {
            string palavra_lida;
            arquivo >> palavra_lida;

            palavras_do_arquivo.push_back(palavra_lida);
        }
        arquivo.close();
        return palavras_do_arquivo;
    }else{
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
}

void salva_arquivo(vector<string> nova_lista){
    ofstream arquivo;
    arquivo.open("palavras.txt");
    
    if (arquivo.is_open()){
        arquivo << nova_lista.size() << endl;

        for (string palavra : nova_lista)
        {
            arquivo << palavra << endl;
        }   

        arquivo.close();
    }else{
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
}

void adiciona_palavra(){
    cout << "Digite a nova palavra, usando letras maiúsculas." << endl;
    string nova_palavra;
    cin >> nova_palavra;


    vector<string> lista_palavras = le_arquivo();
    lista_palavras.push_back(nova_palavra);

    salva_arquivo(lista_palavras);
}

void imprime_fim_de_jogo()
{
    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era: " << PALAVRA_SECRETA << endl;
    if (nao_acertou())
    {
        cout << "Você perdeu! Tente novamente!" << endl;
    }
    else
    {
        cout << "Parabéns! Você acertou a palavra secreta!" << endl;

        cout << "Você desenha adicionar uma nova palavra ao banco? (S/N)" << endl;
        char resposta;
        cin >> resposta;
        if ( toupper(resposta) == 'S'){
            adiciona_palavra();
        }
    }
}


void sorteia_palavra()
{
    vector<string> palavras = le_arquivo();

    srand(time(NULL));
    int indice_sorteado = rand() % palavras.size();

    PALAVRA_SECRETA = palavras[indice_sorteado];
}

int main()
{
    imprime_cabecalho();

    le_arquivo();

    sorteia_palavra();

    while (nao_acertou() && nao_inforcou())
    {
        imprime_erros();

        imprime_palavra();

        chuta();
    }

    imprime_fim_de_jogo();
}
