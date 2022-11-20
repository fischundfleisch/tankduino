# tankduino

Dies hier ist ein Lehrgang um einen autonom fahrenden Minipanzer zu erstellen. 

Ihr benötigt dafür: einen 3d-Drucker und folgende Teile: 
Im beiliegenden Ordner "3dprint" druckt ihr zuerst den TrackInnerFrame 2mal, den TrackOuterFrame 2x (haben zusammen in einem Print Platz)
Dann je einmal TopFrame und baseFrame
6mal Cog
und 31x2 Tracks (gerne auch als Ersatzteil ein oder zwei mehr)

Um die Tracks miteinander zu verbinden, steckt einfach ein Stück Filament hinein.

Zusätzlich ist es gut wenn ihr einen Halter für den Uno und einen für den L298N druckt. Außerdem noch zwei für den Ultraschall HC SR04.

Dann braucht ihr einen Arduino Uno, einen L298N Treiber, M3x30 Gewindeschrauben und Muttern, M4x40 Gewindeschrauben, Muttern und Distanzhülsen,
eine 9V Batterie mit Stecker für die Motoren, eine 4x1,5V Batteriehalterung für den Uno und 4 Getriebemotoren.

Baut erst mal grob nach folgender Anleitung auf: https://www.thingiverse.com/thing:972768

An der Vorderseite bringt ihr zwei HC SR04 an inklusive den passenden Abdeckungen.
Nun verkabelt ihr alles folgendermaßen: 

Je zwei linke und zwei rechte Motoren werden parallel an die Eingänge des L298N angeschlossen. Die 9V Batterie kommt an den Eingang, ein Jumper auf den
5V-EN-Chip, ein zusätzlicher Common Ground an den Arduino (gemeinsame Masse für Signalübertragung).

Dann kommen die Signalpins: ENA auf Arduino Pin 5 (muss ein PWM-Pin sein, wenn wir die Geschwindigkeit regeln wollen)
IN1 auf Pin 7, IN2 auf Pin 8, ENB auf Pin 6 (wieder PWM-Pin), IN3 auf Pin 9, IN4 auf Pin10

Nun versucht mal ohne Ultraschall folgendes: Schreibt einen Arduino Code, der einfach alle Richtungen durchgehend ansteuert. 
Um einen Motor zu bewegen, müsst ihr den Enable-Pin High schalten und dann einen der dazugehörigen IN-Pins High, den anderen Low.

Das könnte so aussehen: 
int ENA = 5;
int IN1 = 7;
int IN2 = 8;

void loop () {
digitalWrite(ENA, HIGH);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);

delay(2000);
}

Macht mal so alle Bewegungen durch: Links vorwärts, links rückwärts, rechts vorwärts, rechts rückwärts, beide gemeinsam Vor und zurück.

Bonuspunkte: Schreibt dafür jeweils eine eigene Funktion, die ihr in der Loop aufruft!

[Beispielcode dafür siehe Folder ;) ]

Nun haben wir zu Beginn gesagt, die EN-Pins sollen PWM-Pins sein. Versucht doch mal, das "digitalWrite(ENA, HIGH)" zu ersetzen durch:

analogWrite(ENA, 150);

Was passiert? Der PWM-Pin kann die Geschwindigkeit zwischen 0 (Minimum) und 255 (Maximum) regulieren. Achtung: bei 255 läuft er über, 
256 entspricht also 0, weil er wieder von vorne anfängt. 265 entspricht dann 10. 

In meinem Beispielcode übergebe ich aus der Loop an die Funktionen die Geschwindigkeit als Parameter. Das spart mir zusätzliche globale
Variablen, damit Speicherplatz und bringt mir mehr Flexibilität. Probiert das ruhig auch aus, das werdet ihr noch oft brauchen.



UND NUN MIT ULTRASCHALL!!

Spätestens jetzt solltet ihr zwei Ultraschallsensoren mit dem Arduino verbinden. Einer sollte eher auf die rechte Seite geneigt sein 
und einer eher auf die linke. So soll unser Auto dann entscheiden können, wo weniger Hindernisse im Weg stehen. 

Zuerst einmal etwas Einfaches: wenn bei einem der beiden Ultraschallsensoren ein Hindernis gemessen wird, das weniger als 10 cm entfernt ist, 
soll das Auto stehen bleiben. 

Nun brauchen wir dafür zwei neue Funktionen, get_distance_left und get_distance_right. Beide senden ein Signal und fangen die Antwort auf. Je 
nachdem wie lange die Antwort gebraucht hat haben wir die Entfernung. 
