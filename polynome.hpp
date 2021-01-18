// NE PAS MODIFIER CE FICHIER

#ifndef POLYNOME
#define POLYNOME

#include <vector>
#include "rationnel.hpp"

class Polynome {
private:
  std::vector<Rationnel> m_coefficients;

  void simplifier();
public:
  Polynome();			// Cree le polynome p(x) = 0
  Polynome(const std::vector<Rationnel>& coefficients); // Cree un polynome ou le coefficient de x^i est coefficients[i]
  Polynome(const Rationnel& coefficient, unsigned int degre); // Cree le monome: coefficient * x^degre
  Polynome(const Polynome& polynome); // Constructeur de copie

  int degre() const;
  const Rationnel coefficient(unsigned int degre) const;

  // Retourne le produit du polynome avec le monome coefficient_monome * x^degre_monome
  Polynome multiplication_par_monome(const Rationnel& coefficent, unsigned int degre) const;

  void swap(Polynome& p); 	// Interchange le contenue du polynome avec celui de p

  friend bool operator<(const Polynome& a, const Polynome& b);
  friend bool operator==(const Polynome& a, const Polynome& b);
};

// Operateurs de comparaison de polynomes
inline bool operator> (const Polynome& a, const Polynome& b){ return b < a; }
inline bool operator<=(const Polynome& a, const Polynome& b){ return !(a > b); }
inline bool operator>=(const Polynome& a, const Polynome& b){ return !(a < b); }  
inline bool operator!=(const Polynome& a, const Polynome& b){ return !(a == b); }

// Operateurs arithmetique de polynomes
Polynome operator+(const Polynome& a, const Polynome& b);
Polynome operator-(const Polynome& a, const Polynome& b);
Polynome operator*(const Polynome& a, const Polynome& b);

std::ostream& operator<<(std::ostream& os, const Polynome& a);

#endif
