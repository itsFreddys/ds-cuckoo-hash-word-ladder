#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <unordered_map>


// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
    std::string line, word;
    std::stringstream ss;

    while(	getline(in, line) )
    {
        ss.clear();
        ss << line;
        while( ss >> word )
        {
            words.insert( word );
        }
    }

}


// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words)
{
    std::vector< std::string > ret;
    // base cases
    if (s1 == s2){ ret.push_back(s1); return ret;} // s1 and s2 are the same
    if (s1.size() != s2.size()) { return ret;}      // s1 and s2 are different sizes, so path not possible
    if (!words.contains(s2)) { return ret; } // s2 are not part of the words

    std::queue<std::string> q;
    std::unordered_map<std::string, std::string> set;
    std::string temp_s;
    std::string alt_s;
    q.push(s1);

    while (!q.empty()){
        temp_s = q.front();
        q.pop();

        for (size_t i=0; i < temp_s.size(); ++i){
            alt_s = temp_s; // cat -> *at -> c*t -> ca*
            for (char c = 'a'; c <= 'z'; ++c){
                alt_s[i] = c;
                // if alt word is end word, break
                if (alt_s == s2) {
                    set[alt_s] = temp_s;
                    break;
                }
                // check if alt_string is part of words, check that it doesnt exist in map set
                if (words.contains(alt_s) && set.count(alt_s) == 0){
                    set[alt_s] = temp_s;
                    q.push(alt_s);
                }
            } if (alt_s == s2) {
				break;
			}
        } if(alt_s == s2){ break;}
    }

	if (set.empty())
			return ret;  // No path found

	std::string current = s2;
	std::vector<std::string> temp_v;
	while (current != s1){
		temp_v.push_back(current);
		current = set[current];
	}
	temp_v.push_back(s1);

	for (size_t i = temp_v.size() - 1; i != 0; --i){
        ret.push_back(temp_v[i]);
    }
	ret.push_back(s2);


    return ret;  // stub obviously
}
