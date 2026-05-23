#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

struct Movie {
    std::string name;
    double rating;
};

class MovieDatabase {
private:
    std::vector<Movie> movies;
    std::unordered_map<std::string, std::vector<Movie>> prefixMap;

public:
    void insert(const std::string& name, double rating);
    std::vector<Movie> getAllAlphabetical() const;
    std::vector<Movie> getMoviesWithPrefix(const std::string& prefix) const;
};

#endif
