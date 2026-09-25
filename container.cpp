#include <iostream>
#include <vector>
#include <map>
#include <set>

template<typename Container>
void CheckContainer(Container& c)
{
    std::cout << c.size() << std::endl;
}

template<typename Container>
class ContainerWrapper
{
    public:
    ContainerWrapper(Container& c)
    {
        m_c = c;
    }
    private:
    void DumpContainer()
    {

    }
    Container m_c;
};

template<typename T,typename V>
struct TwoTypesTest{}; 

template<typename T,typename K>
class VectorWrapper
{
    public:
        VectorWrapper(std::vector<T>& vec,K* k_ptr)
        {
            m_vec = vec;

            if(!k_ptr){
                m_ptr = new K();
            }

            this->DumpVector();
            
        }

    private:
        void DumpVector()
        {
            auto i = m_vec.begin();
            while(i != m_vec.end()){
                std::cout << *i << std::endl;
                i++;
            }
        }
    K* m_ptr = nullptr;
    std::vector<T> m_vec;
    TwoTypesTest<T,K> ttt;
};



int main()
{
    std::vector<int> v = {1,2,3};
    std::map<std::string,int> m  = {{"ONE",1},{"TWO",2},{"THREE",3}};
    std::set<char> s = {'A','B','C','D'};
    std::vector<std::string> str_v = {"ZERO","ONE"};
    CheckContainer(s);
    
    ContainerWrapper< std::map<std::string,int> > cw(m);
    ContainerWrapper< std::vector<int> > cw2(v);
    VectorWrapper<std::string,int> vw(str_v,nullptr);

    return 0;
}