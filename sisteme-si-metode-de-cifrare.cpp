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

// ========= Helpers =========

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
    } while (optiune != 0);
}

void AfisareText(const string& mesaj, const string& text)
{
    cout << "\n====== " << mesaj << ":\n";

    cout << "\nRaw:\n" << text << '\n';

    cout << "\nForma cu index sub litera:\n";
    for (auto caracter : text)
    {
        cout << setw(3) << caracter;
    }
    cout << '\n';
    for (auto caracter : text)
    {
        cout << setw(3) << caracter - 'A';
    }

    cout << '\n';
}

string CitireText(const string& mesaj, char litera_inlocuitoare)
{
    if (litera_inlocuitoare >= 'a' && litera_inlocuitoare <= 'z')
    {
        litera_inlocuitoare -= 'a' - 'A';
    }

    auto mesaj_input = string();
    cout << '\n' << mesaj << ": ";
    cin.ignore();
    getline(cin, mesaj_input);
    transform(mesaj_input.begin(), mesaj_input.end(), mesaj_input.begin(), ::toupper);

    auto ret = string();
    for (auto caracter : mesaj_input)
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
    auto offset = 0;
    cout << "\nOffset: ";
    cin >> offset;

    auto mesaj = CitireText("Text care trebuie cifrat", LITERA_INLOCUITOARE);

    AfisareText("Alfabetul clasic", ALFABET_CLASIC);
    AfisareText("Alfabetul shiftat", GetAlfabetShiftat(offset));

    auto mesaj_cifrat = string();
    for (auto caracter : mesaj) {
        mesaj_cifrat += (caracter + offset - 'A') % 26 + 'A';
    }

    AfisareText("Mesajul initial", mesaj);
    AfisareText("Mesajul cifrat", mesaj_cifrat);
}

void DescifrareCezar()
{
    auto offset = 0;
    cout << "\nOffset: ";
    cin >> offset;

    auto mesaj = CitireText("Text care trebuie descifrat", (LITERA_INLOCUITOARE + offset - 'A') % 26 + 'A');

    AfisareText("Alfabetul clasic", ALFABET_CLASIC);
    AfisareText("Alfabetul shiftat", GetAlfabetShiftat(offset));

    auto mesaj_descifrat = string();
    for (auto caracter : mesaj) {
        mesaj_descifrat += ((caracter - offset - 'A') % 26 + 26) % 26 + 'A';
    }

    AfisareText("Mesajul initial", mesaj);
    AfisareText("Mesajul descifrat", mesaj_descifrat);
}

// ========= Metoda Substitutiei =========

void CifrareSubstitutie()
{
    auto parola = CitireText("Parola", LITERA_INLOCUITOARE);
    auto mesaj = CitireText("Text care trebuie cifrat", LITERA_INLOCUITOARE);

    AfisareText("Alfabetul clasic", ALFABET_CLASIC);

    auto parola_cu_litere_unice = string();
    for (auto caracter : parola) {
        if (parola_cu_litere_unice.find(caracter) == string::npos) {
            parola_cu_litere_unice += caracter;
        }
    }
    AfisareText("Parola cu litere unice", parola_cu_litere_unice);

    auto alfabet_de_cifrare = string(parola_cu_litere_unice);
    for (auto caracter : ALFABET_CLASIC)
    {
        if (alfabet_de_cifrare.find(caracter) == string::npos) {
            alfabet_de_cifrare += caracter;
        }
    }
    reverse(alfabet_de_cifrare.begin(), alfabet_de_cifrare.end());
    AfisareText("Alfabetul de criptare", parola_cu_litere_unice);
}

void DescifrareSubstitutie()
{
    auto parola = CitireText("Parola", LITERA_INLOCUITOARE);
    auto mesaj_input = CitireText("Text care trebuie descifrat", LITERA_INLOCUITOARE); // TODO: Change

    AfisareText("Alfabetul clasic", ALFABET_CLASIC);

}

// ========= Sisteme Polialfabetice (Vigenere) =========

void CifrareVigenere()
{
    auto mesaj_input = CitireText("Text care trebuie cifrat", LITERA_INLOCUITOARE);
}

void DescifrareVigenere()
{
    auto mesaj_input = CitireText("Text care trebuie descifrat", LITERA_INLOCUITOARE);
}

// ========= Metoda Transpozitiei =========

void CifrareTranspozitie()
{
    auto mesaj_input = CitireText("Text care trebuie cifrat", LITERA_INLOCUITOARE);
}

void DescifrareTranspozitie()
{
    auto mesaj_input = CitireText("Text care trebuie descifrat", LITERA_INLOCUITOARE);
}

// ========= Galois =========

void CifrareGalois()
{
    auto mesaj_input = CitireText("Text care trebuie cifrat", LITERA_INLOCUITOARE);
}

void DescifrareGalois()
{
    auto mesaj_input = CitireText("Text care trebuie descifrat", LITERA_INLOCUITOARE);
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
    } while (optiune != 0);

    return EXIT_SUCCESS;
}
