#include <iostream>
#include <thread>
#include <future>

/*
    Promesse (promise) : producteur, stock la valeur et réalise le traitement
                        std::promise<type>
    Futur (future)     : consommateur, attend que la 'promesse' soit réalisé et récupére la valeur
                        std::future<type>
*/

void getNumber(std::promise<int>&& result) // '&&' permet à la fonction de récupérer la responsabilité de la promesse 'result'
{
    result.set_value(188); // stock la valeur '188' dans la 'promesse'
}

int main()
{
    std::promise<int> somePromise;
    std::future<int> someFuture{somePromise.get_future()}; // 'get_future()' récupére la valeur stocké par la promesse 'somePromise'

    std::thread th{getNumber, std::move(somePromise)}; // 'std::move()' permet à 'getNumber' de récupérer la responsabilité de la promesse 'somePromise'

    auto returnValue{someFuture.get()}; // récupère la valeur de 'someFuture'
    std::cout << returnValue << std::endl;

    th.join();

    return 0;
}