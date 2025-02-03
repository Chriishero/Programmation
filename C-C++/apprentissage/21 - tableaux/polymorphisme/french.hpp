#ifndef __FRENCH__
    #define __FRENCH__
    #include "someone.hpp"
    #include <string>

    class French : public Someone
    {
        using Someone::Someone;

        public:
            void sayGoodNight() const noexcept override;
    };

#endif