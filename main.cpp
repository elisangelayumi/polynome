#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "division.hpp"
#include "polynome.hpp"
#include "rationnel.hpp"


bool test_generique_division(const std::string& nom_du_test,
			     const Polynome& dividende,
			     const Polynome& diviseur,
			     std::ostream& out = std::cerr) {
  out << "Execution du test " << nom_du_test << std::endl;
  Polynome quotient;
  Polynome reste;

  out << "  Entree Dividende: " << dividende << std::endl;
  out << "  Entree Diviseur:  " << diviseur << std::endl;
  division(dividende, diviseur, quotient, reste);
  out << "  Sortie Quotient:  " << quotient << std::endl;
  out << "  Sortie Reste:     " << reste << std::endl;
  
  const bool resultat = (quotient * diviseur + reste == dividende) && (reste < diviseur);
  if (resultat) {
    out << "+1 point: Le test a passe" << std::endl;
  } else {
    out << "+0 point: Le test n'a pas passe" << std::endl;
    if (reste >= diviseur) {
      out << "  Le degre du reste est trop grand" << std::endl;
    }
    if (quotient * diviseur + reste != dividende) {
      out << "  L'egalite quotient * diviseur + reste = dividente n'est pas satisfaite" << std::endl;
    }
  }
  out << std::endl;
  return resultat;
}

bool test_generique_plus_grand_commun_diviseur(const std::string& nom_du_test,
					       const Polynome& a,
					       const Polynome& b,
					       std::ostream& out = std::cerr) {
  out << "Execution du test " << nom_du_test << std::endl;
  out << "  m(x) = " << a << std::endl;
  out << "  n(x) = " << b << std::endl;

  const Polynome pgcd = plus_grand_commun_diviseur(a, b);
  out << "  pgcd(m, n) = " << pgcd << std::endl;

  const Polynome polynome_nul;
  if (pgcd == polynome_nul) {
    out << "-0 point: Le plus grand commun diviseur est nul" << std::endl << std::endl;
    return false;
  }

  Polynome quotient_a, quotient_b, reste_a, reste_b;
  division(a, pgcd, quotient_a, reste_a);
  division(b, pgcd, quotient_b, reste_b);
  Polynome pgcd_des_quotients = plus_grand_commun_diviseur(quotient_a, quotient_b);

  bool resultat = true;

  if (reste_a != polynome_nul) {
    out << "  Le polynome " << pgcd << " ne divise pas " << a << std::endl;
    resultat = false;
  }
  if (reste_b != polynome_nul) {
    out << "  Le polynome " << pgcd << " ne divise pas " << b << std::endl;
    resultat = false;
  }
  if (pgcd_des_quotients == polynome_nul) {
    out << "  Le polynome " << pgcd << " n'est pas le plus grand des diviseurs communs" << std::endl;
    resultat = false;
  }

  if (resultat) {
    out << "+1 point: Le test a passe." << std::endl;
  } else {
    out << "+0 point: Le test a echoue." << std::endl;
  }

  out << std::endl;
  
  return resultat;
}

// (x^3 + 2x + 1) / (x + 1) = x^2 - x + 3 reste -2
bool test_instance_vue_en_classe() {
  Rationnel coefficients_dividence[4] = {Rationnel(1), Rationnel(2), Rationnel(0), Rationnel(1)};
  Polynome dividende(std::vector<Rationnel>(coefficients_dividence, coefficients_dividence + 4)); // x^3 + 2x + 1
  Polynome quotient(std::vector<Rationnel>(2, Rationnel(1))); // x + 1
  return test_generique_division("Instance vue en classe", dividende, quotient);
}

// (x^4 - 81) / (x^2 - 9)
bool test_avec_reste_nul() {
  Rationnel coefficients_dividende[5] = {Rationnel(-81), Rationnel(0), Rationnel(0), Rationnel(0), Rationnel(1)};
  Rationnel coefficients_quotient[3] = {Rationnel(-9), Rationnel(0), Rationnel(1)};
  Polynome dividende(std::vector<Rationnel>(coefficients_dividende, coefficients_dividende + 5)); // x^4 - 81
  Polynome quotient(std::vector<Rationnel>(coefficients_quotient, coefficients_quotient + 3)); // x^2 - 9
  return test_generique_division("Division avec reste nul", dividende, quotient);
}

// (x^2 + 1) / 2 
bool test_division_par_un_entier() {
  Rationnel coefficients_dividende[3] = {Rationnel(1), Rationnel(0), Rationnel(1)};
  Polynome dividende(std::vector<Rationnel>(coefficients_dividende, coefficients_dividende + 3)); // x^2 + 1
  Polynome quotient(Rationnel(-2), 0); // -2
  return test_generique_division("Division par un entier", dividende, quotient);
}

bool test_plus_grand_commun_diviseur1() {
  Polynome un(std::vector<Rationnel>(1, Rationnel(1)));
  Rationnel coefficients_a[3] = {Rationnel(1), Rationnel(2), Rationnel(1)}; // x^2 + 2x + 1 = (x + 1)^2
  Rationnel coefficients_b[3] = {Rationnel(-1), Rationnel(0), Rationnel(1)}; // x^2 - 1 = (x + 1)(x - 1)
  Polynome a(std::vector<Rationnel>(coefficients_a, coefficients_a + 3));
  Polynome b(std::vector<Rationnel>(coefficients_b, coefficients_b + 3));
  return test_generique_plus_grand_commun_diviseur("plus_grand_commun_diviseur1", a, b);
}

bool test_plus_grand_commun_diviseur2() {
  Polynome un(std::vector<Rationnel>(1, Rationnel(1)));
  Rationnel coefficients_a[4] = {Rationnel(2), Rationnel(3), Rationnel(1), Rationnel(5)};
  Rationnel coefficients_b[4] = {Rationnel(1), Rationnel(5), Rationnel(0), Rationnel(2)};
  Polynome a(std::vector<Rationnel>(coefficients_a, coefficients_a + 4));
  Polynome b(std::vector<Rationnel>(coefficients_b, coefficients_b + 4));
  return test_generique_plus_grand_commun_diviseur("plus_grand_commun_diviseur2", (a + un) * b, a * b);
}

bool test_statistique(unsigned int degre,
		      unsigned int nb_instances,
		      unsigned int germe,
		      bool (*fonction_test)(const std::string&, const Polynome&, const Polynome&, std::ostream&)) {
  assert(nb_instances > 0);
  assert(0 < degre && degre < 10); // Avec des polynomes randomises de
				   // degre 10 et plus, on peut
				   // s'attendre a des debordements.
  std::cerr << "Execution de " << nb_instances << " instances de division" << std::endl;

  std::srand(germe);
  std::ofstream null_stream;
  
  std::vector<Rationnel> dividende(degre + 1);
  std::vector<Rationnel> diviseur((degre + 1) / 2);
  unsigned int score = 0;

  for (unsigned instance_num = 0; instance_num < nb_instances; instance_num++) {
    for (std::vector<Rationnel>::iterator i = dividende.begin(); i != dividende.end(); i++) {
      *i = Rationnel(std::rand() % 3);
    }
    dividende.back() = Rationnel(1 + std::rand() % 2);
    for (std::vector<Rationnel>::iterator i = diviseur.begin(); i != diviseur.end(); i++) {
      *i = Rationnel(1 + std::rand() % 3);
    }
    diviseur.back() = Rationnel(1 + std::rand() % 2);

    char tampon[100];
    snprintf(tampon, sizeof(tampon), "Test statistiques #%d", instance_num);
    if ((*fonction_test)(tampon, dividende, diviseur, null_stream)) {
      score++;
    }
  }
  std::cerr << "+" << score * 5.0 / nb_instances << " points (" << score << " instances sur " << nb_instances << ")" << std::endl;
  return true;
}

int main(void) {
    test_instance_vue_en_classe();
    test_avec_reste_nul();
    test_division_par_un_entier();
    test_plus_grand_commun_diviseur1();
    test_plus_grand_commun_diviseur2();

    // Un autre germe sera utilise lors de la correction
    // Aucun polynome de degre superieur a 7 ne sera teste, car il y a un risque de depassement d'entier.
    test_statistique(7, 1000, 123, test_generique_division);
    // Un autre germe sera utilise lors de la correction
    // Aucun polynome de degre superieur a 4 ne sera teste, car il y a un risque de depassement d'entier.
    test_statistique(4, 1000, 321, test_generique_plus_grand_commun_diviseur);




    return 0;
}