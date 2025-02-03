#ifndef __NUMBER__
    #define __NUMBER__

    /*
    Un modèle de fonction sert à éviter de réinitialiser plusieurs fois une fonction comme ceci :
        int sum(int a, int b);
        double sum(double a, double b);

        Création d'un modèle :
            template<typename Name, typename Name2 = defaultType>
            Name fonction(Name a, Name b);
            Name2 fonction2(Name2 a, Name2 b);

            Le nom du typename peut être n'importe quoi, il s'agit seulement d'un type générique que le compilateur déduira à l'utilisation de la fonction.

        Surcharge d'un modèle :
                template<typename Name>
            Name fonction(Name a, Name b)
            {
                return a + b;
            }

            bool fonction (bool a, bool b) : on peut changer le contenue du modèle de fonction avec un type non-générique, en le définissant
            {
                un autre calcul...
            }

            Le compilateur privilégie ce qui est non-générique.
    */

    template <typename T = int> // création d'un modèle définie d'une fonction, qui prend en charge plusieurs type, le type par défaut est 'int'
    T sum(T a, T b); // le compilateur va analiser l'utilisation de la fonction dans main.cpp, et instancier la fonction en en déduisant les types qui sont travaillé (int ou double ici)

    #include "number.tpp" // inclue le fichier .tpp où sera défini la fonction 

#endif