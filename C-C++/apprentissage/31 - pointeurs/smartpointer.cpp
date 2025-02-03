#include <iostream>
#include <memory> // inclue les pointeurs intelligent

/*
RAII est un ensemble d'outil qui permet de gérer la mémoire en C++
Pointeur Intelligent : 
    unique_ptr : pointeur qui a la propriété d'un objet alloué dynamiquement, et il sera le seul et unique à posséder la propriété de cet objet, la copie du pointeur est impossible, mais le transfert si
    shared_ptr : pointeur qui peut être copié, tant qu'un propriétaire de la propriété existe encore, l'objet ne sera pas détruit
    weak_ptr   : pointeur partagé qui va agir comme observateur, il n'a pas la propriété de l'objet

    std::move() : transfère la ressource d'un pointeur vers un autre
    release()   : transfère la propriété d'une ressource d'un ponteur vers un autre en libérant la ressource
    lock()      : vérouille un weak pointer
    reset()     : libére un pointeur de la mémoire
    swap()      : échange la propriété d'une ressource entre 2 pointeurs
    get()       : permet par exemple, à un pointeur brut de récupérer la ressource d'un pointeur intelligent unique
    use_count() : compte le nombre de propriétaire d'une ressource
    expired()   : vérifie si une ressource est expiré ou non
*/

int main()
{
    std::unique_ptr<int> uptr{ std::make_unique<int>(35) }; // 'std::make_unique<int>' permet de créer le pointeur unique 'ptr' qui a la propriété de cet entier, auto peut remplacer 'std::unique_ptr<int>'
    // une fois sorti de la porté de la fonction, ce pointeur sera automatiquement libéré de la mémoire

    int* pRaw{uptr.get()}; // le pointeur brut 'pRaw' récupère la ressource pointé par le pointeur intelligent unique 'ptr' sans libération de mémoire, 'ptr' a toujours la propriété

    std::cout << "uptr : " << *uptr << std::endl;
    std::cout << "pRaw : " << *pRaw << std::endl;

    auto uptr2{ uptr.release()}; // tranfère la propriété de la ressource de l'unique pointer 'uptr' vers l'unique pointer 'uptr2', 'uptr' n'a plus la propriété de la ressource
    
    std::cout << "uptr2 : " << *uptr2 << std::endl;
    std::cout << "pRaw : " << *pRaw << std::endl;


    auto sptr{ std::make_shared<int>(100) }; // 'std::make_shared' crée le pointeur partagé 
    auto sptr2{ sptr }; // copie la propriété pointé par le pointeur partagé 'sptr'
    std::weak_ptr<int> wptr{ sptr }; // pointeur faible qui agit en observateur sur la propriété du pointeur 'sptr'

    std::cout << "Proprietaire(s) de la ressource : " << sptr.use_count() << std::endl; // affiche le nombre de propriétaires de la ressource que 'sptr' pointe, un pointeur faible n'est pas propriétaire
    std::cout << "sptr : " << *sptr << std::endl;

    if (wptr.expired()) // vérifie si le pointeur faible 'wptr' est expiré
    {
        std::cout << "Aucun proprietaire." << std::endl;
    }
    else 
    {
        std::cout << wptr.use_count() << " proprietaire(s)" << std::endl; // affiche le nombre de propriétaire de la ressource que 'wptr' OBSERVE, il ne fait pas parti des propriétaires
    }
    
    sptr2.reset(); // libére le pointeur de la mémoire, avant la fin de la porté de la fonction.

    if (sptr2)
    {
        std::cout << "sptr3 : " << *sptr2 << std::endl;
    }
    else
    {
        std::cout << "Le pointeur 'ptr2' a ete libere de la memoire." << std::endl;
    }

    if(auto ob = wptr.lock()) // .lock() vérouille le pointeur faible, et renvoie un pointeur partagé 'ob', ça permet de renvoyer la propriété qu'observe le pointeur faible en le convertissant en pointeur partagé
    {
        std::cout << "wptr (ob) : " << *ob << std::endl;
    }
    else
    {
        std::cout << "Indisponible." << std::endl;
    }
    
    auto ptr1{ std::make_shared<int>(1) };
    auto ptr2{ std::make_shared<int>(2) };

    std::cout << "ptr1 : " << *ptr1 << std::endl;
    std::cout << "ptr2 : " << *ptr2 << std::endl;

    ptr1.swap(ptr2); // échange les ressources entre les pointeurs 'ptr1' et 'ptr2'

    std::cout << "ptr1 : " << *ptr1 << std::endl;
    std::cout << "ptr2 : " << *ptr2 << std::endl;

    return 0;
}