// NE PAS MODIFIER CE FICHIER

#ifndef RATIONNEL
#define RATIONNEL

#include <iostream>

class Rationnel {
private:
  int m_numerateur;
  int m_denominateur;
  static int plus_grand_commun_diviseur(int a, int b);
  void simplifier();
public:
  Rationnel(int numerateur = 0, int denominateur = 1);
  Rationnel(const Rationnel& copie);

  double reel() const;
  int numerateur() const;
  int denominateur() const;

  friend bool operator<(const Rationnel& a, const Rationnel& b);
  friend bool operator==(const Rationnel& a, const Rationnel& b);
};

// Operateurs de comparaison de rationnels
inline bool operator> (const Rationnel& a, const Rationnel& b){ return b < a; }
inline bool operator<=(const Rationnel& a, const Rationnel& b){ return !(a > b); }
inline bool operator>=(const Rationnel& a, const Rationnel& b){ return !(a < b); }  
inline bool operator!=(const Rationnel& a, const Rationnel& b){ return !(a == b); }

// Operateurs arithmetique de rationnels
Rationnel operator+(const Rationnel& a, const Rationnel& b);
Rationnel operator-(const Rationnel& a, const Rationnel& b);
Rationnel operator*(const Rationnel& a, const Rationnel& b);
Rationnel operator/(const Rationnel& a, const Rationnel& b);

std::ostream& operator<<(std::ostream& os, const Rationnel& a);

#endif
