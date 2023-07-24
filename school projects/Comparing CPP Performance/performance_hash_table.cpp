#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();
template <class T>
void hash_table_sort(std::unordered_map<T, int> &ht, std::ostream &ostr, int &output_count) {
  //hash tables don't use sort functions
  (void)ht; //set hash table to void (avoiding warning about unused parameter)
  //print nothing
  ostr << std::endl;
  //set output count to 0, because you don't need this function
  output_count = 0;
}
template <class T>
void hash_table_remove_duplicates(std::unordered_map<T, int> &ht, std::ostream &ostr, int &output_count, std::istream &istr, int &input_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  //similar to maps
  T x;
  while(istr >> x){
    if(ht.find(x)==ht.end()){
      ht.insert(std::make_pair(x, 1));
      ostr << x << std::endl;
    }
    input_count++;
  }
  //uses bucket_count to get the number of buckets
  output_count = ht.bucket_count();
}

template <class T>
void hash_table_mode(std::unordered_map<T, int> &ht, std::ostream &ostr, int &output_count) {
  //similar mode function to the one in BST, changed the iterator type to unordered_map
  typename std::unordered_map<T, int>::iterator iter1 = std::max_element(ht.begin(), ht.end(), [] 
  (const std::pair<T, int> & x, const std::pair<T, int> & y)->bool {
      return x.second < y.second;
  });
  output_count = 1;
  ostr << iter1->first << std::endl;
}

void hash_table_closest_pair(std::unordered_map<int, int> &ht, std::ostream &ostr, int &output_count) {
  //assertion, also using bucket_count for size accuracy
 assert (ht.bucket_count() >= 2);
  output_count = 2;
  // the two elements with closest value must be next to each other in sorted order
  //using three iterators since we can't decrement unordered_maps
  typename std::unordered_map<int, int>::iterator iter1;
  typename std::unordered_map<int, int>::iterator iter2;
  typename std::unordered_map<int, int>::iterator iter3 = ht.begin();
  //loops through the first iterator
  for (iter1 = ht.begin(); iter1 != ht.end(); iter1++) {
    //increments the third one (so its on the next value)
    iter3++;
    //set the second one to the next value
    iter2 = iter3;
    //looping through the iterator to check the values and pairs
    while(iter2 != ht.end()){
      //if we are at the end, break from the for loop
      if(iter1 == ht.end()){
      break;
    }
    //else keep checking values
    iter2++;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << iter2->first << "\n";
  iter2++;
  ostr << iter2->first << "\n";
}
template <class T>
void hash_table_first_sorted(std::unordered_map<T, int> &ht, std::ostream &ostr, int &output_count, int optional_arg) {
  //again, hash tables don't use sorting
  (void)ht; //voiding hash table
  (void)optional_arg; //voiding optional arg
  //print nothing
  ostr << std::endl;
  //set output count to 0 (since function is not being used)
  output_count = 0;
}

void hash_table_longest_substring(std::unordered_map<std::string, int> &ht, std::ostream &ostr, int &output_count) {
  //also similar to previous longest substrings but using similar iterator style seen in
  //closest_pair
  std::string str = "";
  //three iterators since we can't decrement values,
  //we have iterators that keep track of 
  //previous and next values
    typename std::unordered_map<std::string, int>::iterator iter1;
    typename std::unordered_map<std::string, int>::iterator iter2 = ++ht.begin();
    typename std::unordered_map<std::string, int>::iterator iter3 = ht.begin();
    //loopt through the first iterator
    for (iter1 = ht.begin(); iter1 != ht.end(); iter1++){
      //incrementing third and changing the second one
      iter3++;
      iter2 = iter3;
      //loops through the second
        for (iter2 = ht.begin(); iter2 != ht.end(); iter2++ ){
          //loops through their indexes
            for (unsigned int ind1 = 0; ind1 < iter1->first.size(); ind1++){
                for (unsigned int ind2 = str.size()+1; ind2 <= iter1->first.size() - ind1; ind2++ ){
                  //creates substrings
                    std::string sub1 = (iter1->first).substr(ind1, ind2);
                    //checks substings
                    if (iter2->first.find(sub1) != std::string::npos && iter1 != iter2){
                        if (str.length() < sub1.length()){
                            str = sub1;
                        }
                    }
                }
            }
        }
    }
    output_count = 1;
    ostr << str << std::endl;
}


void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

 if (type == "string") {
    // load the data into a map of strings
    std::unordered_map<std::string, int> ht;
    //prioritzing remove duplicates again to avoid sorting, since we want the hashtable to be unsorted
    if (operation == "remove_duplicates") { hash_table_remove_duplicates (ht,ostr,output_count, istr, input_count); }
    else{
      //else, continue for the rest of the function
      std::string s;
    input_count = 0;
    while (istr >> s) {
      ht[s]++;
      input_count++;
    }
       if      (operation == "sort")             { hash_table_sort              (ht,ostr,output_count); }
    else if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { hash_table_first_sorted      (ht,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { hash_table_longest_substring (ht,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }
  //same for the integer types
  else {
    assert (type == "integer");
    // load the data into a map of integers
    std::unordered_map<int, int> ht;
    if (operation == "remove_duplicates") { hash_table_remove_duplicates (ht,ostr,output_count, istr, input_count); }
    else{
      int v;
    input_count = 0;
    while (istr >> v) {
      ht[v]++;
      input_count++;
    }
      if      (operation == "sort")              { hash_table_sort              (ht,ostr,output_count); }
    else if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count); }
    else if (operation == "closest_pair")      { hash_table_closest_pair      (ht,ostr,output_count); }
    else if (operation == "first_sorted")      { hash_table_first_sorted      (ht,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }
}
