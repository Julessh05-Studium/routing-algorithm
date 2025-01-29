# Exposé

> Gruppe: Julian Schumacher und Gregor Gottschewski
> Gruppennummer: 8

## Aufgabenstellung

Es soll ein Commandline-Routenplanungstool in C mit erweiterten Funktionalitäten umgesetzt werden. Als Algorithmus soll der Dijkstra- oder der optimierte A*-Algorithmus verwendet werden. Dieser berechnet den kürzesten Pfad von einem Start- (über Wegpunkte) zu einem Zielpunkt. 

## Funktionalitäten
- Wegpunkte können aus einer Datei gelesen werden
- Der schnellste Pfad soll nach der Berechnung dem Nutzer zur Verfügung gestellt werden (mögliche Ausgabe: `(Start) Stuttgart->München->Nürnberg->Erfurt (Ende)`)
- Ein Debug-Mode soll zur Verfügung stehen, der die einzelnen Berechnungsschritte in der Konsole anzeigt
  - Dieser Output soll auch in einer Datei gespeichert werden können
 
### Optionale Funktionalitäten
- Hinderniserkennung (z.B. gesperrte Straßen oder Wegpunkte)
- Berechnung des benötigten Kraftstoffs (basierend auf einem durchschnittlichen PKW)
