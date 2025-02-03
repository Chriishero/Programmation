#ifndef __EMPLOYE__
    #define __EMPLOYE__
    #include <string>
    #include <ostream>

    class Employe
    {
        public:
            Employe() = delete;
            Employe(std::string last_name, std::string first_name, double salary) noexcept;

            std::string get_first_name() const noexcept;
            double get_salary() const noexcept;

        private:
            std::string _last_name;
            std::string _first_name;
            double _salary;

        friend std::ostream& operator<<(std::ostream& os, const Employe& e) noexcept;

        friend bool operator==(const Employe& e, const Employe& other) noexcept;
        friend bool operator!=(const Employe& e, const Employe& other) noexcept;

        friend bool operator>(const Employe& e, const Employe& other) noexcept;
        friend bool operator<(const Employe& e, const Employe& other) noexcept;
    };

    bool salary_sort(const Employe& e, const Employe& other) noexcept; // initialise la fonction de comparaison qui servira a trier les employés par salaire

#endif