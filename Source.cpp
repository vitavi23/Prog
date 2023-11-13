#include <iostream>
#include <cstdlib> // Pour system("cls")

const int SIZE = 3;

// Fonction pour afficher la grille
void afficherGrille(char grille[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << grille[i][j];
            if (j < SIZE - 1) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i < SIZE - 1) {
            for (int k = 0; k < SIZE * 4 - 1; ++k) {
                std::cout << "-";
            }
            std::cout << std::endl;
        }
    }
}

// Fonction pour vérifier s'il y a une victoire
bool verifierVictoire(char grille[SIZE][SIZE], char symbole) {
    // Vérification horizontale et verticale
    for (int i = 0; i < SIZE; ++i) {
        if ((grille[i][0] == symbole && grille[i][1] == symbole && grille[i][2] == symbole) ||
            (grille[0][i] == symbole && grille[1][i] == symbole && grille[2][i] == symbole)) {
            return true;
        }
    }

    // Vérification diagonale
    if ((grille[0][0] == symbole && grille[1][1] == symbole && grille[2][2] == symbole) ||
        (grille[0][2] == symbole && grille[1][1] == symbole && grille[2][0] == symbole)) {
        return true;
    }

    return false;
}

// Fonction pour vérifier l'égalité
bool verifierEgalite(char grille[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grille[i][j] == ' ') {
                return false; // Il y a encore des cases vides, le jeu n'est pas égal
            }
        }
    }
    return true; // Toutes les cases sont remplies, c'est une égalité
}

int main() {
    char grille[SIZE][SIZE];
    char joueur = 'X'; // Le joueur 1 commence avec X

    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;

    bool rejouer = true;

    while (rejouer) {
        // Initialisation de la grille
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                grille[i][j] = ' ';
            }
        }

        bool jeuEnCours = true;

        while (jeuEnCours) {
            system("cls"); // Efface l'écran (compatible avec Windows, utilisez "clear" pour Linux)

            // Affichage de la grille
            afficherGrille(grille);

            // Demande au joueur de choisir une case
            int mouvement;
            std::cout << "Joueur " << joueur << ", entrez le numéro de la case (1-9) : ";
            std::cin >> mouvement;

            // Vérification de la validité du mouvement
            if (mouvement < 1 || mouvement > SIZE * SIZE || grille[(mouvement - 1) / SIZE][(mouvement - 1) % SIZE] != ' ') {
                std::cout << "Mouvement invalide. Veuillez choisir une autre case." << std::endl;
                continue; // Redemander au même joueur de choisir une case
            }

            // Met le symbole du joueur dans la case choisie
            grille[(mouvement - 1) / SIZE][(mouvement - 1) % SIZE] = joueur;

            // Vérification de la victoire
            if (verifierVictoire(grille, joueur)) {
                system("cls");
                afficherGrille(grille);
                std::cout << "Le joueur " << joueur << " a gagné !" << std::endl;
                if (joueur == 'X') {
                    ++scoreJoueur1;
                }
                else {
                    ++scoreJoueur2;
                }
                jeuEnCours = false;
            }
            else if (verifierEgalite(grille)) {
                system("cls");
                afficherGrille(grille);
                std::cout << "Égalité !" << std::endl;
                jeuEnCours = false;
            }
            else {
                joueur = (joueur == 'X') ? 'O' : 'X'; // Changer de joueur à chaque tour
            }
        }

        // Affichage du score
        std::cout << "Score - Joueur X : " << scoreJoueur1 << " | Joueur O : " << scoreJoueur2 << std::endl;

        // Inverser l'ordre des joueurs pour la prochaine partie
        joueur = (joueur == 'X') ? 'O' : 'X';

        // Demande aux joueurs s'ils veulent rejouer
        char choixRejouer;
        std::cout << "Voulez-vous rejouer ? (O/N) : ";
        std::cin >> choixRejouer;
        rejouer = (choixRejouer == 'O' || choixRejouer == 'o');
    }

    std::cout << "Merci d'avoir joué au Tic Tac Toe !" << std::endl;

    return 0;
}
