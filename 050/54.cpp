#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

class Hand {
private:
  static inline int CARD_BASE = 15;

  std::vector<int> mVals;
  std::vector<char> mSuits;

  std::vector<int> mEval;
  friend bool testHighest();
  friend bool testPair();
  friend bool testTwoPair();
  friend bool testToK();
  friend bool testStraight();
  friend bool testFlush();
  friend bool testFH();
  friend bool testFoK();
  friend bool testSF();
  friend bool testRF();

  int getHighest() { return mVals[0]; }

  int getPair() {
    for (int i = 0; i < this->mVals.size() - 1; i++) {
      if (mVals[i] == mVals[i + 1]) {
        // Value of Pair + high card if the high card is/is not in the pair
        if (i != 0)
          return (mVals[i] * CARD_BASE) + mVals[0];
        if (i == 0) {
          return (mVals[i] * CARD_BASE) + mVals[2];
        }
      }
    }
    return 0;
  }

  int getTwoPair() {

    if (mVals[0] == mVals[1] && mVals[2] == mVals[3])
      return mVals[0] * CARD_BASE * CARD_BASE + mVals[2] * CARD_BASE + mVals[4];

    if (mVals[0] == mVals[1] && mVals[3] == mVals[4])
      return mVals[0] * CARD_BASE * CARD_BASE + mVals[3] * CARD_BASE + mVals[2];

    if (mVals[1] == mVals[2] && mVals[3] == mVals[4])
      return mVals[1] * CARD_BASE * CARD_BASE + mVals[3] * CARD_BASE + mVals[0];

    return 0;
  }

  int getToK() {
    if (mVals[0] == mVals[1] && mVals[1] == mVals[2])
      return CARD_BASE * mVals[0] + mVals[3];
    if (mVals[1] == mVals[2] && mVals[2] == mVals[3])
      return CARD_BASE * mVals[1] + mVals[0];
    if (mVals[2] == mVals[3] && mVals[3] == mVals[4])
      return CARD_BASE * mVals[2] + mVals[0];
    return 0;
  }

  int getFH() {
    if (mVals[0] == mVals[1] && mVals[1] == mVals[2] && mVals[3] == mVals[4])
      return mVals[0] * CARD_BASE + mVals[3];
    if (mVals[0] == mVals[1] && mVals[2] == mVals[3] && mVals[3] == mVals[4])
      return mVals[2] * CARD_BASE + mVals[0];
    return 0;
  }

  int getFoK() {
    if (mVals[0] == mVals[1] && mVals[1] == mVals[2] && mVals[2] == mVals[3]) {
      return mVals[0] * CARD_BASE + mVals[4];
    }
    if (mVals[1] == mVals[2] && mVals[2] == mVals[3] && mVals[3] == mVals[4]) {
      return mVals[1] * CARD_BASE + mVals[0];
    }
    return 0;
  }

  int getStraight() {
    if (mEval[1]) {
      return 0;
    }
    for (int i = 0; i < mVals.size() - 1; i++) {
      if (mVals[i] - 1 != mVals[i + 1])
        return 0;
    }
    return mVals[0];
  }

  int getFlush() {
    for (int i = 0; i < mSuits.size(); i++) {
      if (mSuits[0] != mSuits[i])
        return 0;
    }
    return mVals[0];
  }

  int getSF() { return (mEval[5] && mEval[4]) * mVals[0]; }

  int getRF() { return (mEval[8] && (mVals[0] == 14)); }

public:
  Hand(std::vector<int> v = {}, std::vector<char> s = {})
      : mVals(v), mSuits(s), mEval(10, 0) {

    assert(v.size() == s.size());
    assert(v.size() == 5);

    // Reseting the size of everything
    for (int i = 0; i < v.size(); i++) {
      int maxId = i;
      for (int j = i + 1; j < v.size(); j++) {
        if (mVals[j] > mVals[maxId]) {
          maxId = j;
        }
      }
      std::swap(mVals[i], mVals[maxId]);
      std::swap(mSuits[i], mSuits[maxId]);
    }

    this->mEval[0] = getHighest();
    this->mEval[1] = getPair();
    this->mEval[2] = getTwoPair();
    this->mEval[3] = getToK();
    this->mEval[4] = getStraight();
    this->mEval[5] = getFlush();
    this->mEval[6] = getFH();
    this->mEval[7] = getFoK();
    this->mEval[8] = getSF();
    this->mEval[9] = getRF();
  }

  bool operator>(Hand &other) {
    // std::cout << "-----------\n";
    // std::vector<std::string> names{"High", "Pair", "2Pair", "ToK", "St8",
    // "Flu", "FH", "FoK", "SF", "RF"}; for (int i = 0; i < mEval.size(); i++) {
    //   std::cout << names[i] << "\t" << mEval[i] << " " << other.mEval[i] <<
    //   std::endl;
    // }
    for (int i = mEval.size() - 1; i > -1; i--) {
      if (mEval[i] || other.mEval[i]) {
        return mEval[i] > other.mEval[i];
      }
    }
    return false;
  };
};

bool readHands(std::string &s) {
  std::vector<int> vals(10, 0);
  std::vector<char> suits(10, 'S');
  for (int i = 0; i < 10; i++) {
    int pos = i * 3;
    suits[i] = s[pos + 1];
    char vc = s[pos];
    if (vc >= '2' && vc <= '9')
      vals[i] = vc - '0';
    else if (vc == 'T')
      vals[i] = 10;
    else if (vc == 'J')
      vals[i] = 11;
    else if (vc == 'Q')
      vals[i] = 12;
    else if (vc == 'K')
      vals[i] = 13;
    else if (vc == 'A')
      vals[i] = 14;
  }
  Hand h1({vals.begin(), vals.begin() + 5}, {suits.begin(), suits.begin() + 5});
  Hand h2({vals.begin() + 5, vals.end()}, {suits.begin() + 5, suits.end()});
  return h1 > h2;
}

bool testHighest() {
  std::vector<int> v{14, 13, 12, 11, 10};
  std::vector<char> s{'C', 'C', 'C', 'C', 'C'};
  Hand h(v, s);
  if (h.mEval[0] != 14)
    return false;
  return true;
}

bool testPair() {
  std::vector<int> v{14, 14, 12, 11, 10};
  std::vector<char> s{'C', 'S', 'C', 'C', 'C'};
  Hand h1(v, s);
  if (h1.mEval[1] != 14 * Hand::CARD_BASE + 12) {
    std::cout << "T1 -> Expected: " << (14 * Hand::CARD_BASE + 12)
              << " Received: " << h1.mEval[1] << std::endl;
    return false;
  }
  v = {4, 4, 12, 11, 10};
  Hand h2(v, s);
  if (h2.mEval[1] != 4 * Hand::CARD_BASE + 12) {
    std::cout << "T2 -> Expected: " << (4 * Hand::CARD_BASE + 12)
              << " Received: " << h2.mEval[1] << std::endl;
    return false;
  }
  v = {4, 5, 12, 11, 10};
  h2 = Hand(v, s);
  if (h2.mEval[1] != 0) {
    std::cout << "T3 -> Expected: " << 0 << " Received: " << h2.mEval[1]
              << std::endl;
    return false;
  }
  return true;
}

bool testTwoPair() {
  std::vector<std::vector<int>> v{{14, 14, 12, 12, 10},
                                  {12, 12, 8, 8, 9},
                                  {12, 12, 8, 8, 2},
                                  {12, 10, 8, 8, 2},
                                  {12, 10, 9, 8, 2}};

  std::vector<int> expect{
      14 * Hand::CARD_BASE * Hand::CARD_BASE + 12 * Hand::CARD_BASE + 10,
      12 * Hand::CARD_BASE * Hand::CARD_BASE + 8 * Hand::CARD_BASE + 9,
      12 * Hand::CARD_BASE * Hand::CARD_BASE + 8 * Hand::CARD_BASE + 2, 0, 0};

  std::vector<char> s{'C', 'S', 'C', 'S', 'C'};

  for (int i = 0; i < v.size(); i++) {
    Hand h1(v[i], s);
    if (h1.mEval[2] != expect[i]) {
      std::cout << "T" << i + 1 << " -> Expected: " << expect[i]
                << " Received: " << h1.mEval[2] << std::endl;
      return false;
    }
  }
  return true;
}

bool testToK() {
  std::vector<std::vector<int>> v{{14, 14, 14, 13, 13}, {9, 9, 9, 11, 11},
                                  {9, 9, 9, 6, 5},      {6, 4, 6, 3, 2},
                                  {12, 10, 9, 8, 2},    {12, 8, 8, 8, 7}};

  std::vector<int> expect{14 * Hand::CARD_BASE + 13,
                          9 * Hand::CARD_BASE + 11,
                          9 * Hand::CARD_BASE + 6,
                          0,
                          0,
                          8 * Hand::CARD_BASE + 12};

  std::vector<char> s{'C', 'S', 'D', 'H', 'C'};

  for (int i = 0; i < v.size(); i++) {
    Hand h1(v[i], s);
    if (h1.mEval[3] != expect[i]) {
      std::cout << "T" << i + 1 << " -> Expected: " << expect[i]
                << " Received: " << h1.mEval[3] << std::endl;
      return false;
    }
  }
  return true;
}

bool testStraight() {
  std::vector<std::vector<int>> v{{14, 13, 12, 11, 10}, {12, 11, 10, 8, 9},
                                  {9, 8, 7, 6, 5},      {6, 4, 5, 3, 2},
                                  {12, 10, 9, 8, 2},    {12, 3, 4, 8, 7}};

  std::vector<int> expect{14, 12, 9, 6, 0, 0};
  std::vector<char> s{'C', 'S', 'C', 'S', 'C'};

  for (int i = 0; i < v.size(); i++) {
    Hand h1(v[i], s);
    if (h1.mEval[4] != expect[i]) {
      std::cout << "T" << i + 1 << " -> Expected: " << expect[i]
                << " Received: " << h1.mEval[4] << std::endl;
      return false;
    }
  }
  return true;
}

bool testFlush() {
  std::vector<int> v{14, 13, 12, 11, 10};
  std::vector<char> s{'C', 'C', 'C', 'C', 'C'};
  Hand h(v, s);
  if (h.mEval[5] != 14)
    return false;
  return true;
}

bool testFH() {
  std::vector<std::vector<int>> v{{14, 14, 14, 13, 13}, {9, 9, 9, 11, 11},
                                  {9, 9, 9, 6, 5},      {6, 4, 6, 3, 2},
                                  {12, 10, 9, 8, 2},    {12, 8, 8, 8, 7}};

  std::vector<int> expect{
      14 * Hand::CARD_BASE + 13, 9 * Hand::CARD_BASE + 11, 0, 0, 0, 0};
  std::vector<char> s{'C', 'S', 'D', 'H', 'C'};

  for (int i = 0; i < v.size(); i++) {
    Hand h1(v[i], s);
    if (h1.mEval[6] != expect[i]) {
      std::cout << "T" << i + 1 << " -> Expected: " << expect[i]
                << " Received: " << h1.mEval[6] << std::endl;
      return false;
    }
  }
  return true;
}

bool testFoK() {
  std::vector<std::vector<int>> v{{14, 14, 14, 14, 10}, {9, 9, 9, 9, 11},
                                  {9, 8, 7, 6, 5},      {6, 4, 5, 3, 2},
                                  {12, 10, 9, 8, 2},    {12, 3, 4, 8, 7}};

  std::vector<int> expect{
      14 * Hand::CARD_BASE + 10, 9 * Hand::CARD_BASE + 11, 0, 0, 0, 0};
  std::vector<char> s{'C', 'S', 'D', 'H', 'C'};

  for (int i = 0; i < v.size(); i++) {
    Hand h1(v[i], s);
    if (h1.mEval[7] != expect[i]) {
      std::cout << "T" << i + 1 << " -> Expected: " << expect[i]
                << " Received: " << h1.mEval[7] << std::endl;
      return false;
    }
  }
  return true;
}

bool testSF() {
  std::vector<int> v{14, 13, 12, 11, 10};
  std::vector<char> s{'C', 'C', 'C', 'C', 'C'};
  Hand h(v, s);
  if (h.mEval[8] != 14)
    return false;
  return true;
}

bool testRF() {
  std::vector<int> v{14, 13, 12, 11, 10};
  std::vector<char> s{'C', 'C', 'C', 'C', 'C'};
  Hand h(v, s);
  if (!h.mEval[9])
    return false;
  return true;
}

int main() {

  if (!testHighest()) {
    std::cout << "High test failed\n";
    return 1;
  }
  if (!testPair()) {
    std::cout << "Pair test failed\n";
    return 1;
  }
  if (!testTwoPair()) {
    std::cout << "Pair test failed\n";
    return 1;
  }
  if (!testToK()) {
    std::cout << "ToK test failed\n";
    return 1;
  }
  if (!testStraight()) {
    std::cout << "Str8 test failed\n";
    return 1;
  }
  if (!testFlush()) {
    std::cout << "Flush test failed\n";
    return 1;
  }
  if (!testFH()) {
    std::cout << "FH test failed\n";
    return 1;
  }
  if (!testFoK()) {
    std::cout << "FoK test failed\n";
    return 1;
  }
  if (!testSF()) {
    std::cout << "SF test failed\n";
    return 1;
  }
  if (!testRF()) {
    std::cout << "Royal Flush test failed\n";
    return 1;
  }

  auto file = std::fstream("54.txt", std::ios::in);
  std::string s;
  int count = 0;
  while (std::getline(file, s)) {
    bool win = readHands(s);
    std::cout << s << "  -> " << win << std::endl;
    count += win;
  }
  std::cout << count << std::endl;
}
