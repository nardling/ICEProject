#include <vector>

int stripToInt(const std::vector<int>& strip) {
    int result = 0;
    for (auto it = strip.begin(); it != strip.end(); ++it) {
        result = result << (*it);
        ++result;
    }
    // because every strip ends at STRIP_LENGTH and we don't care
    --result;
    return result;
}

bool isCompatible(int a, int b) {
    return (a & b) == 0;
}

template<typename T>
void printVect(const std::vector<T>& strip) {
    for (const auto& c : strip)
        std::cout << c << " ";
    std::cout << '\n';
}

void printCompatibleStrips(const std::vector<std::vector<int>>& allCompatibleStrips) {
    for (size_t i = 0; i < allCompatibleStrips.size(); ++i) {
        std::cout << i << ": ";
        printVect<int>(allCompatibleStrips[i]);
    }
}