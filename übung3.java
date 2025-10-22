import java.awt.Container;
 import java.util.Scanner;

public class übung3 {
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);
        System.out.println("Bitte Menge angeben:");
        int menge = Integer.parseInt(input.nextLine());

    
        float preisbis5 = 0.60f;
        float preisbis10 = 0.50f;
        float preisAb11 = 0.30f;

        float gesamtpreis = 0.0f;

        if (menge <= 5) {
            gesamtpreis = menge * preisbis5;
        } else if (menge <= 15) {
            gesamtpreis = (5 * preisbis5) + ((menge - 5) * preisbis10);
        } else {
            gesamtpreis = (5 * preisbis5) + (10 * preisbis10) + ((menge - 15) * preisAb11);
        }

        System.out.println("Gesamtpreis für " + menge + " Brötchen: " + gesamtpreis + " Euro");

        input.close(); // Scanner schließen



            /*
         * vergleichsoperatoren:
         *  - kleiner als: <
         *  - kleiner gleich: <=
         *  - gleich: ==
         *  - größer gleich: >=
         *  - größer als: >
         *  - ungleich: !=
         */

        //verweigeung
        //if <Bedingung>{
        //   <Anweisung>
        //}
    }
}




 