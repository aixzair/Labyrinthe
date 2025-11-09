---
title: "Manuel du Joueur"
author: "Alexandre Lerosier"
date: "9 novembre 2025"
geometry: margin=2.5cm
fontsize: 12pt
---

\newpage

# Fonctionnalités

1. [Créer un labyrinthe](#créer-un-labyrinthe)  
2. [Charger un labyrinthe](#charger-un-labyrinthe)  
3. [Jouer](#jouer)  
4. [Classement](#classement)  
5. [Quitter](#quitter)  

\newpage

# 1. Créer un labyrinthe

Permet de générer un nouveau labyrinthe.  
Il faut renseigner la hauteur et la largeur, toutes deux comprises dans l’intervalle [5 ; 99] et impaires.
Il faut aussi indiquer un nom du labyrinthe et choisir si on ajoute des monstres.

# 2. Charger un labyrinthe

Permet de charger un labyrinthe parmi ceux créés précédemment.

# 3. Jouer

**Nécessite :** avoir chargé un labyrinthe.  
Permet de jouer dans le labyrinthe chargé.

## But du jeu

Vous commencez en haut à gauche et devez vous rendre en bas à droite en récupérant la clé pour déverrouiller la porte.
**Attention :** les monstres, les pièges ainsi que vos déplacements vous feront perdre des points, tandis que les pièces vous en rapporteront.

## Déplacements

- Haut : 'z'
- Bas : 's'
- Gauche : 'q'
- Droite : 'd'

## Définition des cases

- o : joueur  
- \# : mur  
- D : porte  
- k : clé  
- $ : pièce  
- ^ : piège  
- G : ogre  
- S : spectre

## Les monstres

Les monstres rôdent dans le labyrinthe. Si vous les touchez, vous perdez des points et le monstre touché disparaît.  
**Attention :** la difficulté augmente chaque fois que vous touchez un monstre.

### Les ogres

Ils restent à proximité de la pièce à laquelle ils ont été assignés.  
La taille de leur zone de déplacement est proportionnelle à la difficulté.

### Les spectres

Les spectres peuvent traverser les murs.  
La distance de leurs déplacements est proportionnelle à la difficulté.

# 4. Classement

**Nécessite :** avoir chargé un labyrinthe.  
Permet de consulter les 10 meilleurs scores du labyrinthe chargé.

# 5. Quitter

Permet de fermer l’application.
