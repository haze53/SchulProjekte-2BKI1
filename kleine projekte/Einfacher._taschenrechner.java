 Übung 2: Benutzereingabe und einfache Ausgabe
*import java.util.Scanner;

public class übung21 {
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);
        System.out.println("Bitte eine Zahl eingeben:");
        double zahl = input.nextDouble();
        System.out.println("Bitte einen Operator eingeben (+, -, *, /):");
        String operator = input.next();
        System.out.println("Bitte eine zweite Zahl eingeben:");
        double zahl2 = input.nextDouble();

        double ergebnis = 0;

        switch (operator) {
            case "+":
                ergebnis = zahl + zahl2;
                System.out.println("Das Ergebnis der Addition ist: " + ergebnis);
                break;
            case "-":
             ergebnis = zahl - zahl2;
                System.out.println("Das Ergebnis der Subtraktion ist: " + ergebnis);
                break;
            case "*":
             ergebnis = zahl * zahl2;
                System.out.println("Das Ergebnis der Multiplikation ist: " + ergebnis);
                break;
             case "/":
                ergebnis = zahl / zahl2;
                System.out.println("Das Ergebnis der Division ist: " + ergebnis);
                break;
            default:
                System.out.println("Ungültiger Operator. Bitte nur +, -, * verwenden");
                break;
        }

        input.close();
    }

}

*/
