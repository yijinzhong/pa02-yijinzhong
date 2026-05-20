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
 * For each of the m prefixes:
 *   - Iterate through all n movies to find matches: O(n * l)
 *     (each name comparison costs O(l) in the worst case)
 *   - Push k matching movies into priority queue: O(k log k)
 *   - Pop k movies out: O(k log k)
 *
 * Per prefix: O(n*l + k*log(k))
 * Total for m prefixes: O(m * (n*l + k*log(k)))
 *
 * Measured runtimes using prefix_large.txt:
 *   input_20_random.csv:    17ms
 *   input_100_random.csv:   36ms
 *   input_1000_random.csv:  227ms
 *   input_76920_random.csv: 19194ms
 *
 * The trend matches O(m*n*l): as n grows ~77x (1000->76920),
 * runtime grows ~84x (227ms->19194ms).
 *
 * Part 3b: Space Complexity Analysis
 *
 * - Storing n movies in vector: O(n * l)
 * - Per query, priority queue holds at most k movies: O(k * l)
 * - m and k do not affect persistent storage.
 * - Overall: O(n * l)
 *
 * Part 3c: Tradeoff
 *
 * This algorithm was designed for correctness first,
 * not specifically for low time or space complexity.
 *
 * Time complexity is O(m*n*l) — not optimal because
 * we scan all n movies for every prefix.
 * The bottleneck is the linear scan: as n grows larger,
 * the runtime grows proportionally, which matches our
 * measured runtimes (n=1000: 227ms, n=76920: 19194ms).
 *
 * Space complexity is O(n*l) — this is unavoidable
 * since all n movies must be stored.
 *
 * Time complexity was harder to optimize than space complexity.
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