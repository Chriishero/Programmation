#include <iostream>
#include <string>
#include <chrono>
#include <thread> // inclus les threads
#include <mutex> // inclus les verrous 

/*
    Programmation asynchrone : principe d'effectué des tâches de manière parallèle et non séquentielle (l'une après l'autre).
    Thread : fil d'execution

    get_id()      : récupère l'indentifiant du thread (sous forme hexadécimal)
    joignable()   : vérifie si le thread est joignable, renvoie un booléen
    th1.swap(th2) : inverse la responsabilité de 2 threads, th1 fera la tâche de th2 et inversement
    detach()      : sépare le fil d'execution de l'objet thread 
    lock()        : permet de faire un respécter un ordre dans l'execution des threads 
    unlock()
    try_lock()    : renvoie une bouléen sur un verrou en le testant
*/

void doTask(std::mutex& m, std::string name, unsigned int delay)
{
    //m.lock(); // verrouille l'opération critique (suite du programme) tant qu'elle est utilisé par un thread
    // les 2 threads n'auront pas un accès possible en MÊME TEMPS de l'opération

    std::lock_guard<std::mutex> lock{m}; // gère le verrouillage et déverrouillage de la tâche automatiquement
 
    for (auto i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(delay)); // permet de dire à ce thread d'attendre un nombre 'delay' de seconde(s).
        std::cout << name << " : " << i << std::endl;
    }

    //m.unlock(); // déverouille
}

int main()
{
    std::cout << "Instruction du thread principal." << std::endl;

    std::mutex mu;

    std::thread th1{doTask, std::ref(mu), "TH1", 1}; // déclare le thread 'th1' avec comme paramètre, une fonction et son paramètre
    std::thread th2{doTask, std::ref(mu),"TH2", 2}; // pour passer un paramètre par référence dans un thread, il faut utiliser 'std::ref'
    // l'ordre d'execution des threads ne va pas changer si ils n'ont pas le même 'delay'

    th1.join(); // '.join()' est une instruction bloquante : attend l'execution du thread, avant de passer à la suite du programme
    th2.join();
    // L'ordre d'execution des tâches des threads 'th1' et 'th2' peut changé, car ils effectuent leur tâche chacun de leur côté

    std::cout << "Autre instruction du thread principal." << std::endl;

    return 0;
}