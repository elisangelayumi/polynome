// NE PAS MODIFIER CE FICHIER

// Prenez note que la somme de deux grands entiers positifs peut
// donner une entier negatif. C'est ce que l'on appelle un
// depassement d'entier.
// https://fr.wikipedia.org/wiki/D%C3%A9passement_d%27entier
   
#include "rationnel.hpp"

#include <assert.h>
#include <cstdlib>
#include <math.h>

// Complexite: Theta(1
Rationnel::Rationnel(int numerateur, int denominateur)
  : m_numerateur(numerateur),
    m_denominateur(denominateur)
{
  assert(denominateur != 0);
  simplifier();
}

// Complexite: Theta(1)
Rationnel::Rationnel(const Rationnel& copie)
  : m_numerateur(copie.m_numerateur),
    m_denominateur(copie.m_denominateur)
{
}


// Complexite: Theta(1)

// Note: C'est bien lineaire dans le nombre de bits pour encoder a,
// mais ce nombre de bits est borne par la constante 8 * sizeof(int).
// Le temps d'execution est donc borne par une constante. Ce ne serait
// pas le cas si nous permettions des entiers de taille arbitraire
// (comme c'est le cas en cryptographie).
int Rationnel::plus_grand_commun_diviseur(int a, int b) {
  assert(a >= 0 && b >= 0 && (a > 0 || b > 0)); // Voir la note sur les depassements d'entier en haut du fichier
  while (b > 0) {
    int reste = a % b;
    a = b;
    b = reste;
  }
  assert(a > 0);
  return a;
}

// Complexite: Theta(1)
void Rationnel::simplifier() {
  if (m_denominateur < 0) {
    m_numerateur = -m_numerateur;
    m_denominateur = -m_denominateur;
  }

  const int pgcd = plus_grand_commun_diviseur(std::abs(m_numerateur), m_denominateur);
  m_numerateur /= pgcd;
  m_denominateur /= pgcd;
  assert(m_denominateur > 0); // Voir la note sur les depassements d'entier en haut du fichier
  assert(m_numerateur != 0 || m_denominateur == 1);
}

// Complexite: Theta(1)
double Rationnel::reel() const {
  return (double)m_numerateur / m_denominateur;
}

// Complexite: Theta(1)
int Rationnel::numerateur() const {
  return m_numerateur;
}

// Complexite: Theta(1)
int Rationnel::denominateur() const {
  return m_denominateur;
}

// Complexite: Theta(1)
bool operator<(const Rationnel& a, const Rationnel& b) {
  return a.reel() < b.reel();
}

// Complexite: Theta(1)
bool operator==(const Rationnel& a, const Rationnel& b) {
  return (a.numerateur() == b.numerateur()) && (a.denominateur() == b.denominateur());
}

// Complexite: Theta(1)
Rationnel operator+(const Rationnel& a, const Rationnel& b) {
  return Rationnel(a.numerateur() * b.denominateur() + b.numerateur() * a.denominateur(), // Numerateur
		   a.denominateur() * b.denominateur()); // Denominateur
}

// Complexite: Theta(1)
Rationnel operator-(const Rationnel& a, const Rationnel& b) {
  return Rationnel(a.numerateur() * b.denominateur() - b.numerateur() * a.denominateur(), // Numerateur
		   a.denominateur() * b.denominateur()); // Denominateur
}

// Complexite: Theta(1)
Rationnel operator*(const Rationnel& a, const Rationnel& b) {
  return Rationnel(a.numerateur() * b.numerateur(), // Numerateur
		   a.denominateur() * b.denominateur()); // Denominateur
}

// Complexite: Theta(1)
Rationnel operator/(const Rationnel& a, const Rationnel& b) {
  assert(b.numerateur() != 0);
  return Rationnel(a.numerateur() * b.denominateur(), // Numerateur
		   a.denominateur() * b.numerateur()); // Denominateur
}

// Complexite: Theta(1)
std::ostream& operator<<(std::ostream& os, const Rationnel& a) {
  if (a.denominateur() == 1) {
    if (a.numerateur() >= 0)
      return os << a.numerateur();
    else
      return os << "(" << a.numerateur() << ")";
  }
  return os << "(" << a.numerateur() << "/" << a.denominateur() << ")";
}
