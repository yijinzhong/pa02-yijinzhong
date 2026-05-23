// Winter'24
// Instructor: Diba Mirza
// Student name: Yijin Zhong
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
   MovieDatabase db;


    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
           db.insert(movieName, movieRating);

    }

    movieFile.close();

    if (argc == 2){
          for (auto& m : db.getAllAlphabetical())
             cout << m.name << ", " << fixed << setprecision(1) << m.rating << "\n";
                    return 0;

    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
vector<pair<string, Movie>> bestMovies;

for (auto& prefix : prefixes) {
    auto movies = db.getMoviesWithPrefix(prefix);
    if (movies.empty()) {
        cout << "No movies found with prefix " << prefix << "\n";
    } else {
        for (auto& m : movies)
            cout << m.name << ", " << fixed << setprecision(1) << m.rating << "\n";
        bestMovies.push_back({prefix, movies[0]});
        cout << "\n";
}
    
}

for (auto& [prefix, m] : bestMovies)
    cout << "Best movie with prefix " << prefix << " is: " << m.name << " with rating " << fixed << setprecision(1) << m.rating << "\n";


    return 0;
}



/* Add your run time analysis for part 3 of the assignment here as commented block*/

/*
 * Part 3a: Time Complexity Analysis
 *
 * Assuming all n movies are already stored in the data structure:
 *
 * Per query:
 *   - Hash lookup in unordered_map: O(1)
 *   - Push at most k matching movies into priority queue: O(k log k)
 *   - Pop k movies out: O(k log k)
 * Per query total: O(k log k)
 * Total for m queries: O(m * k log k)
 * n and l do not affect query time since we use a precomputed hashmap.
 *
 * Measured runtimes using prefix_large.txt:
 *   input_20_random.csv:    6ms
 *   input_100_random.csv:   12ms
 *   input_1000_random.csv:  22ms
 *   input_76920_random.csv: 2667ms
 *
 * Runtime grows with both m and k. As n increases, more movies
 * match each prefix on average, so k grows with n. This explains
 * why runtime grew faster than expected from m alone — the larger
 * dataset increases k, which increases priority queue operations.
 * This is consistent with O(m * k log k).
 *
 * Part 3b: Space Complexity Analysis
 *
 * Assuming n movies are already stored in the data structure,
 * the only extra space used per query is the priority queue.
 * It holds at most k movies at a time, each with a name of
 * length at most l, so space per query is O(k * l).
 * After each query the priority queue is cleared, so m does
 * not accumulate space across queries.
 * Overall extra space complexity: O(k * l)
 *
 * Part 3c: Tradeoff
 *
 * We designed for low time complexity. We used an unordered_map
 * to precompute all prefix mappings for O(1) lookup, and a priority
 * queue to retrieve the top k results sorted by rating in O(k log k).
 *
 * Were you able to achieve a low space complexity as well?
 * No. The unordered_map stores every prefix of every movie name,
 * costing O(n * l^2) space during preprocessing.
 *
 * Why or why not?
 * To eliminate the linear scan over all n movies per query,
 * we had to store all prefix mappings upfront. This is a
 * direct time-space tradeoff: reducing query time from O(n * l)
 * to O(1) required significantly more preprocessing space.
 * Low space and low query time cannot both be achieved
 * with this approach.
 */


bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}