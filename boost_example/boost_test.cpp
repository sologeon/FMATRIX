#include <fstream>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/export.hpp>

#include<iostream>
using namespace std;

/////////////////////////////////////////////////////////////
// gps coordinate
//
// illustrates serialization for a simple type
//
class gps_position
{
private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    // template<class Archive>
    // void serialize(Archive & ar, const unsigned int version)
    // {
    //     ar & degrees;
    //     ar & minutes;
    //     ar & seconds;
    //     ar & age;
    // }
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar & degrees;
        ar & minutes;
        ar & seconds;
        ar & age;
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar & degrees;
        ar & minutes;
        ar & seconds;
        ar & age;
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    int degrees;
    int minutes;
    float seconds;
public:
    gps_position(){};
    gps_position(int d, int m, float s) :
        degrees(d), minutes(m), seconds(s)
    {}

    int age;
    void display(){
        cout << "age: " << this->age << endl;
    }
};

BOOST_CLASS_VERSION(gps_position, 1);

class bus_shop:public gps_position
{
private:
    friend class boost::serialization::access;
    // template<class Archive>
    // void serialize(Archive & ar, const unsigned int version)
    // {
        
        // ar & boost::serialization::base_object<vector>(*this);
    // }
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar & boost::serialization::base_object<gps_position>(*this);
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<gps_position>(*this);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
    bus_shop():gps_position(){};
    bus_shop(int d, int m, float s):gps_position(d, m, s){};
    ~bus_shop(){};
 
};



int main() {
    // create and open a character archive for output
    std::ofstream ofs("filename");

    // create class instance
    gps_position g(35, 59, 24.567f);
    g.age = 10;
    cout << g.age;

    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        // oa << g;
        oa << g;
    	// archive and stream closed when destructors are called
    }

    // ... some time later restore the class instance to its orginal state
    gps_position newg;
    {
        std::ifstream ifs("filename");
        boost::archive::text_iarchive ia(ifs);
        ia >> newg;
        cout << newg.age;
        newg.display();
    }

    cout << endl << "Derived sample" << endl;
    bus_shop bg(42, 19, 13.156);
    bg.age = 30;
    cout << "the age of bg is: " << bg.age << endl;

    std::ofstream bofs("bg");
    {
        boost::archive::text_oarchive boa(bofs);
        boa << bg;
    }

    bus_shop nbg;
    {
        std::ifstream bifs("bg");
        boost::archive::text_iarchive bia(bifs);
        bia >> nbg;
        cout << endl << "the age of nbg is: " << nbg.age << endl;
        nbg.display();
    }

    return 0;
}