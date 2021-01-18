// NE PAS MODIFIER CE FICHIER

#ifndef DIVISION
#define DIVISION

#include "polynome.hpp"
void division(const Polynome& dividende, // Le polynome qui est divise
	      const Polynome& diviseur,  // Le polynome qui divise
	      Polynome& quotient,	   // Parametre de sortie: le resultat de la division
	      Polynome& reste);	   // Parametre de sortie: le reste de la division

Polynome plus_grand_commun_diviseur(const Polynome& a, const Polynome& b);

#endif
