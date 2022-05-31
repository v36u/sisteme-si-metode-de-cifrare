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
    auto mesaj_input = string();
    cout << "\nText care trebuie cifrat: ";
    cin.ignore();
    getline(cin, mesaj_input);
    transform(mesaj_input.begin(), mesaj_input.end(), mesaj_input.begin(), ::toupper);

    auto offset = 0;
    cout << "\nOffset: ";
    cin >> offset;

    AfisareText("Alfabetul clasic", ALFABET_CLASIC);
    AfisareText("Alfabetul shiftat", GetAlfabetShiftat(offset));

    auto mesaj_initial = string();
    auto mesaj_cifrat = string();
    for (auto caracter : mesaj_input) {
        if (caracter < 65 || caracter > 90) {
            mesaj_initial += LITERA_INLOCUITOARE;
            mesaj_cifrat += (LITERA_INLOCUITOARE + offset - 'A') % 26 + 'A';
            continue;
        }
        mesaj_initial += caracter;
        mesaj_cifrat += (caracter + offset - 'A') % 26 + 'A';
    }

    AfisareText("Mesajul initial", mesaj_initial);
    AfisareText("Mesajul cifrat", mesaj_cifrat);
}

void DescifrareCezar()
{
    auto mesaj_input = string();
    cout << "\nText care trebuie descifrat: ";
    cin.ignore();
    getline(cin, mesaj_input);
    transform(mesaj_input.begin(), mesaj_input.end(), mesaj_input.begin(), ::toupper);

    auto offset = 0;
    cout << "\nOffset: ";
    cin >> offset;

    AfisareText("Alfabetul clasic", ALFABET_CLASIC);
    AfisareText("Alfabetul shiftat", GetAlfabetShiftat(offset));

    auto mesaj_initial = string();
    auto mesaj_descifrat = string();
    for (auto caracter : mesaj_input) {
        if (caracter < 65 || caracter > 90) {
            mesaj_initial += LITERA_INLOCUITOARE;
            mesaj_descifrat += ((LITERA_INLOCUITOARE - offset - 'A') % 26 + 26) % 26 + 'A';
            continue;
        }
        mesaj_initial += caracter;
        mesaj_descifrat += ((caracter - offset - 'A') % 26 + 26) % 26 + 'A';
    }

    AfisareText("Mesajul initial", mesaj_initial);
    AfisareText("Mesajul descifrat", mesaj_descifrat);
}

// ========= Metoda Substitutiei =========

void CifrareSubstitutie()
{
}

void DescifrareSubstitutie()
{
}

// ========= Sisteme Polialfabetice (Vigenere) =========

void CifrareVigenere()
{
}

void DescifrareVigenere()
{
}

// ========= Metoda Transpozitiei =========

void CifrareTranspozitie()
{
}

void DescifrareTranspozitie()
{
}

// ========= Galois =========

void CifrareGalois()
{
}

void DescifrareGalois()
{
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
