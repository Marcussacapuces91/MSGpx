/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

/**
 * \file Fichier principal.
 */
#include <iostream>
#include "gpx.h"

using namespace std;

/// Constante du texte de la licence.
static const string LICENCE = "\
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE             \n\
                    Version 2, December 2004                        \n\
                                                                    \n\
 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>                   \n\
                                                                    \n\
 Everyone is permitted to copy and distribute verbatim or modified  \n\
 copies of this license document, and changing it is allowed as long\n\
 as the name is changed.                                            \n\
                                                                    \n\
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE             \n\
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION  \n\
                                                                    \n\
  0. You just DO WHAT THE FUCK YOU WANT TO.                         \n\
                                                                    \n\
This program is free software. It comes without any warranty, to    \n\
the extent permitted by applicable law.                             ";

static const string HELP = "\
MSGpx calcule les d‚nivel‚s des traces GPX                          \n\
Copyright (c) 2010 par Marc Sibert.                                 \n\
                                                                    \n\
Utilisation                                                         \n\
  MSGpx [nom du fichier gpx]                                        \n\
  ou                                                                \n\
  MSGpx --licence                                                   \n\
                                                                    \n\
Licence                                                             \n\
  Ce programme est distribu‚ sous licence WTFPL. Le code source est \n\
  disponible sur simple demande.                                    \n\
  Il inclut le code de TinyXML, qui lui, est sous licence zlib.";

/**
 * Fonction principale chargée de lancer l'application.
 * \param argc Nombre d'arguments (incluant le nom de la commande elle-même.
 * \param argv Un tableau de chaîne contenant chaque argument.
 * \return Un entier EXIT_SUCCESS ou EXIT_FAILURE pour indiquer la bonne
 *         exécussion du programme, ou pas !
 */
int main(int argc, const char* argv[])
{
    if (argc != 2) {
        cout << HELP << endl;
        return EXIT_FAILURE;
    }
    else if (string(argv[1]) == "--licence") {
        cout << LICENCE << endl;
        return EXIT_SUCCESS;
    }
    else {
        try {
            cout << "Analyse du fichier " << argv[1] << endl;
            Gpx gpx(argv[1]);
            cout << "D‚nivel‚s" << endl;
            cout << "  Positif (mont‚e) : " << gpx.getDenivelePositif() << "m" << endl;
            cout << "  N‚gatif (descente) : " << gpx.getDeniveleNegatif() << "m" << endl;
            return EXIT_SUCCESS;
        } catch (exception& e) {
            cerr << e.what() << endl;
            return EXIT_FAILURE;
        } catch (string& e) {
            cerr << e << endl;
            return EXIT_FAILURE;
        } catch (char* e) {
            cerr << e << endl;
            return EXIT_FAILURE;
        } catch (...) {
            cerr << "exception inconnue" << endl;
            return EXIT_FAILURE;
        }
    }
}
