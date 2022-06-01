#include <iostream>
using std::cout;
using std::cin;

#include <iomanip>
using std::setw;

#include <string>
using std::string;
using std::getline;

#include <algorithm>
using std::transform;
using std::reverse;

#include <cmath>
using std::abs;

// ========= General Helpers =========

const auto LITERA_INLOCUITOARE = 'Q';

const auto ALFABET_CLASIC = string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

typedef void (*callback)();

void AlegereCifrareDescifrare(callback callback_cifrare, callback callback_descifrare)
{
    auto optiune = 0;

    do
    {
        cout << "\n1. Cifrare";
        cout << "\n2. Descifrare";
        cout << "\n0. Inapoi";
        cout << "\n~> ";

        cin >> optiune;

        switch (optiune)
        {
        case 0:
            {
                return;
            }
        case 1:
            {
                callback_cifrare();
                return;
            }
        case 2:
            {
                callback_descifrare();
                return;
            }
        default:
            {
                cout << "\nOptiune invalida.\n";
            }
        }
    }
    while (optiune != 0);
}

void AfisareText(const string& mesaj, const string& text, const bool afisare_raw = true)
{
    cout << "\n====== " << mesaj << ":\n";
    
    for (auto caracter : text)
    {
        cout << setw(3) << caracter;
    }
    cout << '\n';
    for (auto caracter : text)
    {
        cout << setw(3) << caracter - 'A';
    }

    if (afisare_raw) {
        cout << "\nRaw: " << text << '\n';
    }

    cout << '\n';
}

string CitireText(const string& interfata)
{
    auto mesaj_input = string();
    auto buffer = string();
    cout << '\n' << interfata << ": ";

    getline(cin, buffer);
    if (buffer.empty() || buffer[0] == '\n' || buffer[0] == '\r' || buffer[0] == '\f')
    {
        getline(cin, mesaj_input);
    }
    else
    {
        mesaj_input = buffer;
    }

    transform(mesaj_input.begin(), mesaj_input.end(), mesaj_input.begin(), ::toupper);
    return mesaj_input;
}

string NormalizareText(const string& text, char litera_inlocuitoare)
{
    if (litera_inlocuitoare >= 'a' && litera_inlocuitoare <= 'z')
    {
        litera_inlocuitoare -= 'a' - 'A';
    }

    auto ret = string();
    for (auto caracter : text)
    {
        if (caracter < 'A' || caracter > 'Z')
        {
            ret += litera_inlocuitoare;
            continue;
        }
        ret += caracter;
    }

    return ret;
}

// ========= Cezar (Substitutie Monoalfabetica folosind un offset)  =========

string GetAlfabetShiftat(const int offset)
{
    auto alfabet_shiftat = string();
    for (auto caracter : ALFABET_CLASIC)
    {
        alfabet_shiftat += (caracter + offset - 'A') % 26 + 'A';
    }
    return alfabet_shiftat;
}

void CifrareCezar()
{
    auto mesaj = NormalizareText(CitireText("Text care trebuie cifrat"), LITERA_INLOCUITOARE);

    auto offset = 0;
    cout << "\nOffset: ";
    cin >> offset;

    AfisareText("Alfabetul clasic", ALFABET_CLASIC, false);
    AfisareText("Alfabetul shiftat", GetAlfabetShiftat(offset), false);

    auto mesaj_cifrat = string();
    for (auto caracter : mesaj)
    {
        mesaj_cifrat += (caracter + offset - 'A') % 26 + 'A';
    }

    AfisareText("Mesajul initial", mesaj, false);
    AfisareText("Mesajul cifrat", mesaj_cifrat);
}

void DescifrareCezar()
{
    auto mesaj = CitireText("Text care trebuie descifrat");

    auto offset = 0;
    cout << "\nOffset: ";
    cin >> offset;

    mesaj = NormalizareText(mesaj, (LITERA_INLOCUITOARE + offset - 'A') % 26 + 'A');

    AfisareText("Alfabetul clasic", ALFABET_CLASIC, false);
    AfisareText("Alfabetul shiftat", GetAlfabetShiftat(offset), false);

    auto mesaj_descifrat = string();
    for (auto caracter : mesaj)
    {
        mesaj_descifrat += ((caracter - offset - 'A') % 26 + 26) % 26 + 'A';
    }

    AfisareText("Mesajul initial", mesaj, false);
    AfisareText("Mesajul descifrat", mesaj_descifrat);
}

// ========= Metoda Substitutiei =========

string GetAlfabetSubstitutie(const string& parola)
{
    auto parola_cu_litere_unice = string();
    for (auto caracter : parola)
    {
        if (parola_cu_litere_unice.find(caracter) == string::npos)
        {
            parola_cu_litere_unice += caracter;
        }
    }
    AfisareText("Parola cu litere unice", parola_cu_litere_unice, false);

    auto alfabet_de_substitutie = string(parola_cu_litere_unice);
    for (auto caracter : ALFABET_CLASIC)
    {
        if (alfabet_de_substitutie.find(caracter) == string::npos)
        {
            alfabet_de_substitutie += caracter;
        }
    }
    reverse(alfabet_de_substitutie.begin(), alfabet_de_substitutie.end());
    AfisareText("Alfabetul de substitutie", alfabet_de_substitutie, false);

    return alfabet_de_substitutie;
}

void CifrareSubstitutie()
{
    auto mesaj = NormalizareText(CitireText("Text care trebuie cifrat"), LITERA_INLOCUITOARE);
    auto parola = NormalizareText(CitireText("Parola"), LITERA_INLOCUITOARE);

    AfisareText("Alfabetul clasic", ALFABET_CLASIC, false);

    auto alfabet_de_substitutie = GetAlfabetSubstitutie(parola);

    auto mesaj_cifrat = string();
    for (auto caracter : mesaj)
    {
        mesaj_cifrat += alfabet_de_substitutie[ALFABET_CLASIC.find(caracter)];
    }

    AfisareText("Mesajul initial", mesaj, false);
    AfisareText("Mesajul cifrat", mesaj_cifrat);
}

void DescifrareSubstitutie()
{
    auto mesaj = CitireText("Text care trebuie descifrat");
    auto parola = NormalizareText(CitireText("Parola"), LITERA_INLOCUITOARE);

    AfisareText("Alfabetul clasic", ALFABET_CLASIC, false);

    auto alfabet_de_substitutie = GetAlfabetSubstitutie(parola);
    mesaj = NormalizareText(mesaj, ALFABET_CLASIC[alfabet_de_substitutie.find(LITERA_INLOCUITOARE)]);

    auto mesaj_descifrat = string();
    for (auto caracter : mesaj)
    {
        mesaj_descifrat += ALFABET_CLASIC[alfabet_de_substitutie.find(caracter)];
    }

    AfisareText("Mesajul initial", mesaj, false);
    AfisareText("Mesajul descifrat", mesaj_descifrat);
}

// ========= Sisteme Polialfabetice (Vigenere) =========

void CifrareVigenere()
{
    auto mesaj = NormalizareText(CitireText("Text care trebuie cifrat"), LITERA_INLOCUITOARE);
    auto parola = NormalizareText(CitireText("Parola"), LITERA_INLOCUITOARE);

    AfisareText("Alfabetul clasic", ALFABET_CLASIC, false);

    auto parola_repetata = string();
    for (size_t index = 0; index < mesaj.size(); index++)
    {
        parola_repetata += parola[index % parola.size()];
    }

    AfisareText("Mesajul initial", mesaj, false);
    AfisareText("Parola repetata", parola_repetata, false);

    auto mesaj_cifrat = string();
    for (size_t index = 0; index < mesaj.size(); index++)
    {
        mesaj_cifrat += ((mesaj[index] - 'A') + (parola_repetata[index] - 'A')) % 26 + 'A';
    }

    AfisareText("Mesajul cifrat", mesaj_cifrat);
}

void DescifrareVigenere()
{
    auto mesaj = CitireText("Text care trebuie descifrat");
    auto parola = NormalizareText(CitireText("Parola"), LITERA_INLOCUITOARE);

    AfisareText("Alfabetul clasic", ALFABET_CLASIC, false);

    auto parola_repetata = string();
    for (size_t index = 0; index < mesaj.size(); index++)
    {
        parola_repetata += parola[index % parola.size()];
    }

    AfisareText("Mesajul initial", mesaj, false);
    AfisareText("Parola repetata", parola_repetata, false);

    auto mesaj_cifrat = string();
    for (size_t index = 0; index < mesaj.size(); index++)
    {
        mesaj_cifrat += abs((mesaj[index] - 'A') - (parola_repetata[index] - 'A')) % 26 + 'A';
    }

    AfisareText("Mesajul cifrat", mesaj_cifrat);
}

// ========= Metoda Transpozitiei =========

void CifrareTranspozitie()
{
    auto mesaj = NormalizareText(CitireText("Text care trebuie cifrat"), LITERA_INLOCUITOARE);
}

void DescifrareTranspozitie()
{
    auto mesaj = NormalizareText(CitireText("Text care trebuie descifrat"), LITERA_INLOCUITOARE);
}

// ========= Galois =========

void CifrareGalois()
{
    auto mesaj = NormalizareText(CitireText("Text care trebuie cifrat"), LITERA_INLOCUITOARE);
}

void DescifrareGalois()
{
    auto mesaj = NormalizareText(CitireText("Text care trebuie descifrat"), LITERA_INLOCUITOARE);
}

int main()
{
    auto optiune = 0;

    do
    {
        cout << "\n1. Cezar (Substitutie Monoalfabetica folosind un offset)";
        cout << "\n2. Metoda Substitutiei";
        cout << "\n3. Sisteme Polialfabetice (Vigenere)";
        cout << "\n4. Metoda Transpozitiei";
        cout << "\n5. Galois";
        cout << "\n0. Iesire";
        cout << "\n~> ";

        cin >> optiune;

        switch (optiune)
        {
        case 0:
            {
                cout << "\nLa revedere!\n";
            }
            break;
        case 1:
            {
                AlegereCifrareDescifrare(CifrareCezar, DescifrareCezar);
            }
            break;
        case 2:
            {
                AlegereCifrareDescifrare(CifrareSubstitutie, DescifrareSubstitutie);
            }
            break;
        case 3:
            {
                AlegereCifrareDescifrare(CifrareVigenere, DescifrareVigenere);
            }
            break;
        case 4:
            {
                AlegereCifrareDescifrare(CifrareTranspozitie, DescifrareTranspozitie);
            }
            break;
        case 5:
            {
                AlegereCifrareDescifrare(CifrareGalois, DescifrareGalois);
            }
            break;
        default:
            {
                cout << "\nOptiune invalida.\n";
            }
        }
    }
    while (optiune != 0);

    return EXIT_SUCCESS;
}
