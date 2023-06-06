Dieser Ordner enthält die Grundgerüste für die Implementierung eines SPL-Compilers als Klausurzulassung im Rahmen des Bachelormoduls Compilerbau (CS1019).
Es stehen Grundgerüste für die Sprachen C und Java zur Verfügung. Die jeweiligen Ordner enthalten ein weiteres README, das zusätzliche essentielle Informationen enthält.


1. Auswahl der Sprache

Entscheiden Sie sich für die Sprache, mit der Sie Ihren SPL-Compiler implementieren möchten. 
Zur Auswahl stehen Java und C. Schauen Sie sich gerne vor Ihrer Entscheidung die zur Verfügung stehenden Quellen und die sprachspezifischen READMEs genauer an.
In beiden Sprachen ist der zu erwartende Aufwand ähnlich. Beide Sprachen haben Aspekte, die die Implementierung des SPL-Compilers an bestimmten Stellen
leichter oder schwerer machen. Entscheiden Sie sich also für die Sprache, mit der Sie sich wohler fühlen.

Den Ordner für die Sprache, die Sie nicht benutzen werden, können Sie löschen.


2. Systemvoraussetzungen

Genaueres zu den Systemvorausetzungen können Sie in der README Ihrer gewählten Sprache erfahren.
Unabhängig von der gewählten Sprache brauchen Sie für die Nutzung der eco32tools und zur Abgabe Ihrer Lösung eine Linux-Installation.
Unter macOS sollten die benötigten Programme ebenfalls funktionieren.

Für die Windowsnutzer unter Ihnen:
Unter Windows 10 können Sie das sogenannte 'Windows Subsystem for Linux' (WSL) nutzen.
Dies ist eine vollwertige Linuxinstallation, die innerhalb von Windows läuft. Sie brauchen also keine Virtuelle Maschine und auch kein Dualboot-Setup.
So haben Sie Zugriff auf alle Linuxprogramme, die Sie sonst unter Windows garnicht, oder nur kompliziert, zum Laufen bekommen.
Dazu zählen zum Beispiel Tools wie ssh, curl, tar, Shellskripts, und alles sonstige.

Die WSL ist für Windowsnutzer in vielen Fällen eine gute (und performantere) Alternative zu einer vollen virtuellen Maschine.
Eine offizielle Anleitung von Microsoft zur Installation von WSL finden Sie hier: https://docs.microsoft.com/en-us/windows/wsl/install-win10


3. Die ECO32-Tools

Die Zielplattform Ihres SPL-Compilers ist der Eco32-Prozessor. Ihr Compiler generiert also Eco32-Assemblercode.
Um Ihren generierten Code anschließend auszuführen, müssen Sie Ihren Code anschließend mit der Eco32-Toolchain zu einer ausführbaren Datei umwandeln.
Die zugehörigen Tools können Sie als separates Archiv im Moodlekurs herunterladen. Mehr zu den Tools erfahren Sie in der Vorlesung, im Praktikum, oder in der dort enthaltenen README.

Die zur Verfügung gestellte Version des Eco32 Simulators (in einer separaten ".tgz"-Datei)  unterstützt derzeit aufgrund von Kompatibilitätsproblemen keine grafischen Funktionen.
Dementsprechend sind auch die grafischen Prozeduren in SPL derzeit nicht benutzbar.


4. Das Abgabeprozedere

Ihr SPL-Compiler wird in zwei Etappen (Hausübungen) abgegeben. Um Hausübung 2 abgeben zu können, müssen Sie zwingend Hausübung 1 bestanden haben.
Die Auswertung der Hausübungen erfolgt automatisiert. Dafür wird Ihr SPL-Compiler als 'tar.gz'-Archiv hochgeladen. Dieses Archiv muss strenge formale Voraussetzungen erfüllen.
Glücklicherweise müssen Sie dieses Archiv nicht von Hand erstellen. Mit diesem Skeleton wird ein Pythonskript geliefert, das Sie durch den Prozess führt.
Näheres zur Bedienung der Abgabe finden Sie in der beiliegenden 'README(Submit).txt'.

Wichtig: Bitte beachten Sie, dass der Abgabeserver nur aus dem THM-Netz heraus erreichbar ist. Sie benötigen von außerhalb der THM also eine VPN-Verbindung (https://www.thm.de/its/services/netzdienste/vpn.html).
