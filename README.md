IRC_Chatbot
===========

Pour compiler : à la racine, utilisez la commande make clean && make
Pour lancer : à la racine, utilisez la commande ./bin/networkizedChatbot




Lain est un bot IRC parlant anglais, et répondant à de multiples noms : Lain, Lainbot, Toaster, Marvin, bot, IRCbot...

Lors du démarrage, il vous sera demandé de spécifier une adresse, un port et un channel.
Si vous désirez fournir une adresse IP, spécifiez i lors du premier prompt.
Si vous désirez vous connecter en utilisant un nom de domaine, précisez h.

Vous sera ensuite demandé le port, puis l'adresse, et enfin le channel concerné.


Dans le cas où vous ne connaissez aucun serveur IRC, celui-ci est mis à votre disposition :
home.inner-universe.fr
Port 6667
Channel #test

Pour interagir avec le drone, un client IRC sera nécessaire. https://kiwiirc.com/client est un client gratuit et sans abonnement qui vous permettra de vous connecter au serveur, une fois ses coordonnées spécifiées.


Expressions :
Répond aux salutations.
                    Exemples d'input : 
                    Hello, Lain!
                    Lain, hi.
                    Plop, bot.
                    
Répond aux insultes.
                    Exemples d'input: 
                    You're a total wanker.
                    What the fuck are you doing?
                    And there's this little brat.



Fonctions :
Donne l'heure.
                    Exemples d'input:
                    Lain, what time is it?
                    Bot, I want the current time now.


Enregistrer la conversation dans un fichier unique appelé Lain-conversation-dump (situé dans le répertoire bin) qui contient, séparé par des timestamp, la totalité des flux bruts capturés par le bot (messages des canaux, mais également messages du serveur et réponses du bot.)
                    Exemples d'input:
                    Lain, start monitoring the conversation now.
                    Bot, could you dump the conversation?


                    Pour arrêter l'enregistrement :
                    Lain, stop monitoring.
                    Bot, terminate saving.


Le bot peut également se déconnecter et terminer son exécution à la demande (le 
                    Exemples :
                    Lain, leave us now.
                    Bot, could you disconnect?



Fonctionnalités supplémentaires : 
-Fonctions réseau (connexion à un IRC)
-Implémentation de protocole réseau (réponses automatiques aux PINGs, construction des headers de message channel)
-Enregistrement dans un fichier


État d'avancement :
Bien que disposant de certaines fonctionnalités assez avancées, nous ne pouvons considérer le bot comme final, voire même avancé. L'objectif principal étant d'utilise lex & yacc pour lui permettre de lui adresser des commandes sous de nombreuses formes différentes n'a pas été totalement rejoint, et la communication avec Lain reste encore maladroite. Certaines phrases qui serait comprises sans ambiguités par un être humain ne le sont pas par le parser.
Nous aimerions continuer à développer le bot au-delà du simple projet étudiant, en lui rajoutant peu à peu des fonctions supplémentaires, comme des commandes ou des expressions enrichies.

A l'heure actuelle, fonctionnent parfaitement la connexion/déconnexion à un serveur arbitraire donné, le parsing sans erreurs des conversations, l'enregistrement des conversations, le maintien de connexion au serveur, la récupération et l'affichage du temps, la détection des insultes et la détection des salutations.
