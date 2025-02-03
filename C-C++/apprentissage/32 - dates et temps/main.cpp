#include <iostream>
#include <chrono> // implémente les dates et temps

/*
    Date calendare :
        std::chrono::year
        std::chrono::month
        std::chrono::day

    Compter un nombre d'années/mois/jours/etc : 
        std::chrono::years
        std::chrono::months
        std::chrono::days
        std::chrono::hours
        std::chrono::minutes
        std::chrono::seconds
        std::chrono::milliseconds
        std::chrono::microseconds
        std::chrono::nanoseconds

    littéraux : y, m, w, d
                h, min, s
                ms, us, ns

    Pour trouver un fuseau horaire, rechercher "Fuseaux horaires IANA"

    .ok()     : booléen si le fuseau horaire est valides
    .format() : formater comme on veut une date 
    std::chrono::system_clock::now() : récupère la date actuel
    std::chrono::zoned_time          : permet de spécifier la zone du fuseau horaire

    Format : 
        %D, %F ou %d, %m, %Y // renvoie la date complète, ou jour, mois, années
        %R, %T,
        %H, %M, %S // heures, minutes, secondes (float)

        %A, %a // jour complet, jour abrégé
        %B, %b // mois complet, mois abrégé
*/

int main()
{
    using namespace std::chrono_literals; // permet d'utiliser tous les suffixes pour les littéraux des valeurs temporelles

    std::chrono::hours h{16h};
    std::chrono::minutes min{54};
    std::cout << h + min << std::endl;

    std::chrono::year y{2023}; // créer une variable de type année
    std::chrono::month m{0}; // affiche 'May', le 5ème mois
    std::chrono::day d{13}; 

    if (d.ok() && m.ok() && y.ok()) // 'ok()' vérifie si les variables sont correct pour une date calendaire
    {
        std::cout << d << "/" << m << "/" << y << std::endl;
    }

    std::chrono::days d1{365}; // 'days' permet de compter PLUSIEURS jours
    std::cout << d1 << std::endl;

    std::chrono::hours h1{16};
    std::chrono::hours h2{4};
    std::cout << h1 + h2 << std::endl;

    auto today{std::chrono::system_clock::now()}; // récupère la date d'aujourd'hui
    auto formatted_date{std::format("{:%d/%m/%Y}", today)}; // formate la date d'aujourd'hui comme on le veut
    std::cout << formatted_date << std::endl;

    std::chrono::zoned_time date{"Europe/Paris", std::chrono::system_clock::now()}; // renvoie la date au fuseau horaire de Paris
    std::cout << date << std::endl;

    return 0;
}