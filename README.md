# Commandes par moniteur serie

## lst

Liste toutes les télécommandes disponnibles.

## lrc

Liste les rolling code pour chaque télécommandes.

## teln

Séléctionner une télécommande ou "n" correspond à un numéro cf ```lst```.

## act

Commande action prenant les parammétres suivants :

1. m : Monter
2. d : Descendre
3. s : My (stop)
4. p : Programmer
5. q : Déprogrammer (Remet le rolling code à 0)


# Codes RF

## Utilisation

Les 3 premiers caractéres doivent êtres égales à 200.
Le 4éme caractére représente la télécommande de 1 à 9.
Le 5éme caractére représente l'action de 1 à 5 :

1. Monter
2. Descendre
3. My (stop)
4. Programmer
5. Déprogrammer (Remet le rolling code à 0)

## Exemples

Monter sur avec la télécommande 1 : ```20011```

Descendre avec le télécommande 6 : ```20062```

Programmer la télécommande 8 : ```20084```


# Dépendences

## MySomfy

[https://github.com/PeekLeon/Somfy-Library](https://github.com/PeekLeon/Somfy-Library)

## RCSwitch

[https://github.com/sui77/rc-switch](https://github.com/sui77/rc-switch)

## EEPROM

Inclus dans l'ide arduino.


