#ifndef __QUESTSTATUS__
    #define __QUESTSTATUS__

    /*
    Classe A, Classe B
        Héritage : B est une sorte de A
        Composition : B fait parti de A

    'Quest_status' fait parti de 'Quest' : composition
    */

    enum class Quest_status
    {
        activated,
        disabled,
        failed
    };
    
#endif