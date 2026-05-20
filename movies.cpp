#include "movies.h"

void MovieDatabase::insert(const std::string& name, double rating) {
    movies.push_back({name, rating});
}

std::vector<Movie> MovieDatabase::getAllAlphabetical() const {
    auto cmp = [](const Movie& a, const Movie& b) {
        return a.name > b.name;
    };
    std::priority_queue<Movie, std::vector<Movie>, decltype(cmp)> pq(cmp);
    for (auto& m : movies)
        pq.push(m);
    std::vector<Movie> result;
    while (!pq.empty()) {
        result.push_back(pq.top());
        pq.pop();
    }
    return result;
}

std::vector<Movie> MovieDatabase::getMoviesWithPrefix(const std::string& prefix) const {
    auto cmp = [](const Movie& a, const Movie& b) {
        if (a.rating != b.rating) return a.rating < b.rating;
        return a.name > b.name;
    };
    std::priority_queue<Movie, std::vector<Movie>, decltype(cmp)> pq(cmp);
    
    for (auto& m : movies) {
        if (m.name.substr(0, prefix.size()) == prefix)
            pq.push(m);
    }
    
    std::vector<Movie> result;
    while (!pq.empty()) {
        result.push_back(pq.top());
        pq.pop();
    }
    return result;
}

