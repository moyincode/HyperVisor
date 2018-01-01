/*
 * Module for type conversions
 *
 * Author :
 *
 * Copyright (C) 2017 , All Rights Reserved.
 */

#include <mainwindow.h>
#include "util.h"
#include <QMessageBox>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

// function to convert string to vector<long long>
std::vector<unsigned long long> strToUllvec(std::string &s) {

    std::stringstream ss(s) ;
    std::vector<unsigned long long> v ;
    std::string token ;
    while(std::getline(ss,token,','))
        v.push_back(strtoull(token.c_str(),NULL,0));
    return v ;
}


// function to convert vector<string> to string
std::string string_from_vector(const std::vector<std::string> &vec) {
    std::string ret_str="";
    if( vec.size() ==0 )
        return ret_str;
    for( auto & val : vec)
    {
        ret_str = ret_str + val + "|" ;
    }
    return std::string(std::begin(ret_str),std::end(ret_str) -1 );

}


// function to convert vector<long> to string
std::string string_from_long_vec(std::vector<UNS_64> vec, std::string seprator)
{
    std::string ret_str="";
    if( vec.size() ==0 )
        return ret_str;
    for( auto & val : vec)
    {
        ret_str = ret_str + std::to_string(val) + seprator ;
    }
    return std::string(std::begin(ret_str),std::end(ret_str) -1 );
}

template <typename C, typename T>
T findKey(C m, T val)
{
    for(auto a : m)
        if (a.second == val)
            return a.first;
    throw JailHouseCell_error("val not present in the given container\n");
}
