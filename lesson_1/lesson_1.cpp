#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>


struct Person
{
private:
    std::string m_Fistname;
    std::string m_Name;
    std::string m_Patronymic;
public:
    Person(std::string Firstname, std::string Name, std::string Patronymic): m_Fistname(Firstname), m_Name(Name), m_Patronymic(Patronymic)
    {

    }

    Person(std::string Firstname, std::string Name): m_Fistname(Firstname), m_Name(Name), m_Patronymic("")
    {
       
    }

    void print_person() const
    {
        std::cout << m_Fistname << '\t' << m_Name << '\t' << m_Patronymic << '\t';
    }

    std::string GetFirstName() const
    {
        return m_Fistname;
    }

    std::string GetName() const
    {
        return m_Name;
    }

    std::string GetPatronimic() const
    {
        return m_Patronymic;
    }

    

    ~Person()
    {

    }

};
/*
struct PhoneNumber
{
private:
  
    std::string m_country_code;
    std::string m_city_code;
    std::string m_phone_number;
    std::string m_adition_number;

public:
    PhoneNumber(std::string con_code, std::string city_code, std::string p_num, std::string add_num) :
        m_country_code(con_code), m_city_code(city_code), m_phone_number(p_num), m_adition_number(add_num)
    {

    }

    PhoneNumber(std::string con_code, std::string city_code, std::string p_num) :
        m_country_code(con_code), m_city_code(city_code), m_phone_number(p_num), m_adition_number(" ")
    {

    }

    void print_number() const
    {
        if (m_adition_number != " ")
        {
            std::cout << "\t+" << m_country_code << " (" << m_city_code << ") " << m_phone_number << " " << m_adition_number << "\n";
        }
        else
        {
            std::cout << "\t+" << m_country_code << " (" << m_city_code << ") " << m_phone_number << "\n";
        }
    }

    ~PhoneNumber()
    {

    }
};
*/

struct PhoneNumber
{
private:
    size_t m_country_code;
    size_t m_city_code;
    size_t m_phone_number;
    size_t m_adition_number;

public:
    PhoneNumber(size_t con_code, size_t city_code, size_t p_num, size_t add_num) :
        m_country_code(con_code), m_city_code(city_code), m_phone_number(p_num), m_adition_number(add_num)
    {

    }

    PhoneNumber(size_t con_code, size_t city_code, size_t p_num) :
        m_country_code(con_code), m_city_code(city_code), m_phone_number(p_num), m_adition_number(0)
    {

    }

    void print_number() const
    {
        if (m_adition_number) 
        {
            std::cout << "\t+" << m_country_code << " (" << m_city_code << ") " << m_phone_number << " " << m_adition_number << "\n";
        }
        else
        {
            std::cout << "\t+" << m_country_code << " (" << m_city_code << ") " << m_phone_number << "\n";
        }
    }

    void ChangeNumber(size_t con_code, size_t city_code, size_t p_num, size_t add_num = 0)
    {
        m_country_code = con_code;
        m_city_code = city_code;
        m_phone_number = p_num;
        m_adition_number = add_num;

    }

    ~PhoneNumber()
    {

    }
};

class PhoneBook
{
private:
    
    std::vector<std::pair<Person, PhoneNumber>> PBook;

public:
    PhoneBook(std::string path)
    {
        std::ifstream phone_book(path);

        if (!phone_book.is_open())
        {
            std::cout << "ERROR: File isn't found!" << std::endl;
        }

        std::string first_name;
        std::string name;
        std::string patronymic;
        std::string country_code;
        std::string city_code;
        std::string number;
        std::string add_number;

        while (phone_book.good())
        {
            std::getline(phone_book, first_name, ',');
            std::getline(phone_book, name, ',');
            std::getline(phone_book, patronymic, ',');
            std::getline(phone_book, country_code, ',');
            std::getline(phone_book, city_code, ',');
            std::getline(phone_book, number, ',');
            std::getline(phone_book, add_number, '\n');

           // std::cout << add_number << std::endl;

            Person person(first_name, name, patronymic);
            
            int co_code = std::stoi(country_code);
            int ci_code = std::stoi(city_code);
            int num = std::stoi(number);
            int add_num = 0;
            if (add_number != "") 
            {
                add_num = std::stoi(add_number);
            }
           

            PhoneNumber p_number(co_code, ci_code, num, add_num);


            //person.print_person();
            //p_number.print_number();
            
            std::pair<Person, PhoneNumber> pair1(person, p_number);
            
            //std::cout << first_name << " " << name << " " << patronymic << " " << country_code << " " << city_code << " " << number << " " << add_number << '\n';

            PBook.push_back(pair1);
            
        }
        phone_book.close();
    }

    void printPhonebook()const
    {
        for (auto i : PBook)
        {
            i.first.print_person();
            i.second.print_number();
        }
    }

    void SortByName() 
    {
        std::sort(PBook.begin(), PBook.end(), [](std::pair<Person, PhoneNumber> pair1, std::pair<Person, PhoneNumber> pair2)
            {return pair1.first.GetFirstName() < pair2.first.GetFirstName(); });

       
        
    }

    void GetPhoneNumber(std::string Firstname) const
    {
        int one_person = 0;
        for (auto i : PBook)
        {
            if (Firstname == i.first.GetFirstName())
            {
                i.first.print_person();
                i.second.print_number();
                one_person++;
            }
        }
        if (one_person == 0)
        {
            std::cout << "Not found!" << std::endl;
        } 
        else if (one_person > 1)
        {
            std::cout << "Found more than 1 person";
        }
    }
     
    void ChangePhoneNumber(size_t country_code, size_t city_code, size_t number, size_t add_number, std::string FirstName, std::string Name, std::string Patronimic = "")
    {
        for (auto i : PBook)
        {
            if ((i.first.GetFirstName() == FirstName) && (i.first.GetName() == Name) && (i.first.GetPatronimic() == Patronimic))
            {
                std::cout << "Previous number: ";
                i.second.print_number();
                std::cout << "Changes number: ";
                i.second.ChangeNumber(country_code, city_code, number, add_number);
                i.second.print_number();
            }
        }
    }

    ~PhoneBook()
    {

    }
};

int main()
{

    PhoneBook pb("phones.csv");

    pb.printPhonebook();

    std::cout << std::endl;

    pb.SortByName();

    pb.printPhonebook();

    std::cout << std::endl;

    pb.GetPhoneNumber("Solovev");

    std::cout << std::endl;

    pb.ChangePhoneNumber(453, 332, 6788983, 0, "Makeev", "Marat");

    


    /*
    std::vector <int> vec{ 2, 5, 8, 1, 3, 9, 6, 89, 23, 4, 7 };

    for (auto i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::sort(vec.begin(), vec.end());
    
    for (auto i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    */

    /*
    Person a("Josh", "Jojn", "Pop");
    Person b("Aran", "Bob");
    Person c("Bob", "Jojn");
    Person d("Bill", "Jojn", "Pop");
    Person e("Ken", "Jojn", "Pop");

    PhoneNumber a1(38, 99, 2323232323, 23);
    PhoneNumber b1(38, 99, 2323232323, 23);
    PhoneNumber c1(38, 99, 2323232323);
    PhoneNumber d1(38, 99, 2323232323);
    PhoneNumber e1(38, 99, 2323232323, 23);

    std::pair<Person, PhoneNumber> pair1(a, a1);
    std::pair<Person, PhoneNumber> pair2(b, b1);
    std::pair<Person, PhoneNumber> pair3(c, c1);
    std::pair<Person, PhoneNumber> pair4(d, d1);
    std::pair<Person, PhoneNumber> pair5(e, e1);

    std::vector<std::pair<Person, PhoneNumber>> ven;

    ven.push_back(pair1);
    ven.push_back(pair2);
    ven.push_back(pair3);
    ven.push_back(pair4);
    ven.push_back(pair5);

    for (auto i : ven)
    {
        std::cout << i.first.GetFirstName() << std::endl;
    }
    std::cout << std::endl;

    std::sort(ven.begin(), ven.end(), [](std::pair<Person, PhoneNumber> pair1, std::pair<Person, PhoneNumber> pair2)
        {return pair1.first.GetFirstName() < pair2.first.GetFirstName(); });

    for (auto i : ven)
        {
            std::cout << i.first.GetFirstName() << std::endl;
        }
    std::cout << std::endl;
    */

    

    
    




    return 0;
}