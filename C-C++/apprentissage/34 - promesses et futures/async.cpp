#include <iostream>
#include <thread>
#include <future>

/*
    Promesse (promise) : producteur, stock la valeur et réalise le traitement
                        std::promise<type>
    Futur (future)     : consommateur, attend que la 'promesse' soit réalisé et récupére la valeur
                        std::future<type>
        std::future<int> someFuture{ std::async(std::launch::async, function) }; : fais le traitement dans un thread distinct
        std::future<int> someFuture{ std::async(std::deferred, function) };      : fais le traitement de manière différé
*/

int getNumber() 
{
    return 2222;
}

int main()
{
    /*std::promise<int> somePromise;
    std::future<int> someFuture(somePromise.get_future()); // 'get_future()' récupére la valeur stocké par la promesse 'somePromise'

    // async permet de faire le traitement de manière asynchrone, renvoie un 'futur' de la valeur retourné par 'getNumber'
    std::async([&somePromise]() 
    {
        int n {getNumber()};
        somePromise.set_value(n); // set la valeur retourné par 'getNumber()' en tant que 'promesse'
    });*/

    std::future<int> someFuture{ std::async(getNumber) }; // récupère la valeur renvoyé par 'getNumber' de manière asynchrone en tant que 'future'

    auto result{someFuture.get()}; // récupère la valeur de 'someFuture'
    std::cout << result << std::endl;

    return 0;
}