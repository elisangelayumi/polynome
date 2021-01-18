
#include "division.hpp"

#include <assert.h>

void division(const Polynome& dividende, // Le polynome qui est divise
	      const Polynome& diviseur,  // Le polynome qui divise
	      Polynome& quotient,	   // Parametre de sortie: le resultat de la division
	      Polynome& reste) {	   // Parametre de sortie: le reste de la division
  assert(diviseur.degre() > 0 || diviseur.coefficient(0).numerateur() != 0); // Pas de division par zero

  // INSEREZ VOTRE CODE ICI

  Polynome monDividende(dividende);
  int degreeMonDividende = monDividende.degre();
  int degreeDiviseur = diviseur.degre();

  while (degreeMonDividende >= degreeDiviseur) {

      Polynome quotientIntermediaire(monDividende.coefficient(degreeMonDividende) / diviseur.coefficient(degreeDiviseur),degreeMonDividende-degreeDiviseur);

      quotient = quotient + quotientIntermediaire;

      Polynome resultatMultiplication = diviseur.multiplication_par_monome(quotientIntermediaire.coefficient(quotientIntermediaire.degre()) * -1,quotientIntermediaire.degre());

      monDividende = monDividende + resultatMultiplication;
      degreeMonDividende = monDividende.degre();
  }
    reste = monDividende;
}

Polynome plus_grand_commun_diviseur(const Polynome& a, const Polynome& b) {
  assert(a >= b);
  assert(a.degre() > 0 || a.coefficient(0).numerateur() != 0);

  // INSEREZ VOTRE CODE ICI

    Polynome monPolyA = a;
    Polynome monPolyB = b;

    while (monPolyB.degre() >= 0){
        Polynome quotient = Polynome();
        Polynome rest = Polynome();

        division(monPolyA, monPolyB, quotient,rest);

        monPolyA.swap(monPolyB);
        monPolyB.swap(rest);
    }

  return monPolyA;
}
