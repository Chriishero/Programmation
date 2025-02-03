#ifndef __UTILS__
    #define __UTILS__

    namespace UtilTooLongNamespace
    {
        namespace subUtil
        {
            void test2();
        }
        
        void test(); // Util::test()
    }

    namespace Util = UtilTooLongNamespace; // using Util = UtilTooLongNamespace;
    
#endif