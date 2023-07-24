#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();

template <class T>
void list_sort(std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // use the list sort algorithm
  lst.sort();
  output_count = lst.size();
  typename std::list<T>::const_iterator iter1;
  for (iter1 = lst.begin(); iter1 != lst.end(); iter1++) {
    ostr << *iter1 << "\n";
  }
}
template <class T>
void list_remove_duplicates(const std::list<T> &lst, std::ostream &ostr, int &output_count) { 
  output_count = 0;
  //using iterators since we can't index lists
  typename std::list<T>::const_iterator iter1;
  typename std::list<T>::const_iterator iter2;
  //loops through checking duplicates
  for (iter1 = lst.begin(); iter1 != lst.end(); iter1++) {
    bool dup = false;
    for (iter2 = lst.begin(); iter2 != iter1; iter2++) {
      //compares the dereferenced values
      if (*iter1 == *iter2) {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << *iter1 << "\n";
      output_count++;
    }
  }
}

template <class T>
void list_mode(std::list<T> &lst, std::ostream &ostr, int &output_count) {
//since this already uses iterators for us, not much to change from vectors
  // use the list sort algorithm
  lst.sort();
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::list<T>::iterator current = lst.begin();
  ++current;
  typename std::list<T>::iterator previous = lst.begin();
  for (; current != lst.end(); ++current, ++previous) {
    if (*current == *previous) {
      // if they are the same element increment the count
      current_count++;
    } else if (current_count >= mode_count) {
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    } else {
      current_count = 1;
    }
  }
  if (current_count >= mode_count) {
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }
  // save the mode to the output list
  output_count = 1;
  ostr << mode << "\n";
}

void list_closest_pair(std::list<int> &lst, std::ostream &ostr, int &output_count) {
  assert (lst.size() >= 2);
  // use the list sort algorithm
  lst.sort();
  output_count = 2;
  int best;
  // the two elements with closest value must be next to each other in sorted order
  //again, using iterators
  typename std::list<int>::iterator iter1;
  typename std::list<int>::iterator iter2;
  for (iter1 = lst.begin(); iter1 != lst.end(); iter1++) {
    //gets the first value
    int first = *iter1;
    //increments the iterator
    iter1++;
    //checks if we are at the end
    if(iter1 == lst.end()){
      break;
    }
    //since you incremented the the iter
    //set a second value to the current iter 
    // which is now the next value
    int second = *iter1;
    //then decrement it again to get back to the first value
    iter1--;
    //takes the difference between the two
    int diff = second-first;
    //if the iterator is still at the beginning or if it's less than the best
    if (iter1 == lst.begin() || diff < best) {
      //set the best to the difference
      best = diff;
      //set the second iterator to the first
      iter2 = iter1;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << *iter2 << "\n";
  //increment to get the next value
  iter2++;
  ostr << *iter2 << "\n";
}

template <class T>
void list_first_sorted(std::list<T> &lst, std::ostream &ostr, int &output_count, int optional_arg) {
  //asserting
  assert (optional_arg >= 1);
  assert ((int)lst.size() >= optional_arg);
  // use the list sort algorithm
  lst.sort();
  output_count = optional_arg;
  typename std::list<T>::iterator iter1 = lst.begin();
  //loops through printing the sorted items
  for (int i = 0; i < output_count; i++) {
    ostr << *iter1 << "\n";
    iter1++;
  }
}
void list_longest_substring(std::list<std::string> &lst, std::ostream &ostr, int &output_count) {
  //creates a string variable to hold the longest substring
  std::string str = "";
  //similar to vectors, but we use iterators instead because we are using lists
    typename std::list<std::string>::iterator iter1;
    typename std::list<std::string>::iterator iter2 = ++lst.begin();
    for (iter1 = lst.begin(); iter1 != --(lst.end()); iter1++){
        for (iter2 = lst.begin(); iter2 != lst.end(); iter2++ ){
            for (unsigned int ind1 = 0; ind1 < iter1->size(); ind1++){
                for (unsigned int ind2 = str.size()+1; ind2 <= (*iter1).size() - ind1; ind2++ ){
                    std::string sub1 = (*iter1).substr(ind1, ind2);
                    //uses npos to go until the end of the string
                    if (iter2->find(sub1) != std::string::npos && iter1 != iter2){
                        if (str.length() < sub1.length()){
                            str = sub1;
                        }
                    }
                }
            }
        }
    }
    //prints out longest substring
    output_count = 1;
    ostr << str << std::endl;
  
}


void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // load the data into a list of strings
    std::list<std::string> lst;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      lst.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a list of integers
    std::list<int> lst;
    int v;
    input_count = 0;
    while (istr >> v) {
      lst.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

}
