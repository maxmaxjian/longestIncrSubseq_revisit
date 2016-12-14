#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

class solution {
  public:
    // solution 1
    // int lengthOfLIS(const std::vector<int> & nums) {
    //     std::vector<std::vector<int>> vecs;
    //     for (auto & n : nums) {
    //         if (vecs.empty())
    //             vecs.push_back(std::vector<int>{n});
    //         else {
    //             if (std::all_of(vecs.begin(), vecs.end(),
    //                             [&](const std::vector<int> &v){return v.back() > n;}))
    //                 vecs.push_back(std::vector<int>{n});
    //             else {
    //                 auto it = vecs.begin();
    //                 while (it != vecs.end() && it->back() > n)
    //                     ++it;
    //                 auto curr = std::next(it);
    //                 while (curr != vecs.end()) {
    //                     if (curr->back() < n && curr->size() > it->size())
    //                         it = curr;
    //                     ++curr;
    //                 }
    //                 auto cpy = *it;
    //                 cpy.push_back(n);
    //                 it = vecs.begin();
    //                 while (it != vecs.end()) {
    //                     if (it->size() == cpy.size())
    //                         it = vecs.erase(it);
    //                     else
    //                         ++it;
    //                 }
    //                 vecs.push_back(cpy);
    //             }
    //         }

    //         std::for_each(vecs.begin(), vecs.end(), [](const std::vector<int> & v){
    //             std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    //             std::cout << std::endl;
    //         });
    //     }

    //     auto it = std::max_element(vecs.begin(), vecs.end(), [](const std::vector<int> & v1, const std::vector<int> & v2){return v1.size() < v2.size();});
        
    //     return it->size();
    // }

    // solution 2 patience solitaire
    int lengthOfLIS(const std::vector<int> & nums) {
        std::vector<std::vector<std::pair<size_t,int>>> vecs;
        for (auto & n : nums) {
            auto it = vecs.begin();
            while (it != vecs.end() && it->back().second < n)
                ++it;
            if (it == vecs.end()) {
                if (it == vecs.begin())
                    vecs.push_back(std::vector<std::pair<size_t,int>>{std::make_pair(0,n)});
                else {
                    auto prev = std::prev(it);
                    vecs.push_back(std::vector<std::pair<size_t,int>>{std::make_pair(prev->size()-1,n)});
                }
            }
            else {
                if (it == vecs.begin())
                    it->push_back(std::make_pair(0,n));
                else {
                    auto prev = std::prev(it);
                    it->push_back(std::make_pair(prev->size()-1,n));
                }
            }

            std::for_each(vecs.begin(), vecs.end(),
                          [](const std::vector<std::pair<size_t,int>> & v){
                              std::for_each(v.begin(), v.end(), [](const std::pair<size_t,int> &p){
                                  std::cout << p.second << " ";
                              });
                              std::cout << std::endl;
                          });
            std::cout << std::endl;
        }

        std::vector<int> lis;
        auto it = vecs.rbegin();
        size_t idx = it->size()-1;
        while (it != vecs.rend()) {
            lis.push_back((*it)[idx].second);
            idx = (*it)[idx].first;
            ++it;
        }
        std::copy(lis.rbegin(), lis.rend(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;

        return vecs.size();
    }    
};

int main() {
    // std::vector<int> nums{10,9,2,5,3,7,101,18};
    std::vector<int> nums{6,3,5,10,11,2,9,14,13,7,4,8,12};

    solution soln;
    int len = soln.lengthOfLIS(nums);
    std::cout << "The length of the longest LIS is:\n" << len << std::endl;
}
