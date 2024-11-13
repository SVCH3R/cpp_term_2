#include <iterator>
#include <type_traits>

template <typename Iterator, typename Distance>
void Advance(Iterator& it, Distance n) {
  if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
                               std::random_access_iterator_tag>) {
    it += n;
  } else {
    for (Distance i = 0; i < n; ++i) {
      ++it;
    }
  }
}

template <typename Iterator>
Iterator Next(Iterator it) {
  if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
                               std::random_access_iterator_tag>) {
    return it + 1;
  } else {
    ++it;
    return it;
  }
}

template <typename Iterator>
Iterator Prev(Iterator it) {
  if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
                               std::random_access_iterator_tag>) {
    return it - 1;
  } else {
    --it;
    return it;
  }
}

template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type Distance(Iterator first, Iterator last) {
  if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
                               std::random_access_iterator_tag>) {
    return last - first;
  } else {
    typename std::iterator_traits<Iterator>::difference_type distance = 0;
    while (first != last) {
      ++distance;
      ++first;
    }
    return distance;
  }
}