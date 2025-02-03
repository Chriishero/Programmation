#ifndef __SPLITTER
    #define __SPLITTER
    #include "split_methode.hpp"
    #include <fstream>
    #include <string>

    class Splitter
    {
        public:
            Splitter() = delete;
            Splitter(std::string txt_path, Methode split_methode, std::string save_path, int page_interval) noexcept;
            
            void save_txt(const std::string content) const noexcept;
            void split_txt() const noexcept;

        private:
            std::string _txt_path;
            Methode _split_methode;
            std::string _save_path;
            int _page_interval;
    };

#endif