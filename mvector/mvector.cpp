#include<iostream>
#include<vector>
#include<math.h>
#include<iterator>
#include<string>
#include<typeinfo>

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/export.hpp>

using namespace std;

template<class T>
class MVECTOR;


template<class T>
class MVECTOR:public vector<T>
{
public:
  MVECTOR():vector<T>(){};
  MVECTOR(int n):vector<T>(n){};
  MVECTOR(int n, const T& val):vector<T>(n, val){};
  MVECTOR(const MVECTOR& x):vector<T>(x){};
  MVECTOR(const vector<T> &x){
    for(int i=0;i<x.size();i++)
      this->push_back(x[i]);
  };
  ~MVECTOR(){};

  MVECTOR<T> operator +(MVECTOR<T> &q);
  MVECTOR<T> operator -(MVECTOR<T> &q);
  MVECTOR<T> operator *(MVECTOR<T> &q);
  MVECTOR<T> operator /(MVECTOR<T> &q);

  // MVECTOR<T> operator+(MVECTOR<T> &q){
  //   MVECTOR<T> res;
  //   for(int i=0;i<q.size();i++){
  //     res.push_back(q.at(i)+this->at(i));
  //   }
  //   return res;
  // };

  // MVECTOR<T> operator-(MVECTOR<T> &q);
  
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<vector<T>>(*this);
        // ar & boost::serialization::base_object<vector>(*this);
    }
    // template<class Archive>
    // void save(Archive & ar, const unsigned int version) const
    // {
    //     ar & boost::serialization::base_object<vector<T>>(*this);
    //     // ar & boost::serialization::base_object<vector>(*this);
    // }
    // template<class Archive>
    // void load(Archive & ar, const unsigned int version)
    // {
    //     ar & boost::serialization::base_object<vector<T>>(*this);
            //     // ar & boost::serialization::base_object<vector>(*this);
    // }
    // BOOST_SERIALIZATION_SPLIT_MEMBER()
    // bool save(string wrpath){
    //     ofstream ofs(wrpath, ios::binary | ios_base::out | ios_base::trunc);
    //     if (!ofs.good())
    //     {
    //         return false;
    //     }
     
    //     boost::archive::binary_oarchive oa(ofs);
    //     oa << this;
    //     return true;
    // }
};


template<class T>
MVECTOR<T> MVECTOR<T>::operator +(MVECTOR<T> &q)
{
    MVECTOR<T> res(q.size());
    for(int i=0;i<q.size();i++){
      // res.push_back(this->at(i)+q.at(i));
      res[i] = this->at(i)-q.at(i);
    }
    return res;
}


template<class T>
MVECTOR<T> MVECTOR<T>::operator -(MVECTOR<T> &q)
{
    MVECTOR<T> res(q.size());
    for(int i=0;i<q.size();i++){
      // res.push_back(this->at(i)-q.at(i));
      res[i] = this->at(i)-q.at(i);
    }
    return res;
}

float v_mean(vector<float> vec){
  int count=0;
  float sum=0.0, mean;
  for(vector<float>::iterator iter=vec.begin(); iter!=vec.end(); iter++){
      count++;
      sum += *iter;
  }
  if (count>0)
    mean = sum / float(count);
  return mean;
}


int main(){
    vector<float> ilistbefore;
    vector<int>ilist;
    for(int i=0;i<10;i++)//push_back(elem)在数组最后添加数据 
    {
        ilist.push_back(i);
        ilistbefore.push_back(float(i));
    }
    // vector<float> ilist = {1.1, 2.2, 3.3, 4.0, 5.5, 6.6, 7.0};
    cout << endl << "The vector ilist is following:" << endl;
    for(vector<int>::iterator iter=ilist.begin(); iter!=ilist.end(); iter++)
        cout<<*iter<<" ";
    cout << endl;

    MVECTOR<int> qv1, qv2;
    for(int i=0;i<10;i++)//push_back(elem)在数组最后添加数据 
    {
        qv1.push_back(i);
        qv2.push_back(i+10);
    }
    cout << endl << "The vector qv1 is following:" << endl;
    for(MVECTOR<int>::iterator iter=qv1.begin(); iter!=qv1.end(); iter++)
        cout<<*iter<<" ";
    cout << endl;
    cout << endl << "The vector qv2 is following:" << endl;
    for(MVECTOR<int>::iterator iter=qv2.begin(); iter!=qv2.end(); iter++)
        cout<<*iter<<" ";
    cout << endl;

    cout << (&qv2)->at(0) << endl;
    cout << qv2[0] << "qv2[0]" << endl;

    qv2[1] = 111;
    cout << qv2[1] << endl;

    cout << qv2.at(1) << "qv2at1" << endl;


    MVECTOR<int> qv3;
    qv3 = qv1+qv2;
    cout << endl << "The vector qv1+qv2 is following:" << endl;
    for(MVECTOR<int>::iterator iter=qv3.begin(); iter!=qv3.end(); iter++)
        cout<<*iter<<" ";
    cout << endl;

    MVECTOR<int> qv4;
    qv4 = qv2-qv1;
    cout << endl << "The vector qv2-qv1 is following:" << endl;
    for(MVECTOR<int>::iterator iter=qv4.begin(); iter!=qv4.end(); iter++)
        cout<<*iter<<" ";
    cout << endl;

    MVECTOR<int> qv5(20, 100);
    cout << endl << "The size of qv5 is: " << qv5.size() << endl;
    cout << endl << "The vector qv5 is following:" << endl;
    for(MVECTOR<int>::iterator iter=qv5.begin(); iter!=qv5.end(); iter++)
        cout<<*iter<<" ";
    cout << endl;

    MVECTOR<int> qv6(qv5);
    cout << endl << "The vector qv6 is following:" << endl;
    for(MVECTOR<int>::iterator iter=qv6.begin(); iter!=qv6.end(); iter++)
        cout<<*iter<<" ";
    cout << endl;

    MVECTOR<int> qv7(ilist);
    cout << endl << "The vector qv7 is following:" << endl;
    for(MVECTOR<int>::iterator iter=qv7.begin(); iter!=qv7.end(); iter++)
        cout<<*iter<<" ";
    cout << endl;

    std::ofstream ofs("filename");
    {
        boost::archive::text_oarchive oa(ofs);
        // oa << qv5;
    }
    // MVECTOR<int> newg;
    // {
    //     // create and open an archive for input
    //     std::ifstream ifs("filename");
    //     boost::archive::text_iarchive ia(ifs);
    //     // read class state from archive
    //     ia >> newg;
    //     cout << endl << "The vector newg is following:" << endl;
    //     for(MVECTOR<int>::iterator iter=newg.begin(); iter!=newg.end(); iter++)
    //         cout<<*iter<<" ";
    //     cout << endl;
    // }


    vector<vector<float>> cachdata(10);
    vector<vector<float>>::iterator v = (cachdata.begin()+2);
    v->push_back(3);
    cout << cachdata[2].size() << endl;
    cout << v->size() << endl;

    cout << v_mean(*(&ilistbefore)) << endl;

    cout << endl << "Hello World" << endl;
    return 0;
}
