#ifndef UTIL_H
#define UTIL_H

#include <mainwindow.h>
#include <QMessageBox>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <map>
#include "J_error.h"

template <typename C, typename T>
T findKey(C m, T val);

std::vector<unsigned long long> strToUllvec(std::string &s) ;


std::string string_from_vector(const std::vector<std::string> &pieces) ;


//template <typename T>
std::string string_from_long_vec(std::vector<UNS_64> vec, std::string seprator);



#endif // UTIL_H



