#include "primer/orset.h"
#include <algorithm>
#include <string>
#include <vector>
#include "common/exception.h"
#include "fmt/format.h"

namespace bustub {

// template<typename T> 

template <typename T>
auto ORSet<T>::Contains(const T &elem) const -> bool {
  // TODO(student): Implement this
  bool exists = false;
  for(auto element = this->Addset.begin(); element != this->Addset.end(); element++){
    if(element->first == elem){
      exists = true;
      break;
    }
  }
  // for(auto element = this->Removeset.begin(); element != this->Removeset.end(); element++){
  //   if(element->first == elem){
  //     exists = false;
  //     break;
  //   }
  // }
  return exists;
  // throw NotImplementedException("ORSet<T>::Contains is not implemented");
}

template <typename T>
void ORSet<T>::Add(const T &elem, uid_t uid) {
  // TODO(student): Implement this
  // throw NotImplementedException("ORSet<T>::Add is not implemented");
  std::pair<T,uid_t> p_add(elem, uid);
  this->Addset.insert(p_add);
}
template <typename T>
void ORSet<T>::hello(){
  std::cout << "Hello\n";
}
template <typename T>
void ORSet<T>::Remove(const T &elem) {
  // TODO(student): Implement this
  std::vector<std::pair<T,uid_t>> vec_remove;
  for(auto element = this->Addset.begin(); element != this->Addset.end(); element++){
    if(element->first == elem){
      vec_remove.push_back(std::pair<T,uid_t>(elem,element->second));
      // this->Addset.erase();
    }
  }
  for(auto element = vec_remove.begin(); element != vec_remove.end(); element++){
    this->Removeset.insert(std::pair<T,uid_t>(element->first,element->second));
    this->Addset.erase(std::pair<T,uid_t>(element->first,element->second)); 
  }
  // throw NotImplementedException("ORSet<T>::Remove is not implemented");
}

template <typename T>
void ORSet<T>::Merge(const ORSet<T> &other) {
  // TODO(student): Implement this
  std::set<std::pair<T,uid_t>> inset;
  // std::set<std::pair<T,uid_t>> inother;
  for(auto element = this->Addset.begin(); element != this->Addset.end(); element++){
    std::pair<T,uid_t> p_element(element->first, element->second);
    if(other.Removeset.count(p_element) == 0){
      inset.insert(p_element);
    }
  }
  for(auto element = other.Addset.begin(); element != other.Addset.end(); element++){
    std::pair<T,uid_t> p_element(element->first, element->second);
    if(this->Removeset.count(p_element) == 0){
      inset.insert(p_element);
    }
  }
  this->Addset = inset;
  this->Removeset.insert(other.Removeset.begin(), other.Removeset.end());
  // throw NotImplementedException("ORSet<T>::Merge is not implemented");
}

template <typename T>
auto ORSet<T>::Elements() const -> std::vector<T> {
  std::vector<T> vec;
  for(auto element = this->Addset.begin(); element != this->Addset.end(); element++){
    vec.push_back(element->first);
  }
  return vec;
  // TODO(student): Implement this
  // throw NotImplementedException("ORSet<T>::Elements is not implemented");
}

template <typename T>
auto ORSet<T>::ToString() const -> std::string {
  auto elements = Elements();
  std::sort(elements.begin(), elements.end());
  return fmt::format("{{{}}}", fmt::join(elements, ", "));
}

template class ORSet<int>;
template class ORSet<std::string>;

}  // namespace bustub
