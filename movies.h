#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>
#include <queue>

struct Movie {
    std::string name;
    double rating;
};

class MovieDatabase {
private:
    std::vector<Movie> movies;

public:
    void insert(const std::string& name, double rating);
    std::vector<Movie> getAllAlphabetical() const;
    std::vector<Movie> getMoviesWithPrefix(const std::string& prefix) const;

    
};

#endif
