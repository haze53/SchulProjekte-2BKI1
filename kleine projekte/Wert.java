
import java.util.Scanner;

public class Wert {
    public static void main(String[] args) {

        double preis = 5.50;

        Scanner input = new Scanner(System.in);
        System.out.println("Bitte geben Sie ihre bestell menge ein:");
        int menge = (int) input.nextDouble();
        if (menge > 200) {
            System.out.println("Sie erhalten die Ware kostenlos.");
        } else {
            double gesamtpreis = preis * menge;
            System.out.println("Der Gesamtpreis für " + menge + " Artikel beträgt: " + gesamtpreis + " Euro.");
            System.out.println("Sie haben " + menge + " Artikel bestellt.");
        }



        }
}

