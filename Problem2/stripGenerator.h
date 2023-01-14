#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <numeric>

#include "parquetHelpers.h"

typedef uint64_t counterType;

class stripGenerator {

    public:
        stripGenerator(int stripLength, int numRows) : stripLength_(stripLength), numRows_(numRows) {}
        stripGenerator(stripGenerator&) = delete;

        void logStrip(const std::vector<int>& strip) {
            allExpandedStrips_.push_back(strip);
            allStrips_.push_back(stripToInt(strip));
            allCompatibleStrips_.push_back({});
        }

        void permuteStrip(std::vector<int>& strip) {
            while(std::next_permutation(strip.begin(), strip.end())) {
                logStrip(strip);
            }
        }

        void generateValidStrips() {
            const int maxThrees = stripLength_ / 3;
            for (int threes = maxThrees; threes >= 0; --threes) {
                const int remainder = stripLength_ - 3 * threes;
                if (remainder & 1)
                    continue;
                else {
                    const int twos = remainder / 2;
                    std::vector<int> baseStrip (twos, 2);
                    for (int i = 0; i < threes; ++i) {
                        baseStrip.push_back(3);
                    }
                    logStrip(baseStrip);
                    permuteStrip(baseStrip);
                }
            }
        }        

        void generateCompatibleStrips() {
            for (size_t i = 0; i < (allStrips_.size() - 1); ++i) {
                for (size_t j = i + 1; j < allStrips_.size(); ++j) {
                    if (isCompatible(allStrips_[i], allStrips_[j])) {
                        allCompatibleStrips_[i].push_back(j);
                        allCompatibleStrips_[j].push_back(i);
                    }
                }
            }
        }

        counterType calculateOptions() {
            std::vector<counterType> current(allStrips_.size(), 1);
            std::vector<counterType> next(allStrips_.size(), 0);
            
            // printVect<counterType>(current);

            for (int i = 0; i < (numRows_ - 1); ++i) {
                for (size_t stripNumber = 0; stripNumber < allStrips_.size(); ++stripNumber) {
                    if (current[stripNumber] > 0) {
                        for (const auto& c : allCompatibleStrips_[stripNumber])
                            next[c] += current[stripNumber];
                    }
                }
                // printVect<counterType>(next);
                memset(current.data(), 0, sizeof(counterType) * allStrips_.size());
                std::swap(current, next);
            }

            counterType totalOptions = 0;
            for (const auto& c : current) {
                totalOptions += c;
            }

            return totalOptions;
        }

    public:
        const int stripLength_;
        const int numRows_;

        std::vector<std::vector<int>> allExpandedStrips_;
        std::vector<int> allStrips_;
        std::vector<std::vector<int>> allCompatibleStrips_;

};