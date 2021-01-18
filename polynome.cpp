// NE PAS MODIFIER CE FICHIER

#include "polynome.hpp"

#include <assert.h>
#include <algorithm>
#include <math.h>

Polynome::Polynome()
  : m_coefficients(1, Rationnel(0))
{
  simplifier();
}

// Cree un polynome ou le coefficient de x^i est coefficients[i]
//
// Complexite: Theta(n) ou la taille du vecteur coefficients
Polynome::Polynome(const std::vector<Rationnel>& coefficients)
  : m_coefficients(coefficients)
{
  simplifier();
}

// Cree le monome: coefficient * x^degre
//
// Complexite: Theta(d) ou d est le degre du polynome
Polynome::Polynome(const Rationnel& coefficient, unsigned int degre)
  : m_coefficients(degre + 1)
{
  m_coefficients[degre] = coefficient;
  simplifier();
}

// Constructeur de copie
//
// Complexite: Theta(d) ou d est le degre du polynome
Polynome::Polynome(const Polynome& polynome)
  : m_coefficients(polynome.m_coefficients)
{
}

void Polynome::simplifier() {
  unsigned int i = m_coefficients.size();
  while (i > 0 && m_coefficients[i - 1].numerateur() == 0) {
    i--;
  }
  m_coefficients.resize(i);
  assert(m_coefficients.empty() || m_coefficients.back().numerateur() != 0);
}

// Complexite: Theta(1)
int Polynome::degre() const {
  return m_coefficients.size() - 1;
}

// Retourne le coefficient du monome x^degre.
//
// Complexite: Theta(1)
const Rationnel Polynome::coefficient(unsigned int degre) const {
  if (degre >= m_coefficients.size())
    return Rationnel(0);
  return m_coefficients.at(degre);
}

// Retourne le produit du polynome avec le monome coefficient_monome * x^degre_monome
//
// Complexite: Theta(n) ou n est le degre du degre du polynome retourne
Polynome Polynome::multiplication_par_monome(const Rationnel& coefficient_monome, unsigned int degre_monome) const {
  std::vector<Rationnel> coefficients_produit(m_coefficients.size() + degre_monome, Rationnel(0));
  for (unsigned int i = 0; i < m_coefficients.size(); i++) {
    coefficients_produit[i + degre_monome] = m_coefficients[i] * coefficient_monome;
  }
  return Polynome(coefficients_produit);
}

// Interchange le contenue du polynome avec p
//
// Complexite: Theta(1)
void Polynome::swap(Polynome& p) {
  m_coefficients.swap(p.m_coefficients);
}

// Compare les degres des polynomes. Attention, le polynome p(x) = 0 a
// un degre de -1. Ceci n'est certainement pas vrai d'un point de vu
// mathematique, mais ca simplifie bien des choses du cote algorithmique.
// 
// Complexite:
//   Pire cas:     Theta(1)
bool operator<(const Polynome& a, const Polynome& b) {
  return a.degre() < b.degre();
}

// Complexite:
//    Pire cas: Theta(d) ou d est le degre des polynomes
//    Meilleur cas: Theta(1)   (si les polynomes n'ont pas le meme degre)
bool operator==(const Polynome& a, const Polynome& b) {
  return a.m_coefficients == b.m_coefficients;
}

// Complexite: Theta(degre_a + degre_b) ou degre_a et degre_b sont les degres des polynomes a et b
Polynome operator+(const Polynome& a, const Polynome& b) {
  std::vector<Rationnel> coefficients(std::max(a.degre(), b.degre()) + 1);
  for (unsigned int i = 0; i < coefficients.size(); i++) {
    coefficients[i] = a.coefficient(i) + b.coefficient(i);
  }
  return Polynome(coefficients);
}

// Complexite: Theta(degre_a + degre_b) ou degre_a et degre_b sont les degres des polynomes a et b
Polynome operator-(const Polynome& a, const Polynome& b) {
  std::vector<Rationnel> coefficients(std::max(a.degre(), b.degre()) + 1);
  for (unsigned int i = 0; i < coefficients.size(); i++) {
    coefficients[i] = a.coefficient(i) - b.coefficient(i);
  }
  return Polynome(coefficients);
}

// Complexite: Theta(d^2) ou d est le plus grand degre entre les polynomes a et b
Polynome operator*(const Polynome& a, const Polynome& b) {
  std::vector<Rationnel> coefficients(a.degre() + b.degre() + 1, Rationnel(0));
  for (unsigned int i = 0; i < coefficients.size(); i++) {
    for (unsigned int j = 0; j <= i; j++) {
      coefficients[i] = coefficients[i] + a.coefficient(j) * b.coefficient(i - j);
    }
  }
  return Polynome(coefficients);
}

// Complexite: O(d) ou d est le degre du polynome
std::ostream& operator<<(std::ostream& os, const Polynome& a) {
  if (a.degre() < 0) {
    return os << "0";
  }

  Rationnel un(1, 1);

  if (a.coefficient(a.degre()) != un || a.degre() == 0) {
    os << a.coefficient(a.degre());
  }
  
  if (a.degre() > 0) {
    os << "x";
    if (a.degre() > 1) {
      os << "^" << a.degre();
    }
  }
  
  for (int i = a.degre() - 1; i >= 0; i--) {
    if (a.coefficient(i).numerateur() != 0) {
      os << " + ";
      if (a.coefficient(i) != un || i == 0) {
	os << a.coefficient(i);
      }
      if (i > 0) {
	os << "x";
	if (i > 1) {
	  os << "^" << i;
	}
      }
    }
  }
  return os;
}
