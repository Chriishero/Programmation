#ifndef __SPLITTER
    #define __SPLITTER
    #include "split_methode.hpp"
    #include <string>

    class Splitter
    {
        Splitter() = delete;
        Splitter(std::string pdf_path, Methode split_methode, std::string save_path) noexcept;

        public:
            void read_pdf() const noexcept;
            void split_pdf() const noexcept;
            void save_pdf() const noexcept;

        private:
            std::string _pdf_path;
            Methode _split_methode;
            std::string _save_path;
    };

#endif